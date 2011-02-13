#include "platform.h"
	
long vid_get_bitmap_screen_width()		
{		
	return 360 ;				// SD940 103c ?  360
}		
		
long vid_get_bitmap_screen_height()		
{		
	return 240;					// SD940 103c
}		
		
int vid_get_viewport_width()
{
	return 360 ;					// SD940 103c ?
}

long vid_get_viewport_height()		
{		
	return 240;					// SD940 103c
}		

long vid_get_bitmap_buffer_width()	
{		
	return 960;					// SD940 103c
}		
	
long vid_get_bitmap_buffer_height()		
{		
	return 270;					// SD940 103c
}		
		
char *camera_jpeg_count_str()		
{		
	return (char*) 0x700B0;		// SD940 103C search on "9999"
}	

char *hook_raw_image_addr()		
{		
    return (char*)0x4219D120;	// SD940 103c FFAD6FF8 from matching subroutine in S90 101a FFB0254C
								// ... search for aCrawBuffP      DCB "CRAW BUFF       %p",0
}		
		
long hook_raw_size()		
{		
	return 0x11CA240;			// SD940 103c Search for "aCrawBuffSizeP" 

}		
		
void *vid_get_bitmap_fb()		
{		
	return (void*)0x403F1000;  	// SD940 103c @ FF8532DC after DispCon_ShowBlackChart
}		
	
void *vid_get_viewport_live_fb() 	
{		
	return (void*)0;
	/* -------
	void **fb=(void **)0x1043;	// SD940 103C @ FF8D8014
	unsigned char buff = *((unsigned char*)0x497C); 	
	if (buff == 0) buff = 2; else buff-- ;	
	return fb[buff];
	-----  */
}		
		
void *vid_get_viewport_fb()		
{		
	return (void*)0x4088B700;	// SD940 103c from matching subroutine in S90 101a
								// search on VRAM Address  sub @ 9FFAD4910)
}		
		
void *vid_get_viewport_fb_d()		
{		
	return (void*)(*(int*)(0x2790+0x54));  // SD940 103c sub_FF869E34 matched to sub in SD90 101a
	// S940: 0x58 @FF869E74  0x2790 @FF86F9F8 (Search for aImageplayer_c	
	// S90 : return (void*)(*(int*)(0x2A20+0x58));   // G11
	// S90 : 0x58 @FF86FA30  0x2A20 @FF86F9F8 (Search for aImageplayer_c	
}		
			
	
		
