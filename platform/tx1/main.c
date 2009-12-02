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

#if 0
int rec_switch_state(void) {
//    mode  = (physw_status[1] & 0x08000000)?MODE_REC:MODE_PLAY; 
    return (physw_status[1] & 0x08000000); 
}
#endif
// TODO this camera defines CAM_SWIVEL_SCREEN but screen position checks didn't exist in mode_get()
int screen_opened(void) {
	return 0;
}

int screen_rotated(void) {
	return 0;
}
