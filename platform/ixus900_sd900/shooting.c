#include "platform.h"

// Camera Parameter of Image Filenumber
// wrong PARAM_FILE_COUNTER cause camera shutdown if RAW is enabled or wrong number in RAW filename (for example always CRW_0001.CRW)
// use "Debug Paramenters -> Debug data display -> Params" to verify
// 0x6D = 109, count of available Camera Parameter
#define PARAM_FILE_COUNTER      0x34

// PROPCASE_AV (68)
// Take a picture with the camera at every zoom step and note each PROPCASE_AV value. Repeat former steps but focus at an very bright light source where camera puts in ND filter (focus a lamp bulp for example). Look at EXIF data from your picture to get correspondig Aperture value.
const ApertureSize aperture_sizes_table[] = {
    { 9, 294, "2.8"},   // Zoom 2.8x, without ND
    {10, 309, "3.2"},
    {11, 328, "3.5"},
    {12, 353, "3.5"},
    {13, 385, "4.0"},
    {14, 416, "4.5"},
    {15, 449, "4.9"},   // Zoom 4.9x, without ND
    {16, 556, "8.0 ND"},   // Zoom 2.8x , with ND (very bright)
    {17, 571, "8.0 ND"},
    {18, 590, "9.0 ND"},
    {19, 615, "10.0 ND"},
    {20, 647, "11.0 ND"},
    {21, 678, "13.0 ND"},
    {22, 711, "14.1 ND"},   // Zoom 4.9x , with canon ND (very bright)
};

// PROPCASE_TV (69)
// This values are more or less generic. Look for max. supported Shutter speed "1/2000" at technical specs for the camera.
// ROM:FF9AFCCC
const ShutterSpeed shutter_speeds_table[] = {
    // # , PropCase value, displayed string, shutter value
    {-12, -384, "15", 15000000},   // PROPCASE_TV = 65152, 1000000 * 15 = 15000000
    {-11, -352, "13", 13000000},   // 65184
    {-10, -320, "10", 10000000},   // 65218
    { -9, -288, "8",   8000000},   // 65248
    { -8, -256, "6",   6000000},   // 65280
    { -7, -224, "5",   5000000},   // 65312
    { -6, -192, "4",   4000000},   // 65344
    { -5, -160, "3.2", 3200000},   // 65376
    { -4, -128, "2.5", 2500000},   // 65408
    { -3,  -96, "2",   2000000},   // 65440
    { -2,  -64, "1.6", 1600000},   // 65472
    { -1,  -32, "1.3", 1300000},   // 65504
    {  0,    0, "1",   1000000},   // PROPCASE_TV = 0
    {  1,   32, "0.8",  800000},   // PROPCASE_TV = 32, 1000000 / 0.8 = 800000
    {  2,   64, "0.6",  600000},   // ...
    {  3,   96, "0.5",  500000},
    {  4,  128, "0.4",  400000},
    {  5,  160, "0.3",  300000},
    {  6,  192, "1/4",  250000},
    {  7,  224, "1/5",  200000},
    {  8,  256, "1/6",  166667},
    {  9,  288, "1/8",  125000},
    { 10,  320, "1/10", 100000},
    { 11,  352, "1/13",  76923},
    { 12,  384, "1/15",  66667},
    { 13,  416, "1/20",  50000},
    { 14,  448, "1/25",  40000},
    { 15,  480, "1/30",  33333},
    { 16,  512, "1/40",  25000},
    { 17,  544, "1/50",  20000},
    { 18,  576, "1/60",  16667},
    { 19,  608, "1/80",  12500},
    { 20,  640, "1/100", 10000},
    { 21,  672, "1/125",  8000},
    { 22,  704, "1/160",  6250},
    { 23,  736, "1/200",  5000},
    { 24,  768, "1/250",  4000},
    { 25,  800, "1/320",  3125},
    { 26,  832, "1/400",  2500},
    { 27,  864, "1/500",  2000},
    { 28,  896, "1/640",  1563},
    { 29,  928, "1/800",  1250},
    { 30,  960, "1/1000", 1000},
    { 31,  992, "1/1250",  800},
    { 32, 1024, "1/1600",  625},
    { 33, 1056, "1/2000",  500},
};

// PROPCASE_ISO_MODE (25/26)
// go through every ISO setting in manual mode and note PROPCASE_ISO_MODE value.
const ISOTable iso_table[] = {
    {-1,     1,    "HI", -1},
    { 0,     0,  "Auto", -1},
    { 1,    80,    "80", -1},
    { 2,   100,   "100", -1},
    { 3,   200,   "200", -1},
    { 4,   400,   "400", -1},
    { 5,   800,   "800", -1},
    { 6,  1600,  "1600", -1},
};

/*
http://www.usa.canon.com/cusa/support/consumer/digital_cameras/powershot_sd_series/powershot_sd900#Specifications
Shooting Modes:
    Auto, Camera M,
    Special Scene (Portrait, Foliage, Snow, Beach, Fireworks, Aquarium, Underwater, ISO 3200, Indoor, Kids & Pets, Night Snapshot),
    Color Accent, Color Swap, Digital Macro, Stitch Assist, Movie

    Still Image: 640 x 480 (Small), 1,600 x 1,200 (Medium 3), 2,272 x 1,704 (Medium 2), 2,816 x 2,112 (Medium 1), 3,648 x 2,736 (Large), 3,648 x 2,048 (Widescreen)
    Movie: 640 x 480 / 320 x 240 (30 fps/15 fps) available up to 4GB or 1 hour for each file size, 1,024 x 768 (15 fps), 160 x 120 (3 min. at 15 fps)
*/

// PROPCASE 49
// Mapping between camera mode and PROPCASE_SHOOTING_MODE
static const CapturemodeMap modemap[] = {   // PROPCASE 0, check with CHDK debug menu option "Show Parameter Data 0"
    {MODE_AUTO,               32768},
    {MODE_M,                  33772},
    {MODE_DIGITAL_MACRO,      33288},
    {MODE_STITCH,             33290},
    {MODE_COLOR_ACCENT,       33305},
    {MODE_MY_COLORS,          33306},   // mode M "color swap" ???
    {MODE_NIGHT_SNAPSHOT,     16395},   // mode SCN NIGHT SNAPSHOT ???
    //{MODE_SCN_NIGHT,          16395},   // mode SCN NIGHT SNAPSHOT ???
    {MODE_SCN_PORTRAIT,       16397},
    {MODE_SCN_KIDS_PETS,      16399},
    {MODE_SCN_INDOOR,         16400},
    {MODE_SCN_FOLIAGE,        16401},
    {MODE_SCN_SNOW,           16402},
    {MODE_SCN_BEACH,          16403},
    {MODE_SCN_FIREWORK,       16404},
    //{MODE_SCN_WATER,          16405},   // old?
    {MODE_SCN_UNDERWATER,     16405},   // ToDo: verify if correct
    {MODE_SCN_AQUARIUM,       16406},
    {MODE_SCN_ISO_3200,       16411},
    {MODE_VIDEO_STD,          2596},
    {MODE_VIDEO_COLOR_ACCENT, 2594},
    {MODE_VIDEO_COLOR_SWAP,   2595},
    {MODE_VIDEO_COMPACT,      2598},
    {MODE_VIDEO_HIRES,        2599},
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

int circle_of_confusion = 5;    // :-)

// compare PROPCASE_TV with shutter_speeds_table
char* shooting_get_tv_str() {
    short int tvv;
    long i;
    _GetPropertyCase(PROPCASE_TV, &tvv, sizeof(tvv));
    for(i=0; i<SS_SIZE; i++) {
        if(shutter_speeds_table[i].prop_id >= tvv)
            return (char*)shutter_speeds_table[i].name;
    }
    return (void*)"?";
}

// compare PROPCASE_AV with aperture_sizes_table
char* shooting_get_av_str() {
    short int avv;
    long i;
    _GetPropertyCase(PROPCASE_AV, &avv, sizeof(avv));
    for(i=0; i<AS_SIZE; i++) {
        if(aperture_sizes_table[i].prop_id == avv)
            return (char*)aperture_sizes_table[i].name;
    }
    return (char*) "?";
}

