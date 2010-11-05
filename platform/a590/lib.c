#include "platform.h"
extern void my_debug_led();
void shutdown()
{

    volatile long *p = (void*)0xc02200a0;
        
    asm(
         "MRS     R1, CPSR\n"
         "AND     R0, R1, #0x80\n"
         "ORR     R1, R1, #0x80\n"
         "MSR     CPSR_cf, R1\n"
         :::"r1","r0");
        
    *p = 0x44;
	
	while(1);
}


#define LED_PR 0xc02200C4

void debug_led(int state)
{
    volatile long *p=(void*)LED_PR;
    if (state)
	p[0]=0x46;
    else
	p[0]=0x44;
}

#define LED_AF 0xc0220080

int get_flash_params_count(void){
 return 114;
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
