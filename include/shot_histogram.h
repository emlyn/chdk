#ifndef SHOT_HISTOGRAM_H
#define SHOT_HISTOGRAM_H

int shot_histogram_set(int enable);
int shot_histogram_isenabled();
void build_shot_histogram();

int shot_histogram_get_range(int histo_from, int histo_to);

#define SHOT_HISTOGRAM_STEP 31
#define SHOT_HISTOGRAM_MARGIN 100

#endif
