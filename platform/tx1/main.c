#include "../generic/main.c"


long get_vbatt_min()
{
    return 3550;
}

long get_vbatt_max()
{
    return 4110;
}

static const struct {
    int zp, fl;
} fl_tbl[] = {
    {  0,   6500 },
    {  1,   6803 },
    {  2,   6934 },
    {  3,   7067 },
    {  4,   7203 },
    {  5,   7340 },
    {  7,   7620 },
    {  9,   7908 },
    {  11,  8207 },
    {  14,  8665 },
    {  19,  9472 },
    {  41, 13743 },
    {  64, 20189 },
    {  72, 23145 },
    {  86, 29387 },
    { 105, 40494 },
    { 107, 41960 },
    { 124, 65000 },
};

#define NUM_FL (sizeof(fl_tbl)/sizeof(fl_tbl[0]))
#define CF_EFL 6035 

const int zoom_points = 125;

int get_effective_focal_length(int zp) {
    return (CF_EFL*get_focal_length(zp))/1000; 
}

int get_focal_length(int zp) 
{
    int i;

    if (zp<fl_tbl[0].zp)
        return fl_tbl[0].fl;
    else if (zp>fl_tbl[NUM_FL-1].zp)
        return fl_tbl[NUM_FL-1].fl;
    else 
        for (i=1; i<NUM_FL; ++i) 
       {
           if (zp==fl_tbl[i-1].zp) 
               return fl_tbl[i-1].fl;
           else if (zp==fl_tbl[i].zp) 
               return fl_tbl[i].fl;
           else if (zp<fl_tbl[i].zp)
               return fl_tbl[i-1].fl+(zp-fl_tbl[i-1].zp)*(fl_tbl[i].fl-fl_tbl[i-1].fl)/(fl_tbl[i].zp-fl_tbl[i-1].zp);
        }
    return fl_tbl[NUM_FL-1].fl;
}

int get_zoom_x(int zp) {
    return get_focal_length(zp)*10/fl_tbl[0].fl;
}

static struct {
	int hackmode;
	int canonmode;
} modemap[] = {
    { MODE_AUTO,               32768 },
//    { MODE_M,                  32772 },
    { MODE_P,                  32772 },
    { MODE_SUPER_MACRO,        33289 },
    { MODE_COLOR_ACCENT,       33306 },
    { MODE_MY_COLORS,          33307 },
    { MODE_STITCH,             33290 }, 
    { MODE_SCN_PORTRAIT,       16397 },
    { MODE_SCN_NIGHT,          16395 },
    { MODE_SCN_INDOOR,         16401 },
    { MODE_SCN_FOLIAGE,        16402 },
    { MODE_SCN_SNOW,           16403 },
    { MODE_SCN_BEACH,          16404 },
    { MODE_SCN_AQUARIUM,       16407 },
    { MODE_VIDEO_STD,          33792 },
    { MODE_VIDEO_MANUAL,       33796 },
    { MODE_VIDEO_COLOR_ACCENT, 34330 },
    { MODE_VIDEO_MY_COLORS,    34331 },
    { MODE_VIDEO_STITCH,       34314 },
    { MODE_VIDEO_PORTRAIT,     17421 },
    { MODE_VIDEO_NIGHT,        17419 },
    { MODE_VIDEO_INDOOR,       17425 },
    { MODE_VIDEO_FOLIAGE,      17426 },
    { MODE_VIDEO_SNOW,         17427 },
    { MODE_VIDEO_BEACH,        17428 },
    { MODE_VIDEO_AQUARIUM,     17431 },
    { MODE_VIDEO_SUPER_MACRO,  34313 },
};

#define MODESCNT (sizeof(modemap)/sizeof(modemap[0]))

int mode_get() {
    int mode, i, t=0xFF;

    mode  = (physw_status[1] & 0x08000000)?MODE_REC:MODE_PLAY; 
    _GetPropertyCase(PROPCASE_SHOOTING_MODE /*49*/, &t, 4);
    for (i=0; i<MODESCNT; ++i) {
	if (modemap[i].canonmode == t) {
	    return (mode | (modemap[i].hackmode & MODE_SHOOTING_MASK));
	}
    }
    return (mode);
}
