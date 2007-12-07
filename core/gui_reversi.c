#include "stdlib.h"
#include "keyboard.h"
#include "platform.h"
#include "core.h"
#include "lang.h"
#include "gui.h"
#include "gui_draw.h"
#include "gui_lang.h"
#include "gui_batt.h"
#include "gui_mbox.h"
#include "gui_reversi.h"

//-------------------------------------------------------------------
#define FIELD_EMPTY             0
#define FIELD_PLAYER1           1
#define FIELD_PLAYER2           2
#define COMPUTER_ONLY           3


#define SCREEN_COLOR            0xF7
#define FIELD_COLOR_WHITE       0xF3
#define FIELD_COLOR_BLACK       0xFE
#define MARKER_COLOR_WHITE      0x33
#define MARKER_COLOR_BLACK      0xFF
#define SELECTED_COLOR          0x9B


//-------------------------------------------------------------------
typedef unsigned char uchar;

//-------------------------------------------------------------------
static uchar Field[8][8];
static uchar Plr;
static uchar CurrPlayer, Computer, InGame=0, NumPl1, NumPl2;

static unsigned short field_size, field_x, field_y, cell_size;

static uchar xPos=3, yPos=3;
static volatile uchar need_redraw = 0, need_redraw_all = 0;

static char buf[128];

//-------------------------------------------------------------------
static void redraw();
static void redrawstatus();

//-------------------------------------------------------------------
static uchar NotPlayer(uchar Pl) {
    if (Pl==FIELD_PLAYER1)
        return FIELD_PLAYER2;
    else
        return FIELD_PLAYER1;
}

//-------------------------------------------------------------------
static void InitField() {
    uchar x, y;
 
    for (x=0; x<8; ++x)
        for (y=0; y<8; ++y)
            Field[x][y]=FIELD_EMPTY;
    
    Field[3][3] = Field[4][4] = FIELD_PLAYER1;
    Field[3][4] = Field[4][3] = FIELD_PLAYER2;
}

//-------------------------------------------------------------------
static uchar GetNum(uchar Player) {
    uchar x, y, N=0;
    
    for (x=0; x<8; ++x)
        for (y=0; y<8; ++y)
            if (Field[x][y]==Player) ++N;
        
    return N;
}

//-------------------------------------------------------------------
static uchar Place(uchar x, uchar y, uchar Player, uchar Placed) {
/*0..64 - Ok 
 0xFF - not empty*/
    int I, J, x1, y1;
    uchar Eated, E;
 
    if (Field[x][y]!=FIELD_EMPTY) {
        return 0xFF;
    } else {
        Eated=0;
        for (I=-1;I<=1;I++) {
            for (J=-1;J<=1;J++) {
                E=0;
                x1=x+I;
                y1=y+J;
                while (((x1>=0) && (x1<8) && (y1>=0) && (y1<8)) && (Field[x1][y1]!=FIELD_EMPTY) && (Field[x1][y1]!=Player)) {
                    E++;
                    x1=x1+I;
                    y1=y1+J;
                }
                if ((Placed) && ((x1>=0) && (x1<8) && (y1>=0) && (y1<8)) && (Field[x1][y1]!=FIELD_EMPTY) && (E>0)) {
                    Field[x][y]=Player;
                    x1=x+I;
                    y1=y+J;
                    while (((x1>=0) && (x1<8) && (y1>=0) && (y1<8)) && (Field[x1][y1]!=FIELD_EMPTY) && (Field[x1][y1]!=Player)) {
                        Field[x1][y1]=Player;
                        x1=x1+I;
                        y1=y1+J;
                    }
                }
                if (((x1>=0) && (x1<8) && (y1>=0) && (y1<8)) && (Field[x1][y1]!=FIELD_EMPTY))
                    Eated+=E;
            }
        }
        return Eated;
    }
}

//-------------------------------------------------------------------
static uchar ComputerPlace(uchar Player) {
    static const uchar PlaceTable[8][8] ={{1,8,2,2,2,2,8,1},
                                          {8,8,6,5,5,6,8,8},
                                          {2,6,4,3,3,4,6,2},
                                          {2,5,3,1,1,3,5,2},
                                          {2,5,3,1,1,3,5,2},
                                          {2,6,4,3,3,4,6,2},
                                          {8,8,6,5,5,6,8,8},
                                          {1,8,2,2,2,2,8,1}};
    uchar PlX[61];
    uchar PlY[61];
    uchar NPl=0, I, J, MaxE=0, E, MinPr=9;
    
    for (I=0; I<8; I++) {
        for (J=0; J<8; J++) {
            E=Place(I, J, Player, 0);
            if ((MinPr>PlaceTable[I][J]) && (E<0xFF) && (E>0)) {
                MinPr=PlaceTable[I][J];
                NPl=0;
                MaxE=0;
            }
            if ((E<0xFF) && (MinPr==PlaceTable[I][J])) {
                if (E>MaxE) {
                    MaxE=E;
                    NPl=1;
                    PlX[1]=I;
                    PlY[1]=J;
                } else {
                    if (E==MaxE) {
                        NPl++;
                        PlX[NPl]=I;
                        PlY[NPl]=J;
                    }
                }
            }
        }
    }
//    E=1;
    srand(get_tick_count());
    E=(rand()%NPl)+1;
    Place(PlX[E],PlY[E],Player,1);
    return ((PlX[E] << 4) | PlY[E]);
}

//-------------------------------------------------------------------
static uchar CanPlace(uchar Player) {
    uchar I, J, E=0, E1;
 
    for (I=0;I<8;I++) {
        for (J=0;J<8;J++) {
            E1=Place(I,J,Player,0);
            if (E1<0xFF) E+=E1;
        }
    }
    return (E>0);
}

//-------------------------------------------------------------------
static void Result() {
    if (NumPl1>NumPl2)
        gui_mbox_init(LANG_REVERSI_MSG_RESULTS_TITLE, LANG_REVERSI_MSG_RESULTS_WON, MBOX_TEXT_CENTER, NULL);
    else if (NumPl1<NumPl2)
        gui_mbox_init(LANG_REVERSI_MSG_RESULTS_TITLE, LANG_REVERSI_MSG_RESULTS_LOST, MBOX_TEXT_CENTER, NULL);
    else
        gui_mbox_init(LANG_REVERSI_MSG_RESULTS_TITLE, LANG_REVERSI_MSG_RESULTS_DRAW, MBOX_TEXT_CENTER, NULL);
    redraw();
    redrawstatus();
    need_redraw_all = 1;
}

//-------------------------------------------------------------------
static void DrawCell(uchar x, uchar y) {
    draw_filled_rect(field_x+cell_size*x, field_y+cell_size*y, 
                     field_x+cell_size*(x+1), field_y+cell_size*(y+1), 
                     (x==xPos && y==yPos)?MAKE_COLOR(SELECTED_COLOR, COLOR_RED):((x+y)&1)?MAKE_COLOR(FIELD_COLOR_WHITE, COLOR_WHITE):MAKE_COLOR(FIELD_COLOR_BLACK, COLOR_WHITE));
}

//-------------------------------------------------------------------
static void DrawMainWindow() {
    uchar x, y;

    draw_filled_rect(0, 0, screen_width-1, screen_height-1, MAKE_COLOR(SCREEN_COLOR, SCREEN_COLOR));
    for (y=0; y<8; ++y) {
        for (x=0; x<8; ++x) {
            DrawCell(x, y);
        }
    }
    for (x=0; x<8; ++x) {
        draw_char(field_x+cell_size*x+((cell_size-FONT_WIDTH)>>1)+1,  field_y-FONT_HEIGHT-1, '1'+x,  MAKE_COLOR(SCREEN_COLOR, COLOR_WHITE));
        draw_char(field_x+cell_size*x+((cell_size-FONT_WIDTH)>>1)+1,  field_y+field_size+3,  '1'+x,  MAKE_COLOR(SCREEN_COLOR, COLOR_WHITE));
    }
    for (y=0; y<8; ++y) {
        draw_char(field_x-FONT_WIDTH-4,  field_y+cell_size*y+((cell_size-FONT_HEIGHT)>>1)+1, 'A'+y,  MAKE_COLOR(SCREEN_COLOR, COLOR_WHITE));
        draw_char(field_x+field_size+3,  field_y+cell_size*y+((cell_size-FONT_HEIGHT)>>1)+1, 'A'+y,  MAKE_COLOR(SCREEN_COLOR, COLOR_WHITE));
    }
}

//-------------------------------------------------------------------
static void InitMainWindow() {
    NumPl1=GetNum(FIELD_PLAYER1);
    NumPl2=GetNum(FIELD_PLAYER2);
    CurrPlayer=FIELD_PLAYER1;
    Computer=FIELD_PLAYER2;
    InGame=0;

    field_size = (screen_height-2*FONT_HEIGHT-4)&0xFFF8;
    field_x = FONT_WIDTH+8;
    field_y = (screen_height-field_size)>>1;
    cell_size = field_size >> 3;

//    DrawMainWindow(); 
}

//-------------------------------------------------------------------
static void NewGame() {
    InitField();
    CurrPlayer=FIELD_PLAYER1;
    Computer=FIELD_PLAYER2;
    NumPl1=2;
    NumPl2=2;
    xPos = yPos = 3;
    InGame=1;
    need_redraw = 1;
}

//-------------------------------------------------------------------
static void Clk(uchar x, uchar y) {
    uchar Placed;
 
    if ((CurrPlayer==Computer) || (! InGame) || (Computer==COMPUTER_ONLY))
        ;
    else {
        Placed=Place(x,y ,CurrPlayer,0);
        if (Placed==0) { 
            gui_mbox_init(LANG_REVERSI_MSG_WRONG_TITLE, LANG_REVERSI_MSG_WRONG_TEXT_1, MBOX_TEXT_CENTER, NULL);
            need_redraw_all = 1;
        } else if (Placed==0xFF) { 
            gui_mbox_init(LANG_REVERSI_MSG_WRONG_TITLE, LANG_REVERSI_MSG_WRONG_TEXT_2, MBOX_TEXT_CENTER, NULL);
            need_redraw_all = 1;
        } else {
            Placed=Place(x, y, CurrPlayer,1);
            CurrPlayer=NotPlayer(CurrPlayer);
            NumPl1=GetNum(FIELD_PLAYER1);
            NumPl2=GetNum(FIELD_PLAYER2);
            need_redraw = 1;
            if (!CanPlace(FIELD_PLAYER1) && !CanPlace(FIELD_PLAYER2)) { 
                InGame=0; 
                Result(); 
            }
            if (InGame && !CanPlace(CurrPlayer)) {
                CurrPlayer=NotPlayer(CurrPlayer);
                need_redraw = 1;
            }
        }
    }
}

//-------------------------------------------------------------------
static void Timer() {
    uchar PPP;
 
    if ((InGame) & (CurrPlayer==Computer || Computer==COMPUTER_ONLY)) {
        if (CanPlace(CurrPlayer)) {
            PPP=ComputerPlace(CurrPlayer);
            //xPos = PPP >> 4; yPos = PPP & 0x0F;
            NumPl1=GetNum(FIELD_PLAYER1);
            NumPl2=GetNum(FIELD_PLAYER2);
            need_redraw=1;
        }
        CurrPlayer=NotPlayer(CurrPlayer);
        if (!CanPlace(FIELD_PLAYER1) && !CanPlace(FIELD_PLAYER2)) { 
            InGame=0; 
            Result(); 
        }
        if (InGame && !CanPlace(CurrPlayer)) { 
            CurrPlayer=NotPlayer(CurrPlayer); 
            need_redraw=1;
        }
    }
}

//-------------------------------------------------------------------
static void redraw() {
    uchar x, y;
  
    for (x=0; x<8; ++x) {
        for (y=0; y<8; ++y) {
            DrawCell(x, y);
            switch (Field[x][y]) {
                case FIELD_EMPTY:
                    break;
                case FIELD_PLAYER1:
                    draw_filled_ellipse(field_x+cell_size*x+(cell_size>>1), field_y+cell_size*y+(cell_size>>1), 
                                        (cell_size>>1)-4, (cell_size>>1)-4, MAKE_COLOR(MARKER_COLOR_WHITE, MARKER_COLOR_WHITE));
                    break;
                case FIELD_PLAYER2:
                    draw_filled_ellipse(field_x+cell_size*x+(cell_size>>1), field_y+cell_size*y+(cell_size>>1), 
                                        (cell_size>>1)-4, (cell_size>>1)-4, MAKE_COLOR(MARKER_COLOR_BLACK, MARKER_COLOR_BLACK));
                    break;
            }
        }
    }

    draw_rect(field_x+cell_size*xPos, field_y+cell_size*yPos, field_x+cell_size*(xPos+1), field_y+cell_size*(yPos+1), COLOR_RED);
}

//-------------------------------------------------------------------
static void redrawstatus() {
    uchar x=field_size+FONT_WIDTH*2+23, y = 25;
    if (InGame) { 
        if (CurrPlayer==FIELD_PLAYER1) { 
            draw_string(x+1, y, lang_str(LANG_REVERSI_MOVE_WHITE), MAKE_COLOR(SCREEN_COLOR, COLOR_WHITE)); 
        } else { 
            draw_string(x+1, y, lang_str(LANG_REVERSI_MOVE_BLACK), MAKE_COLOR(SCREEN_COLOR, COLOR_WHITE)); 
        }
    } else { 
        draw_string(x, y, lang_str(LANG_REVERSI_GAME_OVER), MAKE_COLOR(SCREEN_COLOR, COLOR_WHITE)); 
    }
    draw_string(x, y+FONT_HEIGHT+8, lang_str(LANG_REVERSI_WHITE_BLACK), MAKE_COLOR(SCREEN_COLOR, COLOR_WHITE));
    sprintf(buf, " %d ", NumPl1);
    draw_string(x+FONT_WIDTH*(7-strlen(buf))/2, y+FONT_HEIGHT*2+8, buf, MAKE_COLOR(SCREEN_COLOR, COLOR_WHITE));
    sprintf(buf, " %d ", NumPl2);
    draw_string(x+FONT_WIDTH*7+FONT_WIDTH*(7-strlen(buf))/2, y+FONT_HEIGHT*2+8, buf, MAKE_COLOR(SCREEN_COLOR, COLOR_WHITE));
    draw_rect(x-4, y-4, x+FONT_WIDTH*14+4, y+FONT_HEIGHT*3+8+4, COLOR_WHITE);
    draw_rect(x-2, y-2, x+FONT_WIDTH*14+2, y+FONT_HEIGHT*3+8+2, COLOR_WHITE);
    draw_line(x-2, y+FONT_HEIGHT+4, x+FONT_WIDTH*14+2, y+FONT_HEIGHT+4, COLOR_WHITE);
    draw_line(x+FONT_WIDTH*7, y+FONT_HEIGHT+4, x+FONT_WIDTH*7, y+FONT_HEIGHT*3+8+2, COLOR_WHITE);
}

//-------------------------------------------------------------------
void gui_reversi_init() {
    InitMainWindow();
    NewGame();
    need_redraw_all = 1;
}

//-------------------------------------------------------------------
void gui_reversi_kbd_process() {
    switch (kbd_get_autoclicked_key()) {
        case KEY_UP:
            yPos =(yPos-1)&7;
            need_redraw = 1;
            break;
        case KEY_DOWN:
            yPos =(yPos+1)&7;
            need_redraw = 1;
            break;
        case KEY_LEFT:
            xPos =(xPos-1)&7;
            need_redraw = 1;
            break;
        case KEY_RIGHT:
            xPos =(xPos+1)&7;
            need_redraw = 1;
            break;
        case KEY_SET:
            if (InGame)
                Clk(xPos, yPos);
            else 
                NewGame();
            need_redraw = 1;
            break;
    #if defined (CAMERA_ixus700) || defined (CAMERA_ixus800)
        case KEY_DISPLAY:
    #else
        case KEY_ERASE:
    #endif
            if (InGame)
                Computer=COMPUTER_ONLY;
            else 
                NewGame();
            need_redraw = 1;
            break;
    #if !defined (CAMERA_ixus700) && !defined (CAMERA_ixus800)
        case KEY_DISPLAY:
            gui_mbox_init(LANG_MBOX_ABOUT_TITLE, (int)"REVERSI\n(c) GrAnd, 2007", MBOX_TEXT_CENTER, NULL);
            need_redraw_all = 1;
            break;
    #endif
    }
}

//-------------------------------------------------------------------
void gui_reversi_draw() {
    if (need_redraw_all) {
        need_redraw_all = 0;
        DrawMainWindow();
        need_redraw = 1;
    }
    if (need_redraw) {
        need_redraw = 0;
        redraw();
        redrawstatus();
    }

    sprintf(buf, "Batt:%3d%%", get_batt_perc());
    draw_txt_string(screen_width/FONT_WIDTH-2-9, screen_height/FONT_HEIGHT-1, buf, MAKE_COLOR(SCREEN_COLOR, COLOR_WHITE));

    Timer();
}

