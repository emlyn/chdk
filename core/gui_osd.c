#include "stdlib.h"
#include "keyboard.h"
#include "platform.h"
#include "histogram.h"
#include "core.h"
#include "lang.h"
#include "conf.h"
#include "gui.h"
#include "gui_draw.h"
#include "gui_lang.h"
#include "gui_batt.h"
#include "gui_space.h"
#include "gui_grid.h"
#include "gui_osd.h"

//-------------------------------------------------------------------
typedef struct {
    int     title;
    OSD_pos *pos;
    OSD_pos size;
} OSD_elem;




static OSD_elem osd[]={
    {LANG_OSD_LAYOUT_EDITOR_HISTO,      &conf.histo_pos,        {HISTO_WIDTH+2, HISTO_HEIGHT}   },
    {LANG_OSD_LAYOUT_EDITOR_DOF_CALC,   &conf.dof_pos,          {23*FONT_WIDTH, 2*FONT_HEIGHT}  },
    {LANG_OSD_LAYOUT_EDITOR_STATES,     &conf.mode_state_pos,   {12*FONT_WIDTH, 4*FONT_HEIGHT}   },
    {LANG_OSD_LAYOUT_EDITOR_RAW,     &conf.mode_raw_pos,   {7*FONT_WIDTH, FONT_HEIGHT}   },
    {LANG_OSD_LAYOUT_EDITOR_MISC,       &conf.values_pos,       {9*FONT_WIDTH, 9*FONT_HEIGHT}   },
    {LANG_OSD_LAYOUT_EDITOR_BAT_ICON,   &conf.batt_icon_pos,    {28, 12}                        },
    {LANG_OSD_LAYOUT_EDITOR_SPACE_ICON,   &conf.space_icon_pos,    {103, 7}                        },
    {LANG_OSD_LAYOUT_EDITOR_BAT_TEXT,   &conf.batt_txt_pos,     {5*FONT_WIDTH, FONT_HEIGHT}     },
    {LANG_OSD_LAYOUT_EDITOR_SPACE_TEXT,   &conf.space_txt_pos,     {5*FONT_WIDTH, FONT_HEIGHT}     },
    {LANG_OSD_LAYOUT_EDITOR_CLOCK,      &conf.clock_pos,        {5*FONT_WIDTH, FONT_HEIGHT}     },
    {0}
};
static int osd_to_draw;
static int curr_item;
static char osd_buf[64];
static int step;
static unsigned char *img_buf, *scr_buf;
static int timer = 0;
static char *buf = NULL;
//ARM

static DOF_TYPE dof;
static EXPO_TYPE expo;

#define OSD_STATE    0
#define OSD_MISC     1



//-------------------------------------------------------------------
void gui_osd_init() {
    osd_to_draw = 1;
    curr_item = 0;
    step = 10;
    draw_restore();
}

//-------------------------------------------------------------------
void gui_osd_draw() {
    if (osd_to_draw) {
        int i;
        draw_restore();
        gui_osd_draw_histo();
        gui_osd_draw_dof();
        gui_batt_draw_osd();
        gui_space_draw_osd();
        gui_osd_draw_state();
        gui_osd_draw_raw_info();
        gui_osd_draw_values();
        gui_osd_draw_clock();
        for (i=1; i<=2; ++i) {
            draw_rect((osd[curr_item].pos->x>=i)?osd[curr_item].pos->x-i:0, (osd[curr_item].pos->y>=i)?osd[curr_item].pos->y-i:0, 
                      osd[curr_item].pos->x+osd[curr_item].size.x+i-1, osd[curr_item].pos->y+osd[curr_item].size.y+i-1,
                      COLOR_GREEN);
        }
        sprintf(osd_buf, " %s:  x:%d y:%d s:%d ", lang_str(osd[curr_item].title), osd[curr_item].pos->x, osd[curr_item].pos->y, step);
        draw_string(0, (osd[curr_item].pos->x<strlen(osd_buf)*FONT_WIDTH+4 && osd[curr_item].pos->y<FONT_HEIGHT+4)?screen_height-FONT_HEIGHT:0,
                    osd_buf, MAKE_COLOR(COLOR_RED, COLOR_WHITE));
        osd_to_draw = 0;
    }
}

//-------------------------------------------------------------------
void gui_osd_kbd_process() {
    switch (kbd_get_autoclicked_key()) {
    case KEY_LEFT:
        if (osd[curr_item].pos->x > 0) {
            osd[curr_item].pos->x-=(osd[curr_item].pos->x>=step)?step:osd[curr_item].pos->x;
            osd_to_draw = 1;
        }
        break;
    case KEY_RIGHT:
        if (osd[curr_item].pos->x < screen_width-osd[curr_item].size.x) {
            osd[curr_item].pos->x+=(screen_width-osd[curr_item].size.x-osd[curr_item].pos->x>step)?step:screen_width-osd[curr_item].size.x-osd[curr_item].pos->x;
            osd_to_draw = 1;
        }
        break;
    case KEY_UP:
        if (osd[curr_item].pos->y > 0) {
            osd[curr_item].pos->y-=(osd[curr_item].pos->y>=step)?step:osd[curr_item].pos->y;
            osd_to_draw = 1;
        }
        break;
    case KEY_DOWN:
        if (osd[curr_item].pos->y < screen_height-osd[curr_item].size.y) {
            osd[curr_item].pos->y+=(screen_height-osd[curr_item].size.y-osd[curr_item].pos->y>step)?step:screen_height-osd[curr_item].size.y-osd[curr_item].pos->y;
            osd_to_draw = 1;
        }
        break;
    case KEY_SET:
        ++curr_item;
        if (!osd[curr_item].pos) 
            curr_item = 0;
        osd_to_draw = 1;
        break;
    case KEY_DISPLAY:
        step=(step==1)?10:1;
        osd_to_draw = 1;
        break;
    }
}

//-------------------------------------------------------------------
static void gui_osd_draw_single_histo(int hist, coord x, coord y, int small) {
    register unsigned int i, v, threshold;
    register color cl, cl_over, cl_bg=conf.histo_color>>8;
    coord w=HISTO_WIDTH, h=HISTO_HEIGHT;

    switch (hist) {
        case HISTO_R: 
            cl=COLOR_RED; 
            break;
        case HISTO_G: 
            cl=COLOR_GREEN; 
            break;
        case HISTO_B: 
            cl=((mode_get()&MODE_MASK) == MODE_REC)?0xDF:0xCC; 
            break;
        case HISTO_RGB:
        case HISTO_Y:
        default:
            cl=conf.histo_color; 
            break;
    }

    if (small) {
        h>>=1; w>>=1;
        for (i=0; i<w; ++i) {
            threshold = (histogram[hist][i<<1]+histogram[hist][(i<<1)+1])>>2;

            for (v=1; v<h-1; ++v)
                draw_pixel(x+1+i, y+h-v, (v<=threshold)?cl:cl_bg);
            cl_over = (threshold==h && conf.show_overexp)?conf.histo_color2>>8:cl;
            for (; v<h; ++v)
                draw_pixel(x+1+i, y+h-v, (v<=threshold)?cl_over:cl_bg);
        }
    } else {
        for (i=0; i<w; ++i) {
            threshold = histogram[hist][i];

            for (v=1; v<h-3; ++v)
                draw_pixel(x+1+i, y+h-v, (v<=threshold)?cl:cl_bg);
            cl_over = (threshold==h && conf.show_overexp)?conf.histo_color2>>8:cl;
            for (; v<h; ++v)
                draw_pixel(x+1+i, y+h-v, (v<=threshold)?cl_over:cl_bg);
        }
    }
      
    draw_rect(x, y, x+1+w, y+h, conf.histo_color2&0xFF);
    //Vertical Lines
    if (conf.histo_show_ev_grid) for (i=1;i<=4;i++) draw_line(x+(1+w)*i/5, y, x+(1+w)*i/5, y+h, conf.histo_color2&0xFF);
}

//-------------------------------------------------------------------
void gui_osd_zebra_init() {
    timer = 0;
}

//-------------------------------------------------------------------
static void draw_pixel_buffered(unsigned int offset, color cl) {
    buf[offset] = cl;
}

//-------------------------------------------------------------------
static void gui_osd_draw_zebra_osd() {
    switch (conf.zebra_draw_osd) {
        case ZEBRA_DRAW_NONE:
            break;
        case ZEBRA_DRAW_OSD:
            if (conf.show_osd) {
                draw_set_draw_proc(draw_pixel_buffered);
                if ((mode_get()&MODE_MASK) == MODE_REC) {
                    if (conf.show_grid_lines) {
                        gui_grid_draw_osd(1);
                    }
                    if (conf.show_dof) {
                        gui_osd_draw_dof();
                    }
                    if (conf.show_state) {
                        gui_osd_draw_state();
                    }
                    if (conf.show_remaining_raw) {
                        gui_osd_draw_raw_info();
                    }
                    if (conf.show_values) {
                        gui_osd_draw_values();
                    }
                }
                gui_batt_draw_osd();
                gui_space_draw_osd();
                if (conf.show_clock) {
                    gui_osd_draw_clock();
                }
                draw_set_draw_proc(NULL);
            }
            /* no break here */
        case ZEBRA_DRAW_HISTO:
        default:
            if (conf.show_histo) {
                draw_set_draw_proc(draw_pixel_buffered);
                gui_osd_draw_histo();
                draw_set_draw_proc(NULL);
            }
            break;
    }
}


//-------------------------------------------------------------------
int gui_osd_draw_zebra() {
    unsigned int v, s, x, y, f, over;
    color cl_under=conf.zebra_color>>8, cl_over=conf.zebra_color&0xFF;
    static int need_restore=0;
    int viewport_height;
 int m = ((mode_get()&MODE_MASK) == MODE_REC);
    color cls[] = {
        COLOR_TRANSPARENT,
        (m)?0xDF:0xCC,
        COLOR_GREEN,
        (m)?COLOR_BLUE_LT:0x99,
        COLOR_RED,
        (m)?0x66:0xE2,
        (m)?COLOR_YELLOW:0x66,
        COLOR_BLACK
    };


    if (!buf) {
        buf = malloc(screen_size);
        scr_buf = vid_get_bitmap_fb();
    }

    if (buf) {
        ++timer;
        img_buf=((mode_get()&MODE_MASK) == MODE_PLAY)?vid_get_viewport_fb_d():vid_get_viewport_fb();
        viewport_height = vid_get_viewport_height();
        switch (conf.zebra_mode) {
            case ZEBRA_MODE_ZEBRA_1:
                f = 4;
                break;
            case ZEBRA_MODE_ZEBRA_2:
                f = 8;
                break;
            case ZEBRA_MODE_SOLID:
                f = 1; 
                break;
            case ZEBRA_MODE_BLINKED_1:
                f = timer&2; 
                break;
            case ZEBRA_MODE_BLINKED_3:
                f = timer&8; 
                break;
            case ZEBRA_MODE_BLINKED_2:
            default:
                f = timer&4; 
                break;
        }
        if (!f) {
            if (need_restore) {
                if (conf.zebra_restore_screen || conf.zebra_restore_osd) {
                    draw_restore();
                } else {
                    memset(buf, COLOR_TRANSPARENT, screen_size);
                    gui_osd_draw_zebra_osd();
                    memcpy(scr_buf, buf, screen_size);
                    memcpy(scr_buf+screen_size, buf, screen_size);
                }
                need_restore=0;
            }
            return !(conf.zebra_restore_screen && conf.zebra_restore_osd);
        } else {
            int step_x, step_v;
            over = 255-conf.zebra_over;
                if (conf.zebra_multichannel) {step_x=2; step_v=6;} else {step_x=1; step_v=3;}
                for (s=0, y=1, v=0; y<=viewport_height; ++y) {
                    for (x=0; x<screen_width; x+=step_x, s+=step_x, v+=step_v) {
                        register int yy, uu, vv;
                        int sel;
                        yy = img_buf[v+1];
                         if (conf.zebra_multichannel) {
                          uu = (signed char)img_buf[v];
                          vv = (signed char)img_buf[v+2];
                          sel=0;
                          if (!((conf.zebra_mode == ZEBRA_MODE_ZEBRA_1 || conf.zebra_mode == ZEBRA_MODE_ZEBRA_2) && (y-x-timer)&f)) {
                           if (((yy<<12) +           vv*5743 + 2048)>>12>over) sel  = 4; // R
                           if (((yy<<12) - uu*1411 - vv*2925 + 2048)>>12>over) sel |= 2; // G
                           if (((yy<<12) + uu*7258           + 2048)>>12>over) sel |= 1; // B
                          }
                          buf[s]=buf[s+1]=cls[sel];
                         }
                        else if (((conf.zebra_mode == ZEBRA_MODE_ZEBRA_1 || conf.zebra_mode == ZEBRA_MODE_ZEBRA_2) && (y-x-timer)&f)) buf[s]=COLOR_TRANSPARENT;
                             else buf[s]=(yy>over)?cl_over:(yy<conf.zebra_under)?cl_under:COLOR_TRANSPARENT;
                    }
                    if (y*screen_height/viewport_height == (s+screen_width)/screen_width) {
                        memcpy(buf+s, buf+s-screen_width, screen_width);
                        s+=screen_width;
                    }
                }
            
            
            gui_osd_draw_zebra_osd();
            memcpy(scr_buf, buf, screen_size);
            memcpy(scr_buf+screen_size, buf, screen_size);

            need_restore=1;
            return 1;
        }
    }
    return 0;
}

//-------------------------------------------------------------------
static void gui_osd_draw_blended_histo(coord x, coord y) {
    register unsigned int i, v, red, grn, blu, sel;
    int m = ((mode_get()&MODE_MASK) == MODE_REC);
    color cls[] = {
        conf.histo_color>>8,
        (m)?0xDF:0xCC,
        COLOR_GREEN,
        (m)?COLOR_BLUE_LT:0x99,
        COLOR_RED,
        (m)?0x66:0xE2,
        (m)?COLOR_YELLOW:0x66,
        COLOR_WHITE
    };

    for (i=0; i<HISTO_WIDTH; ++i) {
        red = histogram[HISTO_R][i];
        grn = histogram[HISTO_G][i];
        blu = histogram[HISTO_B][i];

        for (v=1; v<HISTO_HEIGHT; ++v) {
            sel = 0;

            if (v < red) sel = 4;
            if (v < grn) sel |= 2;
            if (v < blu) sel |= 1;

            draw_pixel(x+1+i, y+HISTO_HEIGHT-v, cls[sel]);
        }
    }

    draw_rect(x, y, x+1+HISTO_WIDTH, y+HISTO_HEIGHT, conf.histo_color2&0xFF);
    //Vertical lines
    if (conf.histo_show_ev_grid) for (i=1;i<=4;i++) draw_line(x+(1+HISTO_WIDTH)*i/5, y, x+(1+HISTO_WIDTH)*i/5, y+HISTO_HEIGHT, conf.histo_color2&0xFF);

}

//-------------------------------------------------------------------
void gui_osd_draw_histo() {
    switch (conf.histo_layout) {
        case OSD_HISTO_LAYOUT_Y:
                gui_osd_draw_single_histo(HISTO_Y, conf.histo_pos.x, conf.histo_pos.y, 0);
                break;
        case OSD_HISTO_LAYOUT_A_Y:
                gui_osd_draw_single_histo(HISTO_RGB, conf.histo_pos.x, conf.histo_pos.y, 0);
                gui_osd_draw_single_histo(HISTO_Y, conf.histo_pos.x, conf.histo_pos.y+HISTO_HEIGHT, 0);
                break;
        case OSD_HISTO_LAYOUT_R_G_B:
                gui_osd_draw_single_histo(HISTO_R, conf.histo_pos.x, conf.histo_pos.y, 0);
                gui_osd_draw_single_histo(HISTO_G, conf.histo_pos.x, conf.histo_pos.y+HISTO_HEIGHT, 0);
                gui_osd_draw_single_histo(HISTO_B, conf.histo_pos.x, conf.histo_pos.y+HISTO_HEIGHT*2, 0);
                break;
        case OSD_HISTO_LAYOUT_A_yrgb:
                gui_osd_draw_single_histo(HISTO_RGB, conf.histo_pos.x, conf.histo_pos.y, 0);
                gui_osd_draw_single_histo(HISTO_Y, conf.histo_pos.x, conf.histo_pos.y+HISTO_HEIGHT, 1);
                gui_osd_draw_single_histo(HISTO_R, conf.histo_pos.x+HISTO_WIDTH/2+1, conf.histo_pos.y+HISTO_HEIGHT, 1);
                gui_osd_draw_single_histo(HISTO_G, conf.histo_pos.x, conf.histo_pos.y+HISTO_HEIGHT+HISTO_HEIGHT/2, 1);
                gui_osd_draw_single_histo(HISTO_B, conf.histo_pos.x+HISTO_WIDTH/2+1, conf.histo_pos.y+HISTO_HEIGHT+HISTO_HEIGHT/2, 1);
                break;
        case OSD_HISTO_LAYOUT_Y_argb:
                gui_osd_draw_single_histo(HISTO_Y, conf.histo_pos.x, conf.histo_pos.y, 0);
                gui_osd_draw_single_histo(HISTO_RGB, conf.histo_pos.x, conf.histo_pos.y+HISTO_HEIGHT, 1);
                gui_osd_draw_single_histo(HISTO_R, conf.histo_pos.x+HISTO_WIDTH/2+1, conf.histo_pos.y+HISTO_HEIGHT, 1);
                gui_osd_draw_single_histo(HISTO_G, conf.histo_pos.x, conf.histo_pos.y+HISTO_HEIGHT+HISTO_HEIGHT/2, 1);
                gui_osd_draw_single_histo(HISTO_B, conf.histo_pos.x+HISTO_WIDTH/2+1, conf.histo_pos.y+HISTO_HEIGHT+HISTO_HEIGHT/2, 1);
                break;
        case OSD_HISTO_LAYOUT_BLEND:
                gui_osd_draw_blended_histo(conf.histo_pos.x, conf.histo_pos.y);
                break;
        case OSD_HISTO_LAYOUT_BLEND_Y:
                gui_osd_draw_blended_histo(conf.histo_pos.x, conf.histo_pos.y);
                gui_osd_draw_single_histo(HISTO_Y, conf.histo_pos.x, conf.histo_pos.y+HISTO_HEIGHT, 0);
                break;
        case OSD_HISTO_LAYOUT_A:
        default:
                gui_osd_draw_single_histo(HISTO_RGB, conf.histo_pos.x, conf.histo_pos.y, 0);
                break;
    }

    if (conf.histo_layout != OSD_HISTO_LAYOUT_R_G_B) {
        if (under_exposed && conf.show_overexp) {
            draw_filled_ellipse(conf.histo_pos.x+5, conf.histo_pos.y+5, 3, 3, MAKE_COLOR(conf.histo_color2>>8, conf.histo_color2>>8));
        }

        if (over_exposed && conf.show_overexp) {
            draw_filled_ellipse(conf.histo_pos.x+HISTO_WIDTH-5, conf.histo_pos.y+5, 3, 3, MAKE_COLOR(conf.histo_color2>>8, conf.histo_color2>>8));
        }
    }

    if ((histo_magnification) || (conf.show_overexp )) {
        if ((conf.show_overexp ) && kbd_is_key_pressed(KEY_SHOOT_HALF) && (under_exposed || over_exposed))  
		   draw_string(conf.histo_pos.x+HISTO_WIDTH-FONT_WIDTH*3, conf.histo_pos.y-FONT_HEIGHT, "EXP", conf.histo_color);
        if (histo_magnification) {
		   sprintf(osd_buf, " %d.%02dx ", histo_magnification/1000, histo_magnification/10%100);
		   draw_string(conf.histo_pos.x, conf.histo_pos.y-FONT_HEIGHT, osd_buf, conf.histo_color);
           }
    } else {
        draw_filled_rect(conf.histo_pos.x, conf.histo_pos.y-FONT_HEIGHT, conf.histo_pos.x+8*FONT_WIDTH, conf.histo_pos.y-1, MAKE_COLOR(COLOR_TRANSPARENT, COLOR_TRANSPARENT));
    }
}

//-------------------------------------------------------------------
static void sprintf_dist(char *buf, float dist) {
// length of printed string is always 4
    if (dist<=0 || dist>=MAX_DIST) {
        sprintf(buf, " inf");
    } else if (dist<1000) {
        sprintf(buf, "0.%03d", (int)dist);
    } else if (dist<10000) {
        sprintf(buf, "%d.%02d", (int)(dist/1000), (int)(dist/10)%100);
    } else if (dist<100000) {
        sprintf(buf, "%02d.%d", (int)(dist/1000), (int)(dist/100)%10);
    } else {
        sprintf(buf, "%4d", (int)(dist/1000));
    }
}

static void sprintf_canon_values(char *buf, short dist) 
{
short v=((dist<0)?-dist:dist);	
sprintf(buf, "%s%d.%02d", ((dist<0)?"-":""), v/96, v%96);
}


//-------------------------------------------------------------------

void gui_osd_calc_dof() {
    
    int av, av_min, c_of_c, fl, v, v1, m;
    //long lfpfl=lens_get_focus_pos_fl();

#if defined(CAMERA_ixus700_sd500) || defined(CAMERA_ixus800_sd700) || defined(CAMERA_a560) || defined(CAMERA_ixus850_sd800) || defined(CAMERA_ixus70_sd1000) || defined(CAMERA_ixus950_sd850)    
    av=shooting_get_min_real_aperture();
#else
    av=shooting_get_real_aperture();
#endif
    fl=get_focal_length(lens_get_zoom_point());	
    dof.far_limit=-1.0;
    dof.near_limit=-1.0;
    dof.depth_of_field=-1.0;
    dof.hyperfocal_distance=-1.0;
    dof.subject_distance=-1.0;
        
    if ((av!=0) && (fl!=0)) {
      if (conf.dof_subj_dist_as_near_limit) {
      	v1=(fl*fl);
      	dof.near_limit=shooting_get_canon_subject_distance();
      	av_min=shooting_get_min_real_aperture();
        c_of_c=circle_of_confusion*10;
        if ((av_min!=0) && (c_of_c!=0)) dof.hyperfocal_distance=v1/(c_of_c*av_min);
    		if ((dof.near_limit>0) && (dof.near_limit<MAX_DIST)) {
    			v=(dof.hyperfocal_distance-dof.near_limit);
    			m=dof.hyperfocal_distance*dof.near_limit;
    			if ((v>0) && (m>0)) dof.subject_distance=m/v;  
       		}
        dof.hyperfocal_distance=v1/(c_of_c*av);
        if ((dof.subject_distance>0) && (dof.subject_distance<MAX_DIST)) {
          v = (dof.hyperfocal_distance-dof.subject_distance);
          m=dof.hyperfocal_distance*dof.subject_distance;
          if ((v>0) && (m>0))  dof.far_limit=m/v;
          dof.depth_of_field=dof.far_limit-dof.near_limit;
        }
     }
     else {	
       dof.subject_distance=shooting_get_canon_subject_distance();	
   	   dof.hyperfocal_distance=(fl*fl)/(10*circle_of_confusion*av);
       if (dof.subject_distance>0 && dof.subject_distance<MAX_DIST) {
       	  m = dof.hyperfocal_distance*dof.subject_distance;
          v = (dof.hyperfocal_distance+dof.subject_distance);
          if ((v>0) && (m>0))  dof.near_limit=m/v;
          v = (dof.hyperfocal_distance-dof.subject_distance);
          if ((v>0) && (m>0))  dof.far_limit=m/v;
          dof.depth_of_field=dof.far_limit-dof.near_limit;    
        }
     }  
    }
    if (conf.dof_dist_from_lens) {
      int h=shooting_get_lens_to_focal_plane_width();	
      if (dof.subject_distance>0) dof.subject_distance-=h;
      if (dof.far_limit>0) dof.far_limit-=h;
      if (dof.near_limit>0) dof.near_limit-=h;
      if (dof.hyperfocal_distance>0) dof.hyperfocal_distance-=h;
    }
}

void gui_osd_calc_expo_param() {
     
    expo.av96=shooting_get_av96();
    expo.tv96=shooting_get_tv96();
    expo.sv96=shooting_get_sv96();
    expo.iso=shooting_get_iso_real();
    expo.sv96_market=shooting_get_svm96();
    expo.iso_market=shooting_get_iso_market();
    expo.bv96_measured=shooting_get_bv96();
    expo.ev96_seted=expo.tv96+expo.av96; //Tv96+Av96
    expo.ev96_measured=expo.bv96_measured+expo.sv96;//Bv96+Sv96
    expo.dev96=expo.ev96_measured-expo.ev96_seted;// Ev96_external-Ev96_internal
    expo.bv96_seted=expo.ev96_seted-expo.sv96;
    expo.dev96_canon=shooting_get_canon_overexposure_value();
    expo.b=shooting_get_luminance();
}

void gui_osd_draw_dof() {

    //gui_osd_calc_dof();
    //strcpy(osd_buf, "");
    draw_string(conf.dof_pos.x, conf.dof_pos.y, "S/R1/R2:", conf.osd_color);
    sprintf_dist(osd_buf, dof.subject_distance);
    int i=strlen(osd_buf);
    osd_buf[i]='/';
    sprintf_dist(osd_buf+i+1, dof.near_limit);
    i=strlen(osd_buf);
    osd_buf[i]='/';
    sprintf_dist(osd_buf+i+1, dof.far_limit);
    draw_string(conf.dof_pos.x+8*FONT_WIDTH, conf.dof_pos.y, osd_buf, conf.osd_color);
    
	draw_string(conf.dof_pos.x, conf.dof_pos.y+FONT_HEIGHT, "DOF/HYP:", conf.osd_color);
    sprintf_dist(osd_buf, dof.depth_of_field);
    int j=strlen(osd_buf);
    osd_buf[j]='/';
    sprintf_dist(osd_buf+j+1, dof.hyperfocal_distance);
    draw_string(conf.dof_pos.x+8*FONT_WIDTH, conf.dof_pos.y+FONT_HEIGHT, osd_buf, conf.osd_color);
   
}

static short n, m; //string number

void gui_print_osd_state_string_int(const char * title, int value) {
  strcpy(osd_buf, title);
  sprintf(osd_buf+strlen(osd_buf), "%d", value);
  sprintf(osd_buf+strlen(osd_buf), "%12s", "");
  osd_buf[12]=0;
  draw_string(conf.mode_state_pos.x, conf.mode_state_pos.y+n, osd_buf, conf.osd_color);
  n+=FONT_HEIGHT;
}

void gui_print_osd_state_string_chr(const char *title, const char *value) {
  strcpy(osd_buf, title);
  sprintf(osd_buf+strlen(osd_buf), "%s", value);
  sprintf(osd_buf+strlen(osd_buf), "%12s", "");
  osd_buf[12]=0;    	
  draw_string(conf.mode_state_pos.x, conf.mode_state_pos.y+n, osd_buf, conf.osd_color);
  n+=FONT_HEIGHT;
}

void gui_print_osd_state_string_float(const char * title, const char * fmt, int divisor, int value) {
  strcpy(osd_buf, title);
  sprintf(osd_buf+strlen(osd_buf), fmt, (int)(value/divisor), (int)(value%divisor));
  sprintf(osd_buf+strlen(osd_buf), "%12s", "");
  osd_buf[12]=0;    	
  draw_string(conf.mode_state_pos.x, conf.mode_state_pos.y+n, osd_buf, conf.osd_color);
  n+=FONT_HEIGHT;
}

void gui_print_osd_misc_string_int(const char * title, int value) {
  strcpy(osd_buf, title);
  sprintf(osd_buf+strlen(osd_buf), "%d", value);
  sprintf(osd_buf+strlen(osd_buf), "%9s", "");
  osd_buf[9]=0;
  draw_string(conf.values_pos.x, conf.values_pos.y+m, osd_buf, conf.osd_color);
  m+=FONT_HEIGHT;
}

/*
void gui_print_osd_misc_string_float(const char * title, const char * fmt, int divisor, int value) {
  char s[16];	
  strcpy(osd_buf, title);
  sprintf(s, fmt, (int)(value/divisor), (int)(value%divisor));
  sprintf(osd_buf+strlen(osd_buf), "%6s", s);
  //osd_buf[8]=0;    	
  draw_string(conf.values_pos.x, conf.values_pos.y+m, osd_buf, conf.osd_color);
  m+=FONT_HEIGHT;
}
*/

void gui_print_osd_misc_string_float(const char * title, const char * fmt, int divisor, int value) {
  strcpy(osd_buf, title);
  sprintf(osd_buf+strlen(osd_buf), fmt, (int)(value/divisor), (int)(value%divisor));
  sprintf(osd_buf+strlen(osd_buf), "%9s", "");
  osd_buf[9]=0;
  draw_string(conf.values_pos.x, conf.values_pos.y+m, osd_buf, conf.osd_color);
  m+=FONT_HEIGHT;
}


void gui_print_osd_misc_string_dist(const char * title, int value) {
  strcpy(osd_buf, title);
  sprintf_dist(osd_buf+strlen(osd_buf), (float)value);
  sprintf(osd_buf+strlen(osd_buf), "%9s", "");
  osd_buf[9]=0;
  draw_string(conf.values_pos.x, conf.values_pos.y+m, osd_buf, conf.osd_color);
  m+=FONT_HEIGHT;
}

void gui_print_osd_misc_string_canon_values(const char * title, short value) {
  strcpy(osd_buf, title);
  sprintf_canon_values(osd_buf+strlen(osd_buf), value);
  sprintf(osd_buf+strlen(osd_buf), "%9s", "");
  osd_buf[9]=0;
  draw_string(conf.values_pos.x, conf.values_pos.y+m, osd_buf, conf.osd_color);
  m+=FONT_HEIGHT;
}

//-------------------------------------------------------------------
void gui_osd_draw_raw_info() 
    {
    int x, camera_jpeg_count,jpeg_size,raw_and_jpeg_count,raw_size;
    static int b;
    
    if (conf.show_remaining_raw) 
      {
            raw_size = hook_raw_size() / 1024;
            camera_jpeg_count = atoi(camera_jpeg_count_str());
            
            if (camera_jpeg_count>0)
                {
                jpeg_size=GetFreeCardSpaceKb()/camera_jpeg_count;
                raw_and_jpeg_count=GetFreeCardSpaceKb()/(raw_size+jpeg_size);
                }
            else
                raw_and_jpeg_count=0;
 
            if (raw_and_jpeg_count>0)
                {
                sprintf(osd_buf, "RAW:%3d", raw_and_jpeg_count);
                draw_string(conf.mode_raw_pos.x, conf.mode_raw_pos.y, osd_buf, conf.osd_color);
                }
            else
                {
                sprintf(osd_buf, "DISK FULL!");

                if (conf.mode_raw_pos.x<=3*FONT_WIDTH) 
                    x = 4*FONT_WIDTH;
                else
                    x = conf.mode_raw_pos.x;
                
                if (b > 6)
                    {
                    draw_string(x-3*FONT_WIDTH, conf.mode_raw_pos.y, osd_buf, conf.osd_color_warn); 
                    b = (b>12) ? 0 : b+1;
                    }
                else
                    {
                    draw_string(x-3*FONT_WIDTH, conf.mode_raw_pos.y, osd_buf, conf.osd_color); 
                    b = b+1;
                    } 
                }
         }
    else draw_string(conf.mode_raw_pos.x, conf.mode_raw_pos.y, "RAW", conf.osd_color);
	            
}
//-------------------------------------------------------------------
void gui_osd_draw_state() {
    int a,  gui_mode=gui_get_mode(), m=(mode_get()&MODE_SHOOTING_MASK); 
    long t; 
    
    n=0;

   if (((conf.tv_override_value) && (conf.tv_override_koef)) || gui_mode==GUI_MODE_OSD){
    	if(kbd_is_key_pressed(KEY_SHOOT_HALF)) 
		  { 
		  t=(int)(shooting_get_shutter_speed_from_tv96(shooting_get_tv96())*100000);	
		  gui_print_osd_state_string_float("TV:", "%d.%05d ", 100000, t);
		  }
    	else 
		 {
    	 if (conf.tv_enum_type) gui_print_osd_state_string_chr("TV:",shooting_get_tv_override_value()); 
         else  
          {
		  t=(int)(shooting_get_shutter_speed_override_value()*100000);
          gui_print_osd_state_string_float("TV:", "%d.%05d ", 100000, t);
          }
       }
    }
    if (conf.av_override_value || gui_mode==GUI_MODE_OSD) gui_print_osd_state_string_float("AV:", "%d.%02d ", 100, shooting_get_aperture_from_av96(shooting_get_av96_override_value()));
#if defined (CAMERA_ixus700_sd500) || defined (CAMERA_ixus800_sd700) || defined (CAMERA_ixus70_sd1000) || defined (CAMERA_a560) || defined (CAMERA_a570) || defined (CAMERA_a710) ||  defined (CAMERA_g7)    
    if (conf.nd_filter_state || gui_mode==GUI_MODE_OSD) gui_print_osd_state_string_chr("NDFILTER:", ((conf.nd_filter_state==1)?"IN":"OUT"));
#endif    
    if ((conf.subj_dist_override_value && conf.subj_dist_override_koef && shooting_can_focus()) || ((gui_mode==GUI_MODE_ALT) && shooting_get_common_focus_mode())	|| gui_mode==GUI_MODE_OSD)   {
    	gui_print_osd_state_string_int("SD:",shooting_get_subject_distance_override_value());
        if (gui_mode==GUI_MODE_ALT)  gui_print_osd_state_string_int("FACTOR:",shooting_get_subject_distance_override_koef());   	
      }
    if ((conf.iso_override_value && conf.iso_override_koef)	 || gui_mode==GUI_MODE_OSD)
    	gui_print_osd_state_string_int("ISO:", shooting_get_iso_override_value());
    if ((gui_mode==GUI_MODE_OSD) || (shooting_get_drive_mode())) {
    if ((conf.tv_bracket_value) || (conf.av_bracket_value)  || (conf.iso_bracket_value && conf.iso_bracket_koef) || ((conf.subj_dist_bracket_value) && (conf.subj_dist_bracket_koef) && (shooting_can_focus())))  
        gui_print_osd_state_string_chr("BRACKET:", shooting_get_bracket_type());
      if (conf.tv_bracket_value)  gui_print_osd_state_string_chr("TV:", shooting_get_tv_bracket_value());
      else if  (conf.av_bracket_value) gui_print_osd_state_string_chr("AV:", shooting_get_av_bracket_value());
      else if  (conf.iso_bracket_value && conf.iso_bracket_koef) gui_print_osd_state_string_int("ISO:", shooting_get_iso_bracket_value());
      else if  ((conf.subj_dist_bracket_value) && (conf.subj_dist_bracket_koef) && (shooting_can_focus()))
         gui_print_osd_state_string_int("SD:",shooting_get_subject_distance_bracket_value());
     }
     
/*
 draw_string(conf.mode_state_pos.x, conf.mode_state_pos.y+n, get_debug(), conf.osd_color);
        n+=FONT_HEIGHT;*/
}

//-------------------------------------------------------------------
void gui_osd_draw_values(int showtype) {
    int iso_mode=shooting_get_iso_mode();
    float s=-1.0f;
    
    m=0;
    
    //gui_osd_calc_expo_param();
    
    if (conf.values_show_zoom) {
     int fl, zp=lens_get_zoom_point(), fl1=get_focal_length(zp);     
     switch (conf.zoom_value) {
         case ZOOM_SHOW_FL:
             sprintf(osd_buf, "Z:%d.%dmm%8s", fl1/1000, fl1%1000/100, "");
             break;
         case ZOOM_SHOW_EFL:
             fl=get_effective_focal_length(zp);
             sprintf(osd_buf, "Z:%3dmm%8s", fl/1000, "");
             break;
         case ZOOM_SHOW_X:
         default:
             fl=get_zoom_x(zp);
             sprintf(osd_buf, "Z:%ld/%d.%dx%8s", zp, fl/10, fl%10, "");
             break;
     }
     osd_buf[9]=0;
     draw_string(conf.values_pos.x, conf.values_pos.y, osd_buf, conf.osd_color);
     m+=FONT_HEIGHT;
    }
    
    
    if ((conf.values_show_real_aperture) && (showtype==1)) 
	     gui_print_osd_misc_string_float("Av :", "%d.%02d ", 100, shooting_get_real_aperture());
    if ((conf.show_dof==DOF_SHOW_IN_MISC) && (showtype)) { 
    	 //if (kbd_is_key_pressed(KEY_SHOOT_HALF) && (mode_photo || (m&MODE_SHOOTING_MASK)==MODE_STITCH)) 	
    	 //gui_osd_calc_dof();
    	 if (conf.dof_subj_dist_in_misc) gui_print_osd_misc_string_dist("SD :", dof.subject_distance);
         if (conf.dof_near_limit_in_misc) gui_print_osd_misc_string_dist("NL :", dof.near_limit);
    	 if (conf.dof_far_limit_in_misc) gui_print_osd_misc_string_dist("FL :", dof.far_limit);
         if (conf.dof_depth_in_misc) gui_print_osd_misc_string_dist("DOF:", dof.depth_of_field);
         if (conf.dof_hyperfocal_in_misc) gui_print_osd_misc_string_dist("HYP:", dof.hyperfocal_distance);
    }
    if (showtype==1) {
      if ((iso_mode <= 0) || !(conf.values_show_iso_only_in_autoiso_mode)) {
          if (conf.values_show_real_iso) gui_print_osd_misc_string_int("I-R:", expo.iso);
          if (conf.values_show_market_iso) gui_print_osd_misc_string_int("I-M:", expo.iso_market);
      }
      if (conf.values_show_bv_measured) gui_print_osd_misc_string_canon_values("Bvm:", expo.bv96_measured	);
      if (conf.values_show_bv_seted) gui_print_osd_misc_string_canon_values("Bvs:", expo.bv96_seted	);
      if (conf.values_show_ev_measured) gui_print_osd_misc_string_canon_values("Evm:", expo.ev96_measured);
      if (conf.values_show_ev_seted	) gui_print_osd_misc_string_canon_values("Evs:", expo.ev96_seted	);
      if (conf.values_show_overexposure) gui_print_osd_misc_string_canon_values("dE :", expo.dev96);
      if (conf.values_show_canon_overexposure	) gui_print_osd_misc_string_canon_values("dEc:", expo.dev96_canon);
      if (conf.values_show_luminance) gui_print_osd_misc_string_float("B  :", "%d.%02d ", 100, expo.b);
    }
}
//-------------------------------------------------------------------
void gui_osd_draw_clock() {
    unsigned long t;
    static struct tm *ttm;

    t = time(NULL);
    ttm = localtime(&t);
    sprintf(osd_buf, "%2u:%02u", ttm->tm_hour, ttm->tm_min);
    draw_string(conf.clock_pos.x, conf.clock_pos.y, osd_buf, conf.osd_color);
}

//-------------------------------------------------------------------
