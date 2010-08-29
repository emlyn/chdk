#ifndef EDGE_OVERLAY_H
#define EDGE_OVERLAY_H

// steps for up/down/left/right moving the overlay in ALT mode
#define XINC 6
#define YINC 2

// if you change this, remember to change the mkdir in main too
#define EDGE_SAVE_DIR "A/CHDK/EDGE"

void edge_overlay();
void save_edge_overlay(void);
void load_edge_overlay( const char* );

#endif
