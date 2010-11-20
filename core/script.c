#include "stdlib.h"
#include "keyboard.h"
#include "platform.h"
#include "core.h"
#include "gui.h"
#include "gui_draw.h"
#include "conf.h"
#include "script.h"
#include "console.h"

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
