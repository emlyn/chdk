#include "stdlib.h"
#include "keyboard.h"
#include "platform.h"
#include "core.h"
#include "gui.h"
#include "gui_draw.h"
#include "conf.h"
#include "script.h"
#include "console.h"
#include "action_stack.h"
#include "motion_detector.h"
#include "shot_histogram.h"
#include "lang.h"
#include "gui_lang.h"
#include "kbd.h"

#ifdef OPT_LUA
#include "lauxlib.h"
#endif

//-------------------------------------------------------------------

const char *script_source_str=NULL; //ERR99
char cfg_name[100] = "\0";
char cfg_set_name[100] = "\0";

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
int script_param_order[SCRIPT_NUM_PARAMS];
static char script_params_update[SCRIPT_NUM_PARAMS];
static int script_loaded_params[SCRIPT_NUM_PARAMS];
static long running_script_stack_name = -1;

#ifdef OPT_LUA
static int state_lua_kbd_first_call_to_resume;	// AUJ
#endif

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
static int process_param(const char *param, int update) {
    register const char *ptr = param;
    register int n, i=0;

    while (ptr[0]==' ' || ptr[0]=='\t') ++ptr; // whitespaces
    if (ptr[0] && (ptr[0]>='a' && ptr[0]<='a'+SCRIPT_NUM_PARAMS) && (ptr[1]==' ' || ptr[1]=='\t')) {
        n=ptr[0]-'a';
        ptr+=2;
        while (ptr[0]==' ' || ptr[0]=='\t') ++ptr; // whitespaces
		script_params_update[n] = 1;
        while (i<(sizeof(script_params[0])-1) && ptr[i] && ptr[i]!='\r' && ptr[i]!='\n') {
			if (update) 
			{ if (script_params[n][i]!=ptr[i]) { script_params_update[n] = 0; break; }
			} else script_params[n][i]=ptr[i];
            ++i;
        }
		if (!update) script_params[n][i]=0;
        n++;
    } else n=0; // ??? else produce error message    
    return n; // n=1 if '@param a' was processed, n=2 for 'b' ... n=26 for 'z'. n=0 if failed.
}

//-------------------------------------------------------------------
static void process_default(const char *param, char update) {
    register const char *ptr = param;
    register int n;

    while (ptr[0]==' ' || ptr[0]=='\t') ++ptr; // whitespaces
    if (ptr[0] && (ptr[0]>='a' && ptr[0]<='a'+SCRIPT_NUM_PARAMS) && (ptr[1]==' ' || ptr[1]=='\t')) {
        n=ptr[0]-'a';
        ptr+=2;
		if (!update || script_params_update[n])
        {
			conf.ubasic_vars[n] = strtol(ptr, NULL, 0);
            script_loaded_params[n] = conf.ubasic_vars[n];
        }
    } // ??? else produce error message
}

//-------------------------------------------------------------------
static void script_scan(const char *fn, int update_vars) {
    register const char *ptr = script_source_str;
    register int i, j=0, n;
    char *c;

    c=strrchr(fn, '/');
    strncpy(script_title, (c)?c+1:fn, sizeof(script_title));
    script_title[sizeof(script_title)-1]=0;
    for (i=0; i<SCRIPT_NUM_PARAMS; ++i) {
        script_params[i][0]=0;
        script_param_order[i]=0;
    }

    while (ptr[0]) {
        while (ptr[0]==' ' || ptr[0]=='\t') ++ptr; // whitespaces
        if (ptr[0]=='@') {
            if (strncmp("@title", ptr, 6)==0) {
                ptr+=6;
                process_title(ptr);
            } else if (strncmp("@param", ptr, 6)==0) {
                ptr+=6;
                n=process_param(ptr, 0); // n=1 if '@param a' was processed, n=2 for 'b' ... n=26 for 'z'. n=0 if failed.
                if (n>0 && n<=SCRIPT_NUM_PARAMS) {
                  script_param_order[j]=n;
                  j++;
                }
            } else if (update_vars && strncmp("@default", ptr, 8)==0) {
                ptr+=8;
                process_default(ptr, 0);
            }
        }
        while (ptr[0] && ptr[0]!='\n') ++ptr; // unless end of line
        if (ptr[0]) ++ptr;
    }

    /*for (i=0; i<SCRIPT_NUM_PARAMS; ++i) {
        if (script_params[i][0]) break;
    }
    if (i==SCRIPT_NUM_PARAMS) { // there was no @param in script
        for (i=0; i<3; ++i) {
            strcpy(script_params[i], "Var. ? value");
            script_params[i][5]='a'+i;
        }
    }*/
}

void set_params_values_name(const char *fn, int param_set)
{
	int shift;
	register char *ptr = (param_set >= 0 ? cfg_set_name : cfg_name);
	const char *name;
	
	if (fn == NULL || fn[0] == 0) { ptr[0] = 0; return; }
	
	strncpy(ptr, SCRIPT_DATA_PATH, 100); ptr[99]=0;
	shift = strlen(SCRIPT_DATA_PATH);
	name = strrchr(fn, '/'); 
	if (name) name++; else name=fn;
	strncpy(ptr+shift, name, 100-shift); ptr[99]=0;
	shift = strlen(ptr); if (shift >= 100) shift=99;

	if (param_set >= 0) 
		sprintf(ptr+shift-4, "_%d\0", param_set); else
		strcpy(ptr+shift-3, "cfg\0");
}

//-------------------------------------------------------------------
int load_params_values(const char *fn, int update_vars, int read_param_set)
{
	int i, fd=-1, rcnt;
	register const char *ptr;	
	struct stat st;
	char *buf;
	
	if (fn == NULL || fn[0] == 0) return 0;
	if (read_param_set)
	{
		set_params_values_name(fn, -1);
		// find param set
		fd = open(cfg_name, O_RDONLY, 0777);
		if (fd >= 0)
		{
			buf=umalloc(16);
			rcnt = read(fd, buf, 15);
			buf[rcnt] = 0;
			close(fd);
			conf.script_param_set = strtol(buf, NULL, 0);
			ufree(buf);
		} else conf.script_param_set = 0;
	}
	set_params_values_name(fn, conf.script_param_set);
	if (!update_vars) return 0;
	
	// open and read file
	if (stat(cfg_set_name,&st) != 0)
		return 0;
	buf=umalloc(st.st_size+1);
	if(!buf)
		return 0;
	fd = open(cfg_set_name, O_RDONLY, 0777);
	if (fd < 0) {
		ufree(buf);
		return 0;
	}
	rcnt = read(fd, buf, st.st_size);
	buf[rcnt] = 0;
	close(fd);

	for(i = 0; i < SCRIPT_NUM_PARAMS; ++i) script_params_update[i]=0;
    ptr = buf;

    while (ptr[0]) 
	{
        while (ptr[0]==' ' || ptr[0]=='\t') ++ptr; // whitespaces
        if (ptr[0]=='@')
		{
            if (strncmp("@param", ptr, 6) == 0) 
			{
                ptr+=6;
				process_param(ptr, 1);
            } else if (strncmp("@default", ptr, 8)==0) {
                ptr+=8;
				process_default(ptr, 1);
            }
        }
        while (ptr[0] && ptr[0]!='\n') ++ptr; // unless end of line
        if (ptr[0]) ++ptr;
    }
	ufree(buf);
	return 1;
}

//-------------------------------------------------------------------
void save_params_values(int unconditional)
{
	int i, n, fd, changed=0;
	char *buf,*p;
	for(i = 0; i < SCRIPT_NUM_PARAMS; i++)
	{
		if (script_loaded_params[i] != conf.ubasic_vars[i]) changed++;
		script_loaded_params[i] = conf.ubasic_vars[i];
	}
	if (!unconditional && !changed) return;

	if (cfg_name[0] == 0) set_params_values_name(conf.script_file, -1);
	fd = open(cfg_name, O_WRONLY|O_CREAT, 0777);
	if (fd >= 0)
	{
		char s[20];
		sprintf(s, " %d\n", conf.script_param_set);
		write(fd, s, strlen(s));
		close(fd);
	}
	
	// open and read file
	set_params_values_name(conf.script_file, conf.script_param_set);

	buf=umalloc(SCRIPT_NUM_PARAMS*(28 + 20)); // max possible params * (param description + some extra for @default etc)
	if(!buf)
		return;

	fd = open(cfg_set_name, O_WRONLY|O_CREAT, 0777);
	if (fd < 0) {
		ufree(buf);
		return;
	}
	buf[0] = 0;
	p=buf;
	for(n = 0; n < SCRIPT_NUM_PARAMS; ++n)
	{
		if (script_params[n][0] != 0)
		{
			p+=sprintf(p,"@param %c %s\n@default %c %d\n",'a'+n,script_params[n],'a'+n,conf.ubasic_vars[n]);
		}
	}
	write(fd, buf, strlen(buf));
	close(fd);
	ufree(buf);
}



//-------------------------------------------------------------------
void script_load(const char *fn, int saved_params) {
    int i, update_vars;
    FILE *fd = NULL;
    struct stat st;
    
//    save_params_values(0);

    if(script_source_str && script_source_str != ubasic_script_default)
        free((void *)script_source_str);

    script_source_str = ubasic_script_default;
    update_vars = (strcmp(fn, conf.script_file) != 0) || !saved_params || (saved_params == 2);  // update if new file

    if (!fn[0]) { // load internal script
        if (!conf.script_file[0]) { // internal script was used last time
            fd = fopen(SCRIPT_DEFAULT_FILENAME, "rb");
            if (fd) {
                fn = SCRIPT_DEFAULT_FILENAME;
                update_vars = 1; 
            }
        }
    } else {
        fd = fopen(fn, "rb");
        if (!fd) {
            conf.script_file[0]=0;
            update_vars = 1; 
        }
    }
    // zero size = default script
    if(stat(fn,&st) != 0 || st.st_size == 0) {
        conf.script_file[0]=0;
        update_vars = 1; 
        if(fd) {
            fclose(fd);
            fd=0;
        }
    }
    if (fd){
        int rcnt;
        char *buf;

        buf = malloc(st.st_size+1);
        if(!buf) {
            fclose(fd);
            return;
        }

        // TODO we could process the script here to reduce size
        // or compile for lua
        rcnt = fread(buf, 1, st.st_size,fd);
        if (rcnt > 0){
            buf[rcnt] = 0;
            script_source_str = buf;
            strcpy(conf.script_file, fn);
        }
        else {
            free(buf);
        }
        fclose(fd);
    }

    if (update_vars) {
        for (i=0; i<SCRIPT_NUM_PARAMS; ++i) {
            conf.ubasic_vars[i] = 0;
            script_loaded_params[i] = 0;
        }
    }
    script_scan(conf.script_file, update_vars);
    if (saved_params)
        load_params_values(conf.script_file, update_vars, (saved_params!=2));	
    gui_update_script_submenu();
}

//-------------------------------------------------------------------
static int  print_screen_p;             // print_screen predicate: 0-off 1-on.
static int  print_screen_d = -1;        // print_screen file descriptor.
//static const char print_screen_file[] ="A/CHDK/SCRIPTS/PR_SCREEN.TXT";
static const char print_screen_file_prefix[] = "A/CHDK/LOGS/LOG_";
char print_screen_file[25];
static const char extension_txt[] = ".TXT";

void script_print_screen_init()
{
  print_screen_p = 0;
  if (print_screen_d >= 0) {
    close(print_screen_d);
    print_screen_d = -1;
  }
}

void script_print_screen_end()
{
  if (print_screen_d >= 0) {
    close(print_screen_d);
    print_screen_d = -1;
    print_screen_p = 0;
  }
}

void script_print_screen_statement(int val)
{
  print_screen_p = val;
  if (val) {
    if (print_screen_d>=0) close(print_screen_d);
    int i=0;
    int c=0;
    static char file_number[5];
    strcpy(print_screen_file, print_screen_file_prefix);
    if (val<0) val = -val;
    while (val > 9999) val += -10000;
    for (i=10; i<=1000; i=i*10) { if (val<i) ++c; }
    for (i=1; i<=c; ++i) { sprintf(file_number, "%d", 0); strcat(print_screen_file, file_number); }
    sprintf(file_number, "%d", val);
    strcat(print_screen_file, file_number);
    strcat(print_screen_file, extension_txt);
    print_screen_d = open(print_screen_file, O_WRONLY|O_CREAT|O_TRUNC, 0777);
  }
}

void script_console_add_line(const char *str)
{
    console_add_line(str);

    if (print_screen_p && (print_screen_d >= 0)) {
        char nl = '\n';
		// TODO this should be uncached memory
        write(print_screen_d, str, strlen(str) );
        write(print_screen_d, &nl, 1);
    }
}

static int is_lua()
{
  int len;
  char const* s;
  s = conf.script_file;
  len = strlen( s );
  return len >= 4 && ( s[len-1] == 'a' || s[len-1] == 'A' )
    && ( s[len-2] == 'u' || s[len-2] == 'U' )
    && ( s[len-3] == 'l' || s[len-3] == 'L' )
    && s[len-4] == '.';
}

static void wait_and_end(void)
{
	script_console_add_line("PRESS SHUTTER TO CLOSE");

	// We're not running any more, but we have scheduled stuff that
	// needs to finish. So keep the script marked as running, but don't
	// call any more scripting functions.
	state_kbd_script_run = 3;	
}

static void process_script()
{   // Note: This function is called from an action stack for AS_SCRIPT_RUN.
    
    long t;
    int Lres;

    if (state_kbd_script_run != 3) {
#ifdef OPT_LUA
        if( L ) {
            int top;
            if (state_lua_kbd_first_call_to_resume) {
                state_lua_kbd_first_call_to_resume = 0;
                top = 0;
            } else {
                top = lua_gettop(Lt);
            }
            Lres = lua_resume( Lt, top );

            if (Lres != LUA_YIELD && Lres != 0) {
                script_console_add_line( lua_tostring( Lt, -1 ) );
                if(conf.debug_lua_restart_on_error){
                    lua_script_reset();
                    script_start_gui(0);
                } else {
                    wait_and_end();
                }
                return;
            }

            if (Lres != LUA_YIELD) {
                script_console_add_line(lang_str(LANG_CONSOLE_TEXT_FINISHED));
                action_pop();
                script_end();
            }    
        } else
#endif
        {
#ifdef OPT_UBASIC
            ubasic_run();
            if (ubasic_finished()) {
                script_console_add_line(lang_str(LANG_CONSOLE_TEXT_FINISHED));
                action_pop();
                script_end();
            }    
#endif
        }
    }
}

static int script_action_stack(long p)
{
    // process stack operations
    switch (p) {
        case AS_SCRIPT_RUN:
            if (state_kbd_script_run)
                process_script();
            else
                action_pop();
            break;
        case AS_MOTION_DETECTOR:
            if(md_detect_motion()==0)
            {
                action_pop();
#ifdef OPT_LUA
                if (L)
                {
                       // We need to recover the motion detector's
                       // result and push
                       // it onto the thread's stack.
                       lua_pushnumber( Lt, md_get_result() );
                } else
#endif
                {
#ifdef OPT_UBASIC
                    ubasic_set_md_ret(md_get_result());
#endif
                }
            }
            break;
        default:
            if (!action_stack_standard(p) && !state_kbd_script_run)
            {
                /*finished();*/
                action_pop();
                script_end();
            }
            break;
    }
    
    return 1;
}

long script_stack_start()
{
    running_script_stack_name = action_stack_create(&script_action_stack, AS_SCRIPT_RUN);
    return running_script_stack_name;
}

int script_is_running()
{
    return !action_stack_is_finished(running_script_stack_name);
}

void script_end()
{
    script_print_screen_end();
#ifdef OPT_LUA
    if( L ) {
      lua_script_reset();
    } else
#endif
    {
#ifdef OPT_UBASIC
      ubasic_end();
#endif
    }
	md_close_motion_detector();
	shot_histogram_set(0);
    kbd_key_release_all();
    state_kbd_script_run = 0;

    conf_update_prevent_shutdown();

    vid_bitmap_refresh();
}

long script_start_gui( int autostart )
{
    int i;

    shot_histogram_set(0);
    if (autostart)
        auto_started = 1;
    else
        auto_started = 0;

    kbd_last_clicked = 0;

    /*if (!autostart)*/ kbd_key_release_all();

    console_clear();
    script_print_screen_init();

    if (conf.script_param_save) {
        save_params_values(0);
    }
    if( autostart )
        script_console_add_line("***Autostart***");
    else
        script_console_add_line(lang_str(LANG_CONSOLE_TEXT_STARTED));

    if( is_lua() ) {
#ifdef OPT_LUA
        if( !lua_script_start(script_source_str) ) {
            script_print_screen_end();
            wait_and_end();
            return -1;
        }
        for (i=0; i<SCRIPT_NUM_PARAMS; ++i) {
            if( script_params[i][0] ) {
                char var = 'a'+i;
                lua_pushlstring( L, &var, 1 );
                lua_pushnumber( L, conf.ubasic_vars[i] );
                lua_settable( L, LUA_GLOBALSINDEX );
            }
        }
        state_lua_kbd_first_call_to_resume = 1;
#else
        console_add_line("Cannot run script.");
        console_add_line("There is no Lua");
        console_add_line("support in this build.");
        return -1;
#endif
    } else
    { // ubasic
#ifdef OPT_UBASIC
        ubasic_init(script_source_str);

        for (i=0; i<SCRIPT_NUM_PARAMS; ++i) {
            ubasic_set_variable(i, conf.ubasic_vars[i]);
        }
#else
        console_add_line("Cannot run script.");
        console_add_line("There is no UBasic");
        console_add_line("support in this build.");
        return -1;
#endif
    }

    state_kbd_script_run = 1;

    conf_update_prevent_shutdown();

    return script_stack_start();
}

#ifdef OPT_LUA
long script_start_ptp( char *script , int keep_result )
{
  lua_script_start(script);
  lua_keep_result = keep_result;
  state_lua_kbd_first_call_to_resume = 1;
  state_kbd_script_run = 1;
  kbd_set_block(1);
  auto_started = 0;
  return script_stack_start();
}
#endif

int script_key_is_pressed(int k)
{
    if (k==0xFF)
        return get_usb_power(1);
    if (k > 0)
        return kbd_is_key_pressed(k);
    return 0;
}

int script_key_is_clicked(int k)
{
    if (k==0xFF)
        return get_usb_power(1);
    if (k > 0)
        return (kbd_last_clicked == k);
    return 0;
}

static const struct Keynames {
    int keyid;
    char *keyname;
} keynames[] = {
    { KEY_UP,           "up"         },
    { KEY_DOWN,         "down"       },
    { KEY_LEFT,         "left"       },
    { KEY_RIGHT,        "right"      },
    { KEY_SET,          "set"        },
    { KEY_SHOOT_HALF,   "shoot_half" },
    { KEY_SHOOT_FULL,   "shoot_full" },
    { KEY_ZOOM_IN,      "zoom_in"    },
    { KEY_ZOOM_OUT,     "zoom_out"   },
    { KEY_MENU,         "menu"       },
    { KEY_DISPLAY,      "display"    },
    { KEY_PRINT,        "print"      },
    { KEY_ERASE,        "erase"      },
    { KEY_ISO,          "iso"        },
    { KEY_FLASH,        "flash"      },
    { KEY_MF,           "mf"         },
    { KEY_MACRO,        "macro"      },
    { KEY_VIDEO,        "video"      },
    { KEY_TIMER,        "timer"      },
    { KEY_EXPO_CORR,    "expo_corr"  },
    { KEY_MICROPHONE,   "fe"         },
    { KEY_ZOOM_ASSIST,  "zoom_assist"},
    { KEY_AE_LOCK,      "ae_lock"    },
    { KEY_METERING,     "metering_mode"},
    { 0xFF,             "remote"     },
    { 0xFFFF,           "no_key"     },
};

int script_keyid_by_name (const char *n)
{
    int i;
    for (i=0;i<sizeof(keynames)/sizeof(keynames[0]);i++)
    if (strcmp(keynames[i].keyname,n) == 0)
        return keynames[i].keyid;
    return 0;
}

