#include "stdlib.h"
#include "platform.h"
#include "core.h"
#include "keyboard.h"
#include "conf.h"
#include "ubasic.h"

#define HISTO

#define MENUITEM_MASK 0xf
#define MENUITEM_INFO 1
#define MENUITEM_BOOL 2
#define MENUITEM_INT 3
#define MENUITEM_SUBMENU 4
#define MENUITEM_PROC 5
#define MENUITEM_UP 6
#define MENUITEM_TEXT 7

#define MENUITEM_F_MASK 0xf0
#define MENUITEM_F_UNSIGNED 0x10

static void canon_redraw_bitmap(); /// XXX
static void gui_conf_draw();
static void gui_draw_osd();

static void gui_menuproc_save();

#define MENUSTACK_MAXDEPTH 2

typedef struct {
    const char *text;
    int type;
    int *value;
} CMenuItem;

typedef struct {
    CMenuItem *menu;
    int curpos;
} CMenuItemStacked;

CMenuItem script_submenu[] = {
    {"*** Script ***", MENUITEM_INFO, 0 },
    {"Script shoot delay (.1s)", MENUITEM_INT|MENUITEM_F_UNSIGNED, &conf_script_shoot_delay },
    {"Var. a value", MENUITEM_INT, &conf_ubasic_var_a },
    {"Var. b value", MENUITEM_INT, &conf_ubasic_var_b },
    {"Var. c value", MENUITEM_INT, &conf_ubasic_var_c },
    {"<- Back", MENUITEM_UP, NULL },
    {0}
};

CMenuItem debug_submenu[] = {
    {"*** Debug ***", MENUITEM_INFO, 0 },

    {"Show PropCases", MENUITEM_BOOL, &debug_propcase_show },
    {"PropCase page", MENUITEM_INT, &debug_propcase_page },

    {"<- Back", MENUITEM_UP, NULL },
    {0}
};

CMenuItem root_menu[] = {
    {"*** Main ***", MENUITEM_INFO, 0 },
    {"Show OSD", MENUITEM_BOOL, &conf_show_osd },
    {"Save RAW", MENUITEM_BOOL, &conf_save_raw },
#ifdef HISTO
    {"Show live histo", MENUITEM_BOOL, &conf_show_histo },
#endif
    {"Scripting parameters ->", MENUITEM_SUBMENU, (int*)script_submenu },
    {"Debug parameters ->", MENUITEM_SUBMENU, (int*)debug_submenu },
    {"Save options now...", MENUITEM_PROC, (int*)gui_menuproc_save },
    {0}
};

static CMenuItem *curr_menu;
static CMenuItemStacked gui_menu_stack[MENUSTACK_MAXDEPTH];
static long gui_menu_stack_ptr;
static int gui_menu_curr_item;
static int gui_mode_alt;
static int gui_mode_conf;


const unsigned char fontdata_8x16[4096];
static char *fb;
static int width, height;
static char sbuf[100];

#define SETPIX(_x,_y,_v) fb[(_y)*(width)+(_x)] = \
    fb[(width)*(height)+(_y)*(width)+(_x)] = (_v)

void draw_char(int x, int y, const char ch)
{
    const unsigned char *sym = fontdata_8x16 +
	    ((const unsigned char)ch)*16;
    int i, ii;
    char c;

    // XXX optimize. probably use 4bit -> 32bit lookup table
    // so 4(8) pixels were drawn at a time
    for (i=0;i<16;i++){
	for (ii=0;ii<8;ii++){
	    c = (sym[i] & (0x80>>ii)) ? 0xee:0xff;
	    SETPIX(x+ii,y+i, c);
	}
    }
}

void draw_string(int x, int y, const char *s)
{
    while(*s){
	draw_char(x,y,*s);
	s++;
	x+=8;
	if ((x>=width) && (*s)){
	    draw_char(x-8,y,'>');
	    break;
	}
    }
}

void draw_txt_string(int col, int row, const char *s)
{
    draw_string(col*8, row*16, s);
}

void draw_txt_char(int col, int row, const char c)
{
    draw_char(col*8, row*16, c);
}

#ifdef HISTO
static unsigned int histogram[100];
static unsigned int histo_max;

void do_histo()
{
    unsigned char *img = vid_get_viewport_fb();
    int i, hi;
    for (i=0;i<100;i++){
	histogram[i]=0;
    }
    histo_max = 0;

    for (i=0;i<width*height;i++){
	hi = img[i*3+1]*100/256;
	histogram[hi]++;

	if (histo_max<histogram[hi])
	    histo_max=histogram[hi];
    }
}
#endif

void gui_redraw()
{
	int i,j;
	int threshold;

#if 0
    {
	static char sbuf[100];
	volatile long *si = 0x7dd0;
	extern int taskop_txt_p;
	extern char taskop_txt[6][32];
	long (*f)(long prop, void*p, long size);
	int r,i;

	f = 0xFFC141A8;
//	i = 0;
//	f(conf_ubasic_var_a, &i, 4);
/*
1 - effect
5 - color temp
9 - exp. 
14 - drive timeout
21 - iso value 50..400
24 - image size
23 - quality
39 - aperture
40 - time
69 - tv result

*/
// 39 - aperture
// 40 - exp time
// 65 - focus
// 69 - calc. exp time

	for (i=0;i<10;i++){
	    r = 0;
	    f(conf_ubasic_var_a+i, &r, 4);
	    sprintf(sbuf, "%3d: %d               ", conf_ubasic_var_a+i,r);sbuf[20]=0;
	    draw_string(64,16+16*i,sbuf);
	
	}
/*
	sprintf(sbuf, "d1: %d               ", i);sbuf[20]=0;
	draw_string(64,16,sbuf);

	sprintf(sbuf, "d1: %d               ", (short)i);sbuf[20]=0;
	draw_string(64,32,sbuf);

	sprintf(sbuf, "d1: %x               ", i);sbuf[20]=0;
	draw_string(64,48,sbuf);
*/

//	sprintf(sbuf, "av: %d               ", shooting_get_av());sbuf[20]=0;
//	draw_string(64,64+16,sbuf);

//	sprintf(sbuf, "w: %d               ", si[2]);sbuf[20]=0;
//	draw_string(64,64+32,sbuf);

//	sprintf(sbuf, "w: %d               ", si[3]);sbuf[20]=0;
//	draw_string(64,64+48,sbuf);

//	for (i=0;i<6;i++){
//	    sprintf(sbuf, "%s                  ", taskop_txt[i]);sbuf[32]=0;
//	    draw_string(8,64+64+i*16,sbuf);
//	}
    }
#endif

#ifdef HISTO
    if (conf_show_histo && kbd_is_key_pressed(KEY_SHOOT_HALF)){
	const int hx=219;
	const int hy=48;
	/* box */
	for (i=hx-1;i<=hx+100;i++){
	    SETPIX(i,hy, 0x55);
	    SETPIX(i,hy+50, 0x55);
	}

	for (i=hy;i<hy+50;i++){
	    SETPIX(hx-1,i, 0x55);
	    SETPIX(hx+100,i, 0x55);
	}

	do_histo();

	/* hisogram */
	for (i=0;i<100;i++){
	    if (histo_max > 0)
		threshold = (logf((float)histogram[i]))*50/logf(histo_max);
	    else
		threshold = 50;
	    for (j=1;j<50;j++){
		int x = hx+i;
		int y = hy+50-j;

		if (j<=threshold)
		    SETPIX(x,y, 0x55);
		else
		    SETPIX(x,y, 0);
	    }
	}
    }
#endif	


    if (gui_mode_conf){
	gui_conf_draw();
	draw_txt_string(20, 14, "<CNF>");
    } else {

	if (conf_show_osd){
	    gui_draw_osd();
	}
    
	if (gui_mode_alt){
	    draw_txt_string(20, 14, "<ALT>");
	}
    }

}

void gui_kbd_process()
{

    if (kbd_is_key_clicked(KEY_MENU)){
	gui_mode_conf = !gui_mode_conf;
	if (!gui_mode_conf){
	    canon_redraw_bitmap();
	} else {
	    if (curr_menu == NULL){
		curr_menu = root_menu;
		gui_menu_curr_item = 0;
		gui_menu_stack_ptr = 0;
	    }
	}
	return;
    }

    if (gui_mode_conf){
	switch (kbd_get_clicked_key()){
	case KEY_UP:
	    if (gui_menu_curr_item>0)
		gui_menu_curr_item--;
	    break;
	case KEY_DOWN:
	    if (curr_menu[gui_menu_curr_item+1].text)
		gui_menu_curr_item++;
	    break;
	case KEY_LEFT:{
	    long v = *curr_menu[gui_menu_curr_item].value;

	    switch (curr_menu[gui_menu_curr_item].type & MENUITEM_MASK){
	    case MENUITEM_INT:
		v -= 1;
		if ( curr_menu[gui_menu_curr_item].type & MENUITEM_F_UNSIGNED){
		    if (v < 0)
			v = 0;
		}
		break;
	    }
	    *curr_menu[gui_menu_curr_item].value = v;
	    break;
	}
	case KEY_RIGHT:
	    switch (curr_menu[gui_menu_curr_item].type & MENUITEM_MASK){
	    case MENUITEM_INT:
		*curr_menu[gui_menu_curr_item].value += 1;
		break;
	    }
	    break;
	case KEY_SET:
	    switch (curr_menu[gui_menu_curr_item].type & MENUITEM_MASK){
	    case MENUITEM_BOOL:
		*curr_menu[gui_menu_curr_item].value =
			!(*curr_menu[gui_menu_curr_item].value);
		break;
	    case MENUITEM_PROC:{
		void (*proc)();
		proc = (void*)curr_menu[gui_menu_curr_item].value;
		proc();
		gui_menu_curr_item = 0;
		return;
		}
	    case MENUITEM_SUBMENU:
		gui_menu_stack[gui_menu_stack_ptr].menu = curr_menu;
		gui_menu_stack[gui_menu_stack_ptr].curpos = gui_menu_curr_item;
		curr_menu = (void*)curr_menu[gui_menu_curr_item].value;
		gui_menu_curr_item = 0;
		gui_menu_stack_ptr++;
		// FIXME check on stack overrun;
		if (gui_menu_stack_ptr > MENUSTACK_MAXDEPTH){
		    draw_txt_string(0, 0, "E1");
		    gui_menu_stack_ptr = 0;
		}
		break;
	    case MENUITEM_UP:
		if (gui_menu_stack_ptr > 0){
		    gui_menu_stack_ptr--;
		    curr_menu = gui_menu_stack[gui_menu_stack_ptr].menu;
		    gui_menu_curr_item = gui_menu_stack[gui_menu_stack_ptr].curpos;
		}
		break;
	    }
	    break;
	case KEY_ERASE:
//	    {
//		void (*f)(long a, long b, long c) = 0xFFC1408C;
//		long p = 0;
//		f(40,&p,2);
//	    }
//	    lens_set_focus_pos(2000);
//	    makedump();
//	    shooting_set_tv_rel(2);
//	    shooting_set_av_rel(2);
	    break;
	}
    }
}

void gui_kbd_enter()
{
    // XXX set custom palette
    gui_mode_alt = 1;
}

void gui_kbd_leave()
{
    // XXX restore palette
    gui_mode_alt = 0;
    gui_mode_conf = 0;
    canon_redraw_bitmap();
}

void gui_init()
{
    fb = vid_get_bitmap_fb();
    width = vid_get_bitmap_width();
    height  = vid_get_bitmap_height();
}

void canon_redraw_bitmap()
{
    ubasic_error = 0;
    draw_txt_string(20, 14, "     ");
    // TODO
}

void gui_conf_draw()
{
    static char tbuf[64];
    int imenu;
    int c=3,r=2;
    int l;
    int itemh;
    const int itemw = 37;


    for (imenu=0; curr_menu[imenu].text; imenu++){
	itemh = 0;
	switch (curr_menu[imenu].type & MENUITEM_MASK){
	case MENUITEM_INFO:
	    l = strlen(curr_menu[imenu].text);
	    draw_txt_string(c+(itemw-l)/2, r, curr_menu[imenu].text);
	    itemh=2;
	    draw_txt_char(c,r,' ');
	    draw_txt_char(c+itemw-1,r,' ');
	    break;
	case MENUITEM_BOOL:
	    sprintf(tbuf, " %-31s [%c] ", curr_menu[imenu].text,
		(*curr_menu[imenu].value) ? '*': ' ');
	    draw_txt_string(c, r, tbuf);
	    itemh=1;
	    break;
	case MENUITEM_INT:
	    sprintf(tbuf, " %-27s [%5d] ", curr_menu[imenu].text,
		*curr_menu[imenu].value);
	    draw_txt_string(c, r, tbuf);
	    itemh=1;
	    break;
	case MENUITEM_UP:
	case MENUITEM_SUBMENU:
	case MENUITEM_PROC:
	case MENUITEM_TEXT:
	    sprintf(tbuf, " %-35s ", curr_menu[imenu].text);
	    draw_txt_string(c, r, tbuf);
	    itemh=1;
	    break;
	}
	if (gui_menu_curr_item == imenu){
	    draw_txt_char(c,r,'>');
	    draw_txt_char(c+itemw-1,r,'<');
	}
	r+=itemh;
    }
}

extern long physw_status[3];
static char osd_buf[32];
extern long GetPropertyCase(long opt_id, void *buf, long bufsize);

void gui_draw_osd()
{
    if (conf_save_raw){
	draw_txt_string(40, 3, "RAW");
    } else {
	draw_txt_string(40, 3, "   ");
    }

    if (state_kbd_script_run){
	draw_txt_string(40, 4, "SCR");
    } else {
	draw_txt_string(40, 4, "   ");
    }

    sprintf(osd_buf, "Z:%d/%d  ", lens_get_zoom_point(), lens_get_zoom_pos());
    draw_txt_string(35, 6, osd_buf);
    sprintf(osd_buf, "F:%d  ", lens_get_focus_pos());
    draw_txt_string(35, 7, osd_buf);
    sprintf(osd_buf, "V:%d  ", stat_get_vbatt());
    draw_txt_string(35, 8, osd_buf);

    sprintf(osd_buf, "1:%8x  ", physw_status[2]);
    draw_txt_string(28, 10, osd_buf);

    if (debug_propcase_show){
	static char sbuf[100];
	int r,i, p;

	for (i=0;i<10;i++){
	    r = 0;
	    p = debug_propcase_page*10+i;
	    GetPropertyCase(p, &r, 4);
	    sprintf(sbuf, "%3d: %d              ", p, r);sbuf[20]=0;
	    draw_string(64,16+16*i,sbuf);
	}
    
    }


    if (ubasic_error){
	const char *msg;
    if (ubasic_error >= UBASIC_E_ENDMARK) {
        msg = ubasic_errstrings[UBASIC_E_UNKNOWN_ERROR];
    } else {
	    msg = ubasic_errstrings[ubasic_error];
	}
	sprintf(osd_buf, "uBASIC:%d %s ", ubasic_linenumber(), msg);
	draw_txt_string(0, 0, osd_buf);
    }
}

void gui_menuproc_save()
{
    conf_save(1);
}
