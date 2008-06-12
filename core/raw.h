#ifndef RAW_H
#define RAW_H

#include "camera.h"

//-------------------------------------------------------------------
#define RAW_PREFIX_IMG          0
#define RAW_PREFIX_CRW          1
#define RAW_PREFIX_SND          2

#define RAW_EXT_JPG             0
#define RAW_EXT_CRW             1
#define RAW_EXT_CR2             2
#define RAW_EXT_THM             3
#define RAW_EXT_WAV             4

//-------------------------------------------------------------------

#define RAW_ROWLEN ((CAM_RAW_ROWPIX*10)/8)

//-------------------------------------------------------------------
extern int raw_savefile();
extern void raw_postprocess();
extern void raw_prepare_develop(char* filename);
extern void load_bad_pixels_list(char* filename);
unsigned short get_raw_pixel(unsigned int x,unsigned  int y);

//-------------------------------------------------------------------
#endif
