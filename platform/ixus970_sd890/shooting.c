#define PARAM_FILE_COUNTER      0x38
#define PARAM_EXPOSURE_COUNTER  0x02

#include "platform.h"

// These F-numbers are the "mock" values shown by the cam.
// They're linked to FL (zoom) and ND8 filter.
//id (hack id), prop_id (canon id), name
const ApertureSize aperture_sizes_table[] = {
	/*first row: zoom position using propertycase #195
	second row: zoom value in x (100=1x) using misc values
	third row: real aperture using misc values
	fourth row: aperture using 'standard' Canon on-screen display
	fifth row: Av using propertycase #23
	0    1.0    3.24    3.2    326
	1    1.3    3.41    3.5    340
	2    1.6    3.60    3.5    355
	3    1.9    3.78    4.0    369
	4    2.3    3.98    4.0    383
	5    2.7    4.17    4.0    396
	6    3.1    4.36    4.5    408
	7    3.7    4.58    4.5    422
	8    3.7    4.82    5.0    436
	9    3.7    5.11    5.0    452
	10    3.7    5.47    5.6    471
	11    3.7    5.86    5.7    490*/
	{  0, 326,  "3.2" },
	{  1, 340,  "3.5" },  
	{  2, 355,  "3.5" },
	{  3, 369,  "4.0" },
	{  4, 383,  "4.0" },
	{  5, 396,  "4.0" },
	{  6, 408,  "4.5" },
	{  7, 422,  "4.5" },
	{  8, 436,  "5.0" },
	{  9, 452,  "5.0" },
	{ 10, 471,  "5.6" },
	{ 11, 490,  "5.7" },
	/*And the same physical apertures for the firework mode in SCN position
	0    1.0    3.24    9.0    601
	1    1.3    3.41   10.0    615
	2    1.6    3.60   10.0    630
	3    1.9    3.78   11.0    644
	4    2.3    3.98   11.0    658
	5    2.7    4.17   11.0    671
	6    3.1    4.36   13.0    683
	7    3.7    4.58   13.0    697
	8    3.7    4.82   14.0    711
	9    3.7    5.11   14.0    727
	10    3.7    5.47   16.0    746
	11    3.7    5.86   16.0    765*/
	{ 12, 601,  "9.0" },
	{ 13, 615, "10.0" },
	{ 14, 630, "10.0" },
	{ 15, 644, "11.0" },
	{ 16, 658, "11.0" },
	{ 17, 671, "11.0" },
	{ 18, 683, "13.0" },
	{ 19, 697, "13.0" },
	{ 20, 711, "14.0" },
	{ 21, 727, "14.0" },
	{ 22, 746, "16.0" },
	{ 23, 765, "16.0" }
};

// Another set of "mock" values
// hacks id, prop_id, name[8], usec
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
	{  32, 1024, "1/1600",  625 },
	{  33, 1056, "1/2000",  500 },
	{  34, 1088, "1/2500",  400 },
	{  35, 1120, "1/3200",  313 }
};

const ISOTable iso_table[] = {
	{ -1,    1,   "HI", -1},
	{  0,    0, "Auto", -1},
	{  1,   80,   "80", -1},
	{  2,  100,  "100", -1},
	{  3,  200,  "200", -1},
	{  4,  400,  "400", -1},
	{  5,  800,  "800", -1},
	{  6, 1600, "1600", -1},
	{  7, 3200, "3200", -1}
};

/*
http://www.usa.canon.com/consumer/controller?act=ModelInfoAct&tabact=ModelTechSpecsTabAct&fcategoryid=224&modelid=16719

Shooting Modes
	Auto, Camera M,
    Special Scene
        (Portrait, Foliage, Snow, Beach, Sunset, Fireworks, Aquarium, ISO 3200,
        Indoor, Kids & Pets, Night Snapshot),
    Color Accent, Color Swap, Digital Macro, Stitch Assist, Movie
Movie: 640 x 480 (30 fps/30 fps LP), 320 x 240 (30 fps) available up to 4GB or 60 minutes,
    640 x 480 (up to 2 hours at 0.5 fps/1 fps), 160 x 120 (up to 3 min. at 15 fps)

canon mode list FFAF9460 in 100b
*/
static const CapturemodeMap modemap[] = {
	{ MODE_LONG_SHUTTER,       32774 }, // guessed
	{ MODE_AUTO,               32768 },
	{ MODE_P,                  32772 },
	{ MODE_DIGITAL_MACRO,      33288 },
	{ MODE_COLOR_ACCENT,       33307 },
	{ MODE_COLOR_SWAP,         33308 },
	{ MODE_STITCH,             33290 },
	//
	{ MODE_SCN_NIGHT_SNAPSHOT, 16395 },
	{ MODE_SCN_KIDS_PETS,      16400 },
	{ MODE_SCN_INDOOR,         16401 },
	{ MODE_SCN_SUNSET,         16402 },
	{ MODE_SCN_FOLIAGE,        16403 },
	{ MODE_SCN_SNOW,           16404 },
	{ MODE_SCN_BEACH,          16405 },
	{ MODE_SCN_FIREWORK,       16406 },
	{ MODE_SCN_AQUARIUM,       16408 },
	{ MODE_SCN_ISO_3200,       16413 },
	{ MODE_SCN_PORTRAIT,       16397 },
	//
	{ MODE_VIDEO_STD,          2599  },
	{ MODE_VIDEO_COMPACT,      2601  },
	{ MODE_VIDEO_COLOR_ACCENT, 2597  },
	{ MODE_VIDEO_COLOR_SWAP,   2598  },
	{ MODE_VIDEO_TIME_LAPSE,   2603  },
};

#include "../generic/shooting.c"

long get_file_next_counter()
{
	return get_file_counter();
}

long get_target_file_num()
{
	long n;

	n = get_file_next_counter();
	n = (n>>4)&0x3FFF;
	return n;
}

long get_target_dir_num()
{
	long n;

	n = get_file_next_counter();
	n = (n>>18)&0x3FF;
	return n;
}

int circle_of_confusion = 5;
