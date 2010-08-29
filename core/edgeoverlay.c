#include "edgeoverlay.h"
#include "platform.h"
#include "conf.h"
#include "keyboard.h"
#include "stdlib.h"
#include "gui_draw.h"
#include "bitvector.h"
 
// the way we save edge overlays on their own...
#define EDGE_FILE_PREFIX "EDG_"
#define EDGE_FILE_FORMAT EDGE_FILE_PREFIX "%04d.edg"
 
typedef enum _edge_fsm_state
{
    EDGE_LIVE = 0,
    EDGE_FROZEN
} edge_fsm_state_t;
 
static edge_fsm_state_t fsm_state = EDGE_LIVE;
static bit_vector_t* edgebuf = NULL;
static int xoffset = 0, yoffset = 0;
 
static int viewport_size;   // whole viewport size in bytes ??
static int viewport_width;      // screenwidth * 3, width in bytes of one viewport line ??
static int viewport_height;
#if CAM_USES_ASPECT_CORRECTION
static int viewportw; //nandoide , width of viewport (not necessarily equal to width of screen)
#endif
  
static void get_viewport_size()
{
    // since screen_height is used in the drawing downwards, we should use it
    // here too to calculate the buffer we need...
 
#if CAM_USES_ASPECT_CORRECTION//nandoide sept-2009 get the viewport dimensions, not the screen dimensions, on sx200is they aren't the same.
    viewport_height = vid_get_viewport_height()-EDGE_HMARGIN*2; //don't trace bottom lines
    viewportw = vid_get_viewport_width();
    viewport_width = viewportw * 3;
    viewport_size = viewport_height * viewport_width;
#else
    viewport_height = screen_height;//vid_get_viewport_height();
    viewport_width = screen_width * 3;
    viewport_size = viewport_height * screen_width * 3;
#endif
}
 
static void ensure_allocate_imagebuffer()
{
    if(edgebuf == NULL)
    {
        edgebuf = bv_create(viewport_size, 1);
    }
}
 
static void reset_edge_overlay()
{
    bv_free(edgebuf);
    edgebuf = NULL;
    fsm_state = EDGE_LIVE;
}
 
static int is_buffer_ready()
{
    if (edgebuf == NULL) return 0;
    if (edgebuf->ptr == NULL) return 0; // this should never happen, but it does not hurt to check
    return 1;
}
 
// scans a filename for the number of the edge detection file it contains
static int get_edge_file_num(const char* fn)
{
    int num = 0;
    if( strncmp(fn,EDGE_FILE_PREFIX,sizeof(EDGE_FILE_PREFIX)-1) == 0 )
    {
        // has the correct beginning at least, now try to read as a number...
        fn += sizeof(EDGE_FILE_PREFIX);
        while( *fn == '0' ) // skip leading 0s
        {
            ++fn;
        }
        while( isdigit(*fn) )
        {
            num *= 10;
            num += *fn - '0';
            ++fn;
        }
        // ignore anything else after it, that is like the ending etc.
    }
    return num;
}
  
// saves the actual active overlay data to a file.
void save_edge_overlay(void)
{
 
    char fn[64];
    char msg[64];
    FILE *fd;
    DIR* d;
    int fnum = 0;
    int fr = 0;
    int zoom = 0;
    struct dirent* de;
    static struct utimbuf t;
    // nothing to save? then dont save
 
    if( !is_buffer_ready() )
    {
        draw_string(0, 0, "No overlay to save.", conf.osd_color);
        return;
    }
 
    zoom = shooting_get_zoom();
 
    // first figure out the most appropriate filename to use
    d = opendir(EDGE_SAVE_DIR);
    if( ! d )
    {
        return;
    }
 
    while( (de = readdir(d)) )
    {
        fr = get_edge_file_num(de->d_name);
        if( fr > fnum )
        {
            fnum = fr;
        }
    }
    ++fnum; // the highest is set, we use the next one
    get_viewport_size();
    // open the right file
    sprintf(fn, EDGE_SAVE_DIR "/" EDGE_FILE_FORMAT, fnum );
    fd = fopen(fn, "wb");
    if(fd !=NULL)
    {
        // write the data
        fwrite(edgebuf->ptr,edgebuf->ptrLen,1,fd);
        fwrite(&zoom,sizeof(zoom),1,fd);
        fclose(fd);
        t.actime = t.modtime = time(NULL);
        utime(fn, &t);
        sprintf(msg, "Saved as %s",fn);
        draw_string(0, 0, msg, conf.osd_color);
    }
    closedir(d);
}
 
// load the edge overlay from a file
void load_edge_overlay(const char* fn)
{
    FILE *fd;
    int ret,ret2;
    int zoom;
 
    get_viewport_size();
    ensure_allocate_imagebuffer( );
    fd = fopen(fn,"rb");
    if( fd != NULL )
    {
        ret = fread(edgebuf->ptr,edgebuf->ptrLen,1,fd);
        ret2 = fread (&zoom,sizeof(zoom),1,fd);
        fclose(fd);
        if( (ret == 1) && (ret2 == 1) )
        {
            fsm_state = EDGE_FROZEN;    // switch to "edge overlay frozen"-mode
            if (conf.edge_overlay_zoom)
            {
                shooting_set_zoom(zoom);
            }
        }
    }
}
 
static void average_filter_row(const unsigned char* ptrh1,  // previous row
                               const unsigned char* ptrh2,  // current row
                               const unsigned char* ptrh3,  // next row
                               unsigned char* smptr )       // write results here
{
    int x;
#if CAM_USES_ASPECT_CORRECTION
    for (x=12; x<(viewportw - 4) * 3; x+=6)
#else
    for (x=12; x<(screen_width - 4) * 3; x+=6)
#endif
    {
        *(smptr + x + 1) = (*(ptrh1 + x - 1) +
                            *(ptrh1 + x + 1) +
                            *(ptrh1 + x + 3) +
 
                            *(ptrh2 + x - 1) +
                            *(ptrh2 + x + 1) +
                            *(ptrh2 + x + 3) +
 
                            *(ptrh3 + x - 1) +
                            *(ptrh3 + x + 1) +
                            *(ptrh3 + x + 3)) / 9;
 
        *(smptr + x + 3) = (*(ptrh1 + x + 1) +
                            *(ptrh1 + x + 3) +
                            *(ptrh1 + x + 4) +
 
                            *(ptrh2 + x + 1) +
                            *(ptrh2 + x + 3) +
                            *(ptrh2 + x + 4) +
 
                            *(ptrh3 + x + 1) +
                            *(ptrh3 + x + 3) +
                            *(ptrh3 + x + 4)) / 9;
 
        *(smptr + x + 4) = (*(ptrh1 + x + 3) +
                            *(ptrh1 + x + 4) +
                            *(ptrh1 + x + 5) +
 
                            *(ptrh2 + x + 3) +
                            *(ptrh2 + x + 4) +
                            *(ptrh2 + x + 5) +
 
                            *(ptrh3 + x + 3) +
                            *(ptrh3 + x + 4) +
                            *(ptrh3 + x + 5)) / 9;
 
        *(smptr + x + 5) = (*(ptrh1 + x + 4) +
                            *(ptrh1 + x + 5) +
                            *(ptrh1 + x + 7) +
 
                            *(ptrh2 + x + 4) +
                            *(ptrh2 + x + 5) +
                            *(ptrh2 + x + 7) +
 
                            *(ptrh3 + x + 4) +
                            *(ptrh3 + x + 5) +
                            *(ptrh3 + x + 7)) / 9;
    }
}
 
// Sobel edge detector
static void calc_edge_overlay()
{
    const int bPlayMode = (mode_get() & MODE_MASK) == MODE_PLAY;
    const unsigned char* img = bPlayMode ? vid_get_viewport_fb_d() :  vid_get_viewport_fb();
    const unsigned char * ptrh1 = NULL;    // previous pixel line
    const unsigned char * ptrh2 = NULL;    // current pixel line
    const unsigned char * ptrh3 = NULL;    // next pixel line
    unsigned char* smbuf = NULL;
    unsigned char * smptr = NULL;    // pointer to line in smbuf
    int x, y;
    int conv1, conv2;
    
    const int y_min = EDGE_HMARGIN;
    const int y_max = EDGE_HMARGIN + viewport_height;
    const int x_min = 6;
#if CAM_USES_ASPECT_CORRECTION
    const int x_max = (viewportw - 4) * 3;
#else
    const int x_max = (screen_width - 4) * 3;
#endif

    xoffset =0;
    yoffset =0;
 
    // Reserve buffers
    ensure_allocate_imagebuffer();
    if( !is_buffer_ready() ) return;
 
    // Clear all edges, if any
    memset(edgebuf->ptr, 0, edgebuf->ptrLen);
 
    // In every 6 bytes four pixels are described in the
    // viewport (UYVYYY format). For edge detection we only
    // consider the second in the current and the first
    // in the next pixel.
 
 
    if (conf.edge_overlay_filter)
    {
        smbuf = (unsigned char*)malloc(viewport_width*3);
        memset(smbuf, 0, viewport_width*3);
        if (smbuf==NULL)
            return;
 
        // Prefill smbuf with three lines of avergae-filtered data.
        // This looks much more complex then it actually is.
        // We really are just summing up nine pixels in a 3x3 box
        // and averaging the current pixel based on them. And
        // we do it 4 bytes at a time because of the UYVYYY format.
        for (y = -1; y <= 1; ++y)
        {
            ptrh1 = img + (EDGE_HMARGIN+y-1) * viewport_width;
            ptrh2 = img + (EDGE_HMARGIN+y  ) * viewport_width;
            ptrh3 = img + (EDGE_HMARGIN+y+1) * viewport_width;
            smptr = smbuf + (y+1) * viewport_width;
 
            average_filter_row(ptrh1, ptrh2, ptrh3, smptr);
        }
    }
 
    for (y = y_min; y < y_max; ++y)
    {
        if (conf.edge_overlay_filter)
        {
            // We need to shift up our smbuf one line,
            // and fill in the last line (which now empty)
            // with average-filtered data from img.
            // By storing only three lines of smoothed picture
            // in memory, we save memory.
 
            // Shift
            memcpy(smbuf+viewport_width*0, smbuf+viewport_width*1, viewport_width);
            memcpy(smbuf+viewport_width*1, smbuf+viewport_width*2, viewport_width);
 
            // Filter new line
            ptrh1 = img +  y * viewport_width;
            ptrh2 = img + (y+1)    * viewport_width;
            ptrh3 = img + (y+2) * viewport_width;
            smptr = smbuf + 2 * viewport_width;
            average_filter_row(ptrh1, ptrh2, ptrh3, smptr);
 
            ptrh1 = smbuf + 0 * viewport_width;
            ptrh2 = smbuf + 1 * viewport_width;
            ptrh3 = smbuf + 2 * viewport_width;
        }
        else
        {
            ptrh1 = img + (y-1) * viewport_width;
            ptrh2 = img +  y    * viewport_width;
            ptrh3 = img + (y+1) * viewport_width;
        }
 
        // Now we do sobel on the current line
 
        for (x = x_min; x < x_max; x += 6)
        {
            // convolve vert (second Y)
            conv1 = *(ptrh1 + x + 1) * ( 1) +
                    *(ptrh1 + x + 4) * (-1) +
 
                    *(ptrh2 + x + 1) * ( 2) +
                    *(ptrh2 + x + 4) * (-2) +
 
                    *(ptrh3 + x + 1) * ( 1) +
                    *(ptrh3 + x + 4) * (-1);
            if  (conv1 < 0)     // abs()
                conv1 = -conv1;
 
            // convolve vert (first Y of next pixel)
            conv2 = *(ptrh1 + x + 1) * ( 1) +
                    *(ptrh1 + x + 3) * ( 2) +
                    *(ptrh1 + x + 4) * ( 1) +
 
                    *(ptrh3 + x + 1) * (-1) +
                    *(ptrh3 + x + 3) * (-2) +
                    *(ptrh3 + x + 4) * (-1);
            if  (conv2 < 0)     // abs()
                conv2 = -conv2;
 
            if (conv1 + conv2 > conf.edge_overlay_thresh)
            {
                bv_set(edgebuf, (y-EDGE_HMARGIN)*viewport_width + x/3, 1);
            }
 
            // Do it once again for the next 'pixel'
 
            // convolve vert (second Y)
            conv1 = *(ptrh1 + x + 5) * ( 1) +
                    *(ptrh1 + x + 9) * (-1) +
 
                    *(ptrh2 + x + 5) * ( 2) +
                    *(ptrh2 + x + 9) * (-2) +
 
                    *(ptrh3 + x + 5) * ( 1) +
                    *(ptrh3 + x + 9) * (-1);
            if  (conv1 < 0)     // abs()
                conv1 = -conv1;
 
            // convolve vert (first Y of next pixel)
            conv2 = *(ptrh1 + x + 5) * ( 1) +
                    *(ptrh1 + x + 7) * ( 2) +
                    *(ptrh1 + x + 9) * ( 1) +
 
                    *(ptrh3 + x + 5) * (-1) +
                    *(ptrh3 + x + 7) * (-2) +
                    *(ptrh3 + x + 9) * (-1);
            if  (conv2 < 0)     // abs()
                conv2 = -conv2;
 
            if (conv1 + conv2 > conf.edge_overlay_thresh)
            {
                bv_set(edgebuf, (y-EDGE_HMARGIN)*viewport_width + x/3+1, 1);
            }
        }   // for x
    }   // for y
 
    if (smbuf != NULL)
    {
        free(smbuf);
        smbuf = NULL;
    }
 
//  For an even more improved edge overlay, enabling the following lines will 
//  post-filter the results of the edge detection, removing false edge 'dots'
//  from the display. However, the speed hit is large. In the developer's opinion
//  this code is not needed, but if you want that additional quality and do not 
//  care so much about performance, you can enable it.
// 
//    if (conf.edge_overlay_filter)
//    {
//        // Here we do basic filtering on the detected edges.
//        // If a pixel is marked as edge but just a few of its
//        // neighbors are also edges, then we assume that the
//        // current pixel is just noise and delete the mark.
//
//        bit_vector_t* bv_tmp = bv_create(edgebuf->nElem, edgebuf->nBits);
//        if (bv_tmp != NULL)
//        {
//            memset(bv_tmp->ptr, 0, bv_tmp->ptrLen);
//
//            for (y = 1; y < viewport_height-1; ++y)
//            {
//#if CAM_USES_ASPECT_CORRECTION
//                for (x=12; x<(viewportw - 4); ++x)
//#else
//                for (x=12; x<(screen_width - 4); ++x)
//#endif
//                {
//                    int bEdge = bv_get(edgebuf, y*viewport_width + x);
//                    if (bEdge)
//                    {
//                        // Count the number of neighbor edges
//                        int sum =
//                            bv_get(edgebuf, (y-1)*viewport_width + (x-1)) +
//                            bv_get(edgebuf, (y-1)*viewport_width + (x)) +
//                            bv_get(edgebuf, (y-1)*viewport_width + (x+1)) +
//
//                            bv_get(edgebuf, (y)*viewport_width + (x-1)) +
////              bv_get(&edgebuf, (y)*viewport_width + (x)) + //  we only inspect the neighbors
//                            bv_get(edgebuf, (y)*viewport_width + (x+1)) +
//
//                            bv_get(edgebuf, (y+1)*viewport_width + (x-1)) +
//                            bv_get(edgebuf, (y+1)*viewport_width + (x)) +
//                            bv_get(edgebuf, (y+1)*viewport_width + (x+1));
//
//                        if (!conf.edge_overlay_show)
//                        {
//                            if (sum >= 5)    // if we have at least 5 neighboring edges
//                                bv_set(bv_tmp, y*viewport_width + x, 1);   // keep the edge
//                            // else
//                            // there is no need to delete because the buffer is already zeroed
//                        }
//                    }
//                }   // for x
//            }   // for y
//
//            // Swap the filtered edge buffer for the real one
//            bit_vector_t* swap_tmp = edgebuf;
//            edgebuf = bv_tmp;
//            bv_free(swap_tmp);
//        }   // NULL-check
//    }   // if filtering
 
}
 
static void draw_edge_overlay()
{
    int x, y;
    int x_off, y_off;
 
    const int y_min = EDGE_HMARGIN;
    const int y_max = EDGE_HMARGIN+viewport_height;
    const int x_min = 6;
#if CAM_USES_ASPECT_CORRECTION
    const int x_max = (viewportw - 4);
#else
    const int x_max = (screen_width - 4);
#endif

    if( !is_buffer_ready() ) return;
 
    for (y = y_min; y < y_max; ++y)
    {
        y_off = y + yoffset;
 
        if ((y_off > y_min) && (y_off < y_max)) // do not draw outside of allowed area
        {
            for (x = x_min; x < x_max; ++x)
            {
                x_off = x + xoffset;
 
                if ((x_off > x_min) && (x_off < x_max)) // do not draw outside of allowed area
                {
                    // Draw a pixel to the screen wherever we detected an edge.
                    // If there is no edge based on the newest data, but there is one painted on the screen
                    // from previous calls, delete it from the screen.
                    if (bv_get(edgebuf, (y-y_min)*viewport_width + x))
                        draw_pixel(ASPECT_VIEWPORT_XCORRECTION(x_off), y_off, conf.edge_overlay_color );
                    else if (draw_get_pixel(ASPECT_VIEWPORT_XCORRECTION(x_off), y_off) == conf.edge_overlay_color)
                        draw_pixel(ASPECT_VIEWPORT_XCORRECTION(x_off), y_off, 0 );
                }
            }   // for x
        }
    }   // for y
 
 
    // Drawing the overlay is over.
    // But as a finishing touch we clear up garbage on the screen
    // by clearing those parts that the overlay has left.
 
    if (xoffset != 0)
    {
        // Cleans up leftover from horizontal motion
 
        const int x_min_c = (xoffset < 0) ? x_max + xoffset : x_min;
        const int x_max_c = (xoffset > 0) ? x_min + xoffset : x_max;
 
        for (y = y_min; y < y_max; ++y)
        {
            for (x = x_min_c; x < x_max_c; ++x)
            {
                if (draw_get_pixel(ASPECT_VIEWPORT_XCORRECTION(x), y) == conf.edge_overlay_color)  // if there is an edge drawn on the screen but there is no edge there based on the newest data, delete it from the screen
                    draw_pixel(ASPECT_VIEWPORT_XCORRECTION(x), y, 0 );
            }
        }
    }
 
    if (yoffset != 0)
    {
        // Cleans up leftover from vertical motion
 
        const int y_min_c = (yoffset < 0) ? y_max + yoffset : y_min;
        const int y_max_c = (yoffset > 0) ? y_min + yoffset : y_max;
 
        for (y = y_min_c; y < y_max_c; ++y)
        {
            for (x = x_min; x < x_max; ++x)
            {
                if (draw_get_pixel(ASPECT_VIEWPORT_XCORRECTION(x), y) == conf.edge_overlay_color)  // if there is an edge drawn on the screen but there is no edge there based on the newest data, delete it from the screen
                    draw_pixel(ASPECT_VIEWPORT_XCORRECTION(x), y, 0 );
            }
        }
    }
}

static void set_offset_from_overlap()
{
    const int y_max = viewport_height;
#if CAM_USES_ASPECT_CORRECTION
    const int x_max = (viewportw - 4);
#else
    const int x_max = (screen_width - 4);
#endif

    switch(conf.edge_overlay_pano)
    {
    case 0:     // pano off
        xoffset = 0;
        yoffset = 0;
        break;
    case 1:     // pano from left to right
        xoffset = -x_max*(100-conf.edge_overlay_pano_overlap)/100;
        break;
    case 2:     // pano from top to bottom
        yoffset = -y_max*(100-conf.edge_overlay_pano_overlap)/100;
        break;
    case 3:     // pano from right to left
        xoffset = x_max*(100-conf.edge_overlay_pano_overlap)/100;
        break;
    case 4:     // pano from bottom to top
        yoffset = y_max*(100-conf.edge_overlay_pano_overlap)/100;
        break;
    case 5:     // free mode
    default:
        // free mode: change position with "ALT" and cursor
        // nothing to do here.
        break;
    }
}
 
 
// Main edge overlay function.
// It works by detecting edges using the Sobel operator
// (calc_edgeoverlay()), the detected edges are then stored into an
// array of 1-bit elements. A set bit indicates that there is an
// edge and that it should be drawn onto the overlay.
// When needed, the 1-bit edge buffer is drawn onto the screen
// (dynamically decompressing it) using draw_edge_overlay().
void edge_overlay()
{
    // Was the shutter fully pressed the last time we ran?
    // We use this to make sure that the user has released
    // the button before processing the next FullPress event.
    // This prevents switching FSM states more than once
    // per press.
    static int bFullPress_prev = 0;
 
    // Have we already started taking pictures in panorama mode?
    // We use this variable to be able to detect if panorama
    // mode has been turned off.
    static int bPanoInProgress = 0;
 
    // Precalculate some values to make the rest of the
    // code easier to read.
    const int bHalfPress = kbd_is_key_pressed(KEY_SHOOT_HALF);
    const int bFullPress = kbd_is_key_pressed(KEY_SHOOT_FULL);
    const int bPlayMode = (mode_get() & MODE_MASK) == MODE_PLAY;
    const int bPanoramaMode = (conf.edge_overlay_pano != 0);
    const int bNeedHalfPress = (conf.edge_overlay_show != 1);
    const int bDisplayInPlay = (conf.edge_overlay_play == 1);
    const int bGuiModeNone = (gui_get_mode() == GUI_MODE_NONE);
    const int bGuiModeAlt = (gui_get_mode() == GUI_MODE_ALT);
    const int bCanDisplay = (
                                (!bPlayMode && (bHalfPress || !bNeedHalfPress)) ||   // we have a HalfPress in rec-mode
                                ( bPlayMode && bDisplayInPlay)  // or we are in play-mode with the right settings
                            );
 
    if (bPanoInProgress && !bPanoramaMode)
    {
        // This means panorama mode has been recently
        // turned off in the menu. So let's release
        // Frozen mode for the user.
        reset_edge_overlay();
        bPanoInProgress = 0;
    }
 
    get_viewport_size();

    // For just two states a state machine is not actually needed.
    // But it is scalable in the future in case anybody
    // wants to extend the functionality of edge overlay.
    switch (fsm_state)
    {
    case EDGE_LIVE:
    {
        // In this state we assume no edge overlay in memory,
        // but we are ready to create one if the user presses wishes so.
 
        if (bFullPress && !bFullPress_prev && bGuiModeNone)
        {
            calc_edge_overlay();
            set_offset_from_overlap();
            fsm_state = EDGE_FROZEN;
            
            bPanoInProgress = bPanoramaMode;
        }
        else if (bCanDisplay && (bGuiModeAlt || bGuiModeNone))
        {
            calc_edge_overlay();
            draw_edge_overlay();
        }
        else
        {
            // Nothing happens. So do nothing.
            // Or rather, we could clean up if we are that bored.
            bv_free(edgebuf);
            edgebuf = NULL;
        }
 
        break;
    }
    case EDGE_FROZEN:
    {
        // We have a stored edge overlay in memory and we display
        // it on screen in 'frozen' mode.
 
        // Move edge overlay around.
        if (gui_get_mode() == GUI_MODE_ALT)
        {
            if (kbd_is_key_pressed(KEY_RIGHT))
                xoffset +=XINC;
            if (kbd_is_key_pressed(KEY_LEFT))
                xoffset -=XINC;
            if (kbd_is_key_pressed(KEY_DOWN))
                yoffset +=YINC;
            if (kbd_is_key_pressed(KEY_UP))
                yoffset -=YINC;
        }
 
        // In event of a FullPress, we either capture a new
        // overlay and stay frozen, OR we go back to live mode.
        if (bFullPress && !bFullPress_prev && bGuiModeNone)
        {
            if (bPanoramaMode)
            {
                calc_edge_overlay();
                set_offset_from_overlap();
                bPanoInProgress = 1;
            }
            else
                fsm_state = EDGE_LIVE;
        }
        else if (bCanDisplay && (bGuiModeAlt || bGuiModeNone))
        {
            draw_edge_overlay();
            draw_string(0, 0, "Frozen", conf.osd_color);
        }
 
        break;
    }   // case
    }   // switch
 
    bFullPress_prev = bFullPress;
}   // function
 
 
 
 
