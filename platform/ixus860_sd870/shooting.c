#define PARAM_FILE_COUNTER      0x38

// DRYOS-Notes:
// propertycase
//   196 - overall brightness (of viewport?)

#include "platform.h"

const ApertureSize aperture_sizes_table[] = {
    {  9, 293, "2.8" },
    { 10, 324, "3.2" },
    { 11, 352, "3.5" },
    { 12, 380, "4.0" },
    { 13, 408, "4.5" },
    { 14, 436, "5.0" },
    { 15, 464, "5.6" },
    { 16, 512, "6.3" },
    { 17, 544, "7.1" },
    { 18, 576, "8.0" },
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
    {  32, 1021, "1/1600",  625 },
    {  33, 1053, "1/2000",  500 },
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
};          

/*
http://www.usa.canon.com/consumer/controller?act=ModelInfoAct&fcategoryid=224&modelid=15655#ModelTechSpecsAct

Shooting Modes
	Auto, Camera M,
	Special Scene
		(Portrait, Foliage, Snow, Beach, Fireworks, Aquarium, Underwater, Indoor
		Kids & Pets, Night Snapshot),
	Color Accent, Color Swap, Digital Macro, Stitch Assist, Movie
video
640 x 480 (30 fps/30 fps LP), 320 x 240 (30 fps) available up to 4GB or 60 minutes, 640 x 480 (2 hours at 0.5 fps/1 fps),
160 x 120 (3 min. at 15 fps)

canon mode list @FFACFEF8 in 100c
*/
// PROPCACE 49
static const CapturemodeMap modemap[] = {
//    { ???,               32774 }, // "long shutter" in canon list
    { MODE_AUTO,               32768 }, 
    { MODE_P,                  32772 },
    { MODE_DIGITAL_MACRO,      33288 },
    { MODE_SCN_PORTRAIT,       16397 },
    { MODE_NIGHT_SNAPSHOT,     16395 }, // actually SCN, named SCN_NIGHT on other cams
    { MODE_COLOR_ACCENT,       33306 },
    { MODE_MY_COLORS,          33307 },
    { MODE_SCN_KIDS_PETS,      16400 },
    { MODE_SCN_INDOOR,         16401 },
    { MODE_SCN_FOLIAGE,        16402 },
    { MODE_SCN_SNOW,           16403 },
    { MODE_SCN_BEACH,          16404 },
    { MODE_SCN_FIREWORK,       16405 },
    { MODE_SCN_AQUARIUM,       16407 },
    { MODE_SCN_UNDERWATER,     16406 },
    { MODE_VIDEO_STD,          2597  },
    { MODE_VIDEO_COMPACT,      2599  },
    { MODE_VIDEO_COLOR_ACCENT, 2595  },
    { MODE_VIDEO_MY_COLORS,    2596  },
    { MODE_VIDEO_TIME_LAPSE,   2601  },
    { MODE_STITCH,             33290 },
};

#include "../generic/shooting.c"

//const int dof_tbl[] = {4600, 6140, 7560, 9110, 10830, 12670, 14690, 17300};;
//const int dof_tbl_size = sizeof(dof_tbl)/sizeof(dof_tbl[0]);

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
