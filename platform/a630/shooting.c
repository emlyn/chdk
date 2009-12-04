#define PARAM_FILE_COUNTER      0x34

#include "platform.h"

const ApertureSize aperture_sizes_table[] = {
    {  9, 288, "2.8" },
    { 10, 320, "3.2" },
    { 11, 352, "3.5" },
    { 12, 384, "4.0" },
    { 13, 416, "4.5" },
    { 14, 448, "5.0" },
    { 15, 480, "5.6" },
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
    {  34, 1084, "1/2500",  400 },
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
 valid modes from 100c dump @FFD682D0, names guessed from a540, g7, 
from
http://www.usa.canon.com/consumer/controller?act=ModelInfoAct&tabact=ModelTechSpecsTabAct&fcategoryid=221&modelid=14108
Shooting Modes
    Auto; Creative: P, Av, Tv, M, C; Image: Portrait, Landscape, Night Scene, 
    Special Scene
        Foliage, Snow, Beach, Fireworks, Underwater, Indoor, Kids & Pets,
        Night Snapshot, Color Accent, Color Swap,
    Stitch Assist, Movie
Video resolutions
    640 x 480 / 320 x 240 (30 fps/15 fps) available up to 1GB or 1 hour for each file size,
    160 x 120 (3 min. at 15 fps)
*/
static const CapturemodeMap modemap[] = {
    // above are common on most cameras except very old vxworks that use 0-n, should be OK
    { MODE_M,                  32769 },
    { MODE_AV,                 32770 },
    { MODE_TV,                 32771 },
    { MODE_P,                  32772 },
    { MODE_AUTO,               32768 },
    { MODE_PORTRAIT,           32781 },
    { MODE_LANDSCAPE,          32780 },
    { MODE_STITCH,             33290 },
    { MODE_NIGHT,              32782 }, // s3is a540 "night scene" on dial, different from "night snapshot" under "scene" below
    // the following are suspect, but probably fairly similar scene modes
    { MODE_SCN_NIGHT,          16395 }, // a540 "night snapshot" g7 SCN_NIGHT
    { MODE_SCN_KIDS_PETS,      16399 }, // a540 "kids and pets" g7 SCN_CHILD
    { MODE_SCN_INDOOR,         16400 }, // a540 "indoor" g7 SCN_PARTY
    { MODE_SCN_FOLIAGE,        16401 }, // a540 "foliage" g7 SCN_GRASS
    { MODE_SCN_SNOW,           16402 }, // a540, g7 "snow" 
    { MODE_SCN_BEACH,          16403 }, // a540, g7 "beach"
    { MODE_SCN_FIREWORK,       16404 }, // a540, g7 "fireworks"
    { MODE_SCN_UNDERWATER,     16405 }, // a540 "under water"
    // the following are very suspect
    { MODE_MY_COLORS,          16922 }, // g7 MODE_MY_COLORS
    { MODE_SCN_COLOR_ACCENT,   16921 }, // a540 MODE_SCN_COLOR_SWAP, g7 MODE_SCN_COLOR_ACCENT
    { MODE_VIDEO_COLOR_ACCENT,  2594 }, // a540 MODE_VIDEO_SPEED, g7 MODE_VIDEO_COLOR_ACCENT
    { MODE_VIDEO_MY_COLORS,     2595 }, // a540 MODE_VIDEO_COMPACT, g7 MODE_VIDEO_MY_COLORS
    { MODE_VIDEO_STD,           2596 }, // g7 MODE_VIDEO_STD
    { MODE_VIDEO_COMPACT,       2598 }, // g7 MODE_VIDEO_COMPACT
//    { ???,      8221  }, // in canon list, C maybe ?
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

int circle_of_confusion = 6;
