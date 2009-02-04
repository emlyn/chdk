#include "edgeoverlay.h"
#include "platform.h"
#include "conf.h"
#include "keyboard.h"
#include "stdlib.h"
#include "gui_draw.h"

// This edge overlay code has major changes to the "old" one. One major change
// is, that it doesn cause my cam (ixus 950) to crash anymore by mistaking the
// boundaries of the viewport buffer it can read from and write pixels to.
// Unfortunately it still has the bug (that is also present in the original
// version) that when you move the overlay too much you again overwrite data.
// One might not necessarily notice it at once, or at all, but for me
// unfortunately it overwrote vital data for the chdk menu structure.
// 
// Also the old version was flickering for me and wasn't playing well with the
// chdk osd. I tried to change a bit about that, which makes it also a bit
// faster updating, at least on my cam.
//
// And then of course, this can load the viewport to a seperate file 

// the way we save edge overlays on their own...
#define EDGE_FILE_PREFIX "EDG_"
#define EDGE_FILE_FORMAT EDGE_FILE_PREFIX "%04d.edg"

static char * imgbuf = 0;
static char * imgbuf_end = 0;
static int inmem=0;
// whole viewport size in bytes ??
static int viewport_size = 0;
// width in bytes of one viewport line ??
static int viewport_width;// screenwidth * 3
// flag to remember if current buffer is already saved, so hitting save won't
// save it again
static int is_saved = 0;
// set this to 1 when things need to be moved, so that a redraw clears "old"
// pixels... Otherwise it just will write pixels that need edge overlay data.
// This sometimes leaves trails when the pixel alignment isn't nice but it is
// better than writing "transparent" to everwhere, essentially overwriting
// important things that will cause flickering.
static int need_redraw = 0;

// debug output that waits
void out_wait( const char* buf );

void get_viewport_size( ) {
	static int viewport_height;

	// since screen_height is used in the drawing downwards, we should use it
	// here too to calculate the buffer we need...
	viewport_height = screen_height;//vid_get_viewport_height();
	viewport_width = screen_width * 3;
	viewport_size = viewport_height * screen_width * 3;
}

void ensure_allocate_imagebuffer( ) { 
	if(imgbuf == 0)
	{
		imgbuf = malloc( viewport_size );
		imgbuf_end = imgbuf + (viewport_size);
	}
}

// scans a filename for the number of the edge detection file it contains
int get_edge_file_num( const char* fn )
{
	int num = 0;
	if( strncmp(fn,EDGE_FILE_PREFIX,sizeof(EDGE_FILE_PREFIX)-1) == 0 )
	{ // has the correct beginning at least, now try to read as a number...
		fn += sizeof(EDGE_FILE_PREFIX);
		while( *fn == '0' ) // skip leading 0s
		{
			++fn;
		}
		while( isdigit(*fn) )
		{
			num *= 10;
			num += *fn - '0';
			++fn;
		}
		// ignore anything else after it, that is like the ending etc.
	}
	return num;
}

// we eat up to 300k of memory, for people needing it we have a menu point
// where they can manually free it. makes of course only sense when the edge
// overlay is not active.
void free_memory_edge_overlay(void){
	char buf[64];
	free(imgbuf);
	imgbuf = 0;
	sprintf(buf,"Freed %u byte",viewport_size);
	draw_string(30, 10, buf, conf.osd_color);
	viewport_size = 0;
}

// saves the actual active overlay data to a file... Well, actually the
// viewport is saved...
void save_edge_overlay(void){

	char fn[64];
	char msg[64];
	FILE *fd;
	DIR* d;
	int fnum = 0;
	int fr = 0;
	int zoom = 0;
	struct dirent* de;
	static struct utimbuf t;
	// nothing to save? then dont save
	if( !imgbuf ) return;
	zoom = shooting_get_zoom();
	
	// first figure out the most appropriate filename to use
	d = opendir(EDGE_SAVE_DIR);
	if( ! d )
	{
		return;
	}

	while( (de = readdir(d)) )
	{
		fr = get_edge_file_num(de->d_name);
		if( fr > fnum )
		{
			fnum = fr;
		}
	}
	++fnum; // the highest is set, we use the next one
	get_viewport_size();
	// open the right file
	sprintf(fn, EDGE_SAVE_DIR "/" EDGE_FILE_FORMAT, fnum );
	fd = fopen(fn, "wb");
	if(fd !=NULL)
	{
		// write the data
		fwrite(imgbuf,viewport_size,1,fd);
		fwrite(&zoom,sizeof(zoom),1,fd);
		is_saved = 1;
		fclose(fd);
		t.actime = t.modtime = time(NULL);
		utime(fn, &t);
		sprintf(msg, "Saved as %s",fn);
		draw_string(30, 10, msg, conf.osd_color);
	}
	closedir(d);
}

// load the viewport copy thats being used for edge detection (and from that
// displaying) from a file
void load_edge_overlay( const char* fn ) {
	FILE *fd;
	int ret,ret2;
	int zoom;

	is_saved = 1; // won't want to save it again, its already there
	get_viewport_size();
	ensure_allocate_imagebuffer( );
	fd = fopen(fn,"rb");
	if( fd != NULL )
	{
		ret = fread(imgbuf,viewport_size,1,fd);
		ret2 = fread (&zoom,sizeof(zoom),1,fd);
		fclose(fd);
		if( (ret == 1) && (ret2 == 1) )
		{
			inmem = 1; // fake having loaded stuff
			if (conf.edge_overlay_zoom)	{
				shooting_set_zoom(zoom);
			}
		}
	}
}

// paint the edge overlay
void edge_overlay(){

	static int shotTaken = 0;
	static int imgmem = 0;
	static int ymin = 0;
	static int thresh;
	thresh = conf.edge_overlay_thresh; //40
	static int xoffset = 0;
	static int yoffset = 0;
	static int full_press = 0;//cure for flaky behavior. due to multiple  returns to the scrip during one full press
	static char strbuf[7] = "Frozen";
	static unsigned char *img;
	int i, hi, c;
	int x, y, h, v, ymax, y1, x1, y2;
	const char * ptrh1;
	const char * ptrh2;
	const char * ptrv1;
	const char * ptrv2;
	char xbuf[64];
	char * optr;

	is_saved = 0; // a new one, we could potentially save it
	if((mode_get()&MODE_MASK) != MODE_PLAY)
	{
		img = vid_get_viewport_fb();
	}
	else
	{
		img = vid_get_viewport_fb_d();
	}
	get_viewport_size();
	ensure_allocate_imagebuffer( );
	if(imgbuf == 0) return; // ensure failed, make the best we can out of it

	if(conf.edge_overlay_play || ((mode_get()&MODE_MASK) != MODE_PLAY))  {
		// setup offsets for moving the edge overlay around. Always set
		// need_redraw so that we actually do a complete redraw, overwriting
		// also old pixels
		if (gui_get_mode()==GUI_MODE_ALT) {
				if (kbd_is_key_pressed(KEY_RIGHT)) {
					xoffset -=XINC;
					++need_redraw;
				}
				if (kbd_is_key_pressed(KEY_LEFT)) {
					xoffset +=XINC;
					++need_redraw;
				}
				if (kbd_is_key_pressed(KEY_DOWN)) {
					yoffset -=YINC;
					++need_redraw;
				}
				if (kbd_is_key_pressed(KEY_UP)) {
					yoffset +=YINC;
					++need_redraw;
				}
		}
		if ((kbd_is_key_pressed(KEY_SHOOT_HALF)||kbd_is_key_pressed(KEY_SHOOT_FULL)) && (conf.edge_overlay_lock!=1)) {
			if (kbd_is_key_pressed(KEY_SHOOT_FULL) && !full_press) {
				shotTaken = 1 - shotTaken;
				memcpy(imgbuf,img,viewport_size);
				ymin = CALCYMARGIN;
				inmem = 1;
				full_press = 1;
				xoffset = 0;
				yoffset = 0;
				return;
			}
			if(shotTaken) {
				return;
			}
			memcpy(imgbuf,img,viewport_size);
			ymin = CALCYMARGIN;
			inmem = 1;
			xoffset = 0;
			yoffset = 0;
			return;
		}
		else full_press = 0;



		if (inmem && (ymin < screen_height-CALCYMARGIN)) {
			ymax = ymin + (screen_height - 2 * CALCYMARGIN) / NSTAGES;
			if(ymax > screen_height - CALCYMARGIN) ymax = screen_height - CALCYMARGIN;
			for (y=ymin; y<ymax; y++) {
				ptrh1 = imgbuf + y * viewport_width + 7;
				ptrh2 = imgbuf + y * viewport_width - 5;
				ptrv1 = imgbuf + (y + 1) * viewport_width + 1;
				ptrv2 = imgbuf + (y - 1) * viewport_width + 1;
				optr = imgbuf + y * viewport_width + 3;
				for (x=12; x<(screen_width- 4) * 3; x+=6) {
					h = ptrh1[x] - ptrh2[x];
					if(h  < 0) h = -h;
					v = ptrv1[x] - ptrv2[x];
					if(v  < 0) v = -v;
					optr[x] = h + v;
					h = ptrh1[x + 3] - ptrh2[x + 3];
					if(h  < 0) h = -h;
					v = ptrv1[x + 3] - ptrv2[x + 3];
					if(v  < 0) v = -v;
					optr[x + 2] = h + v;
				}
			}
			ymin += (screen_height - 2 * CALCYMARGIN) / NSTAGES;
			return;
		}

		if(inmem &&(ymin >= screen_height-CALCYMARGIN) && 
			((gui_get_mode() == GUI_MODE_NONE) || (gui_get_mode() == GUI_MODE_ALT))){

				for (y=MARGIN; y<screen_height-MARGIN; y++) {
					y1 = y + yoffset;
					if((y1 < CALCYMARGIN) || (y1 >= screen_height - CALCYMARGIN)) {
						/*
						for (x=MARGIN; x < screen_width - MARGIN; x+=2) {
							draw_pixel(x, y, 0);
							draw_pixel(x+1, y, 0);
						}
						*/
					}
					else {
						for (x=MARGIN; x < screen_width - MARGIN; x+=2) {
							x1 = x + xoffset;
							// leave a margin normally, only write to it when a
							// full redraw is requested
							if((x1 < 12) || (x1 >= screen_width-13)) {
								if( need_redraw )
								{
									draw_pixel(x, y, 0);
									draw_pixel(x+1, y, 0);
								}
							}
							else {
								// draw a pixel if the threshold is reached. If
								// not, draw it transparent only if we want a
								// complete redraw to overwrite spurious pixels
								// or if the color of the existing pixel is the
								// same as the overlay color
								if(imgbuf[y1 * viewport_width + x1 * 3 + 3]  > thresh)
								{
									draw_pixel(x, y, conf.edge_overlay_color );
								}
								else if( need_redraw || (draw_get_pixel(x,y) == conf.edge_overlay_color) )
								{
									draw_pixel(x, y, 0);
								}

								if(imgbuf[y1 * viewport_width + x1 * 3 + 5]  > thresh)
								{
									draw_pixel(x+1, y, conf.edge_overlay_color );
								}
								else if( need_redraw || (draw_get_pixel(x,y) == conf.edge_overlay_color) )
								{
									draw_pixel(x+1, y, 0);
								}
							}
						}
				}
				// disabled drawing the grid, the new way of drawing the
				// overlay should leave the standard grid intact, allowing the
				// custom grid to remain intact too.
				if(shotTaken) draw_string(30, 10, strbuf, conf.osd_color);
			}
			// If a complete redraw was requested, decrement the request. That
			// way we do it as much as it was requested, also in one run. Will
			// cause some flickering, but better than nothing.
			if( need_redraw )
			{
				--need_redraw;
			}
			return;
		}
	}
	else {
		full_press = 0;
		inmem = 0;
		shotTaken = 0;
		ymin = 0;
		xoffset = 0;
		yoffset = 0;
	}
	return;
}

// there used to be some commented out version here. it was confusing, so I
// removed it. Its still in the svn anyways.
 
// vim: tabstop=4 shiftwidth=4
