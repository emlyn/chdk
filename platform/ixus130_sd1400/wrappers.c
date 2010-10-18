#include "../generic/wrappers.c"

long lens_get_focus_pos()
{
	//return _GetFocusLensSubjectDistance();    // returns plaintext, calls GetCurrentTargetDistance to get value
	return _GetCurrentTargetDistance(); 
}

long lens_get_focus_pos_from_lens()
{
	return _GetCurrentTargetDistance(); 
	//return _GetFocusLensSubjectDistanceFromLens(); 
}

long lens_get_target_distance()
{
	return _GetCurrentTargetDistance();
}

// Prevent warning: implicit declaration of function `_OpLog_Get'
extern long _OpLog_Get(long i);

//VERIFY_SD780 Only one arg?
long OpLog_Get(long i)
{
	return _OpLog_Get(i);
}
