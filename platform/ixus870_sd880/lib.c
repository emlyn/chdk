#include "platform.h"
#include "lolevel.h"

void vid_bitmap_refresh()
{
 extern int enabled_refresh_physical_screen; // screen lock counter
 int old_val = enabled_refresh_physical_screen;
 if ( old_val == 0 )
 {
   _ScreenLock(); // make sure code is called at least once
 } else {
   enabled_refresh_physical_screen=1; // forces actual redraw
 }
 _RefreshPhysicalScreen(1); // unlock/refresh

 // restore original situation
 if ( old_val > 0 )
 {
   _ScreenLock();
   enabled_refresh_physical_screen = old_val;
 }
}


void shutdown()
{
	volatile long *p = (void*)0xC022001C; // from sub_FF829230 (e.g. called at end of task_Bye)

        // based on IRQdisable (why use CPSR_cf instead of CPSR_cxsf?)
	asm(
		"MRS     R1, CPSR\n"
		"AND     R0, R1, #0x80\n"
		"ORR     R1, R1, #0x80\n"
		"MSR     CPSR_cf, R1\n"
		:::"r1","r0");
	
	*p = 0x44;  // power off.
	
	while(1); // no nothing while power is being switched off
}

void debug_led(int state)
{
 // using direct-print led for debugging
 *((int*) 0xC02200D4) = state ? 0x46 : 0x44;
}

void ubasic_set_led(int led, int state, int bright) {
  // approximation of behaviour advertised in documentation.
  long val = state ? 0x46 : 0x44;
  switch ( led )
  {
    case 4:
      *((volatile long *) 0xC0220136) = val;
      break;
    case 5:
      *((volatile long *) 0xC0220136) = val;
      *((volatile long *) 0xC0220133) = val;
      break;
    case 7:
      *((volatile long *) 0xC0220133) = val;
      break;
    case 8:
      *((volatile long *) 0xC02200D4) = val;
      break;
    case 9:
      *((volatile long *) 0xC0223030) = val;
      break;
    default:
      break;
  }
}

int get_flash_params_count(void){
 // Size of table at FlashParamTable (stubs_min.S)
 // ( <first unk_ after FlashParamTable> - FlashParamTable ) / 4
 return 120; 
}

void JogDial_CW(void){
 _PostLogicalEventForNotPowerType(0x874, 2);  // RotateJogDialRight
}

void JogDial_CCW(void){
 _PostLogicalEventForNotPowerType(0x875, 2);  // RotateJogDialLeft
}

void vid_turn_off_updates()
{
  _ScreenLock();
}

void vid_turn_on_updates()
{
  _RefreshPhysicalScreen(1);
}

extern void _set_control_event(int);
extern void _PB2Rec();
extern void _Rec2PB();
int switch_mode_usb(int mode)
{
  if ( mode == 0 )
  {
    _Rec2PB();
    _set_control_event(0x80000902); // 0x10A5 ConnectUSBCable
  } else if ( mode == 1 )
  {
    _set_control_event(0x902); // 0x10A6 DisconnectUSBCable
    _PB2Rec();
  } else {
    return 0;
  }

  return 1;
}
