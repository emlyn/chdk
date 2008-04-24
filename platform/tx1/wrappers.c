#include "../generic/wrappers.c"

long lens_get_focus_pos()
{
    return _GetFocusLensSubjectDistance();
}

long lens_get_focus_pos_from_lense()
{
    return _GetFocusLensSubjectDistanceFromLens();
}

long lens_get_target_distance()
{
    return _GetCurrentTargetDistance();
}

/*
int PostLEDMessage(LED_CONTROL* led)
{
}
*/
