#include "stdlib.h"
#include "platform.h"
#include "core.h"
#include "keyboard.h"
#include "conf.h"
#include "math.h"
#include "gui.h"
#include "gui_draw.h"
#include "histogram.h"

#define HISTOGRAM_IDLE_STAGE (6)


static float identity(float x);
static float logarithmic(float x);


unsigned char histogram[5][HISTO_WIDTH];                    // RGBYG
long exposition_thresh;
long under_exposed;
long over_exposed;
long histo_magnification;

static unsigned int histogram_proc[5][HISTO_WIDTH];         // RGBYG
static float histo_max_invw[5], histo_max_center_invw[5];   // RGBYG
static long histogram_stage=0;
static unsigned int histo_max[5], histo_max_center[5];      // RGBYG
static float (*histogram_transform)(float) = identity;
static int histo_main = HISTO_RGB;


float identity(float x)
{
    return x;
}

float logarithmic(float x) {
    return log(x);
}

void histogram_set_mode(unsigned int mode) {
    switch (mode) {
        case HISTO_MODE_LOG: 
            histogram_transform = logarithmic; 
            break;
        case HISTO_MODE_LINEAR: 
        default:
            histogram_transform = identity; 
            break;
    }
}

void histogram_set_main(unsigned int main) {
    histo_main = main;
}

static int clip(int v) {
    if (v<0) v=0;
    if (v>255) v=255;
    return v;
}

void histogram_process()
{
    static unsigned char *img;
    int i, hi, c;
    int y, v, u;
	static int x, img_offset;
    static int viewport_size;
    unsigned int histo_fill[5];

	    switch (histogram_stage) {
        case 0:
            img=((mode_get()&MODE_MASK) == MODE_PLAY)?vid_get_viewport_fb_d():((kbd_is_key_pressed(KEY_SHOOT_HALF))?vid_get_viewport_fb():vid_get_viewport_live_fb());
      	
        	if (img==NULL){
	    	  img = vid_get_viewport_fb();
		    }
			img_offset = vid_get_viewport_image_offset();		// offset into viewport for when image size != viewport size (e.g. 16:9 image on 4:3 LCD)
            viewport_size = vid_get_viewport_height() * vid_get_viewport_buffer_width();
            for (c=0; c<5; ++c) {
                for (i=0; i<HISTO_WIDTH; ++i) {
                    histogram_proc[c][i]=0;
                }
                histo_max[c] = histo_max_center[c] = 0;
            }

            histogram_stage=1;
            break;
        
        case 1:
        case 2:
        case 3:
			x = 0;
            for (i=(histogram_stage-1)*6; i<viewport_size*3; i+=6*3*2) {
                y = img[img_offset+i+1];
                u = *(signed char*)(&img[img_offset+i]);
                if (u&0x00000080) u|=0xFFFFFF00;
                v = *(signed char*)(&img[img_offset+i+2]);
                if (v&0x00000080) v|=0xFFFFFF00;

                hi = y*HISTO_WIDTH/256; // Y
                ++histogram_proc[HISTO_Y][hi];
                hi = clip(((y<<12)          + v*5743 + 2048)/4096)*HISTO_WIDTH/256; // R
                ++histogram_proc[HISTO_R][hi];
                hi = clip(((y<<12) - u*1411 - v*2925 + 2048)/4096)*HISTO_WIDTH/256; // G
                ++histogram_proc[HISTO_G][hi];
                hi = clip(((y<<12) + u*7258          + 2048)/4096)*HISTO_WIDTH/256; // B
                ++histogram_proc[HISTO_B][hi];

				// Handle case where viewport memory buffer is wider than the actual buffer.
				x++;
				if (x == vid_get_viewport_width())
				{
					i += vid_get_viewport_row_offset();
					x = 0;
				}
			}

            ++histogram_stage;
            break;

        case 4:
            for (i=0; i<HISTO_WIDTH; ++i) { // G
                histogram_proc[HISTO_RGB][i]=histogram_proc[HISTO_R][i]+histogram_proc[HISTO_G][i]+histogram_proc[HISTO_B][i];
            }
            for (c=0; c<5; ++c) { // calculate maximums
                for (i=0; i<HISTO_WIDTH; ++i) {
                    if (histo_max[c]<histogram_proc[c][i])
                        histo_max[c]=histogram_proc[c][i];
                    if (histo_max_center[c]<histogram_proc[c][i] && i>=conf.histo_ignore_boundary && i<HISTO_WIDTH-conf.histo_ignore_boundary)
                        histo_max_center[c]=histogram_proc[c][i];
                }
                
                if (histo_max[c] > 0) {
                    histo_max_invw[c] = ((float)HISTO_HEIGHT)/histogram_transform((float)histo_max[c]);
                } else {
                    histo_max_invw[c] = 0.0f;
                }

                if (histo_max_center[c] > 0) {
                    histo_max_center_invw[c] = ((float)HISTO_HEIGHT)/histogram_transform((float)histo_max_center[c]);
                } else {
                    histo_max_center_invw[c] = 0.0f;
                }
            }

            if (histo_max[HISTO_RGB] > 0) { // over- / under- expos
                under_exposed = (histogram_proc[HISTO_RGB][0]*8
                                +histogram_proc[HISTO_RGB][1]*4
                                +histogram_proc[HISTO_RGB][2]) > exposition_thresh;

                over_exposed = (histogram_proc[HISTO_RGB][HISTO_WIDTH-3]
                               +histogram_proc[HISTO_RGB][HISTO_WIDTH-2]*4
                               +histogram_proc[HISTO_RGB][HISTO_WIDTH-1]*8) > exposition_thresh;
            } else {
                over_exposed = 0;
                under_exposed = 1;
            }

            histogram_stage=5;
            state_expos_recalculated = 1;
            break;

        case 5:
            for (c=0; c<5; ++c) {
                histo_fill[c]=0;
                for (i=0; i<HISTO_WIDTH; ++i) {
                    histogram[c][i] = (histogram_transform((float)histogram_proc[c][i]))*histo_max_center_invw[c];
                    if (histogram[c][i] > HISTO_HEIGHT)
                        histogram[c][i] = HISTO_HEIGHT;
                    histo_fill[c]+=histogram[c][i];
                }
            }

            if (conf.histo_auto_ajust) {
                histo_magnification = histo_fill[histo_main]*1000/(HISTO_HEIGHT*HISTO_WIDTH);
                if (histo_magnification<200) { // try to ajust if average level is less than 20%
                    histo_magnification=200*1000/histo_magnification;
                    for (c=0; c<5; ++c) {
                        for (i=0;i<HISTO_WIDTH;i++) {
                            histogram[c][i] = (histogram_transform((float)histogram_proc[c][i]))*histo_max_center_invw[c]*histo_magnification/1000;
                            if (histogram[c][i] > HISTO_HEIGHT)
                                histogram[c][i] = HISTO_HEIGHT;
                        }
                    }
                } else 
                    histo_magnification=0;
            } else {
                histo_magnification=0;
            }

            histogram_stage=0;
            break;

        case HISTOGRAM_IDLE_STAGE:
            break;
    }

}

void histogram_stop()
{
    histogram_stage=HISTOGRAM_IDLE_STAGE;
}


void histogram_restart()
{
    histogram_stage = 0;
}


