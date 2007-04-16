#include "lolevel.h"
#include "platform.h"
#include "core.h"
#include "keyboard.h"
#include "math.h"

const ApertureSize aperture_sizes_table[] = {
    {  9, 288, "2.8", },
    { 10, 320, "3.2", },
    { 11, 352, "3.5", },
    { 12, 384, "4.0", },
    { 13, 416, "4.5", },
    { 14, 448, "5.0", },
    { 15, 480, "5.6", },
    { 16, 512, "6.3", },
    { 17, 544, "7.1", },
    { 18, 576, "8.0", },
};

const ShutterSpeed shutter_speeds_table[] = {
    {-13, -384, "15", 15000000  },
    {-12, -352, "13", 13000000  },
    {-11, -320, "10", 10000000  },
    {-9, -288, "8", 8000000  },
    {-8, -256, "6", 6000000  },
    {-7, -224, "5", 5000000  },
    {-6, -192, "4", 4000000  },
    {-5, -160, "3.2", 3200000  },
    {-4, -128, "2.5", 2500000  },
    {-3, -96 , "2", 2000000  },
    {-2, -64 , "1.6", 1600000  },
    {-1, -32 , "1.3", 1300000  },
    { 0, 0, "1", 1000000  },
    { 1, 32, "0.8", 800000 },
    { 2, 64, "0.6", 600000 },
    { 3, 96, "0.5", 500000 },
    { 4, 128, "0.4", 400000 },
    { 5, 160, "0.3", 300000 },
    { 6, 192, "1/4", 250000 },
    { 7, 224, "1/5", 200000 },
    { 8, 256, "1/6", 166667 },
    { 9, 288, "1/8", 125000 },
    {10, 320, "1/10", 100000 },
    {11, 352, "1/13",  76923 },
    {12, 384, "1/15",  66667 },
    {13, 416, "1/20",  50000 },
    {14, 448, "1/25",  40000 },
    {15, 480, "1/30",  33333 },
    {16, 512, "1/40",  25000 },
    {17, 544, "1/50",  20000 },
    {18, 576, "1/60",  16667 },
    {19, 608, "1/80",  12500 },
    {20, 640, "1/100",  10000 },
    {21, 672, "1/125",   8000 },
    {22, 704, "1/160",   6250 },
    {23, 736, "1/200",   5000 },
    {24, 768, "1/250",   4000 },
    {25, 800, "1/320",   3125 },
    {26, 832, "1/400",   2500 },
    {27, 864, "1/500",   2000 },
    {28, 896, "1/640",   1563 },
    {30, 928, "1/800",   1250 },
    {31, 960, "1/1000",   1000 },
    {32, 992, "1/1250",    800 },
    {33, 1021, "1/1600",    625 },
    {34, 1053, "1/2000",    500 },
    {35, 1084, "1/2500",    400 },
};

const ISOTable iso_table[] = {
    {0, 50,   "50", -1},
    {1, 100, "100", -1},
    {2, 200, "200", -1},
    {3, 400, "400", -1},
};

#define SS_SIZE (sizeof(shutter_speeds_table)/sizeof(shutter_speeds_table[0]))
#define SSID_MIN (shutter_speeds_table[0].id)
#define SSID_MAX (shutter_speeds_table[SS_SIZE-1].id)

#define AS_SIZE (sizeof(aperture_sizes_table)/sizeof(aperture_sizes_table[0]))
#define ASID_MIN (aperture_sizes_table[0].id)
#define ASID_MAX (aperture_sizes_table[AS_SIZE-1].id)

#define ISO_SIZE (sizeof(iso_table)/sizeof(iso_table[0]))
#define ISO_MIN (iso_table[0].id)
#define ISO_MAX (iso_table[ISO_SIZE-1].id)

int shooting_get_tv()
{
    short int tvv;
    long i;
    _GetPropertyCase(40, &tvv, sizeof(tvv));
    for (i=0;i<SS_SIZE;i++){
	if (shutter_speeds_table[i].prop_id == tvv)
	    return shutter_speeds_table[i].id;
    }
    return 0;
}

const ShutterSpeed *shooting_get_tv_line()
{
    short int tvv;
    long i;
    _GetPropertyCase(40, &tvv, sizeof(tvv));
    for (i=0;i<SS_SIZE;i++){
	if (shutter_speeds_table[i].prop_id == tvv)
	    return &shutter_speeds_table[i];
    }
    return 0;

}

void shooting_set_tv(int v)
{
    long i;
//    if ((v<SSID_MIN) || (v>SSID_MAX))
//	return;


    for (i=0;i<SS_SIZE;i++){
	if (shutter_speeds_table[i].id == v){
	    short int vv = shutter_speeds_table[i].prop_id;
	    _SetPropertyCase(40, &vv, sizeof(vv));
	    return;
	}
    }

}

void shooting_set_tv_rel(int v)
{
    int cv = shooting_get_tv();
    shooting_set_tv(cv+v);
}

int shooting_get_av()
{
    short int avv;
    long i;
    _GetPropertyCase(39, &avv, sizeof(avv));
    for (i=0;i<AS_SIZE;i++){
	if (aperture_sizes_table[i].prop_id == avv)
	    return aperture_sizes_table[i].id;
    }
    return 0;
}

int shooting_get_real_av()
{
#if 1
    short int avv = 0;
    _GetPropertyCase(68, &avv, sizeof(avv));
    return (int)(((double)pow(1.4142135623730950488016887242097/* sqrt(2) */, ((double)avv)/96.0))*100.0);
#else
    return (int)(((double)pow(1.4142135623730950488016887242097/* sqrt(2) */, ((double)_GetCurrentAvValue())/96.0))*100.0);
#endif
}

void shooting_set_av(int v)
{
    long i;

//    if ((v<ASID_MIN) || (v>ASID_MAX))
//	return;

    for (i=0;i<AS_SIZE;i++){
	if (aperture_sizes_table[i].id == v){
	    short int vv = aperture_sizes_table[i].prop_id;
	    _SetPropertyCase(39, &vv, sizeof(vv));
	    return;
	}
    }
}

void shooting_set_av_rel(int v)
{
    int cv = shooting_get_av();
    shooting_set_av(cv+v);
}

int shooting_in_progress()
{
    int t = 0;
    _GetPropertyCase(205, &t, 4);
    return t != 0;
}

int shooting_is_flash_ready()
{
    int t = 0;
/* well, I'm not sure what's exactly is happening here
 * but it works for a610-100e
 */
    _GetPropertyCase(204, &t, 4);
    if (t == 3){
	_GetPropertyCase(221, &t, 4);
	return (t==1) && _IsStrobeChargeCompleted();
    }
    return 1;
}

long get_file_counter()
{
#ifndef PARAM_FILE_COUNTER
#	error Please define PARAM_FILE_COUNTER in platform`s shooting.c!
#endif

    long v = 0;
    get_parameter_data(PARAM_FILE_COUNTER, &v, 4);
    return v;
}

