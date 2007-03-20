#include "conf.h"
#include "stdlib.h"

#define SCRIPT_BUF_SIZE 2048

#define FN_COUNTER  "A/RCFG.BIN"
#define FN_SCRIPT  "A/SCRIPT.BAS"
#define CNF_MAGICK_VALUE (0x5acd20c1)

int conf_show_osd;
int conf_save_raw;
int conf_script_shoot_delay;
int conf_show_histo;
int conf_raw_fileno;
int conf_ubasic_var_a;
int conf_ubasic_var_b;
int conf_ubasic_var_c;

int confns_enable_memdump;


int state_shooting_progress;
const char *state_ubasic_script;
int state_save_raw_nth_only;
int state_expos_recalculated;
int state_expos_under;
int state_expos_over;

int state_debug1;
int debug_propcase_show;
int debug_propcase_page;
int debug_vals_show;

static int dfirst;
static char ubasic_script_buf[SCRIPT_BUF_SIZE];

const char *ubasic_script_default =
#if 1
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
    "sleep 1000\n"
    "for s=1 to 999\n"
      "shoot\n"
      "sleep 2000\n"
    "next s\n"
    "shoot\n"
    "end\n";
#endif

static void load_defaults()
{
    conf_show_osd = 1;
    conf_save_raw = 0;
    conf_script_shoot_delay = 20;
    conf_show_histo = 0;
    conf_raw_fileno = 1000;
    conf_ubasic_var_a = 0;
    conf_ubasic_var_b = 0;
    conf_ubasic_var_c = 0;
}

static void do_save(int fd)
{
    long t;
    t = CNF_MAGICK_VALUE;
    write(fd, &t, 4);

    write(fd, &conf_raw_fileno, 4);
    write(fd, &conf_show_osd, 4);
    write(fd, &conf_save_raw, 4);
    write(fd, &conf_script_shoot_delay, 4);
    write(fd, &conf_show_histo, 4);
    write(fd, &conf_ubasic_var_a, 4);
    write(fd, &conf_ubasic_var_b, 4);
    write(fd, &conf_ubasic_var_c, 4);
}

static int do_restore(int fd)
{
    int rcnt;
    long t;

    /* read magick value */
    rcnt = read(fd, &t, 4);
    if ((rcnt != 4) || (t != CNF_MAGICK_VALUE))
	return 1;

    /* read raw file number counter */
    rcnt = read(fd, &t, 4);
    if (rcnt != 4)
	return 1;
    conf_raw_fileno = (t|3) + 1;

    /* read: osd */
    rcnt = read(fd, &conf_show_osd, 4);
    if (rcnt != 4)
	return 1;

    /* read: raw */
    rcnt = read(fd, &conf_save_raw, 4);
    if (rcnt != 4)
	return 1;

    /* read: script shoot delay */
    rcnt = read(fd, &conf_script_shoot_delay, 4);
    if (rcnt != 4)
	return 1;

    /* read: histogram */
    rcnt = read(fd, &conf_show_histo, 4);
    if (rcnt != 4)
	return 1;

    /* read: conf_ubasic_var_a */
    rcnt = read(fd, &conf_ubasic_var_a, 4);
    if (rcnt != 4)
	return 1;

    /* read: conf_ubasic_var_b */
    rcnt = read(fd, &conf_ubasic_var_b, 4);
    if (rcnt != 4)
	return 1;

    /* read: conf_ubasic_var_c */
    rcnt = read(fd, &conf_ubasic_var_c, 4);
    if (rcnt != 4)
	return 1;

    return 0;
}


void conf_save(int force)
{
    int fd;

    if (((conf_raw_fileno & 3) == 0) || (dfirst == 1) || force){
	dfirst = 0;

	fd = open(FN_COUNTER, O_WRONLY|O_CREAT, 0777);
	if (fd >= 0){
	    do_save(fd);
	    close(fd);
	}
    }
}


void conf_restore()
{
    int fd;

    fd = open(FN_COUNTER, O_RDONLY, 0777);
    if (fd >= 0){
	if (do_restore(fd))
	    load_defaults();
	close(fd);
    } else {
	load_defaults();
    }
    dfirst = 1;

    state_ubasic_script = ubasic_script_default;

    fd = open(FN_SCRIPT, O_RDONLY, 0777);
    if (fd >= 0){
	int rcnt = read(fd, ubasic_script_buf, SCRIPT_BUF_SIZE);
	if (rcnt > 0){
	    if (rcnt == SCRIPT_BUF_SIZE) { /* FIXME TODO script is too big? */
		ubasic_script_buf[SCRIPT_BUF_SIZE-1] = 0;
	    } else
		ubasic_script_buf[rcnt] = 0;
	    state_ubasic_script = ubasic_script_buf;
	}
	close(fd);
    }
}

