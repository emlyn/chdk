#include "platform.h"

//  prop 23, "Photo", "CanonSi"
//  290 95/32  96   without ND filter
//  307 107/32 102
//  325 107/32 108
//  347 116/32 115
//  367 116/32 122
//  369 128/32 129
//  413 139/32 137
//  443 149/32 147
//  470 159/32 156
//  494 162/32 164
//  
//  488 159/32 162  with ND filter
//  505 170/32 168
//  523 170/32 174
//  545 181/32 181
//  565 181/32 188
//  587 192/32 195
//  611 203/32 203
//  641 213/32 213
//  668 221/32 222
//  692 221/32 230
const ApertureSize aperture_sizes_table[] = {
//       idx, p23, CanonSi/32
	{  9, 290, "3.0" },
	{ 10, 307, "3.2" },
	{ 11, 325, "3.4" },
	{ 12, 347, "3.6" },
	{ 13, 367, "3.8" },
	{ 14, 369, "4.0" },
	{ 15, 413, "4.3" },
	{ 16, 443, "4.6" },
	{ 17, 470, "4.9" },
	{ 18, 494, "5.1" },
	{ 19, 488, "5.1" },
	{ 20, 505, "5.3" },
	{ 21, 523, "5.4" },
	{ 22, 545, "5.7" },
	{ 23, 565, "5.9" },
	{ 24, 587, "6.1" },
	{ 25, 611, "6.3" },
	{ 26, 641, "6.7" },
	{ 27, 668, "6.9" },
	{ 28, 692, "7.2" },
};

// taken from ixus860, not checked!
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
    {  32, 1021, "1/1600",  625 },
    {  33, 1053, "1/2000",  500 },
};

// idx, propcase 149, name, -1
const ISOTable iso_table[] = {
	{ -1,    1,   "HI", -1},
	{  0,    0, "Auto", -1},
	{  1,   80,   "80", -1},
	{  2,  100,  "100", -1},
	{  3,  200,  "200", -1},
	{  4,  400,  "400", -1},
	{  5,  800,  "800", -1},
	{  6, 1600, "1600", -1},
	{  7, 3200, "3200", -1},
};          

/*
http://www.usa.canon.com/consumer/controller?act=ModelInfoAct&fcategoryid=224&modelid=17626#ModelTechSpecsAct

Shooting Modes
    Auto, P,
    Special Scene
        (Portrait, Foliage, Snow, Beach, Sunset, Fireworks, Aquarium,
        Underwater, ISO 3200, Indoor, Kids & Pets, Night Snapshot,
        Color Accent, Color Swap, Digital Macro, Stitch Assist),
    Movie
Movie: 640 x 480 (30 fps), 320 x 240 (30 fps) available up to 4GB or 60 minutes per clip

canon mode list FFB2D2EC in 100e
*/
static const CapturemodeMap modemap[] = {
	{ MODE_VIDEO_STD,          2600   },
	{ MODE_VIDEO_COLOR_ACCENT, 2598   },
	{ MODE_VIDEO_COLOR_SWAP,   2599   },
	{ MODE_SCN_PORTRAIT,       16397  },
	{ MODE_SCN_NIGHT_SNAPSHOT, 16395  },
    { MODE_SCN_KIDS_PETS,      16400  },
	{ MODE_SCN_INDOOR,         16401  },
	{ MODE_SCN_SUNSET,         16402  },
	{ MODE_SCN_FOLIAGE,        16403  },
	{ MODE_SCN_SNOW,           16404  },
	{ MODE_SCN_BEACH,          16405  },
	{ MODE_SCN_FIREWORK,       16406  },
	{ MODE_SCN_AQUARIUM,       16408  },
    { MODE_SCN_UNDERWATER,     16407  },
	{ MODE_SCN_ISO_3200,       16413  },
    { MODE_SCN_DIGITAL_MACRO,  33288  }, // not a normal SCN value, but under SCN in canon docs
	{ MODE_SCN_COLOR_ACCENT,   16923  },
    { MODE_SCN_COLOR_SWAP,     16924  },
	{ MODE_SCN_STITCH,         16906  },
	{ MODE_AUTO,               32768  },
	{ MODE_P,                  32772  },
	{ MODE_LONG_SHUTTER,       32774  }, // guessed
};

#define PARAM_FILE_COUNTER      0x38
#define PARAM_EXPOSURE_COUNTER  0x02
#include "../generic/shooting.c"

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

int circle_of_confusion = 5;
