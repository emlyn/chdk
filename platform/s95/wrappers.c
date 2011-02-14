#include "../generic/wrappers.c"

#define RAND_MAX 0x7fffffff


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


// S95 firmware does not include rand(), srand() so we add them here

static unsigned int next = 1;

int rand_r(unsigned int *seed)
{
	*seed = *seed * 1103515245 + 12345;
	return (*seed % ((unsigned int) RAND_MAX + 1));
}

int _rand(void)
{
	return (rand_r(&next));
}

void* _srand(unsigned int seed)
{
	next = seed;
	return 0;				// unused return value
}
