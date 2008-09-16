#ifndef SHOT_HISTOGRAM_H
#define SHOT_HISTOGRAM_H

extern unsigned short shot_histogram[1024];
extern unsigned short shot_margin_left, shot_margin_top, shot_margin_right, shot_margin_bottom;

void build_shot_histogram();

int shot_histogram_get_range(int histo_from, int histo_to);

#define SHOT_HISTOGRAM_STEP 31
#define SHOT_HISTOGRAM_MARGIN 100

#endif
