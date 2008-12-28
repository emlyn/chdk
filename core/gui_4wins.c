//Conect4: Kettmeister, CHDKLover german forum (www.wirklemms.de)
#include "stdlib.h"
#include "keyboard.h"
#include "platform.h"
#include "core.h"
#include "lang.h"
#include "conf.h"
#include "gui.h"
#include "gui_osd.h"
#include "gui_draw.h"
#include "gui_lang.h"
#include "gui_batt.h"
#include "gui_mbox.h"
#include "gui_4wins.h"

#define BORDER		 20
#define RECT_SIZE	 30
#define BORDER_TOP	 RECT_SIZE
#define FIELD_HEIGHT 7
#define FIELD_WIDTH	 7
#define P1_COLOR	 MAKE_COLOR(0x23,0x23)
#define P2_COLOR	 MAKE_COLOR(0x16,0x16)
#define BG_COLOR	 MAKE_COLOR(0xDE,0xDE)
#define FIELD_COLOR	 MAKE_COLOR(0xAA,0xAA)//(füllfarbe,rand)
#define TEXT_COLOR   MAKE_COLOR(BG_COLOR, COLOR_WHITE)
#define INFO_COLOR   MAKE_COLOR(0xEF, 0xEF)
#define INFO_TEXT_COLOR   MAKE_COLOR(INFO_COLOR, COLOR_WHITE)

char cursor_position,cur_player=1;
char field[FIELD_HEIGHT][FIELD_WIDTH];
char finished=0;
char badColumns[7];
char in_game=0;
char mode_rival=0; //1=person 0=cam
char count_win[2]={0,0};

//-------------------------------------------------------------------
static char isFull(int column)
{
	if(field[column-1][6]) 
		return 1; 
	else 
		return 0;
}

static char set_stone(int column, char player, char visible)
{
	int i;
    in_game=1;
	if(!isFull(column))
	{
		for(i=1;field[column-1][i];i++);			//1 ist wichtig (0=Fundament)
		if (visible) {
			draw_filled_ellipse((BORDER+((column-1)*RECT_SIZE))+15, (BORDER+((6-i)*RECT_SIZE))+15+BORDER_TOP, 10,10, (cur_player==1)?P1_COLOR:P2_COLOR);
		}
		field[column-1][i]=player;
		return 1;
	} 
	else return 0;
}
/*====================      KI   ===========================*/
static void unset_stone(int column)
{
  int i;
  for(i=1;field[column-1][i]&&i<=6;i++);			//1 ist wichtig (0=Fundament)
  field[column-1][i-1]=0;
}

char ki_isBadColumn(int column){
  if(badColumns[column-1]) return column; else return 0;
}

char ki_3(char player) {
  int i,j,a;
  //waagerecht und Diagonal (über Anstieg)
  for(i=0;i<=3;i++){		// column
    for(j=1;j<=6;j++){		//row 
      if(field[i][j]==player&&field[i+1][j]==player&&field[i+2][j]==player&&field[i+3][j]==0&&field[i+3][j-1]) return i+4;	//***-
      if(field[i][j]==player&&field[i+1][j]==player&&field[i+2][j]==0&&field[i+3][j]==player&&field[i+2][j-1]) return i+3;	//**-*
      if(field[i][j]==player&&field[i+1][j]==0&&field[i+2][j]==player&&field[i+3][j]==player&&field[i+1][j-1]) return i+2;	//*-**
      if(field[i][j]==0&&field[i+1][j]==player&&field[i+2][j]==player&&field[i+3][j]==player&&field[i][j-1]) return i+1;	//-***
    }
    for(j=1;j<=3;j++){
      if(field[i][j]==player&&field[i+1][j+1]==player&&field[i+2][j+2]==player&&field[i+3][j+3]==0&&field[i+3][j+3-1]) return i+4;	//***-
      if(field[i][j]==player&&field[i+1][j+1]==player&&field[i+2][j+2]==0&&field[i+3][j+3]==player&&field[i+2][j+2-1]) return i+3;	//**-*
      if(field[i][j]==player&&field[i+1][j+1]==0&&field[i+2][j+2]==player&&field[i+3][j+3]==player&&field[i+1][j+1-1]) return i+2;	//*-**
      if(field[i][j]==0&&field[i+1][j+1]==player&&field[i+2][j+2]==player&&field[i+3][j+3]==player&&field[i][j-1]) return i+1;		//-***
    }
    for(j=4;j<=6;j++){
        if(field[i][j]==player&&field[i+1][j-1]==player&&field[i+2][j-2]==player&&field[i+3][j-3]==0&&field[i+3][j-3-1]) return i+4;	//***-
        if(field[i][j]==player&&field[i+1][j-1]==player&&field[i+2][j-2]==0&&field[i+3][j-3]==player&&field[i+2][j-2-1]) return i+3;	//**-*
        if(field[i][j]==player&&field[i+1][j-1]==0&&field[i+2][j-2]==player&&field[i+3][j-3]==player&&field[i+1][j-1-1]) return i+2;	//*-**
        if(field[i][j]==0&&field[i+1][j-1]==player&&field[i+2][j-2]==player&&field[i+3][j-3]==player&&field[i][j-1]) return i+1;		//-***
    }
  }
  //Unterreihentrick in allen ebenen
  for(i=0;i<=2;i++){
    for(j=1;j<=6;j++) if(field[i][j]==0&&field[i+1][j]==player&&field[i+2][j]==0&&field[i+3][j]==player&&field[i+4][j]==0&&field[i][j-1]&&field[i+2][j-1]&&field[i+4][j-1]) return i+3;	//_*_*_
    for(j=1;j<=3;j++) if(field[i][j]==0&&field[i+1][j+1]==player&&field[i+2][j+2]==0&&field[i+3][j+3]==player&&field[i+4][j+4]==0&&field[i][j-1]&&field[i+2][j+2-1]&&field[i+4][j+4-1]) return i+3;	//_*_*_
    for(j=4;j<=6;j++) if(field[i][j]==0&&field[i+1][j-1]==player&&field[i+2][j-2]==0&&field[i+3][j-3]==player&&field[i+4][j-4]==0&&field[i][j-1]&&field[i+2][j-2-1]&&field[i+4][j-4-1]) return i+3;	//_*_*_
  }
  //senkrecht
  for(i=0;i<=6;i++) for(j=1;j<=3;j++) if(field[i][j]==player&&field[i][j+1]==player&&field[i][j+2]==player&&field[i][j+3]==0) return i+1;
  return 0;
}

char ki_2(char player) {
  int i,j,a;
  //waagerecht und Diagonal über Anstieg
  for(i=0;i<=3;i++){		//column
    for(j=1;j<=6;j++){		//row 
      if(field[i][j]==player&&field[i+1][j]==player&&field[i+2][j]==0&&field[i+3][j]==0&&(field[i+2][j-1]||field[i+3][j-1])&&!ki_isBadColumn(i+3)) return i+3;	//**-- return und if ändern
      if(field[i][j]==player&&field[i+1][j]==0&&field[i+2][j]==0&&field[i+3][j]==player&&(field[i+1][j-1]||field[i+2][j-1])&&!ki_isBadColumn(i+2)) return i+2;	//*--* (i+3 geht auch)
      if(field[i][j]==0&&field[i+1][j]==0&&field[i+2][j]==player&&field[i+3][j]==player&&(field[i][j-1]||field[i+1][j-1])&&!ki_isBadColumn(i+2)) return i+2;	//--**
      if(field[i][j]==0&&field[i+1][j]==player&&field[i+2][j]==0&&field[i+3][j]==player&&(field[i][j-1]||field[i+2][j-1])&&!ki_isBadColumn(i+3)) return i+3;	//-*-*
      if(field[i][j]==player&&field[i+1][j]==0&&field[i+2][j]==player&&field[i+3][j]==0&&(field[i+1][j-1]||field[i+3][j-1])&&!ki_isBadColumn(i+2)) return i+2;	//*-*-
    }
    for(j=1;j<=3;j++){
      if(field[i][j]==player&&field[i+1][j+1]==player&&field[i+2][j+2]==0&&field[i+3][j+3]==0&&field[i+2][j+2-1]&&!ki_isBadColumn(i+3)) return i+3;	//**-- return und if ändern
      if(field[i][j]==player&&field[i+1][j+1]==player&&field[i+2][j+2]==0&&field[i+3][j+3]==0&&field[i+3][j+3-1]&&!ki_isBadColumn(i+3)) return i+4;	//**-- return und if ändern
      if(field[i][j]==player&&field[i+1][j+1]==0&&field[i+2][j+2]==0&&field[i+3][j+3]==player&&(field[i+1][j+1-1]||field[i+2][j+2-1])&&!ki_isBadColumn(i+2)) return i+2;	//*--* (i+3 geht auch)
      if(field[i][j]==0&&field[i+1][j+1]==0&&field[i+2][j+2]==player&&field[i+3][j+3]==player&&(field[i][j-1]||field[i+1][j+1-1])&&!ki_isBadColumn(i+2)) return i+2;	//--**
      if(field[i][j]==0&&field[i+1][j+1]==player&&field[i+2][j+2]==0&&field[i+3][j+3]==player&&(field[i][j-1]||field[i+2][j+2-1])&&!ki_isBadColumn(i+3)) return i+3;	//-*-*
      if(field[i][j]==player&&field[i+1][j+1]==0&&field[i+2][j+2]==player&&field[i+3][j+3]==0&&(field[i+1][j+1-1]||field[i+3][j+3-1])&&!ki_isBadColumn(i+2)) return i+2;	//*-*-
    }
    for(j=4;j<=6;j++){
      if(field[i][j]==player&&field[i+1][j-1]==player&&field[i+2][j-2]==0&&field[i+3][j-3]==0&&field[i+2][j-2-1]&&!ki_isBadColumn(i+3)) return i+3;	//**-- return und if ändern
      if(field[i][j]==player&&field[i+1][j-1]==player&&field[i+2][j-2]==0&&field[i+3][j-3]==0&&field[i+3][j-3-1]&&!ki_isBadColumn(i+3)) return i+4;	//**-- return und if ändern
      if(field[i][j]==player&&field[i+1][j-1]==0&&field[i+2][j-2]==0&&field[i+3][j-3]==player&&(field[i+1][j-1-1]||field[i+2][j-2-1])&&!ki_isBadColumn(i+2)) return i+2;	//*--* (i+3 geht auch)
      if(field[i][j]==0&&field[i+1][j-1]==0&&field[i+2][j-2]==player&&field[i+3][j-3]==player&&(field[i][j-1]||field[i+1][j-1-1])&&!ki_isBadColumn(i+2)) return i+2;	//--**
      if(field[i][j]==0&&field[i+1][j-1]==player&&field[i+2][j-2]==0&&field[i+3][j-3]==player&&(field[i][j-1]||field[i+2][j-2-1])&&!ki_isBadColumn(i+3)) return i+3;	//-*-*
      if(field[i][j]==player&&field[i+1][j-1]==0&&field[i+2][j-2]==player&&field[i+3][j-3]==0&&(field[i+1][j-1-1]||field[i+3][j-3-1])&&!ki_isBadColumn(i+2)) return i+2;	//*-*-
    }
  }
  //senkrecht
  for(i=0;i<=6;i++) for(j=1;j<=3;j++) if(field[i][j]==player&&field[i][j+1]==player&&field[i][j+2]==0&&!ki_isBadColumn(i+1)) return i+1;
  return 0;
}

char ki_findColumn(char mode, char player) {							//player = 1|2
  char erg=0, cam=player, otherplayer, i, counter=0;
  static char str[64];
  otherplayer=(player==1)?2:1;
  switch(mode) {
  case 'b':
  case 1: erg=ki_3(cam);												//ich3
          if(!erg&&mode!='b') erg=ki_3(otherplayer); else break;		//du3
          if(!erg) {													//ungünstige Spalten ermitteln
            for(i=1;i<=7;i++) {
              if(!isFull(i)) {
                set_stone(i,9,0);										//Stein setzen 9=irgendwas
                badColumns[i-1]=ki_findColumn('b',otherplayer);			//ungünstige Spalten ermitteln b=bad
                if(!badColumns[i-1]) badColumns[i-1]=ki_findColumn('b',cam);
                unset_stone(i);
              } else badColumns[i-1]=9;								//9=full
//              sprintf(str,"%d %d %d %d %d %d %d",badColumns[0],badColumns[1],badColumns[2],badColumns[3],badColumns[4],badColumns[5],badColumns[6]);
//              draw_txt_string(30, 3, str, TEXT_COLOR);
            }
          } else break;
          erg=ki_2(cam);												//ich2 (für passivere Methode vertauschen)
          if(!erg) erg=ki_2(otherplayer); else break;					//du2
          if(!erg) erg=(!isFull(4)&&!ki_isBadColumn(4))?4:0; else break;	//mitte
          if(!erg) do erg=(rand()%7)+1; while((isFull(erg)||erg==0||ki_isBadColumn(erg))&&counter++<100);	//zufall
          if(counter>100) for(i=1;i<=7;i++) if(!isFull(i)) erg=i;
          break;
  }
  return erg;
}
/*======================= K I   END ===============================*/
void draw_txt_message(char* text) {
    coord w, x, y;
    int l;
    color cl = MAKE_COLOR(COLOR_RED, COLOR_WHITE);
    l=strlen(text);
    w=l*FONT_WIDTH+10;

    x = (screen_width-w)>>1; y = ((screen_height)>>1);
    draw_filled_round_rect(x, y, x+w, y+FONT_HEIGHT+6, MAKE_COLOR(COLOR_RED, COLOR_RED));
    draw_string(x+((w-strlen(text)*FONT_WIDTH)>>1), y+4, text, cl);
}
//-------------------------------------------------------------------
static void change_player()
{
	if (cur_player==1) cur_player=2; else cur_player=1;
	draw_filled_ellipse((BORDER+((cursor_position)*RECT_SIZE))+15, BORDER+10, 10,10, (cur_player==1)?P1_COLOR:P2_COLOR);
}
//-------------------------------------------------------------------
static char win_query()
{
	int i=0;
	int j=0;
	
	if (isFull(1) && isFull(2) && isFull(3) && isFull(4) && isFull(5) && isFull(6) && isFull(7)) return 9;

	for(i=0;i<4;i++)
	{
		for(j=1;j<4;j++)
		{
			// '1'
			if(field[i][j]==1 && field[i+1][j+1]==1 && field[i+2][j+2]==1 && field[i+3][j+3]==1) return 1; // diagonal  >  
			if(field[i][j+3]==1 && field[i+1][j+2]==1 && field[i+2][j+1]==1 && field[i+3][j]==1) return 1; // diagonal  >  /
			// '2'
			if(field[i][j]==2 && field[i+1][j+1]==2 && field[i+2][j+2]==2 && field[i+3][j+3]==2) return 1;// diagonal  >  
			if(field[i][j+3]==2 && field[i+1][j+2]==2 && field[i+2][j+1]==2 && field[i+3][j]==2) return 1;// diagonal  >  /
		}
	}
	
	for(i=0;i<7;i++)
	{
		for(j=1;j<4;j++)
		{
			if(field[i][j]==2 && field[i][j+1]==2 && field[i][j+2]==2 && field[i][j+3]==2) return 1; // vertical  >  |
			if(field[i][j]==1 && field[i][j+1]==1 && field[i][j+2]==1 && field[i][j+3]==1) return 1; // vertical  >  |
		}
	}
	
	for(i=0;i<4;i++)
	{
		for(j=1;j<7;j++)
		{
			if(field[i][j]==2 && field[i+1][j]==2 && field[i+2][j]==2 && field[i+3][j]==2) return 1; // horizontal  >  -
			if(field[i][j]==1 && field[i+1][j]==1 && field[i+2][j]==1 && field[i+3][j]==1) return 1;	// horizontal  >  -
		}
	}
	
	return 0;
}
//-------------------------------------------------------------------
void win() {
  if(win_query()==1){
    finished=1;
    count_win[cur_player-1]++;
    draw_txt_message(lang_str((cur_player==1)?LANG_CONNECT4_P1_WIN:(mode_rival)?LANG_CONNECT4_P2_WIN:LANG_CONNECT4_CAM_WIN));
  }	else if (win_query()==9) {
    finished=1;
    draw_txt_message(lang_str(LANG_CONNECT4_DRAW));
  }
  change_player();
}
//-------------------------------------------------------------------
void draw_mode()
{
	draw_txt_string(30, 4, "            ", TEXT_COLOR);
	if (mode_rival==1)
		draw_txt_string(30, 4, lang_str(LANG_CONNECT4_HUMAN), TEXT_COLOR);
	else
		draw_txt_string(30, 4, PLATFORM, TEXT_COLOR);
}
//-------------------------------------------------------------------
void change_mode()
{
	cur_player=1;
	count_win[0]=count_win[1]=0;
	if(mode_rival==1)
		mode_rival=0;	//CAM
	else
		mode_rival=1;	//HUMAN
	draw_mode();
}
//-------------------------------------------------------------------
void set()
{
	if(finished==0)
	{
		if(cursor_position==7 && in_game==0)	
		{
			change_mode();
		}
		else
		{
			if(cur_player==1 || (cur_player==2 && mode_rival==1)) if(set_stone(cursor_position+1,cur_player,1)) win();
			if((mode_rival==0 && cur_player==2) && !finished) if(set_stone(ki_findColumn(1, cur_player),cur_player, 1)) win();
		}
	}
}
//-------------------------------------------------------------------
static void move_cursor(int in_x_pos)
{
	draw_filled_ellipse((BORDER+((cursor_position)*RECT_SIZE))+15, BORDER+10, 10,10,BG_COLOR);
	if(in_game)
	{
		if(cursor_position==0 && in_x_pos<0) 
			cursor_position=7+in_x_pos; 
		else 
			cursor_position=(cursor_position+in_x_pos)%7;
	}
	else
	{
		if(cursor_position==0 && in_x_pos<0) 
			cursor_position=8+in_x_pos; 
		else 
			cursor_position=(cursor_position+in_x_pos)%8;
	}
	draw_filled_ellipse((BORDER+((cursor_position)*RECT_SIZE))+15, BORDER+10, 10,10, (cur_player==1)?P1_COLOR:P2_COLOR);
}
//-------------------------------------------------------------------
int gui_4wins_init() 
{
	static char str[16];
	int i=0,j=0;

	cursor_position=3;
	finished=in_game=0;
	srand(time(NULL));
	
	draw_filled_rect(0, 0, 360, 240, BG_COLOR);		// draw backgraund
	draw_filled_rect(BORDER, BORDER+BORDER_TOP, BORDER+(7*RECT_SIZE), BORDER+(6*RECT_SIZE)+BORDER_TOP, FIELD_COLOR);
	draw_filled_round_rect(240, 90, 360-BORDER, 240-10, INFO_COLOR);
    draw_txt_string(12, 0, lang_str(LANG_MENU_GAMES_CONNECT4), TEXT_COLOR);
    draw_line(0,15,360,15,0xEF);

	for(i=0;i<7;i++)
	{
		for(j=0;j<6;j++)
		{
			field[i][j+1]=0;
			draw_filled_ellipse(BORDER+(i*RECT_SIZE)+(RECT_SIZE/2), BORDER+(j*RECT_SIZE)+(RECT_SIZE/2)+BORDER_TOP, 10, 10, BG_COLOR);
		}
	}
	for(i=0;i<7;i++)
	{
		field[i][0]=9;
	}

	move_cursor(0);
	draw_txt_string(30, 3, lang_str(LANG_CONNECT4_RIVAL), TEXT_COLOR);
    sprintf(str, "%d",count_win[0]);
	draw_txt_string(screen_width/FONT_WIDTH-2-10, screen_height/FONT_HEIGHT-9, str, MAKE_COLOR(INFO_COLOR, P1_COLOR));
    sprintf(str, ":");
	draw_txt_string(screen_width/FONT_WIDTH-2-7, screen_height/FONT_HEIGHT-9, str, INFO_TEXT_COLOR);
    sprintf(str, "%d",count_win[1]);
	draw_txt_string(screen_width/FONT_WIDTH-2-4, screen_height/FONT_HEIGHT-9, str, MAKE_COLOR(INFO_COLOR, P2_COLOR));
	draw_mode();
	if(cur_player==2&&!mode_rival) set();
	return 1;
}
//-------------------------------------------------------------------
void gui_4wins_kbd_process() 
{
	switch (kbd_get_autoclicked_key()) 
	{
		case KEY_SET:
		    if(!finished) set(); else gui_4wins_init();
			break;
		case KEY_LEFT:
			if(finished==0)
				move_cursor(-1);
			break;
		case KEY_RIGHT:
			if(finished==0)
				move_cursor(1);
			break;
	}
}
//-------------------------------------------------------------------
void gui_4wins_draw() {
  static char str[16];
  sprintf(str, "%3d%%", get_batt_perc());
  draw_txt_string(screen_width/FONT_WIDTH-2-13, screen_height/FONT_HEIGHT-2, str, INFO_TEXT_COLOR);
  gui_osd_draw_clock(300,208,INFO_TEXT_COLOR);
}
