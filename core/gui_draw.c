#include "stdlib.h"
#include "platform.h"
#include "core.h"
#include "keyboard.h"
#include "conf.h"
#include "font.h"
#include "gui_draw.h"

//-------------------------------------------------------------------
static char*    frame_buffer[2];
unsigned int    screen_width=0, screen_height=0, screen_size=0;
unsigned int    screen_buffer_width=0, screen_buffer_height=0, screen_buffer_size=0;
void            (*draw_pixel_proc)(unsigned int offset, color cl);

//-------------------------------------------------------------------
static void draw_pixel_std(unsigned int offset, color cl) {
    frame_buffer[0][offset] = frame_buffer[1][offset] = cl & 0xff;
}

//-------------------------------------------------------------------
void draw_set_draw_proc(void (*pixel_proc)(unsigned int offset, color cl)) {
    draw_pixel_proc = (pixel_proc)?pixel_proc:draw_pixel_std;
}

#if CAM_USES_ASPECT_CORRECTION //nandoide sept-2009 

unsigned int (*aspect_xcorrection_proc)(unsigned int x);
unsigned int (*aspect_ycorrection_proc)(unsigned int y);

//-------------------------------------------------------------------
unsigned int aspect_xcorrection_std(unsigned int x) {
   return (ASPECT_XCORRECTION(x));
}
//-------------------------------------------------------------------
static unsigned int aspect_ycorrection_std(unsigned int y) {
   return (ASPECT_YCORRECTION(y));
}
//-------------------------------------------------------------------
unsigned int aspect_xcorrection_games_360(unsigned int x) {
   return (ASPECT_GAMES_XCORRECTION(x));
}
//-------------------------------------------------------------------
unsigned int aspect_ycorrection_games_360(unsigned int y) {
   return (ASPECT_GAMES_YCORRECTION(y));
}
//-------------------------------------------------------------------
void draw_set_aspect_xcorrection_proc(unsigned int (*xcorrection_proc)(unsigned int x)) {
   aspect_xcorrection_proc = (xcorrection_proc)?xcorrection_proc:aspect_xcorrection_std;
}
//-------------------------------------------------------------------
void draw_set_aspect_ycorrection_proc(unsigned int (*ycorrection_proc)(unsigned int y)) {
   aspect_ycorrection_proc = (ycorrection_proc)?ycorrection_proc:aspect_ycorrection_std;
}
//-------------------------------------------------------------------
void draw_set_environment(unsigned int (*xcorrection_proc)(unsigned int x), 
                                       unsigned int (*ycorrection_proc)(unsigned int y),
                                       int screenx, int screeny ) {
   screen_width=screenx;
   screen_height=screeny;
   draw_set_aspect_xcorrection_proc(xcorrection_proc);
   draw_set_aspect_ycorrection_proc(ycorrection_proc);
}

#endif

//-------------------------------------------------------------------
void draw_init() {
    register int i;

    screen_width = vid_get_bitmap_screen_width();
    screen_height  = vid_get_bitmap_screen_height();
    screen_size = screen_width * screen_height;
    screen_buffer_width = vid_get_bitmap_buffer_width();
    screen_buffer_height = vid_get_bitmap_buffer_height();
    screen_buffer_size = screen_buffer_width * screen_buffer_height;
    frame_buffer[0] = vid_get_bitmap_fb();
    frame_buffer[1] = frame_buffer[0] + screen_buffer_size;
    draw_set_draw_proc(NULL);
    #if CAM_USES_ASPECT_CORRECTION
      draw_set_aspect_xcorrection_proc(NULL);
      draw_set_aspect_ycorrection_proc(NULL);
    #endif
}



#if CAM_USES_ASPECT_CORRECTION

// nandoide: sept-2009: draw_pixel_xarray draws a horizontal line at height y, from xi to xf
// includes a correction of aspect ratio on x from buffer to screen
// can be used to optimize computations (offset calculus) in other primitives (rectangles, and so on...) and compensate tne increase in computation time 
// of aspect ratio correction.
// sx200is:
//    we have a 720x240 efective memory buffer (in a 960x270 physical memory buffer) and a screen of 320x240 (!) 
//   the drawing primitives work on screen coordinates (the other approach, less modular it's to paint on buffer coordinates, deforming on x direction, I think it would be harder to live with it
//   and requires a full bunch of changes of the actual software).
//   then we do paint a x coordinate transformed in buffer by a factor 720/320=9/4 and then we do correct (deform) x  to x*9/4 previously to save it on buffer
// other:
//     the default mapping is x=x (NOTE: I think important to check that on every model, and necessary in newer models. it seems to me very strange screen sizes of 360x240 for 4/3 and 480/240 for 16/9 (SX1S).

void draw_pixel_xarray(coord y, coord xi, coord xf, color cl) {
    if (xi >= screen_width || y >= screen_height) return;
    else {
        unsigned int offsetx, offsetxf, offsetxi, offsety;
        offsety=aspect_ycorrection_proc(y) * screen_buffer_width;
        offsetxi = aspect_xcorrection_proc(xi);
        xf++;
        offsetxf= (xf >= screen_width) ? screen_buffer_width - 1 :  aspect_xcorrection_proc(xf);
        for (offsetx=offsetxi; offsetx<=offsetxf-1; offsetx++) {
           draw_pixel_proc(offsety+offsetx, cl);
        }
    }
}

#if  CAM_USES_ASPECT_YCORRECTION
//generalization for cases than we need to correct both coordinates: symetric algorithm
void draw_pixel_rectanglearray(coord yi, coord yf, coord xi, coord xf, color cl) {
    if (xi >= screen_width || yi >= screen_height) return;
    else {
        unsigned int offsetx, offsetxf, offsetxi, offsety, offsetyf, offsetyi, offset;
        offsetyi = aspect_ycorrection_proc(yi);
        yf++;
        offsetyf= (yf >= screen_height) ? screen_buffer_height - 1 :  aspect_ycorrection_proc(yf);
        offsetxi = aspect_xcorrection_proc(xi);
        xf++;
        offsetxf= (xf >= screen_width) ? screen_buffer_width - 1 :  aspect_xcorrection_proc(xf);
        for (offsety=offsetyi; offsety<=offsetyf-1; offsety++) {
          offset=offsety*screen_buffer_width;
          for (offsetx=offsetxi; offsetx<=offsetxf-1; offsetx++) {
             draw_pixel_proc(offset+offsetx, cl);
          }
        }
    }
}
#endif

// nandoide sept-2009: draw_pixel version that calls draw_pixel_xarray for calculations. It's necessary to paint more than a pixel. In other case we got holes due
// to the nature of discrete drawing algoritms and the aspect-ratio correction.
// so, we need paint a horizontal line from the point coordinate to the next point (x to x+1)
// it's a brute force algorithm and it's possible that we have aliasing problems ... 
// but the display seems OK on sx200is ( good!) , due perhaps to the fact that the system makes a final reverse (bilinear?) resize 720 -> 320, to display the buffer data.

void draw_pixel(coord x, coord y, color cl) {
  #if  CAM_USES_ASPECT_YCORRECTION
    draw_pixel_rectanglearray(y, y, x, x, cl);
  #else
    draw_pixel_xarray(y, x, x, cl);
  #endif
}

color draw_get_pixel(coord x, coord y) {
    if (x >= screen_width || y >= screen_height) return 0;
    return frame_buffer[0][y * screen_buffer_width + aspect_xcorrection_proc(x) ];
}
#else
//-------------------------------------------------------------------
void draw_pixel(coord x, coord y, color cl) {
    if (x >= screen_width || y >= screen_height) return;
    else {
        register unsigned int offset = y * screen_buffer_width + x;
        draw_pixel_proc(offset, cl);
   }
}

//-------------------------------------------------------------------
color draw_get_pixel(coord x, coord y) {
    if (x >= screen_width || y >= screen_height) return 0;
    return frame_buffer[0][y * screen_buffer_width + x];
}
#endif

//-------------------------------------------------------------------
#define swap(v1, v2)   {v1^=v2; v2^=v1; v1^=v2;}
//-------------------------------------------------------------------
void draw_line(coord x1, coord y1, coord x2, coord y2, color cl) {
     unsigned char steep = abs(y2 - y1) > abs(x2 - x1);
     if (steep) {
         swap(x1, y1);
         swap(x2, y2);
     }
     if (x1 > x2) {
         swap(x1, x2);
         swap(y1, y2);
     }
     int deltax = x2 - x1;
     int deltay = abs(y2 - y1);
     int error = 0;
     int y = y1;
     int ystep = (y1 < y2)?1:-1;
     int x;
     for (x=x1; x<=x2; ++x) {
         if (steep) draw_pixel(y, x, cl);
         else draw_pixel(x, y, cl);
         error += deltay;
         if ((error<<1) >= deltax) {
             y += ystep;
             error -= deltax;
         }
     }
}
//-------------------------------------------------------------------
void draw_rect(coord x1, coord y1, coord x2, coord y2, color cl) {
    unsigned int xMin, yMin, xMax, yMax, x, y;
    if (x1>x2) {
    	xMax=x1; xMin=x2;
    } else {
    	xMin=x1; xMax=x2;
    }
    if (y1>y2) {
    	yMax=y1; yMin=y2;
    } else {
    	yMin=y1; yMax=y2;
    }
    if (xMax>=screen_width) xMax=screen_width-1;
    if (xMin>=screen_width) xMin=screen_width-1;
    if (yMax>=screen_height) yMax=screen_height-1;
    if (yMin>=screen_height) yMin=screen_height-1;

    for (y=yMin; y<=yMax; ++y) {
      draw_pixel(xMin, y, cl & 0xff);
      draw_pixel(xMax, y, cl & 0xff);
    }
    #if CAM_USES_ASPECT_CORRECTION &&  !CAM_USES_ASPECT_YCORRECTION
      draw_pixel_xarray(yMin, xMin+1, xMax-1, cl & 0xff);
      draw_pixel_xarray(yMax, xMin+1, xMax-1, cl & 0xff);
    #else
      for (x=xMin+1; x<=xMax-1; ++x) {
          draw_pixel(x, yMin, cl & 0xff);
          draw_pixel(x, yMax, cl & 0xff);
      }
    #endif
}
//-------------------------------------------------------------------
void draw_round_rect(coord x1, coord y1, coord x2, coord y2, color cl) { 
    unsigned int xMin, yMin, xMax, yMax, x, y; 
    if (x1>x2) { 
       xMax=x1; xMin=x2; 
    } else { 
       xMin=x1; xMax=x2; 
    } 
    if (y1>y2) { 
       yMax=y1; yMin=y2; 
    } else { 
       yMin=y1; yMax=y2; 
    } 
    if (xMax>=screen_width) xMax=screen_width-1; 
    if (xMin>=screen_width) xMin=screen_width-1; 
    if (yMax>=screen_height) yMax=screen_height-1; 
    if (yMin>=screen_height) yMin=screen_height-1; 

    for (y=yMin+2; y<=yMax-2; ++y) { 
      draw_pixel(xMin, y, cl & 0xff); 
      draw_pixel(xMax, y, cl & 0xff); 
    } 
    #if CAM_USES_ASPECT_CORRECTION &&  !CAM_USES_ASPECT_YCORRECTION
       draw_pixel_xarray(yMin, xMin+2, xMax-2, cl & 0xff);
       draw_pixel_xarray(yMax, xMin+2, xMax-2, cl & 0xff);
    #else  
       for (x=xMin+2; x<=xMax-2; ++x) { 
           draw_pixel(x, yMin, cl & 0xff); 
           draw_pixel(x, yMax, cl & 0xff); 
       } 
    #endif
} 
//-------------------------------------------------------------------
void draw_filled_rect(coord x1, coord y1, coord x2, coord y2, color cl) {
    unsigned int xMin, yMin, xMax, yMax, x, y;
    if (x1>x2) {
    	xMax=x1; xMin=x2;
    } else {
    	xMin=x1; xMax=x2;
    }
    if (y1>y2) {
    	yMax=y1; yMin=y2;
    } else {
    	yMin=y1; yMax=y2;
    }
    if (xMax>=screen_width) xMax=screen_width-1;
    if (xMin>=screen_width) xMin=screen_width-1;
    if (yMax>=screen_height) yMax=screen_height-1;
    if (yMin>=screen_height) yMin=screen_height-1;

    draw_rect(x1, y1, x2, y2, cl);
    for (y=yMin+1; y<=yMax-1; ++y) {
      #if CAM_USES_ASPECT_CORRECTION &&  !CAM_USES_ASPECT_YCORRECTION
        draw_pixel_xarray(y, xMin+1, xMax-1, cl>>8);
      #else  
        for (x=xMin+1; x<=xMax-1; ++x) {
          draw_pixel(x, y, cl>>8);
        }
      #endif
    }
}
//-------------------------------------------------------------------
void draw_filled_round_rect(coord x1, coord y1, coord x2, coord y2, color cl) { 
    unsigned int xMin, yMin, xMax, yMax, x, y; 
    if (x1>x2) { 
       xMax=x1; xMin=x2; 
    } else { 
       xMin=x1; xMax=x2; 
    } 
    if (y1>y2) { 
       yMax=y1; yMin=y2; 
    } else { 
       yMin=y1; yMax=y2; 
    } 
    if (xMax>=screen_width) xMax=screen_width-1; 
    if (xMin>=screen_width) xMin=screen_width-1; 
    if (yMax>=screen_height) yMax=screen_height-1; 
    if (yMin>=screen_height) yMin=screen_height-1; 

    draw_round_rect(x1, y1, x2, y2, cl); 
    for (y=yMin+1; y<=yMax-1; ++y) {
      #if CAM_USES_ASPECT_CORRECTION &&  !CAM_USES_ASPECT_YCORRECTION
        draw_pixel_xarray(y, xMin+1, xMax-1, cl>>8);
      #else     
          for (x=xMin+1; x<=xMax-1; ++x) { 
            draw_pixel(x, y, cl>>8); 
          }
      #endif      
    } 
} 
//-------------------------------------------------------------------
void draw_char(coord x, coord y, const char ch, color cl) {
    const unsigned char *sym = (unsigned char*)current_font +
	    ((const unsigned char)ch)*FONT_HEIGHT;
    int i, ii;
    char c;

    // XXX optimize. probably use 4bit -> 32bit lookup table
    // so 4(8) pixels were drawn at a time
    for (i=0; i<FONT_HEIGHT; i++){
	for (ii=0; ii<FONT_WIDTH; ii++){
            draw_pixel(x+ii ,y+i, (sym[i] & (0x80>>ii))? cl&0xff : cl>>8);
	}
    }
}

//-------------------------------------------------------------------
void draw_string(coord x, coord y, const char *s, color cl) {
    while(*s){
	draw_char(x, y, *s, cl);
	s++;
	x+=FONT_WIDTH;
	if ((x>=screen_width) && (*s)){
	    draw_char(x-FONT_WIDTH,y, '>', cl);
	    break;
	}
    }
}

//-------------------------------------------------------------------
void draw_txt_rect(coord col, coord row, unsigned int length, unsigned int height, color cl) {
    draw_rect(col*FONT_WIDTH, row*FONT_HEIGHT, (col+length)*FONT_WIDTH-1, (row+height)*FONT_HEIGHT-1, cl);
}

//-------------------------------------------------------------------
void draw_txt_rect_exp(coord col, coord row, unsigned int length, unsigned int height, unsigned int exp, color cl) {
    draw_rect(col*FONT_WIDTH-exp, row*FONT_HEIGHT-exp, (col+length)*FONT_WIDTH-1+exp, (row+height)*FONT_HEIGHT-1+exp, cl);
}

//-------------------------------------------------------------------
void draw_txt_filled_rect(coord col, coord row, unsigned int length, unsigned int height, color cl) {
    draw_filled_rect(col*FONT_WIDTH, row*FONT_HEIGHT, (col+length)*FONT_WIDTH-1, (row+height)*FONT_HEIGHT-1, cl);
}

//-------------------------------------------------------------------
void draw_txt_filled_rect_exp(coord col, coord row, unsigned int length, unsigned int height, unsigned int exp, color cl) {
    draw_filled_rect(col*FONT_WIDTH-exp, row*FONT_HEIGHT-exp, (col+length)*FONT_WIDTH-1+exp, (row+height)*FONT_HEIGHT-1+exp, cl);
}

//-------------------------------------------------------------------
void draw_txt_string(coord col, coord row, const char *str, color cl) {
    draw_string(col*FONT_WIDTH, row*FONT_HEIGHT, str, cl);
}

//-------------------------------------------------------------------
void draw_txt_char(coord col, coord row, const char ch, color cl) {
    draw_char(col*FONT_WIDTH, row*FONT_HEIGHT, ch, cl);
}

//-------------------------------------------------------------------
void draw_clear() {
    register unsigned int i;
    for (i=0; i<screen_buffer_size; ++i)
        frame_buffer[0][i] = frame_buffer[1][i] = COLOR_TRANSPARENT;
}

//-------------------------------------------------------------------
void draw_restore() {
    vid_bitmap_refresh();
}

//-------------------------------------------------------------------
void draw_fill(coord x, coord y, color cl_fill, color cl_bound) {
   if (draw_get_pixel(x, y) != cl_bound && draw_get_pixel(x, y) != cl_fill) {
       draw_pixel(x, y, cl_fill);

       draw_fill((x+1), y, cl_fill,cl_bound);
       draw_fill((x-1), y, cl_fill,cl_bound);
       draw_fill(x, (y+1), cl_fill,cl_bound);
       draw_fill(x, (y-1), cl_fill,cl_bound);
   }
}

//-------------------------------------------------------------------
void draw_circle(coord x, coord y, const unsigned int r, color cl) {
    int dx = 0;
    int dy = r;
    int p=(3-(r<<1));

    do {
        draw_pixel((x+dx),(y+dy),cl);
        draw_pixel((x+dy),(y+dx),cl);
        draw_pixel((x+dy),(y-dx),cl);
        draw_pixel((x+dx),(y-dy),cl);
        draw_pixel((x-dx),(y-dy),cl);
        draw_pixel((x-dy),(y-dx),cl);
        draw_pixel((x-dy),(y+dx),cl);
        draw_pixel((x-dx),(y+dy),cl);

        ++dx;

        if (p<0) 
            p += ((dx<<2)+6);
        else {
            --dy;
            p += (((dx-dy)<<2)+10);
        }
    } while (dx<=dy);
}

//-------------------------------------------------------------------
void draw_ellipse(coord xc, coord yc, unsigned int a, unsigned int b, color cl) {
    int x = 0, y = b;
    long a2 = (long)a*a, b2 = (long)b*b;
    long crit1 = -((a2>>2) + (a&1) + b2);
    long crit2 = -((b2>>2) + (b&1) + a2);
    long crit3 = -((b2>>2) + (b&1));
    long t = -a2*y;
    long dxt = b2*x*2, dyt = -2*a2*y;
    long d2xt = b2*2, d2yt = a2*2;

    while (y>=0 && x<=a) {
        draw_pixel(xc+x, yc+y, cl);
        if (x!=0 || y!=0)
            draw_pixel(xc-x, yc-y, cl);
        if (x!=0 && y!=0) {
            draw_pixel(xc+x, yc-y, cl);
            draw_pixel(xc-x, yc+y, cl);
        }
        if (t + b2*x <= crit1 || t + a2*y <= crit3)
            ++x, dxt += d2xt, t += dxt;
        else if (t - a2*y > crit2)
            --y, dyt += d2yt, t += dyt;
        else {
            ++x, dxt += d2xt, t += dxt;
            --y, dyt += d2yt, t += dyt;
        }
   }
}

//-------------------------------------------------------------------
void draw_filled_ellipse(coord xc, coord yc, unsigned int a, unsigned int b, color cl) {
    int x = 0, y = b;
    int rx = x, ry = y;
    unsigned int width = 1;
    unsigned int height = 1;
    long a2 = (long)a*a, b2 = (long)b*b;
    long crit1 = -((a2>>2) + (a&1) + b2);
    long crit2 = -((b2>>2) + (b&1) + a2);
    long crit3 = -((b2>>2) + (b&1));
    long t = -a2*y;
    long dxt = 2*b2*x, dyt = -2*a2*y;
    long d2xt = 2*b2, d2yt = 2*a2;
    
    color cl_fill = ((cl >> 8) & 0xff) | (cl & 0xff00);

    if (b == 0) {
        draw_filled_rect(xc-a, yc, (a<<1)+1, 1, cl_fill);
    } else {
        while (y>=0 && x<=a) {
            if (t + b2*x <= crit1 || t + a2*y <= crit3) {
                if (height == 1)
                    ; /* draw nothing */
                else if (ry*2+1 > (height-1)*2) {
                    draw_filled_rect(xc-rx, yc-ry, xc-rx+width-1, yc-ry+(height-1)-1, cl_fill);
                    draw_filled_rect(xc-rx, yc+ry+1, xc-rx+width-1, yc+ry+1+(1-height)-1, cl_fill);
                    ry -= height-1;
                    height = 1;
                }
                else {
                    draw_filled_rect(xc-rx, yc-ry, xc-rx+width-1, yc-ry+(ry*2+1)-1, cl_fill);
                    ry -= ry;
                    height = 1;
                }
                ++x, dxt += d2xt, t += dxt;
                rx++;
                width += 2;
            }
            else if (t - a2*y > crit2) {
                --y, dyt += d2yt, t += dyt;
                height++;
            }
            else {
                if (ry*2+1 > height*2) {
                    draw_filled_rect(xc-rx, yc-ry, xc-rx+width-1, yc-ry+height-1, cl_fill);
                    draw_filled_rect(xc-rx, yc+ry+1, xc-rx+width-1, yc+ry+1-height-1, cl_fill);
                }
                else {
                    draw_filled_rect(xc-rx, yc-ry, xc-rx+width-1, yc-ry+(ry*2+1)-1, cl_fill);
                }
                ++x, dxt += d2xt, t += dxt;
                --y, dyt += d2yt, t += dyt;
                rx++;
                width += 2;
                ry -= height;
                height = 1;
            }
        }

        if (ry > height) {
            draw_filled_rect(xc-rx, yc-ry, xc-rx+width-1, yc-ry+height-1, cl_fill);
            draw_filled_rect(xc-rx, yc+ry+1, xc-rx+width-1, yc+ry+1-height-1, cl_fill);
        }
        else {
            draw_filled_rect(xc-rx, yc-ry, xc-rx+width-1, yc-ry+(ry*2+1)-1, cl_fill);
        }
    }
}
