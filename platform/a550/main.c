//A540 + A560

#include "../generic/main.c"

long get_vbatt_min()
{
	return 2100;
}

long get_vbatt_max()
{
	return 2800;
}

static const int fl_tbl[] =
{ 5800, 6600, 7900, 9900, 12700, 16000, 19600, 23200 };
#define NUM_FL (sizeof(fl_tbl)/sizeof(fl_tbl[0]))
#define CF_EFL 60345

const int zoom_points= NUM_FL;

int get_effective_focal_length(int zp)
{
	return (CF_EFL*get_focal_length(zp))/10000;
}

int get_focal_length(int zp)
{
	if (zp<0)
		return fl_tbl[0];
	else if (zp>NUM_FL-1)
		return fl_tbl[NUM_FL-1];
	else
		return fl_tbl[zp];
}

int get_zoom_x(int zp)
{
	if (zp<1)
		return 10;
	else if (zp>NUM_FL-1)
		return fl_tbl[NUM_FL-1]*10/fl_tbl[0];
	else
		return fl_tbl[zp]*10/fl_tbl[0];
}

static struct
{
	int hackmode;
	int canonmode;
} modemap[] =
{
		{ MODE_AUTO, 32768 },
		{ MODE_P, 32772 },
//  { MODE_M,                  32769 },
		{ MODE_VIDEO_STD, 2597 },
		{ MODE_VIDEO_SPEED, 2598 },
		{ MODE_VIDEO_COMPACT, 2599 },
		{ MODE_SCN_AQUARIUM, 16407 },
		{ MODE_SCN_NIGHT, 16398 },
		{ MODE_SCN_GRASS, 16402 },
		{ MODE_SCN_SNOW, 16403 },
		{ MODE_SCN_BEACH, 16404 },
		{ MODE_SCN_FIREWORK, 16405 },
		{ MODE_INDOOR, 32785 },
		{ MODE_KIDS_PETS, 32784 },
		{ MODE_NIGHT_SNAPSHOT, 32779 },
		{ MODE_LANDSCAPE, 32780 },
		{ MODE_PORTRAIT, 32781 }, 
};
#define MODESCNT (sizeof(modemap)/sizeof(modemap[0]))

int mode_get()
{
	int mode, i, t=0xFF;

	_GetPropertyCase(219, &t, 4);
	//mode = (playrec_mode==1 || playrec_mode==2) ? MODE_REC : MODE_PLAY;	// a560																					
	mode = (physw_status[1] & 0x00000040) ? MODE_REC : MODE_PLAY; //eb5ccdc0 ( 110111000000 ):eb5cc980 ( 100110000000 )
	mode |= (t == 270) ? MODE_SCREEN_ROTATED : 0;
	//mode |= (physw_status[2] & 0x00008000)?0:MODE_SCREEN_OPENED;
	//mode |= (physw_status[2] & 0x00004000)?0:MODE_SCREEN_ROTATED;

	_GetPropertyCase(PROPCASE_SHOOTING_MODE, &t, 4);
	for (i=0; i<MODESCNT; ++i)
	{
		if (modemap[i].canonmode == t)
		{
			return (mode | (modemap[i].hackmode & MODE_SHOOTING_MASK));
		}
	}
	return (mode);
}
