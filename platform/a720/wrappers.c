#include "../generic/wrappers.c"

long lens_get_focus_pos()
{
    //return _GetFocusLensSubjectDistance();    // returns plaintext, calls GetCurrentTargetDistance to get value
    return _GetCurrentTargetDistance(); 
}

long lens_get_target_distance()
{
    return _GetCurrentTargetDistance();
}
