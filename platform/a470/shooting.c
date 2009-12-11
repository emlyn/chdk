#define PARAM_FILE_COUNTER      0x38

// DRYOS-Notes:
// propertycase
//   196 - overall brightness (of viewport?)

#include "platform.h"

const ApertureSize aperture_sizes_table[] = {
    {  9, 307, "3.0" },
    { 10, 333, "3.2" },
    { 11, 360, "3.5" },
    { 12, 391, "4.0" },
    { 13, 426, "4.5" },
    { 14, 457, "5.0" },
    { 15, 495, "5.8" },
    { 16, 586, "9.0 ND" },
    { 17, 612, "10.0 ND" },
    { 18, 639, "10.0 ND" },
    { 19, 670, "11.0 ND" },
    { 20, 705, "14.0 ND" },
    { 21, 736, "14.0 ND" },
    { 21, 774, "18.0 ND" },
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
http://www.usa.canon.com/consumer/controller?act=ModelInfoAct&fcategoryid=221&modelid=16338#ModelTechSpecsAct

Shooting Modes
    Auto, Camera M, 
    Special Scene 
        (Portrait, Foliage, Snow, Beach, Sunset, Fireworks, Aquarium, 
        Indoor, Kids & Pets, Night Snapshot),
    Super Macro, Movie

Movie: 640 x 480 (20 fps/20 fps LP), 320 x 240 (30 fps) available up to 4GB or 60 minutes,
    160 x 120 (up to 3 minutes at 15 fps)
canon mode list FFE8FAB4 in 100e
*/
static const CapturemodeMap modemap[] = {
    { MODE_LONG_SHUTTER,       32774 }, // guessed
    { MODE_AUTO,               32768 },
    { MODE_P,                  32772 },
    { MODE_SUPER_MACRO,        33289 }, // guessed
    { MODE_VIDEO_STD,          2599  },
    { MODE_VIDEO_COMPACT,      2601  },
    { MODE_SCN_AQUARIUM,       16408 },  
    { MODE_SCN_SUNSET,         16402 },  // was NIGHT, but night snapshot is below
    { MODE_SCN_FOLIAGE,        16403 },
    { MODE_SCN_SNOW,           16404 },  
    { MODE_SCN_BEACH,          16405 },  
    { MODE_SCN_FIREWORK,       16406 }, 
	{ MODE_SCN_PORTRAIT,       16397 },	
    { MODE_SCN_INDOOR,         16401 },
    { MODE_SCN_KIDS_PETS,      16400 },	
    { MODE_SCN_NIGHT_SNAPSHOT, 16395 },
};

#include "../generic/shooting.c"

const int dof_tbl[] = {5800, 6420, 7060, 7700, 8340, 9950, 11550, 13160, 14750, 17150, 19570, 22760, 26750, 30750, 34800};
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

int circle_of_confusion = 5;
