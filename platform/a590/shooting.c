#define PARAM_FILE_COUNTER      0x38

// DRYOS-Notes:
// propertycase
//   196 - overall brightness (of viewport?)

#include "platform.h"

const ApertureSize aperture_sizes_table[] = {
    {  9, 273, "2.6" },
	{ 10, 288, "2.8" },
    { 11, 320, "3.2" },
    { 13, 352, "3.5" },
    { 13, 384, "4.0" },
    { 14, 416, "4.5" },
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
http://www.usa.canon.com/consumer/controller?act=ModelInfoAct&tabact=ModelTechSpecsTabAct&fcategoryid=221&modelid=16336	
Shooting Modes
	Auto, Easy, P, Av, Tv, M, Portrait, Landscape,
	Special Scene 
		Foliage, Snow, Beach, Sunset, Fireworks, Night Scene, Aquarium
	Indoor, Kids & Pets, Night Snapshot, Movie <- yes, these are dial, not scene!
video resolutions
640 x 480 (20 fps/20 fps LP), 320 x 240 (30 fps) available up to 4GB or 60 minutes,
160 x 120 (3 minutes at 15 fps) 
canon mode list @FFEAED68 in 100e
*/
// PROPCASE 49, verified by whim in http://chdk.setepontos.com/index.php/topic,3228.msg44199.html#msg44199
static const CapturemodeMap modemap[] = {
// common modes
	{ MODE_M,                  32769 },
	{ MODE_TV,                 32771 },
	{ MODE_AV,                 32770 },
    { MODE_P,                  32772 },
    { MODE_AUTO,               32768 },
	{ MODE_PORTRAIT,           32781 },
	{ MODE_INDOOR,             32785 },
	
	{ MODE_KIDS_PETS,          32784 },
	{ MODE_LANDSCAPE,          32780 },
    { MODE_NIGHT_SNAPSHOT,     32779 },
    { MODE_SCN_NIGHT_SCENE,    16398 },
    { MODE_SCN_SUNSET,         16402 },
    { MODE_SCN_FOLIAGE,        16403 },
    { MODE_SCN_SNOW,           16404 },
    { MODE_SCN_BEACH,          16405 },
//    { ???,                   32791 }, in canon mode list, has underwater icon ?
    { MODE_SCN_AQUARIUM,       16408 },
    { MODE_SCN_FIREWORK,       16406 },
    { MODE_VIDEO_STD,           2599 },
    { MODE_VIDEO_COMPACT,       2601 },
    { MODE_EASY,               33311 },
// not in canon list, but set OK 
// 33306 ?
//  2597 note: this was listed as VIDEO_STD in the old mode map,
//       but that is actually 2599 per whims test. Sets compact mode.
// 33288 macro/digital macro ?
//
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
