#include "stdlib.h"
#include "keyboard.h"
#include "platform.h"
#include "core.h"
#include "gui.h"
#include "gui_draw.h"
#include "conf.h"
#include "script.h"

//-------------------------------------------------------------------

#define SCRIPT_BUF_SIZE             8192
#define SCRIPT_CONSOLE_NUM_LINES    5
#define SCRIPT_CONSOLE_LINE_LENGTH  25
#define SCRIPT_CONSOLE_X            0
#define SCRIPT_CONSOLE_Y            (14-SCRIPT_CONSOLE_NUM_LINES)

//-------------------------------------------------------------------
const char *state_ubasic_script;

static char ubasic_script_buf[SCRIPT_BUF_SIZE];
static const char *ubasic_script_default =
#if 0
    "@title Default script\n"
    "@param a Shoot count\n"
    "@default a 2\n"
    "@param b Step\n"
    "@default b 3\n"

    "sleep 1000\n"

    "if a<1 then let a=2\n"
    "if b<1 then let b=3\n"

    "for s=1 to a\n"
      "shoot\n"
      "for n=1 to b\n"
        "click \"right\"\n"
      "next n\n"
    "next s\n"
    "shoot\n"

    "for n=1 to a*b\n"
      "click \"left\"\n"
    "next n\n"

    "end\n";
#else
    "@title Default Script\n"
    "@param a Times to Repeat\n"
    "@default a 5\n"
    "@param b Display Delay\n"
    "@default b 3\n"

    "if a<1 then let a=1\n"
    "if b<1 then let b=1\n"

    "for n=1 to a\n"
        "if n>1 then print \"*****\"\n"
        "print \"This is a default script.\"\n"
        "sleep 1000\n"
        "print \"Scripts run when shutter\"\n"
        "sleep 1000\n"
        "print \"is pressed in ALT mode.\"\n"
        "sleep 1000\n"
        "print \"Press shutter to exit.\"\n"
        "sleep b*1000\n"
    "next n\n"

    "end\n";
#endif

char script_title[36];
char script_params[SCRIPT_NUM_PARAMS][28];
char script_console_buf[SCRIPT_CONSOLE_NUM_LINES][SCRIPT_CONSOLE_LINE_LENGTH+1];
static int script_console_lines=0;
//-------------------------------------------------------------------
static void process_title(const char *title) {
    register const char *ptr = title;
    register int i=0;

    while (ptr[0]==' ' || ptr[0]=='\t') ++ptr; // whitespaces
    while (i<(sizeof(script_title)-1) && ptr[i] && ptr[i]!='\r' && ptr[i]!='\n') {
        script_title[i]=ptr[i];
        ++i;
    }
    script_title[i]=0;
}

//-------------------------------------------------------------------
static void process_param(const char *param) {
    register const char *ptr = param;
    register int n, i=0;

    while (ptr[0]==' ' || ptr[0]=='\t') ++ptr; // whitespaces
    if (ptr[0] && (ptr[0]>='a' && ptr[0]<='a'+SCRIPT_NUM_PARAMS) && (ptr[1]==' ' || ptr[1]=='\t')) {
        n=ptr[0]-'a';
        ptr+=2;
        while (ptr[0]==' ' || ptr[0]=='\t') ++ptr; // whitespaces
        while (i<(sizeof(script_params[0])-1) && ptr[i] && ptr[i]!='\r' && ptr[i]!='\n') {
            script_params[n][i]=ptr[i];
            ++i;
        }
        script_params[n][i]=0;
    } // ??? else produce error message
}

//-------------------------------------------------------------------
static void process_default(const char *param) {
    register const char *ptr = param;
    register int n;

    while (ptr[0]==' ' || ptr[0]=='\t') ++ptr; // whitespaces
    if (ptr[0] && (ptr[0]>='a' && ptr[0]<='a'+SCRIPT_NUM_PARAMS) && (ptr[1]==' ' || ptr[1]=='\t')) {
        n=ptr[0]-'a';
        ptr+=2;
        conf.ubasic_vars[n] = strtol(ptr, NULL, 0);
    } // ??? else produce error message
}

//-------------------------------------------------------------------
static void script_scan(const char *fn, int update_vars) {
    register const char *ptr = state_ubasic_script;
    register int i;
    char *c;

    c=strrchr(fn, '/');
    strncpy(script_title, (c)?c+1:fn, sizeof(script_title));
    script_title[sizeof(script_title)-1]=0;
    for (i=0; i<SCRIPT_NUM_PARAMS; ++i) {
        script_params[i][0]=0;
    }

    while (ptr[0]) {
        while (ptr[0]==' ' || ptr[0]=='\t') ++ptr; // whitespaces
        if (ptr[0]=='@') {
            if (strncmp("@title", ptr, 6)==0) {
                ptr+=6;
                process_title(ptr);
            } else if (strncmp("@param", ptr, 6)==0) {
                ptr+=6;
                process_param(ptr);
            } else if (update_vars && strncmp("@default", ptr, 8)==0) {
                ptr+=8;
                process_default(ptr);
            }
        }
        while (ptr[0] && ptr[0]!='\n') ++ptr; // unless end of line
        if (ptr[0]) ++ptr;
    }

    for (i=0; i<SCRIPT_NUM_PARAMS; ++i) {
        if (script_params[i][0]) break;
    }
    if (i==SCRIPT_NUM_PARAMS) { // there was no @param in script
        for (i=0; i<3; ++i) {
            strcpy(script_params[i], "Var. ? value");
            script_params[i][5]='a'+i;
        }
    }
}

//-------------------------------------------------------------------
void script_load(const char *fn) {
    int fd=-1, i, update_vars;

    state_ubasic_script = ubasic_script_default;
    update_vars = (strcmp(fn, conf.script_file) != 0);  // update if new file

    if (!fn[0]) { // load internal script
        if (!conf.script_file[0]) { // internal script was used last time
            fd = open(SCRIPT_DEFAULT_FILENAME, O_RDONLY, 0777);
            if (fd>=0) {
                fn = SCRIPT_DEFAULT_FILENAME;
                update_vars = 1; 
            }
        }
    } else {
        fd = open(fn, O_RDONLY, 0777);
        if (fd<0) {
            conf.script_file[0]=0;
            update_vars = 1; 
        }
    }

    if (fd>=0){
	int rcnt = read(fd, ubasic_script_buf, SCRIPT_BUF_SIZE);
	if (rcnt > 0){
	    if (rcnt == SCRIPT_BUF_SIZE) { /* FIXME TODO script is too big? */
		ubasic_script_buf[SCRIPT_BUF_SIZE-1] = 0;
	    } else
		ubasic_script_buf[rcnt] = 0;
	    state_ubasic_script = ubasic_script_buf;
	}
	close(fd);
        strcpy(conf.script_file, fn);
    }

    if (update_vars) {
        for (i=0; i<SCRIPT_NUM_PARAMS; ++i) {
            conf.ubasic_vars[i] = 0;
        }
    }
    script_scan(fn, update_vars);
    gui_update_script_submenu();
}

//-------------------------------------------------------------------
void script_console_clear() {
    register int i;

    for (i=0; i<SCRIPT_CONSOLE_NUM_LINES; ++i) {
        script_console_buf[i][0]=0;
    }
    script_console_lines=0;
    draw_restore();
}

//-------------------------------------------------------------------
void script_console_draw() {
    register int i, l;
    static char buf[8];

    for (i=0; i<script_console_lines; ++i) {
        l=strlen(script_console_buf[i]);
        draw_txt_string(SCRIPT_CONSOLE_X, SCRIPT_CONSOLE_Y+SCRIPT_CONSOLE_NUM_LINES-script_console_lines+i, script_console_buf[i], MAKE_COLOR(COLOR_BG, COLOR_FG));
        for (; l<SCRIPT_CONSOLE_LINE_LENGTH; ++l)
            draw_txt_char(SCRIPT_CONSOLE_X+l, SCRIPT_CONSOLE_Y+SCRIPT_CONSOLE_NUM_LINES-script_console_lines+i, ' ', MAKE_COLOR(COLOR_BG, COLOR_FG));
    }

}

//-------------------------------------------------------------------
void script_console_add_line(const char *str) {
    register int i;

    if (script_console_lines == SCRIPT_CONSOLE_NUM_LINES ) {
        for (i=1; i<SCRIPT_CONSOLE_NUM_LINES; ++i) {
            strcpy(script_console_buf[i-1], script_console_buf[i]);
        }
        --script_console_lines;
    }

    strncpy(script_console_buf[script_console_lines], str, SCRIPT_CONSOLE_LINE_LENGTH);
    script_console_buf[script_console_lines][SCRIPT_CONSOLE_LINE_LENGTH]=0;
    
    ++script_console_lines;

    script_console_draw();
}

//-------------------------------------------------------------------
//-------------------------------------------------------------------
//-------------------------------------------------------------------
