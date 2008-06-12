#include "platform.h"

void *hook_raw_fptr()
{
	return (void*)0; // What does this do? Doesn't seem to be called
}

void *hook_raw_ret_addr()
{
	return (void*)0; // What does this do? Doesn't seem to be called
}

char *hook_raw_image_addr()
{
	// Found at ROM:FFA11E84
	// Search for aCrawBuffP and search backwards for the second printf argument
	// ROM:FFA11E84   LDR     R6, =0x1163B8E0
	// .....
	// ROM:FFA11ED4   MOV     R1, R6
	// ROM:FFA11ED8   ADR     R0, aCrawBuffP  @ "CRAW BUFF       %p"
	// ROM:FFA11EDC   BL      sub_FFA13590

	return (char*)0x1163B8E0;
}

long hook_raw_size()
{
	// Found at ROM:FFA11EE0
	// Search for aCrawBuffSizeP, take value from second printf argument
	// ROM:FFA11EE0   LDR     R1, =0x9DCCE0
	// ROM:FFA11EE4   ADR     R0, aCrawBuffSizeP @ "CRAW BUFF SIZE  %p"
	// ROM:FFA11EE8   BL      sub_FFA13590
	
	return 0x9DCCE0;
}

void *vid_get_viewport_live_fb()
{
	// Deprecated, still exists for historical reasons.
	// Should return null pointer.
	
	return (void*)0x0;
}

void *vid_get_bitmap_fb()
{
	// Found at ROM:FF912380
	// Search for BmpDDev.c
	
	return (void*)0x10361000; 
}

void *vid_get_viewport_fb()
{
	// Found at ROM:FFA103D8
	// Search for aVramAddressP
	// ROM:FFA103D8   LDR     R1, =0x10D29360
	// ROM:FFA103DC   LDR     R0, =0x7E900
	// ROM:FFA103E0   STR     R1, [R4]
	// ROM:FFA103E4   STR     R0, [R4,#4]
	// ROM:FFA103E8   ADR     R0, aVramAddressP @ "VRAM Address  : %p\r"

	return (void*)0x10D29360;
}

void *vid_get_viewport_fb_d()
{
	// Found in sub_FF85B3FC (unsure, seems to do the same as this function)
	// Search for aImageplayer_c to get at least the base value (0x56D8)
	// ROM:FF85B3FC   LDR     R0, =0x56D8
	// ROM:FF85B400   LDR     R0, [R0,#0x4C]
	// ROM:FF85B404   BX      LR

	return (void*)(*(int*)0x5724);  // 0x56D8 + 0x4C
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
	// Found at ROM:FF9BE548.
	// Search for a9999
	// ROM:FF9BE548   LDR     R0, =0x58304
	// ROM:FF9BE54C   ADR     R1, a9999       @ "9999"
	// ROM:FF9BE550   BL      sprintf
	
	return (char*)0x58304;
}





long vid_get_bitmap_buffer_width() { return 360; }

long vid_get_bitmap_buffer_height() { return 240; }
