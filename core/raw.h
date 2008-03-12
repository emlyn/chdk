#ifndef RAW_H
#define RAW_H

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

#if defined (CAMERA_g7) || (CAMERA_a640)
#define ROWPIX 3736   // for 10 MP
#define ROWS   2772   // for 10 MP

#elif defined (CAMERA_a630)
#define ROWPIX 3344   // for 8 MP
#define ROWS   2484   // for 8 MP

#elif defined (CAMERA_a620) || defined (CAMERA_a710) || defined (CAMERA_a560) || defined (CAMERA_a570) || defined (CAMERA_ixus700_sd500) || defined (CAMERA_ixus850_sd800) || defined (CAMERA_ixus70_sd1000) || defined(CAMERA_a550)
#define ROWPIX 3152   // for 7 MP
#define ROWS   2340   // for 7 MP

#elif defined (CAMERA_a700) || defined (CAMERA_s3is) || defined (CAMERA_ixus65_sd630) || defined (CAMERA_ixus800_sd700)
#define ROWPIX 2888   // for 6 MP
#define ROWS   2136   // for 6 MP

#elif defined (CAMERA_a610) || defined (CAMERA_s2is) || defined (CAMERA_ixus55_sd450)
#define ROWPIX 2672   // for 5 MP
#define ROWS   1968   // for 5 MP

#elif defined (CAMERA_a720) || defined (CAMERA_s5is) || defined (CAMERA_ixus950_sd850)
#define ROWPIX 3336   // for new 8 MP
#define ROWS   2480   // for new 8 MP

#elif defined (CAMERA_a650)
#define ROWPIX 4104   // for 12 MP
#define ROWS   3048   // for 12 MP

#elif defined (CAMERA_a460)
#define ROWPIX 2664   // for 5 MP 1/3" sensor size
#define ROWS   1968   // for 5 MP 1/3" sensor size

#else
#error camera type not defined

#endif

#define ROWLEN ((ROWPIX*10)/8)

//-------------------------------------------------------------------
extern int raw_savefile();
extern void raw_postprocess();
extern void raw_prepare_develop(char* filename);
extern void load_bad_pixels_list(char* filename);

//-------------------------------------------------------------------
#endif
