#include "keyboard.h"
#include "conf.h"
#include "platform.h"
#include "../generic/wrappers.c"

long lens_get_focus_pos()
{
    static long v=MAX_DIST;
    return (kbd_is_key_pressed(KEY_SHOOT_HALF) || state_kbd_script_run  || shooting_get_common_focus_mode())?v=_GetFocusLensSubjectDistance():v;
//  return _GetFocusLensSubjectDistance();
}

long lens_get_focus_pos_from_lens()
{
    static long v=MAX_DIST;
    return (kbd_is_key_pressed(KEY_SHOOT_HALF) || state_kbd_script_run  || shooting_get_common_focus_mode())?v=_GetFocusLensSubjectDistanceFromLens():v;
}

long lens_get_target_distance()
{
    static long v=MAX_DIST;
    return (kbd_is_key_pressed(KEY_SHOOT_HALF) || state_kbd_script_run  || shooting_get_common_focus_mode())?v=_GetCurrentTargetDistance():v;
// return _GetCurrentTargetDistance();
}
