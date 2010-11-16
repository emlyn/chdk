#include "../generic/wrappers.c"

long lens_get_focus_pos()
{
    return _GetFocusLensSubjectDistance();
}

long lens_get_focus_pos_from_lens()
{
    return _GetFocusLensSubjectDistanceFromLens(); 
}


long lens_get_target_distance()
{
    return _GetCurrentTargetDistance();
}


void camera_set_led(int led, int state, int bright)
{
        // 0 gr  
        // 1 orange 
        // 2 yel 
        // 8 dp  
        // 9 af  

  int leds[] = {0,2,8,1,8,9};
  if(led < 4 || led > 9 || led == 6) return;
  _LEDDrive(leds[led-4], state<=1 ? !state : state);
} 


