#define PARAM_FILE_COUNTER      0x38

#include "platform.h"

// These F-numbers are the "mock" values shown by the cam.
// They're linked to FL (zoom) and ND8 filter.
// aperture_sizes_table[].id is just a serial number.
const ApertureSize aperture_sizes_table[] = { // PROPCASE 26
    {  9, 295, "2.8" }, // zoom 1.0
    { 10, 318, "3.2" }, // zoom 1.2
    { 11, 342, "3.5" }, // etc.
    { 12, 368, "4.0" },
    { 13, 396, "4.0" },
    { 14, 427, "4.5" },
    { 15, 461, "5.0" },
    { 16, 493, "5.8" },
// The rest are the same physical apertures as above, but with ND8:
    { 17, 576, "8.0" },
    { 18, 599, "9.0" },
    { 19, 623, "10.0" },
    { 20, 649, "11.0" },
    { 21, 677, "11.0" },
    { 22, 708, "13.0" },
    { 23, 742, "14.0" },
    { 24, 774, "16.0" },
};

// OLD copied comment!
// TODO copied from 850
// Another set of "mock" values, which can probably
// be derived from the table found at FFB4E258 in FW.
// At the moment, I see no reason to amend it.
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
};

const ISOTable iso_table[] = {
    { -1,     1,    "HI", -1},
    {  0,     0,  "Auto", -1},
    {  1,    80,    "80", -1},
    {  2,   100,   "100", -1},
    {  3,   200,   "200", -1},
    {  4,   400,   "400", -1},
    {  5,   800,   "800", -1},
    {  6,  1600,  "1600", -1},
};          

// TODO setting the DP button as a shortcut to movie in canon menu
// gives a value of (current mode)+1024 while movie is recording, unless
// already in movie mode
static const CapturemodeMap modemap[] = {
    { MODE_AUTO,               32768 }, 
    { MODE_M,                  32769 },
    { MODE_P,                  32772 },
    { MODE_PORTRAIT,           16397 },
    { MODE_NIGHT_SNAPSHOT,     16395 },
    { MODE_SCN_KIDS_PETS,      16400 },
    { MODE_SCN_INDOOR,         16401 },
    { MODE_SCN_SUNSET,         16402 },
    { MODE_SCN_FOLIAGE,        16403 },
    { MODE_SCN_SNOW,           16404 },
    { MODE_SCN_BEACH,          16405 },
    { MODE_SCN_FIREWORK,       16406 },
    { MODE_SCN_UNDERWATER,     16407 },
    { MODE_SCN_AQUARIUM,       16408 },
    { MODE_SCN_ISO_3200,       16413 },
    { MODE_DIGITAL_MACRO,      33288 }, // SCN
    { MODE_SCN_COLOR_ACCENT,   16923 },
    { MODE_SCN_COLOR_SWAP,     16924 },
    { MODE_STITCH,             16906 }, // SCN, either direction
    { MODE_QUICK,              33312 },

    { MODE_VIDEO_STD,          2600  },
    { MODE_VIDEO_COLOR_ACCENT, 2598  },
    { MODE_VIDEO_COLOR_SWAP,   2599  },
};

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

// not used ? -> CAM_DRAW_EXPOSITION
/*
char* shooting_get_tv_str()
{
    short int tvv;
    long i;
    _GetPropertyCase(PROPCASE_TV, &tvv, sizeof(tvv));	// 262 for DiGiC III
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
    _GetPropertyCase(PROPCASE_AV, &avv, sizeof(avv));	// 23 for DiGiC III
    for (i=0;i<AS_SIZE;i++){
	if (aperture_sizes_table[i].prop_id == avv)
	    return (char*)aperture_sizes_table[i].name;
    }
    return (char*) "?";
}

char* shooting_get_iso_str()
{
    short int isov;
    long i;
    _GetPropertyCase(PROPCASE_ISO_MODE, &isov, sizeof(isov));
    for (i=0;i<ISO_SIZE;i++){
   if (iso_table[i].prop_id == isov)
       return (char*)iso_table[i].name;
    }
    return (char*) "?";
}
*/
