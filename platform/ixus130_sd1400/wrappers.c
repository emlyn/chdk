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

/*
void camera_set_led(int led, int state, int bright)
{ 
        struct led_control led_c; 
        char convert_table[11]={0,1,2,3,0,2,3,1,8,10,10};  // s3 to a710 (and a720) convert table

        //char convert_table[6]={0,1,2,3,8,10};  // Test a720, values 0-5 are valid

        // 0 gr  
        // 1 red 
        // 2 yel 
        // 3 pw  
        // 8 dp  
        // 9 af  

        led_c.led_num=convert_table[led%11]; 
        led_c.action=state<=1 ? !state : state; 
        led_c.brightness=bright; 
        led_c.blink_count=255; 
        _PostLEDMessage(&led_c); 
} 
*/

