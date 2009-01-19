#include "stdlib.h"
#include "platform.h"
#include "core.h"
#include "keyboard.h"
#include "conf.h"
#include "font.h"
#include "ubasic.h"
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
}

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
    for (x=xMin+1; x<=xMax-1; ++x) {
        draw_pixel(x, yMin, cl & 0xff);
        draw_pixel(x, yMax, cl & 0xff);
    }
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
    for (x=xMin+2; x<=xMax-2; ++x) { 
        draw_pixel(x, yMin, cl & 0xff); 
        draw_pixel(x, yMax, cl & 0xff); 
    } 
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
	for (x=xMin+1; x<=xMax-1; ++x) {
	    draw_pixel(x, y, cl>>8);
	}
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
     for (x=xMin+1; x<=xMax-1; ++x) { 
       draw_pixel(x, y, cl>>8); 
     } 
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
