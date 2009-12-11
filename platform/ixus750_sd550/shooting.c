#define PARAM_FILE_COUNTER      0x2F // via debug parameters 

#include "platform.h"

const ApertureSize aperture_sizes_table[] = {
    {  9, 294, "2.8" },
    { 10, 309, "3.2" },
    { 11, 328, "3.5" },
    { 12, 353, "3.5" },
    { 13, 385, "4.0" },
    { 14, 384, "4.0" },
    { 15, 416, "4.5" },
    { 16, 449, "4.9" },
    { 17, 545, "7.1" },
    { 18, 560, "7.1" },
    { 19, 579, "8.0" },
    { 20, 604, "9.0" },
    { 21, 636, "10" },
    { 22, 667, "11" },
    { 23, 700, "13" },

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
    {  35, 1117, "1/3200",  313 },
};

const ISOTable iso_table[] = {
    {  0,    0, "Auto", -1},
    {  1,   50,   "50", -1},
    {  2,  100,  "100", -1},
    {  3,  200,  "200", -1},
    {  4,  400,  "400", -1},
};          

/*
http://www.usa.canon.com/consumer/controller?act=ModelInfoAct&tabact=ModelTechSpecsTabAct&fcategoryid=224&modelid=12466
Shooting Modes
    Auto; Manual,
    Special Scene
        (Portrait, Foliage, Snow, Beach, Fireworks, Underwater, Indoor,
        Kids & Pets, Night Snapshot),
    Digital Macro, My Colors, Stitch Assist, Movie
Movie: 640 x 480/320 x 240 (30 fps/15 fps) available up to 1GB, 
    320 x 240 (1 min. at 60 fps), 160 x 120 (3 min. at 15 fps)
canon mode list FF960434 in 100f
*/
static const CapturemodeMap modemap[] = {
    { MODE_P,                   0 }, // guessed!
    { MODE_LONG_SHUTTER,        1 }, // guessed!
    { MODE_DIGITAL_MACRO,       2 },
    { MODE_MY_COLORS,           3 },
    { MODE_STITCH,             	4 },
    { MODE_AUTO,                5 },
    { MODE_SCN_PORTRAIT,        6 },
    { MODE_SCN_FOLIAGE,         7 },
    { MODE_SCN_SNOW,            8 },
    { MODE_SCN_BEACH,           9 },
    { MODE_SCN_UNDERWATER,     10 },
    { MODE_SCN_INDOOR,         11 },
    { MODE_SCN_NIGHT_SNAPSHOT, 12 },
    { MODE_SCN_KIDS_PETS,      13 },
    { MODE_SCN_FIREWORK,       14 }, 
    { MODE_VIDEO_STD,          15 }
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

int circle_of_confusion = 6;

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

