#include "../generic/wrappers.c"

long lens_get_focus_pos()
{
    return _GetFocusLensSubjectDistance();
}
//ARM BEGIN
//long lens_get_focus_pos_fl()
//{
//    return _GetFocusLensSubjectDistanceFromLens();
//}
//ARM END

long lens_get_target_distance()
{
    return _GetCurrentTargetDistance();
}
