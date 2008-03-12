#include "stdlib.h"
#include "keyboard.h"
#include "platform.h"
#include "core.h"
#include "lang.h"
#include "conf.h"
#include "gui.h"
#include "gui_draw.h"
#include "gui_lang.h"
#include "gui_batt.h"
#include "gui_mbox.h"
#include "gui_sokoban.h"

//-------------------------------------------------------------------
#define FIELD_WIDTH             15
#define FIELD_HEIGHT            15

#define SCREEN_COLOR            0xF7
#define WALL_COLOR_1            COLOR_GREY
#define WALL_COLOR_2            COLOR_BLACK
#define BOX_COLOR_1             0x26
#define BOX_COLOR_2             COLOR_BLACK
#define BOX_COLOR_3             0x66
#define PLACE_COLOR_1           0x99
#define PLACE_COLOR_2           COLOR_BLACK
#define PLAYER_COLOR_1          COLOR_GREEN
#define PLAYER_COLOR_2          COLOR_BLACK

#define MARKER_WALL             '#'
#define MARKER_BOX              '$'
#define MARKER_PLACE            '.'
#define MARKER_BOX_PLACE        '*'
#define MARKER_PLAYER           '@'
#define MARKER_PLAYER_PLACE     '+'
#define MARKER_EMPTY            ' '

#define UNDO_SIZE               1000

//-------------------------------------------------------------------
#include "gui_sokoban_levels.h"
#define NUM_LEVELS (sizeof(fields)/sizeof(fields[0]))

static int need_redraw;
static int  moves;
static char field[FIELD_HEIGHT][FIELD_WIDTH];

static int cell_size;
static int xPl, yPl;

static int undo[UNDO_SIZE/10];
static int undo_begin, undo_end, undo_curr;

//-------------------------------------------------------------------
static void sokoban_undo_add(int dx, int dy, int box) {
    int offs, bits, value;

    value = ((box)?1:0)<<2;
    if (dx) {
        value |= ((dx<0)?1:0)<<1;
    } else {
        value |= (((dy<0)?1:0)<<1)|1;
    }
    
    offs = undo_curr/10;
    bits = (undo_curr%10)*3;
    undo[offs] &= ~(7<<bits);
    undo[offs] |= (value&7)<<bits;

    if (++undo_curr==UNDO_SIZE) undo_curr=0;
    if (undo_curr==undo_begin) {
        if (++undo_begin==UNDO_SIZE) undo_begin=0;
    }
    undo_end=undo_curr;
} 

//-------------------------------------------------------------------
static void sokoban_undo() {
    int dx=0, dy=0, value;
    
    if (undo_curr!=undo_begin) {
        if (undo_curr==0) undo_curr=UNDO_SIZE;
        --undo_curr;
        
        value = (undo[undo_curr/10]>>((undo_curr%10)*3))&7;
        if (value&1) dy=1; else dx=1;
        if (value&2) {dy=-dy; dx=-dx;}

        field[yPl][xPl]=(field[yPl][xPl]==MARKER_PLAYER_PLACE)?MARKER_PLACE:MARKER_EMPTY;
        if (value&4) {
            field[yPl+dy][xPl+dx]=(field[yPl+dy][xPl+dx]==MARKER_BOX_PLACE)?MARKER_PLACE:MARKER_EMPTY;
            field[yPl][xPl]=(field[yPl][xPl]==MARKER_PLACE)?MARKER_BOX_PLACE:MARKER_BOX;
        }
        xPl-=dx; yPl-=dy;
        field[yPl][xPl]=(field[yPl][xPl]==MARKER_PLACE)?MARKER_PLAYER_PLACE:MARKER_PLAYER;
        --moves;
    }
}

//-------------------------------------------------------------------
static void sokoban_redo() {
    int dx=0, dy=0, value;
    
    if (undo_curr!=undo_end) {
        value = (undo[undo_curr/10]>>((undo_curr%10)*3))&7;
        if (value&1) dy=1; else dx=1;
        if (value&2) {dy=-dy; dx=-dx;}

        field[yPl][xPl]=(field[yPl][xPl]==MARKER_PLAYER_PLACE)?MARKER_PLACE:MARKER_EMPTY;
        xPl+=dx; yPl+=dy;
        if (value&4) {
            field[yPl][xPl]=(field[yPl][xPl]==MARKER_BOX_PLACE)?MARKER_PLACE:MARKER_EMPTY;
            field[yPl+dy][xPl+dx]=(field[yPl+dy][xPl+dx]==MARKER_PLACE)?MARKER_BOX_PLACE:MARKER_BOX;
        }
        field[yPl][xPl]=(field[yPl][xPl]==MARKER_PLACE)?MARKER_PLAYER_PLACE:MARKER_PLAYER;
        ++moves;

        ++undo_curr;
        if (undo_curr==UNDO_SIZE) undo_curr=0;
    }
}

//-------------------------------------------------------------------
static void sokoban_undo_reset() {
    undo_begin=undo_end=undo_curr=0;
}

//-------------------------------------------------------------------
static void sokoban_set_level(int lvl) {
    int x=0, y, w=0, h=0;
    const char *p=fields[lvl];

    // determine dimensions
    while (*p) {
      if (*p=='|') {
          ++h;
          if (x>w) w=x;
          x=0;
      } else {
          ++x;
      }
      ++p;
    }
    if (x>w) w=x;

    // clear field
    for (y=0; y<FIELD_HEIGHT; ++y)
        for (x=0; x<FIELD_WIDTH; ++x)
            field[y][x]=MARKER_EMPTY;
    
    // place maze at the center
    p=fields[lvl];
    for (y=(FIELD_HEIGHT-h)/2; y<FIELD_HEIGHT; ++y, ++p) {
        for (x=(FIELD_WIDTH-w)/2; x<FIELD_WIDTH && *p && *p!='|'; ++x, ++p) {
            field[y][x]=*p;
            if (field[y][x] == MARKER_PLAYER || field[y][x] == MARKER_PLAYER_PLACE) {
              xPl = x; yPl = y;
            }
        }
        if (!*p) break;
    }

    conf.sokoban_level = lvl;
    moves = 0;
    sokoban_undo_reset();
}

//-------------------------------------------------------------------
static int sokoban_finished() {
    int x, y;

    for (y=0; y<FIELD_HEIGHT; ++y)
        for (x=0; x<FIELD_WIDTH; ++x)
            if (field[y][x]==MARKER_BOX) 
                return 0;
    return 1;
}

//-------------------------------------------------------------------
static void sokoban_next_level() {
    if (++conf.sokoban_level >= NUM_LEVELS) conf.sokoban_level = 0;
    sokoban_set_level(conf.sokoban_level);
    need_redraw = 1;
}

//-------------------------------------------------------------------
static int sokoban_move(int dx, int dy) {
    switch (field[yPl+dy][xPl+dx]) {
        case MARKER_WALL:
            return 0;
            break;
        case MARKER_BOX:
        case MARKER_BOX_PLACE:
            if (field[yPl+dy*2][xPl+dx*2]==MARKER_WALL || field[yPl+dy*2][xPl+dx*2]==MARKER_BOX || field[yPl+dy*2][xPl+dx*2]==MARKER_BOX_PLACE)
                return 0;
            break;
        case MARKER_PLACE:
        case MARKER_EMPTY:
            break;
    }
    field[yPl][xPl]=(field[yPl][xPl]==MARKER_PLAYER_PLACE)?MARKER_PLACE:MARKER_EMPTY;
    xPl+=dx; yPl+=dy;
    if (field[yPl][xPl]==MARKER_BOX || field[yPl][xPl]==MARKER_BOX_PLACE) {
        field[yPl][xPl]=(field[yPl][xPl]==MARKER_BOX_PLACE)?MARKER_PLACE:MARKER_EMPTY;
        field[yPl+dy][xPl+dx]=(field[yPl+dy][xPl+dx]==MARKER_PLACE)?MARKER_BOX_PLACE:MARKER_BOX;
        sokoban_undo_add(dx, dy, 1);
    } else {
        sokoban_undo_add(dx, dy, 0);
    }
    field[yPl][xPl]=(field[yPl][xPl]==MARKER_PLACE)?MARKER_PLAYER_PLACE:MARKER_PLAYER;
    return 1;
}

//-------------------------------------------------------------------
static void sokoban_draw_box(int x, int y, color cl) {
    draw_filled_rect(x*cell_size, y*cell_size, x*cell_size+cell_size-1, y*cell_size+cell_size-1, cl);
    draw_line(x*cell_size+2, y*cell_size, x*cell_size+2, y*cell_size+cell_size-1, cl);
    draw_line(x*cell_size+cell_size-1-2, y*cell_size, x*cell_size+cell_size-1-2, y*cell_size+cell_size-1, cl);
    draw_line(x*cell_size+2, y*cell_size+2, x*cell_size+cell_size-1-2, y*cell_size+2, cl);
    draw_line(x*cell_size+2, y*cell_size+cell_size-1-2, x*cell_size+cell_size-1-2, y*cell_size+cell_size-1-2, cl);
}

//-------------------------------------------------------------------
void gui_sokoban_init() {
    cell_size = screen_height/FIELD_HEIGHT;
    sokoban_set_level(conf.sokoban_level);
    need_redraw = 1;
}

//-------------------------------------------------------------------
void gui_sokoban_kbd_process() {
    switch (kbd_get_autoclicked_key()) {
        case KEY_UP:
            moves+=sokoban_move(0, -1);
            need_redraw = 1;
            break;
        case KEY_DOWN:
            moves+=sokoban_move(0, +1);
            need_redraw = 1;
            break;
        case KEY_LEFT:
            moves+=sokoban_move(-1, 0);
            need_redraw = 1;
            break;
        case KEY_RIGHT:
            moves+=sokoban_move(+1, 0);
            need_redraw = 1;
            break;
        case KEY_SET:
            if (moves == 0) {
                sokoban_next_level();
            }
            break;
        case KEY_ZOOM_OUT:
            sokoban_undo();
            need_redraw = 1;
            break;
        case KEY_ZOOM_IN:
            sokoban_redo();
            need_redraw = 1;
            break;
     #if defined (CAMERA_ixus700_sd500) || defined (CAMERA_ixus800_sd700) || defined (CAMERA_a560) || defined (CAMERA_ixus850_sd800) || defined (CAMERA_ixus70_sd1000) || defined (CAMERA_a460) || defined(CAMERA_ixus55_sd450) || defined(CAMERA_a550)
        case KEY_DISPLAY:
     #else
        case KEY_ERASE:
     #endif
            sokoban_set_level(conf.sokoban_level);
            need_redraw = 1;
            break;
     #if !defined (CAMERA_ixus700_sd500) && !defined (CAMERA_ixus800_sd700) && !defined (CAMERA_a560) && !defined (CAMERA_ixus850_sd800) && !defined (CAMERA_ixus70_sd1000) && !defined (CAMERA_a460) && !defined(CAMERA_ixus55_sd450) && !defined(CAMERA_a550)
        case KEY_DISPLAY:
            gui_mbox_init(LANG_MBOX_ABOUT_TITLE, (int)"SOKOBAN\n(c) GrAnd, 2007", MBOX_TEXT_CENTER, NULL);
            need_redraw = 1;
            break;
     #endif
    }
}

//-------------------------------------------------------------------
void gui_sokoban_draw() {
    int y, x;
    static char str[16];

    if (need_redraw) {
        need_redraw = 0;
        for (y=0; y<FIELD_HEIGHT; ++y) {
            for (x=0; x<FIELD_WIDTH; ++x) {
                switch (field[y][x]) {
                    case MARKER_WALL:
                        draw_filled_rect(x*cell_size, y*cell_size, x*cell_size+cell_size-1, y*cell_size+cell_size-1, MAKE_COLOR(WALL_COLOR_1, WALL_COLOR_2));
                        break;
                    case MARKER_BOX:
                        sokoban_draw_box(x, y, MAKE_COLOR(BOX_COLOR_1, BOX_COLOR_2));
                        break;
                    case MARKER_PLACE:
                        draw_filled_rect(x*cell_size, y*cell_size, x*cell_size+cell_size-1, y*cell_size+cell_size-1, MAKE_COLOR(SCREEN_COLOR, SCREEN_COLOR));
                        draw_filled_rect(x*cell_size+4, y*cell_size+4, x*cell_size+cell_size-1-4, y*cell_size+cell_size-1-4, MAKE_COLOR(PLACE_COLOR_1, PLACE_COLOR_2));
                        break;
                    case MARKER_BOX_PLACE:
                        sokoban_draw_box(x, y, MAKE_COLOR(BOX_COLOR_3, BOX_COLOR_2));
                        break;
                    case MARKER_PLAYER:
                    case MARKER_PLAYER_PLACE:
                        draw_filled_rect(x*cell_size, y*cell_size, x*cell_size+cell_size-1, y*cell_size+cell_size-1, MAKE_COLOR(SCREEN_COLOR, SCREEN_COLOR));
                        draw_filled_ellipse(x*cell_size+(cell_size>>1)-1, y*cell_size+(cell_size>>1)-1, (cell_size>>1)-3, (cell_size>>1)-3, MAKE_COLOR(PLAYER_COLOR_1, PLAYER_COLOR_2));
                        break;
                    case MARKER_EMPTY:
                    default:
                        draw_filled_rect(x*cell_size, y*cell_size, x*cell_size+cell_size-1, y*cell_size+cell_size-1, MAKE_COLOR(SCREEN_COLOR, SCREEN_COLOR));
                        break;
                }
            }
        }

        draw_line(cell_size*FIELD_WIDTH, 0, cell_size*FIELD_WIDTH, screen_height-1, COLOR_WHITE);
        draw_line(cell_size*FIELD_WIDTH+1, 0, cell_size*FIELD_WIDTH+1, screen_height-1, COLOR_BLACK);

        draw_filled_rect(cell_size*FIELD_WIDTH+2, 0, screen_width-1, 7, MAKE_COLOR(SCREEN_COLOR, SCREEN_COLOR));

        sprintf(str, "%s: %-6d", lang_str(LANG_SOKOBAN_TEXT_LEVEL), conf.sokoban_level+1);
        draw_string(cell_size*FIELD_WIDTH+2, 8, str, MAKE_COLOR(SCREEN_COLOR, COLOR_WHITE));
        sprintf(str, "%s: %-6d", lang_str(LANG_SOKOBAN_TEXT_MOVES), moves);
        draw_string(cell_size*FIELD_WIDTH+2, 8+FONT_HEIGHT, str, MAKE_COLOR(SCREEN_COLOR, COLOR_WHITE));

        draw_filled_rect(cell_size*FIELD_WIDTH+2, 8+FONT_HEIGHT*2, screen_width-1, screen_height-1, MAKE_COLOR(SCREEN_COLOR, SCREEN_COLOR));

        if (sokoban_finished()) {
            gui_mbox_init(LANG_SOKOBAN_MSG_FINISH_TITLE, LANG_SOKOBAN_MSG_FINISH_TEXT, MBOX_TEXT_CENTER, NULL);
            sokoban_next_level();
        }
    }

    sprintf(str, "Batt:%3d%%", get_batt_perc());
    draw_txt_string(screen_width/FONT_WIDTH-2-9, screen_height/FONT_HEIGHT-1, str, MAKE_COLOR(SCREEN_COLOR, COLOR_WHITE));
}

