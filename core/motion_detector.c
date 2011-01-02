
/*

Motion detection module


Author: mx3 (Max Sagaydachny) . win1251 ( Максим Сагайдачный )
Email: win.drivers@gmail.com
Skype: max_dtc
ICQ#: 125-985-663
Country: Ukraine
Sity: Kharkiv


20070912 mx3: first version

20070918 mx3: speed optimization, 



*/


void dump_memory();

#ifdef OPT_MD_DEBUG
#define MD_REC_CALLS_CNT 2048
#define MD_INFO_BUF_SIZE 4096
#endif

#include "motion_detector.h"
#include "action_stack.h"
#include "console.h"

#include "gui.h"
#include "gui_draw.h"


#define MD_XY2IDX(x,y) ((y)*motion_detector->columns+x)

void md_kbd_sched_immediate_shoot(int no_release);


enum {

	MD_MEASURE_MODE_U=0,
	MD_MEASURE_MODE_Y=1,
	MD_MEASURE_MODE_V=2,
	MD_MEASURE_MODE_R=3,
	MD_MEASURE_MODE_G=4,
	MD_MEASURE_MODE_B=5
};

enum {
    MD_DO_IMMEDIATE_SHOOT=1,
    MD_MAKE_DEBUG_LOG_FILE=2,
    MD_MAKE_RAM_DUMP_FILE=4,
    MD_NO_SHUTTER_RELEASE_ON_SHOOT=8
};

enum {
	MD_REGION_NONE=0,
	MD_REGION_INCLUDE=1,
	MD_REGION_EXCLUDE=2
};





//#define MD_XY2IDX(x,y) ((y)*motion_detector->columns+x)


struct motion_detector_s {
	int *curr; // points to buff1 or buff2
	int *prev; // points to buff2 or buff1
	int buff1[MOTION_DETECTOR_CELLS];
	int buff2[MOTION_DETECTOR_CELLS];
	int points[MOTION_DETECTOR_CELLS];

	int columns;
	int rows;
	int threshold;
	int pixel_measure_mode;
	int timeout;
	int measure_interval;

	int last_measure_time;
	int start_time;

	int running;
	int detected_cells;

	int draw_grid;
	int clipping_region_mode;
	int clipping_region_row1;
	int clipping_region_column1;
	int clipping_region_row2;
	int clipping_region_column2;

	int previous_picture_is_ready;

	int return_value;
	int parameters;
	int pixels_step;
	int msecs_before_trigger;

// debug
#ifdef OPT_MD_DEBUG
	int comp_calls_cnt;
	int comp_calls[MD_REC_CALLS_CNT];
#endif
};

static struct motion_detector_s *motion_detector=NULL;


//motion_detector->curr=NULL;



static int clip(int v) {
    if (v<0) v=0;
    if (v>255) v=255;
    return v;
}


// TODO add script interface, currently done when script ends
void md_close_motion_detector()
{
	free(motion_detector);
	motion_detector=NULL;
}


int md_init_motion_detector(
 int columns,
 int rows,
 int pixel_measure_mode,
 int detection_timeout,
 int measure_interval,
 int threshold,
 int draw_grid,
 int clipping_region_mode,
 int clipping_region_column1,
 int clipping_region_row1,
 int clipping_region_column2,
 int clipping_region_row2,
 int parameters,
 int pixels_step,
 int msecs_before_trigger
){

	if(!motion_detector) {
		motion_detector=malloc(sizeof(struct motion_detector_s));
		if(!motion_detector)
			return 0; // TODO make sure callers handle this
	}
#ifdef OPT_MD_DEBUG
	motion_detector->comp_calls_cnt=0;
#endif
	motion_detector->previous_picture_is_ready=0;
	motion_detector->curr=motion_detector->buff1;
	motion_detector->prev=motion_detector->buff2;

	if(		pixel_measure_mode != MD_MEASURE_MODE_Y 
		&&	pixel_measure_mode != MD_MEASURE_MODE_U
		&&	pixel_measure_mode != MD_MEASURE_MODE_V
		&&	pixel_measure_mode != MD_MEASURE_MODE_R
		&&	pixel_measure_mode != MD_MEASURE_MODE_G
		&&	pixel_measure_mode != MD_MEASURE_MODE_B
		){
		pixel_measure_mode = MD_MEASURE_MODE_Y;
	}


	if( columns<1 || rows<1 || columns * rows > MOTION_DETECTOR_CELLS ){
		columns=3;
		rows=3;
	}

	if(msecs_before_trigger<0){
		msecs_before_trigger=0;
	}

	if (pixels_step<1){
		pixels_step=1;
	}

	if(detection_timeout<0){
		detection_timeout=0;
	}

	if(measure_interval<0) {
		measure_interval=0;
	}

	if(threshold<0) {
		threshold=0;
	}


	motion_detector->msecs_before_trigger=msecs_before_trigger;
	motion_detector->parameters = parameters;
	motion_detector->pixels_step=pixels_step;
	motion_detector->columns=columns;
	motion_detector->rows=rows;
	motion_detector->return_value=0;
	

	motion_detector->pixel_measure_mode=pixel_measure_mode;
	motion_detector->timeout=detection_timeout;
	motion_detector->measure_interval=measure_interval;
	motion_detector->threshold=threshold;
	motion_detector->draw_grid=draw_grid;


	if (clipping_region_column1>clipping_region_column2){
		motion_detector->clipping_region_column2=clipping_region_column1;
		motion_detector->clipping_region_column1=clipping_region_column2;
	} else {
		motion_detector->clipping_region_column2=clipping_region_column2;
		motion_detector->clipping_region_column1=clipping_region_column1;
	}

	if (clipping_region_row1>clipping_region_row2){
		motion_detector->clipping_region_row2=clipping_region_row1;
		motion_detector->clipping_region_row1=clipping_region_row2;
	} else {
		motion_detector->clipping_region_row2=clipping_region_row2;
		motion_detector->clipping_region_row1=clipping_region_row1;
	}

	if (clipping_region_mode!=MD_REGION_NONE && clipping_region_mode!=MD_REGION_INCLUDE && clipping_region_mode!=MD_REGION_EXCLUDE){
		clipping_region_mode=MD_REGION_NONE;
	}
	motion_detector->clipping_region_mode=clipping_region_mode;

	motion_detector->detected_cells=0;
	motion_detector->previous_picture_is_ready=0;
	motion_detector->start_time=get_tick_count();

	motion_detector->last_measure_time = motion_detector->start_time - motion_detector->measure_interval;

	motion_detector->running=1;

	action_push(AS_MOTION_DETECTOR);
	draw_clear();

	return 1;
}

#ifdef OPT_MD_DEBUG
void md_save_calls_history(){
	char buf[200], fn[30];
	char big[MD_INFO_BUF_SIZE];
	int big_ln;
	int calls,i, ln, fd;
  static struct utimbuf t;
    unsigned long t2;
    static struct tm *ttm;


	if( (motion_detector->parameters & MD_MAKE_DEBUG_LOG_FILE) == 0 ){
		return;
	}
	

	strcpy(fn,"A/MD_INFO.TXT");//,BUILD_NUMBER,motion_detector->pixels_step);
	fd = open(fn, O_WRONLY|O_CREAT, 0777);
	if( fd>=0) {
		console_add_line("Writing info file...");
		lseek(fd,0,SEEK_END);
    t2 = time(NULL);
    ttm = localtime(&t2);
    big_ln=sprintf(big, 
				"\r\n--- %04u-%02u-%02u  %02u:%02u:%02u\r\n"
				"CHDK Ver: %s [ #%s ]\r\nBuild Date: %s %s\r\nCamera:  %s [ %s ]\r\n"
				"[%dx%d], threshold: %d, interval: %d, pixels step: %d\r\n"
				"region: [%d,%d-%d,%d], region type: %d\r\n"
				"wait interval: %d, parameters: %d, calls: %d, detected cells: %d\r\n", 
				1900+ttm->tm_year, ttm->tm_mon+1, ttm->tm_mday, ttm->tm_hour, ttm->tm_min, ttm->tm_sec,
				HDK_VERSION, BUILD_NUMBER, __DATE__, __TIME__, PLATFORM, PLATFORMSUB,
				motion_detector->columns, motion_detector->rows, motion_detector->threshold, motion_detector->measure_interval, motion_detector->pixels_step,
				motion_detector->clipping_region_column1, motion_detector->clipping_region_row1, motion_detector->clipping_region_column2, motion_detector->clipping_region_row2, motion_detector->clipping_region_mode,
				motion_detector->msecs_before_trigger, motion_detector->parameters, motion_detector->comp_calls_cnt,
				motion_detector->detected_cells
		);

		calls = ( motion_detector->comp_calls_cnt < MD_REC_CALLS_CNT) ?motion_detector->comp_calls_cnt: MD_REC_CALLS_CNT;

		for(i=0;i<calls;i++){
			ln=sprintf(buf,"[%d] - %d\r\n",i,motion_detector->comp_calls[i]);
			if(big_ln+ln>MD_INFO_BUF_SIZE){
	      write(fd,big,big_ln);
				big_ln=0;
			} 
			memcpy(big+big_ln,buf,ln+1);
			big_ln+=ln;
		}
    write(fd,big,big_ln);
		close(fd);
	  t.actime = t.modtime = time(NULL);
    utime(fn, &t);
	}
}

static void mx_dump_memory(void *img){
	char fn[36];
	int fd, i;
	static int cnt=0;

    started();
    mkdir("A/MD");

		do {
			cnt++;
			sprintf(fn, "A/MD/%04d.FB", cnt);
			fd = open(fn, O_RDONLY, 0777);

			if(fd>=0){
				close(fd);
			}
		} while(fd>=0);


		sprintf(fn, "A/MD/%04d.FB", cnt );
		fd = open(fn, O_WRONLY|O_CREAT, 0777);
		if (fd) {
	    write(fd, img, screen_width*vid_get_viewport_height()*3);
	    close(fd);
		}
  vid_bitmap_refresh();
  finished();

}
#else
#define md_save_calls_history()
#define mx_dump_memory(x)
#endif


int md_detect_motion(void){
	int *tmp;
	unsigned char * img;
	int viewport_size;
	int img_offset;		// used as offset into img buffer when image size != viewport size (e.g. 16:9 image on 4:3 LCD)
	int vp_w, vp_h, pix_N, idx, tmp2, tick, vp_w_mul_y, in_clipping_region, x_step, y_step, do_calc;
	int val;

	register int i, col, row, x, y;

//	static char buf[128];
	double vp_hr, vp_wr;



	if(!md_running()){ 
		return 0;
	}

	tick=get_tick_count();
#ifdef OPT_MD_DEBUG
	if(motion_detector->comp_calls_cnt < MD_REC_CALLS_CNT) {
		motion_detector->comp_calls[motion_detector->comp_calls_cnt]=tick;
	}
	motion_detector->comp_calls_cnt++;
#endif

	if(motion_detector->start_time + motion_detector->timeout < tick ) {
		md_save_calls_history();
		motion_detector->running = 0;
		return 0;
	}

	if(motion_detector->last_measure_time + motion_detector->measure_interval > tick){
		// wait for the next time
		return 1;
	}

	motion_detector->last_measure_time=tick;

// swap pointers so we don't need to copy last data array into Previous one
	tmp=motion_detector->curr;
	motion_detector->curr=motion_detector->prev;
	motion_detector->prev=tmp;

//	memset(motion_detector->points,0, sizeof(motion_detector->points));
// WARNING. maybe not optimized
	for(i=0 ; i<motion_detector->rows*motion_detector->columns ; i++ ){
		motion_detector->points[i]=0;
		motion_detector->curr[i]=0;
	}


	// >> fill "curr" array
 

//  if (strcmp(PLATFORM,"a610")==0 || strcmp(PLATFORM,"a710")==0) {
	 img = vid_get_viewport_live_fb();
		if(img==NULL){
			img = vid_get_viewport_fb();
        }
/* the following is commented because of a bugreport: http://chdk.kernreaktor.org/mantis/view.php?id=70
#if defined (CAMERA_s5is)
long bufoff = *((long *) 0x218C);
if(bufoff == 0) {
    bufoff = 2;
} else {
    bufoff--;
}
img += bufoff * 0x7E900;
#endif
*/

#ifdef OPT_MD_DEBUG
	if(motion_detector->comp_calls_cnt==50 && (motion_detector->parameters & MD_MAKE_RAM_DUMP_FILE) != 0 ){
		mx_dump_memory((char*)img);
	}
#endif

	vp_h=vid_get_viewport_height();
	vp_w=vid_get_viewport_buffer_width();
	img_offset = (vid_get_viewport_yoffset() * vp_w + vid_get_viewport_xoffset()) * 3;

	x_step=vid_get_viewport_width()/motion_detector->columns;
	y_step=vp_h/motion_detector->rows;

	for(row=0, col=0; row < motion_detector->rows ; ){
		do_calc=0;
		in_clipping_region=0;

		if (
				 col+1 >= motion_detector->clipping_region_column1 
			&& col+1 <= motion_detector->clipping_region_column2
			&& row+1 >= motion_detector->clipping_region_row1
			&& row+1 <= motion_detector->clipping_region_row2
			){
				in_clipping_region=1;
		}

		if(motion_detector->clipping_region_mode==MD_REGION_EXCLUDE && in_clipping_region==0){
			do_calc=1;
		} 

		if(motion_detector->clipping_region_mode==MD_REGION_INCLUDE && in_clipping_region==1){
			do_calc=1;
		}

		if(motion_detector->clipping_region_mode==MD_REGION_NONE){
			do_calc=1;
		}

		if(do_calc==1){
		  idx=MD_XY2IDX(col,row);
			for(x=col*x_step;x<(col+1)*x_step;x+=motion_detector->pixels_step){
				for(y=row*y_step;y<(row+1)*y_step;y+=motion_detector->pixels_step){
					int cy,cv,cu;

					cy=img[img_offset + (y*vp_w+x)*3 + 1];

// ARRAY of UYVYYY values
// 6 bytes - 4 pixels

					if((x%2)==0){
						cu=img[img_offset + (y*vp_w+x)*3];
						cv=img[img_offset + (y*vp_w+x)*3 + 2];
					} else {
						cu=img[img_offset + (y*vp_w+x-1)*3];
						cv=img[img_offset + (y*vp_w+x-1)*3 + 2];
					}

					switch(motion_detector->pixel_measure_mode){
						MD_MEASURE_MODE_Y:
							val=cy;
							break;
						MD_MEASURE_MODE_U:
							val=cu;
							break;
						MD_MEASURE_MODE_V:
								val = cv;
							break;

						MD_MEASURE_MODE_R:
                val = clip(((cy<<12)           + cv*5743 + 2048)/4096); // R
							break;

						MD_MEASURE_MODE_G:
                val = clip(((cy<<12) - cu*1411 - cv*2925 + 2048)/4096); // G
							break;

						MD_MEASURE_MODE_B:
                val = clip(((cy<<12) + cu*7258           + 2048)/4096); // B
							break;

						default:
								val=cy;
							break;
					}
					motion_detector->curr[ idx ]+=val;
					motion_detector->points[ idx ]++;
				}
			}
		}

		col++;
		if(col>=motion_detector->columns){
			col=0;
			row++;
		}
	}
	// << fill "curr" array


	if(motion_detector->previous_picture_is_ready==0){
		motion_detector->previous_picture_is_ready=1;
		motion_detector->start_time=get_tick_count();
		motion_detector->last_measure_time=motion_detector->start_time-motion_detector->measure_interval;
		return 1;
	}


	// >> compare arrays here

		for ( col=0, row=0; row < motion_detector->rows; ){
		  idx=MD_XY2IDX(col,row);
			tmp2=0;
			if(motion_detector->points[idx]>0){
				motion_detector->prev[idx] = (motion_detector->curr[idx]-motion_detector->prev[idx])/motion_detector->points[idx];
				tmp2 = ( motion_detector->prev[idx] < 0 ) ? -motion_detector->prev[idx] : motion_detector->prev[idx] ;
			}
	
			if( tmp2 > motion_detector->threshold ){
				if (motion_detector->start_time+motion_detector->msecs_before_trigger < tick){
					motion_detector->detected_cells++;
				}
			}

			col++;
			if(col>=motion_detector->columns){
				col=0;
				row++;
			}
		}
		
	// << compare arrays here


	if( motion_detector->detected_cells > 0 ){
//		sprintf(buf,"-cells: %d", motion_detector->detected_cells);
//		script_console_add_line(buf);

		if (motion_detector->start_time+motion_detector->msecs_before_trigger < tick){
			motion_detector->running=0;
            motion_detector->return_value = motion_detector->detected_cells;
            
//			md_save_calls_history();
			if( ( motion_detector->parameters&MD_DO_IMMEDIATE_SHOOT ) !=0){
				//make shoot
				//kbd_sched_shoot();
				md_kbd_sched_immediate_shoot(motion_detector->parameters&MD_NO_SHUTTER_RELEASE_ON_SHOOT);
			}
			return 0;
		}
	}


	return 1;
}


int md_get_cell_diff(int column, int row){

	if(!motion_detector){
		return 0;
	}
	if (column<1 || column > motion_detector->columns){
		return 0;
	}

	if (row<1 || row > motion_detector->rows ){
		return 0;
	}
	

	return motion_detector->prev[ MD_XY2IDX(column-1,row-1) ];
}



int md_running(){
	return motion_detector?motion_detector->running:0;
}


void md_draw_grid(){
	int x_step, y_step, col, row;
	int xoffset, yoffset;
	int do_draw_rect, i, tmp2, in_clipping_region, color, col_start, col_stop, row_start, row_stop;

	if(!md_running() || motion_detector->draw_grid==0){
		return ;
	}

	xoffset = ASPECT_VIEWPORT_XCORRECTION(vid_get_viewport_xoffset());	// used when image size != viewport size
	yoffset = vid_get_viewport_yoffset();	// used when image size != viewport size

	x_step=(screen_width-xoffset*2)/motion_detector->columns;
	y_step=(screen_height-yoffset*2)/motion_detector->rows;
#if 0
	row_start=1;
	row_stop=motion_detector->rows;
	if(motion_detector->clipping_region_mode==2){
		row_start=motion_detector->clipping_region_row1;
		row_stop=motion_detector->clipping_region_row2+1;
		col_start=motion_detector->clipping_region_column1;
		col_stop=motion_detector->clipping_region_column2+1;
	}
	if(motion_detector->clipping_region_mode==0 || motion_detector->clipping_region_mode==2){
		for(col=col_start;col<col_stop;col++){
			draw_line(col*x_step,0,col*x_step,screen_height, COLOR_GREEN);
		}
		for(row=row_start;row<row_stop;row++){
			draw_line(0,row*y_step,screen_width,row*y_step, COLOR_GREEN);
		}
	} else if(motion_detector->clipping_region_mode==1){
		for(col=1;col<motion_detector->columns;col++){
			if(col<){
				draw_line(col*x_step,0,col*x_step,screen_height, COLOR_GREEN);
			}
		}
	}
#endif

	for ( col=0, row=0; row < motion_detector->rows; ){
		i=MD_XY2IDX(col,row);
		tmp2 = ( motion_detector->prev[i] < 0 ) ? -motion_detector->prev[i] : motion_detector->prev[i] ;

			in_clipping_region=0;
			if ( col+1>=motion_detector->clipping_region_column1 
				&& col+1<=motion_detector->clipping_region_column2
				&& row+1>=motion_detector->clipping_region_row1
				&& row+1<=motion_detector->clipping_region_row2
				){
					in_clipping_region=1;
			}

			do_draw_rect=0;

			if(motion_detector->clipping_region_mode==MD_REGION_EXCLUDE && in_clipping_region==0){
				do_draw_rect=1;
			}

			if(motion_detector->clipping_region_mode==MD_REGION_INCLUDE && in_clipping_region==1){
				do_draw_rect=1;
			}

			if(motion_detector->clipping_region_mode==MD_REGION_NONE){
				do_draw_rect=1;
			}

			if(do_draw_rect==1){
				color=COLOR_GREEN;
				if( tmp2 > motion_detector->threshold){
					color=COLOR_RED;
				}
				draw_rect(xoffset+x_step*col+2,yoffset+y_step*row+2, xoffset+x_step*(col+1)-2, yoffset+y_step*(row+1)-2,color);
			}

			col++;
			if( col >= motion_detector->columns ){
				row++;
				col=0;
			}
	}

}

int md_get_result()
{
    return motion_detector->return_value;
}
