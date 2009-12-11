#define PARAM_FILE_COUNTER      0x34

#include "platform.h"

const ApertureSize aperture_sizes_table[] = {
    {  9, 288, "2.8" },
    { 10, 299, "2.8" },
    { 11, 312, "3.2" },
    { 12, 329, "3.2" },
    { 13, 347, "3.5" },
    { 14, 371, "4.0" },
    { 15, 400, "4.0" },
    { 16, 438, "5.0" },
    { 17, 476, "5.6" },
    { 18, 480, "5.6" },
    { 19, 483, "5.6" },
    { 20, 500, "6.3" },
    { 21, 517, "6.3" },
    { 22, 535, "7.1" },
    { 23, 559, "8.0" },
    { 24, 588, "8.0" },
    { 25, 626, "10.0" },
    { 26, 668, "11.0" }, 
    { 27, 668, "11.0" }, 
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
};          

/*
http://www.usa.canon.com/consumer/controller?act=ModelInfoAct&fcategoryid=224&modelid=13019#ModelTechSpecsAct

Shooting Modes
    Auto, Camera M,
    Special Scene
        (Portrait, Foliage, Snow, Beach, Fireworks, Underwater, Indoor,
        Kids & Pets, Night Snapshot, Color Accent, Color Swap),
    Digital Macro, My Colors, Stitch Assist, Movie
Movie: 640 x 480 / 320 x 240 (30 fps/15 fps) available up to 1GB or 1 hour for each file size,
    320 x 240 (1 min. at 60 fps), 160 x 120 (3 min. at 15 fps)
canon mode list FF972360 in 100b
*/
static const CapturemodeMap modemap[] = {
    { MODE_LONG_SHUTTER,       32774 }, // guessed!
    { MODE_AUTO,               32768 },
    { MODE_P,                  32772 },
    { MODE_DIGITAL_MACRO,      33288 }, 
    { MODE_VIDEO_STD,          2593  },
// remaining video modes missing, guessed, based on a540
    { MODE_VIDEO_COLOR_ACCENT, 2591  },
    { MODE_VIDEO_COLOR_SWAP,   2592  },
    { MODE_VIDEO_SPEED,        2594  },
    { MODE_VIDEO_COMPACT,      2595  },
    { MODE_STITCH,             33290 },
    { MODE_SCN_COLOR_SWAP,     16921 }, // was MY_COLORS
    { MODE_SCN_UNDERWATER,     16405 },
    { MODE_SCN_NIGHT_SNAPSHOT, 16395 },
    { MODE_SCN_PORTRAIT,       16397 },
    { MODE_SCN_KIDS_PETS,      16399 },
    { MODE_SCN_INDOOR,         16400 },
    { MODE_SCN_FOLIAGE,        16401 }, // was MODE_LANDSCAPE, but not not in canon list
    { MODE_SCN_SNOW,           16402 },
    { MODE_SCN_BEACH,          16403 },
    { MODE_SCN_FIREWORK,       16404 },
    { MODE_SCN_COLOR_ACCENT,   16920 }
};

#include "../generic/shooting.c"

long get_file_next_counter() {
    return ((get_file_counter()>>4)+1)<<4;
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

char* shooting_get_tv_str()
{
    short int tvv;
    long i;
    _GetPropertyCase(PROPCASE_TV, &tvv, sizeof(tvv));
    for (i=0;i<SS_SIZE;i++){
	if (shutter_speeds_table[i].prop_id >= tvv)
	    return (char*)shutter_speeds_table[i].name;
    }
    return (void*)"?";
}

char* shooting_get_av_str()
{
    short int avv;
    long i;
    _GetPropertyCase(PROPCASE_AV, &avv, sizeof(avv));
    for (i=0;i<AS_SIZE;i++){
	if (aperture_sizes_table[i].prop_id == avv)
	    return (char*)aperture_sizes_table[i].name;
    }
    return (char*) "?";
}

