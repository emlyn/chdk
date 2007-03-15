#include "stdlib.h"
#include "platform.h"
#include "core.h"
#include "keyboard.h"
#include "conf.h"
#include "ubasic.h"
#include "gui.h"
#include "histogram.h"

static float identity(float x);


unsigned char histogram[HISTO_SIZE];
long exposition_thresh;
long under_exposed;
long over_exposed;

static unsigned int histogram_proc[HISTO_SIZE];
static float histo_max_invw;
static long histogram_stage;
static unsigned int histo_max;
static float (*histogram_transform)(float) = identity;


float identity(float x)
{
    return x;
}


void histogram_process()
{
    unsigned char *img;
    int i, hi;

//    if (kbd_is_key_pressed(KEY_SHOOT_HALF)){
	img = vid_get_viewport_fb();
//    } else {
//	img = vid_get_viewport_live_fb();
//    }

    switch (histogram_stage) {
    case 0:
	for (i=0;i<HISTO_SIZE;i++){
	    histogram_proc[i]=0;
	}
	histo_max = 0;

	histogram_stage=1;
	break;
    case 1:

	for (i=0;i<gui_pixel_cnt;i+=3){
	    hi = img[i*3+1]*HISTO_SIZE/256;
	    histogram_proc[hi]++;

	    if (histo_max<histogram_proc[hi])
		histo_max=histogram_proc[hi];
	}

	histogram_stage=2;
	break;
    case 2:

	for (i=1;i<gui_pixel_cnt;i+=3){
	    hi = img[i*3+1]*HISTO_SIZE/256;
	    histogram_proc[hi]++;

	    if (histo_max<histogram_proc[hi])
		histo_max=histogram_proc[hi];
	}

	histogram_stage=3;
	break;
    case 3:

	for (i=2;i<gui_pixel_cnt;i+=3){
	    hi = img[i*3+1]*HISTO_SIZE/256;
	    histogram_proc[hi]++;

	    if (histo_max<histogram_proc[hi])
		histo_max=histogram_proc[hi];
	}

	histogram_stage=4;
	break;
    case 4:

	if (histo_max > 0){
	    histo_max_invw = 50.0f/histogram_transform((float)histo_max);

	    under_exposed = (histogram_proc[0]*8+histogram_proc[1]*4+histogram_proc[2]) >
		    exposition_thresh;

	    over_exposed = (histogram_proc[HISTO_SIZE-3]+histogram_proc[HISTO_SIZE-2]*4+
		    histogram_proc[HISTO_SIZE-1]*8) > exposition_thresh;
	} else {
	    histo_max_invw = 0.0f;
	}
	histogram_stage=5;
	break;
    case 5:

	for (i=0;i<HISTO_SIZE;i++){
	    histogram[i] = (histogram_transform((float)histogram_proc[i]))*histo_max_invw;
	}

	histogram_stage=0;
	break;
    }

}
