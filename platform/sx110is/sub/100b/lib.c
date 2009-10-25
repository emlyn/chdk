#include "platform.h"

char *hook_raw_image_addr()
{
//found 0x11A34C40 at 0xFFC3C948 and 0x10805040 at FFC7D80C
// not for sure: 53A4 at 0xFFC51A60 and 0x53A4+0x18 at 0xFFC518D4
	return (char*) (*(int*)(0x53A4+0x18) ? 0x11A34C40 : 0x10805040);	
}

long hook_raw_size()
{
   //      ROM:FFE60BB4                 LDR     R1, =0xEC04F0
   return 0xEC04F0;
}


void *vid_get_viewport_live_fb()
{
   void **fb=(void **)0x21a0; //ROM:FFC285D0 dword_FFC285D0  DCD 0x21A0, look also at ROM:FFC27FF0
   unsigned char buff = *((unsigned char*)0x2014); //ROM:FFC285C8 dword_FFC285C8  DCD 0x2014    , look also at ROM:FFC27FA0
    if (buff == 0) buff = 2;  else buff--;
    return fb[buff];
}

void *vid_get_bitmap_fb()
{
    return (void*)0x10361000;		// found at some addresses e.g. 0xffc32078 or 0xFFDD97B8 , guided by sx100 an a720 and sx10
}

void *vid_get_viewport_fb()
{
    return (void*)0x10659DE0; // found at some addresses e.g. 0xffe5ea50 , guided by sx100 and a720 ans sx10
}

void *vid_get_viewport_fb_d()
{
    return (void*)(*(int*)0x5114);   //0x50C0 + 0x54, 0x50C0 found at 0xFFC45E78 and look at 0xffc46568/0xFFC46594
}


long vid_get_bitmap_screen_width()
{
    return 360;
}

long vid_get_bitmap_screen_height()
{
    return 240;
}

long vid_get_viewport_height()
{
    return 240;
}
char *camera_jpeg_count_str()
{
	// Found at ROM:FFD84BC0	
 return (void*)0x45E58;
}

long vid_get_bitmap_buffer_width() { return 360; }

long vid_get_bitmap_buffer_height() { return 240; }

/*
GetBatteryTemperature usually will get back temperature of battery compartment/batteries. GetBatteryTemperature is implemented in Canon's firmware for SX110is.
Firmware entry point is identified (0xffc3885c) but function is not usable. Camera will crash if Canon's GetBatteryTemperature is called by CHDK.
To avoid a crash Canon's GetBatteryTemperature must not called. As long CHDK general code do not distinguish between cameras that support or don't support GetBatteryTemperature, 
this function will be implemented as specific CHDK-code. It returns always with -99 (which means -99° Celsius or -146° Fahrenheit).
Original entry point in Canon's firmware is disabled (in stubs_entry.S).
*/

int _GetBatteryTemperature()
{
      return -99;
}

