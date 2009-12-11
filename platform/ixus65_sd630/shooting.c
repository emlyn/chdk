#define PARAM_FILE_COUNTER      0x34

#include "platform.h"

const ApertureSize aperture_sizes_table[] = {
    {  9, 290, "2.8" },
    { 10, 313, "3.2" },
    { 11, 337, "3.5" },
    { 12, 391, "4.0" },
    { 13, 420, "4.5" },
    { 14, 448, "5.0" },
    { 15, 480, "5.6" },
    { 16, 512, "6.3" },
    { 17, 544, "7.1" },
    { 18, 576, "8.0" },
    { 19, 999, "x.x" },
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
    {  0,    0, "Auto", -1},
    {  1,   50,   "50", -1},
    {  2,  100,  "100", -1},
    {  3,  200,  "200", -1},
    {  4,  400,  "400", -1},
    {  5,  800,  "800", -1},
};          

/*
canon modemap @FF973AD4 in 100a
according to http://www.usa.canon.com/consumer/controller?act=ModelInfoAct&fcategoryid=224&modelid=12956#ModelTechSpecsAct
Shooting Modes
    Auto, Camera M, Portrait, 
    Special Scene
        Foliage, Snow, Beach, Fireworks, Underwater, Indoor,
        Kids & Pets, Color Accent, Color Swap,
    Night Snapshot, Digital Macro, My Colors, Stitch Assist, Movie

Movie: 640 x 480 / 320 x 240 (30 fps/15 fps) available up to 1GB or 1 hour for each file size, 320 x 240 (1 min. at 60 fps), 160 x 120 (3 min. at 15 fps)
*/
/* names below mostly guessed from a540 and ixus60_sd600 */
static const CapturemodeMap modemap[] = {
    // common, should be OK
    { MODE_P,                  32772 }, // may be called manual, but effectively P
    { MODE_AUTO,               32768 },
    { MODE_PORTRAIT,           32781 },
    { MODE_STITCH,             33290 },

    // the following match a540 and ixus60
    { MODE_SCN_KIDS_PETS,      16399 }, // "kids and pets"
    { MODE_SCN_INDOOR,         16400 }, // "indoor"
    { MODE_SCN_FOLIAGE,        16401 }, // "foliage"
    { MODE_SCN_SNOW,           16402 }, // "snow"
    { MODE_SCN_BEACH,          16403 }, // "beach"
    { MODE_SCN_FIREWORK,       16404 }, // "fireworks"
    { MODE_SCN_UNDERWATER,     16405 }, // "under water"
    { MODE_SCN_COLOR_ACCENT,   16920 }, // "color accent"
    { MODE_SCN_COLOR_SWAP,     16921 }, // "color swap"

    { MODE_DIGITAL_MACRO,      33288 }, // ixus60
    { MODE_NIGHT_SNAPSHOT,     32779 }, // ixus60
    { MODE_LONG_SHUTTER,       32774 }, // guessed

    // guessed, match a540 and ixus60
    { MODE_VIDEO_STD,          2593  },
    { MODE_VIDEO_SPEED,        2594  },
    { MODE_VIDEO_COMPACT,      2595  },
    { MODE_VIDEO_COLOR_ACCENT, 2591  },
    { MODE_VIDEO_COLOR_SWAP,   2592  },
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
    if (get_target_file_num()%100 == 1) ++n;
    return n;
}

int circle_of_confusion = 6;

void change_video_tables(int a, int b)
{
}

char* shooting_get_tv_str()
{
    short int tvv;
    long i;
    
    _GetPropertyCase(PROPCASE_TV, &tvv, sizeof(tvv));

    for (i=0;i<SS_SIZE;i++)
    {
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

    for (i = 0; i < AS_SIZE-1; i++)
    {
        if (aperture_sizes_table[i].prop_id <= avv && aperture_sizes_table[i+1].prop_id > avv)
          return (char*)aperture_sizes_table[i].name;
    }
    return (char*) "?";
}
