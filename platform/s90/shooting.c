#define PARAM_FILE_COUNTER      0x38 // G11 OK
#define PARAM_EXPOSURE_COUNTER  0x02 // G11 OK

#include "platform.h"

// These F-numbers are the "mock" values shown by the cam.
// They're linked to FL (zoom) and ND8 filter.
// aperture_sizes_table[].id is just a serial number.
const ApertureSize aperture_sizes_table[] = { // PROPCASE 26
    {  9, 201, "2.0" }, 
    { 10, 224, "2.2" }, 
    { 11, 256, "2.5" },
    { 12, 288, "2.8" },
    { 13, 320, "3.2" },
    { 14, 352, "3.5" },
    { 15, 384, "4.0" },
    { 16, 416, "4.5" },
    { 17, 448, "5.0" },
    { 18, 480, "5.6" },
    { 19, 512, "6.3" },
    { 20, 544, "7.1" },
	{ 21, 576, "8.0" },
};


const ShutterSpeed shutter_speeds_table[] = {
    { -12, -384, "15", 15000000 },
    { -11, -352, "13", 13000000 },
    { -10, -320, "10", 10000000 },
    {  -9, -288, "8",   8000000 },
    {  -8, -256, "6",   6000000 },
    {  -7, -224, "5",   5000000 },
    {  -6, -192, "4",   4000000 },
    {  -5, -160, "3.2", 3200000 },
    {  -4, -128, "2.5", 2500000 },
    {  -3,  -96, "2",   2000000 },
    {  -2,  -64, "1.6", 1600000 },
    {  -1,  -32, "1.3", 1300000 },
    {   0,    0, "1",   1000000 },
    {   1,   32, "0.8",  800000 },
    {   2,   64, "0.6",  600000 },
    {   3,   96, "0.5",  500000 },
    {   4,  128, "0.4",  400000 },
    {   5,  160, "0.3",  300000 },
    {   6,  192, "1/4",  250000 },
    {   7,  224, "1/5",  200000 },
    {   8,  256, "1/6",  166667 },
    {   9,  288, "1/8",  125000 },
    {  10,  320, "1/10", 100000 },
    {  11,  352, "1/13",  76923 },
    {  12,  384, "1/15",  66667 },
    {  13,  416, "1/20",  50000 },
    {  14,  448, "1/25",  40000 },
    {  15,  480, "1/30",  33333 },
    {  16,  512, "1/40",  25000 },
    {  17,  544, "1/50",  20000 },
    {  18,  576, "1/60",  16667 },
    {  19,  608, "1/80",  12500 },
    {  20,  640, "1/100", 10000 },
    {  21,  672, "1/125",  8000 },
    {  22,  704, "1/160",  6250 },
    {  23,  736, "1/200",  5000 },
    {  24,  768, "1/250",  4000 },
    {  25,  800, "1/320",  3125 },
    {  26,  832, "1/400",  2500 },
    {  27,  864, "1/500",  2000 },
    {  28,  896, "1/640",  1563 },
    {  29,  928, "1/800",  1250 },
    {  30,  960, "1/1000", 1000 },
    {  31,  992, "1/1250",  800 },
    {  32, 1024, "1/1600",  625 }
};

const ISOTable iso_table[] = {
    {  0,     0,  "Auto", -1},
    {  1,    80,    "80", -1},
    {  2,   100,   "100", -1},
	{  3,   125,   "125", -1},
	{  4,   160,   "160", -1},
    {  5,   200,   "200", -1},
	{  6,   250,   "250", -1},
	{  7,   320,   "320", -1},
    {  8,   400,   "400", -1},
	{  9,   500,   "500", -1},
	{ 10,   640,   "650", -1},
    { 11,   800,   "800", -1},
	{ 12,  1000,  "1000", -1},
	{ 13,  1250,  "1250", -1},
    { 14,  1600,  "1600", -1},
	{ 15,  2000,  "2000", -1},
	{ 16,  2500,  "2500", -1},
    { 17,  3200,  "3200", -1}
};        

static const CapturemodeMap modemap[] = {
	{ MODE_AUTO,               32768  },
	{ MODE_P,                  32772  }, // also C1,C2
	{ MODE_TV,                 32771  },
	{ MODE_AV,                 32770  },
	{ MODE_M,                  32769  },
    { MODE_LOWLIGHT,	       32799  },

	{ MODE_VIDEO_COLOR_ACCENT, 2601   },
	{ MODE_VIDEO_COLOR_SWAP,   2602   },
	{ MODE_VIDEO_STD,          2603   },

	{ MODE_SCN_NIGHT_SNAPSHOT, 16395  },
	{ MODE_SCN_LANDSCAPE,	   16396  },
	{ MODE_SCN_PORTRAIT,       16397  },
	{ MODE_SCN_STITCH,         16906  },
	{ MODE_SCN_NOSTALGIC,      16931  },
	{ MODE_SCN_COLOR_SWAP,     16924  },
	{ MODE_SCN_COLOR_ACCENT,   16923  },
	{ MODE_SCN_SNOW,           16404  },
	{ MODE_SCN_FOLIAGE,        16403  },
	{ MODE_SCN_AQUARIUM,       16408  },
	{ MODE_SCN_UNDERWATER,     16407  },
	{ MODE_SCN_BEACH,          16405  },
	{ MODE_SCN_FIREWORK,       16406  },
	{ MODE_SCN_NIGHT_SCENE,    16398  },
	{ MODE_SCN_SUNSET,         16402  },
	{ MODE_SCN_INDOOR,     	   16401  },
	{ MODE_SCN_KIDS_PETS,      16400  }
};


#include "../generic/shooting.c"

const int dof_tbl[] = {6000, 6850, 7490, 8560, 9640, 10700, 12850, 14980, 18190, 22500};
const int dof_tbl_size = sizeof(dof_tbl)/sizeof(dof_tbl[0]);

long get_file_next_counter() {
    return get_file_counter();
}

long get_target_file_num() {
    long n;
    
    n = get_file_next_counter();
    n = (n>>4)&0x3FFF;
    return n;
}

long get_target_dir_num() {
    long n;
    
    n = get_file_next_counter();
    n = (n>>18)&0x3FF;
    return n;
}

int circle_of_confusion = 7;

