#include "platform.h"
#include "conf.h"
#include "shot_histogram.h"
#include "camera.h"
#include "raw.h"
#include "stdlib.h"

#define RAW_TARGET_DIRECTORY    "A/DCIM/%03dCANON"
#define RAW_TARGET_FILENAME     "%s_%04d.%s"

// we could use sensor bitdepth here. For now, we just discard low bits if > 10bpp
#define SHOT_HISTOGRAM_SAMPLES 1024
#define SHOT_HISTOGRAM_SIZE (SHOT_HISTOGRAM_SAMPLES*sizeof(short))

unsigned short *shot_histogram=NULL;
unsigned short shot_margin_left=0, shot_margin_top=0, shot_margin_right=0, shot_margin_bottom=0;

// enable or disable shot histogram
int shot_histogram_set(int enable)
{
 if(enable) {
  if(shot_histogram)
   return 1;
  shot_histogram=malloc(SHOT_HISTOGRAM_SIZE);
  if(!shot_histogram)
   return 0;
 }
 else {
  free(shot_histogram);
  shot_histogram=NULL;
 }
 return 1;
}

int shot_histogram_isenabled()
{
 return(shot_histogram != NULL);
}

void build_shot_histogram()
{
 // read samples from RAW memory and build an histogram of its luminosity
 // actually, it' just reading pixels, ignoring difference between R, G and B, 
 // we just need an estimate of luminance
 // SHOT_HISTOGRAM_MARGIN defines a margin around the sensor that will be ignored 
 // (dead area)
 if(!shot_histogram_isenabled())
 	return;
 
 int x, y, x0, x1, y0, y1;
 
 int marginstep;
 
 short p;
 memset(shot_histogram,0,SHOT_HISTOGRAM_SIZE);
 
 marginstep= (CAM_RAW_ROWPIX - 2 * SHOT_HISTOGRAM_MARGIN)/10;

 // In future, support definition of a sort of "spot metering" 
 x0 = SHOT_HISTOGRAM_MARGIN + shot_margin_left * marginstep;
 x1 = CAM_RAW_ROWPIX - SHOT_HISTOGRAM_MARGIN - shot_margin_right * marginstep;
 y0 = SHOT_HISTOGRAM_MARGIN + shot_margin_top * marginstep;
 y1 = CAM_RAW_ROWS - SHOT_HISTOGRAM_MARGIN - shot_margin_bottom * marginstep;

 //x0 = SHOT_HISTOGRAM_MARGIN ;
 //x1 = CAM_RAW_ROWPIX - SHOT_HISTOGRAM_MARGIN ;
 //y0 = SHOT_HISTOGRAM_MARGIN;
 //y1 = CAM_RAW_ROWS - SHOT_HISTOGRAM_MARGIN;

 
 // just read one pixel out of SHOT_HISTOGRAM_STEP, one line out of SHOT_HISTOGRAM_STEP 
 for (y = y0 ; y < y1; y +=SHOT_HISTOGRAM_STEP ) 
 for (x = x0 ; x < x1; x +=SHOT_HISTOGRAM_STEP )  
 {
  p=get_raw_pixel(x,y);
// > 10bpp compatibility: discard the lowest N bits
#if CAM_SENSOR_BITS_PER_PIXEL > 10
  p >>= CAM_SENSOR_BITS_PER_PIXEL-10;
#endif
  shot_histogram[p]++;
 }
 /*
 // dump to file (just for debugging / logging purposes)
 // for each shoot, creates a HSTnnnnn.DAT file containing 2*1024 bytes
 char fn[64];
 char dir[32];
 sprintf(dir, RAW_TARGET_DIRECTORY, (conf.raw_in_dir)?get_target_dir_num():100);
 sprintf(fn, "%s/", dir);
 sprintf(fn+strlen(fn), RAW_TARGET_FILENAME, "HST", get_target_file_num(), "DAT");
 
 char buf[64];
 int fd = open(fn, O_WRONLY|O_CREAT, 0777);
 if (fd>=0) 
 {
  write(fd, shot_histogram, 2048);
  close(fd);
 } */
}



int shot_histogram_get_range(int histo_from, int histo_to)
// Examines the histogram, and returns the percentage of pixels that 
// have luminance between histo_from and histo_to
{
 int x, tot, rng;
 tot=0;
 rng=0;
 
 if(!shot_histogram_isenabled()) // TODO we could return an error somehow
  return 0;
 for (x = 0 ; x < SHOT_HISTOGRAM_SAMPLES; x ++ )  
 {
	 tot += shot_histogram[x];
	 if (x>=histo_from  && x <= histo_to)  
   {
	  rng += shot_histogram[x];
   } 	 
 }
 
 return (rng*100)/tot;
 
}
