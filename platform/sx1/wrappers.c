#include "../generic/wrappers.c"

long lens_get_focus_pos()
{
	//return _GetFocusLensSubjectDistance();    // returns plaintext, calls GetCurrentTargetDistance to get value
	return _GetCurrentTargetDistance(); 
}

long lens_get_focus_pos_from_lense()
{
	return _GetCurrentTargetDistance(); 
	//return _GetFocusLensSubjectDistanceFromLens(); 
}

long lens_get_target_distance()
{
	return _GetCurrentTargetDistance();
}
