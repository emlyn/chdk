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
	 
	//ERR99: TODO G11
    //return _GetCurrentTargetDistance();
	return 0;
}


