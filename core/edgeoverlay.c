#include "edgeoverlay.h"
#include "platform.h"
#include "conf.h"
#include "keyboard.h"
#include "stdlib.h"
#include "gui_draw.h"

// until the edge thresh is put into conf structure I have hardcoded the threshold  see "thresh" below
static char * imgbuf = 0;
 

void edge_overlay(){

	//if(!(conf.edge_overlay_thresh) || !(conf.edge_overlay_enable)) return;

	static int inmem=0;
	static int viewport_height;
	static int viewport_width;// screenwidth * 3
	static int viewport_size;
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
	char * ptrh1;
	char * ptrh2;
	char * ptrv1;
	char * ptrv2;
	char * optr;


	img = vid_get_viewport_fb();
    viewport_height = vid_get_viewport_height();
	viewport_width = screen_width * 3;
    viewport_size = viewport_height * screen_width;
	if(imgbuf == 0) imgbuf = malloc(viewport_size * 3);
 
	if((mode_get()&MODE_MASK) != MODE_PLAY) {
		if (kbd_is_key_pressed(KEY_RIGHT)) {
			xoffset -=XINC;
		}
		if (kbd_is_key_pressed(KEY_LEFT)) {
			xoffset +=XINC;
		}
		if (kbd_is_key_pressed(KEY_DOWN)) {
			yoffset -=YINC;
		}
		if (kbd_is_key_pressed(KEY_UP)) {
			yoffset +=YINC;
		}
 
		if (kbd_is_key_pressed(KEY_SHOOT_HALF)||kbd_is_key_pressed(KEY_SHOOT_FULL)) {
			if (kbd_is_key_pressed(KEY_SHOOT_FULL) && !full_press) {
				shotTaken = 1 - shotTaken;
				memcpy(imgbuf,img,viewport_size * 3);
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
			memcpy(imgbuf,img,viewport_size * 3);
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
				//thresh = (conf.edge_overlay_thresh - 1) * 12;
				for (y=MARGIN; y<screen_height-MARGIN; y++) {
					y1 = y + yoffset;
					if((y1 < CALCYMARGIN) || (y1 >= screen_height - CALCYMARGIN)) {
						for (x=MARGIN; x < screen_width - MARGIN; x+=2) {
							draw_pixel(x, y, 0);
							draw_pixel(x+1, y, 0);
						}
					}
					else {
						for (x=MARGIN; x < screen_width - MARGIN; x+=2) {
							x1 = x + xoffset;
							if((x1 < 12) || (x1 >= screen_width-13)) {
								draw_pixel(x, y, 0);
								draw_pixel(x+1, y, 0);
							}
							else {
								c = 0;
								if(imgbuf[y1 * viewport_width + x1 * 3 + 3]  > thresh)
									c = conf.edge_overlay_color;
								draw_pixel(x, y, c);
								c = 0;
								if(imgbuf[y1 * viewport_width + x1 * 3 + 5]  > thresh)
									c = conf.edge_overlay_color;
								draw_pixel(x+1, y, c);
							}
						}
				}
				for (y2=MARGIN; y2<screen_height-MARGIN; y2++) {
					draw_pixel(XGRID1,y2,0xff);
					draw_pixel(XGRID2,y2,0xff);
					if(y2 == YGRID1) for (x=MARGIN; x < screen_width - MARGIN; x++) draw_pixel(x,y2,0xff);
					if(y2 == YGRID2) for (x=MARGIN; x < screen_width - MARGIN; x++) draw_pixel(x,y2,0xff);
				}
				if(shotTaken) draw_string(30, 10, strbuf, conf.osd_color);
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
 

/*// Code to test the idea of an edge overlay
// Put  		edge_overlay(); 		after the line histogram_process(); 
 
 
// Put the following after  the line #include "motion_detector.h" in main.c
#include "gui_draw.h"
 
// until the edge thresh is put into conf structure I have hardcoded the threshold  see "thresh" below
static char * imgbuf = 0;
 
#define MARGIN 30
#define CALCYMARGIN 3
#define EDGECOLOR 0x66
#define NSTAGES 4
#define XINC 6
#define YINC 2
#define XGRID1 120
#define XGRID2 240
#define YGRID1 80
#define YGRID2 160
 
void edge_overlay(){
	static int inmem=0;
	static int viewport_height;
	static int viewport_width;// screenwidth * 3
	static int viewport_size;
	static int shotTaken = 0;
	static int imgmem = 0;
	static int ymin = 0;
	static  int thresh = 40;
	static int xoffset = 0;
	static int yoffset = 0;
	static int full_press = 0;//cure for flaky behavior. due to multiple  returns to the scrip during one full press
	static char strbuf[7] = "Frozen";
 	static unsigned char *img;
	int i, hi, c;
	int x, y, h, v, ymax, y1, x1, y2;
	char * ptrh1;
	char * ptrh2;
	char * ptrv1;
	char * ptrv2;
	char * optr;
 
//	if(!conf.edge_thresh) return;
 
	img = vid_get_viewport_fb();
    viewport_height = vid_get_viewport_height();
	viewport_width = screen_width * 3;
    viewport_size = viewport_height * screen_width;
	if(imgbuf == 0) imgbuf = malloc(viewport_size * 3);
 
	if((mode_get()&MODE_MASK) != MODE_PLAY) {
		if (kbd_is_key_pressed(KEY_RIGHT)) {
			xoffset -=XINC;
		}
		if (kbd_is_key_pressed(KEY_LEFT)) {
			xoffset +=XINC;
		}
		if (kbd_is_key_pressed(KEY_DOWN)) {
			yoffset -=YINC;
		}
		if (kbd_is_key_pressed(KEY_UP)) {
			yoffset +=YINC;
		}
 
		if (kbd_is_key_pressed(KEY_SHOOT_HALF)||kbd_is_key_pressed(KEY_SHOOT_FULL)) {
			if (kbd_is_key_pressed(KEY_SHOOT_FULL) && !full_press) {
				shotTaken = 1 - shotTaken;
				memcpy(imgbuf,img,viewport_size * 3);
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
			memcpy(imgbuf,img,viewport_size * 3);
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
//				thresh = (conf.edge_thresh - 1) * 12;
				for (y=MARGIN; y<screen_height-MARGIN; y++) {
					y1 = y + yoffset;
					if((y1 < CALCYMARGIN) || (y1 >= screen_height - CALCYMARGIN)) {
						for (x=MARGIN; x < screen_width - MARGIN; x+=2) {
							draw_pixel(x, y, 0);
							draw_pixel(x+1, y, 0);
						}
					}
					else {
						for (x=MARGIN; x < screen_width - MARGIN; x+=2) {
							x1 = x + xoffset;
							if((x1 < 12) || (x1 >= screen_width-13)) {
								draw_pixel(x, y, 0);
								draw_pixel(x+1, y, 0);
							}
							else {
								c = 0;
								if(imgbuf[y1 * viewport_width + x1 * 3 + 3]  > thresh)
									c = EDGECOLOR;
								draw_pixel(x, y, c);
								c = 0;
								if(imgbuf[y1 * viewport_width + x1 * 3 + 5]  > thresh)
									c = EDGECOLOR;
								draw_pixel(x+1, y, c);
							}
						}
				}
				for (y2=MARGIN; y2<screen_height-MARGIN; y2++) {
					draw_pixel(XGRID1,y2,0xff);
					draw_pixel(XGRID2,y2,0xff);
					if(y2 == YGRID1) for (x=MARGIN; x < screen_width - MARGIN; x++) draw_pixel(x,y2,0xff);
					if(y2 == YGRID2) for (x=MARGIN; x < screen_width - MARGIN; x++) draw_pixel(x,y2,0xff);
				}
				if(shotTaken) draw_string(30, 10, strbuf, conf.osd_color);
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
 
//End of edge detector code.  next put  		edge_overlay(); 		after the line histogram_process(); 
*/
