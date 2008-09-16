#include "stdlib.h"
#include "keyboard.h"
#include "platform.h"
#include "core.h"
#include "lang.h"
#include "gui.h"
#include "gui_lang.h"
#include "gui_draw.h"
#include "gui_bench.h"

//-------------------------------------------------------------------
static struct {
    int screen_input_bps;
    int screen_output_bps;
    int memory_read_bps;
    int memory_write_bps;
    int disk_read_buf_bps;
    int disk_write_buf_bps;
    int disk_write_raw_bps;
    int disk_write_mem_bps;
} bench;
static char buf[32];
static int bench_to_draw;

//-------------------------------------------------------------------
#define SCREEN_COLOR            0xF7

//-------------------------------------------------------------------
void gui_bench_init() {
    bench.screen_input_bps=-1;
    bench.screen_output_bps=-1;
    bench.memory_read_bps=-1;
    bench.memory_write_bps=-1;
    bench.disk_read_buf_bps=-1;
    bench.disk_write_buf_bps=-1;
    bench.disk_write_raw_bps=-1;
    bench.disk_write_mem_bps=-1;
    bench_to_draw = 1;
}

//-------------------------------------------------------------------
static void gui_bench_draw_results_screen(int pos, int value, int ss) {
    if (value!=-1) {
        if (value)
            sprintf(buf, "%7d Kb/s  %3d FPS", value/1024, value/ss);
        else
            sprintf(buf, lang_str(LANG_BENCH_CALCULATING));
        draw_txt_string(18, pos, buf, MAKE_COLOR(SCREEN_COLOR, COLOR_WHITE));
    }
}

//-------------------------------------------------------------------
static void gui_bench_draw_results(int pos, int value) {
    if (value!=-1) {
        if (value)
            sprintf(buf, "%7d Kb/s      ", value/1024);
        else
            sprintf(buf, lang_str(LANG_BENCH_CALCULATING));
        draw_txt_string(18, pos, buf, MAKE_COLOR(SCREEN_COLOR, COLOR_WHITE));
    }
}

//-------------------------------------------------------------------
void gui_bench_draw() {
    switch (bench_to_draw) {
        case 1:
            draw_filled_rect(0, 0, screen_width-1, screen_height-1, MAKE_COLOR(SCREEN_COLOR, SCREEN_COLOR));
            draw_txt_string(1, 0,  lang_str(LANG_BENCH_TITLE), MAKE_COLOR(SCREEN_COLOR, COLOR_WHITE));

            draw_txt_string(1, 2,  lang_str(LANG_BENCH_SCREEN),       MAKE_COLOR(SCREEN_COLOR, COLOR_WHITE));
            draw_txt_string(3, 3,  lang_str(LANG_BENCH_WRITE), MAKE_COLOR(SCREEN_COLOR, COLOR_WHITE));
            draw_txt_string(3, 4,  lang_str(LANG_BENCH_READ), MAKE_COLOR(SCREEN_COLOR, COLOR_WHITE));

            draw_txt_string(1, 6,  lang_str(LANG_BENCH_MEMORY),       MAKE_COLOR(SCREEN_COLOR, COLOR_WHITE));
            draw_txt_string(3, 7,  lang_str(LANG_BENCH_WRITE), MAKE_COLOR(SCREEN_COLOR, COLOR_WHITE));
            draw_txt_string(3, 8,  lang_str(LANG_BENCH_READ), MAKE_COLOR(SCREEN_COLOR, COLOR_WHITE));

            draw_txt_string(1, 10, lang_str(LANG_BENCH_FLASH_CARD),   MAKE_COLOR(SCREEN_COLOR, COLOR_WHITE));
            draw_txt_string(3, 11, lang_str(LANG_BENCH_WRITE_RAW), MAKE_COLOR(SCREEN_COLOR, COLOR_WHITE));
            draw_txt_string(3, 12, lang_str(LANG_BENCH_WRITE_MEM), MAKE_COLOR(SCREEN_COLOR, COLOR_WHITE));
            draw_txt_string(3, 13, lang_str(LANG_BENCH_WRITE_64K), MAKE_COLOR(SCREEN_COLOR, COLOR_WHITE));
            draw_txt_string(3, 14, lang_str(LANG_BENCH_READ_64K), MAKE_COLOR(SCREEN_COLOR, COLOR_WHITE));
            
            /* no break here */
        case 2:
            gui_bench_draw_results_screen(3, bench.screen_output_bps, screen_buffer_size);
            gui_bench_draw_results_screen(4, bench.screen_input_bps, screen_width * vid_get_viewport_height() * 3);

            gui_bench_draw_results(7, bench.memory_write_bps);
            gui_bench_draw_results(8, bench.memory_read_bps);

            gui_bench_draw_results(11, bench.disk_write_raw_bps);
            gui_bench_draw_results(12, bench.disk_write_mem_bps);
            gui_bench_draw_results(13, bench.disk_write_buf_bps);
            gui_bench_draw_results(14, bench.disk_read_buf_bps);

            bench_to_draw = 0;
            break;
        default:
            bench_to_draw = 0;
            break;
    }
}

//-------------------------------------------------------------------
static void gui_bench_run() {
    register long t;
    register int i, n;
    int s, x=0x55;
    register int *buf;
    register char *scr;
    char c;
    
    bench_to_draw = 2;

    bench.screen_output_bps = 0;
    gui_bench_draw();
    scr = vid_get_bitmap_fb();
    s = screen_buffer_size;
    t = get_tick_count();
    for (c=0; c<64; ++c)
        for (i=0; i<s; ++i)
            scr[i] = c;
    t = get_tick_count() - t;
    bench.screen_output_bps = s*64*100 / (t/10);
    bench_to_draw = 1;
    
    bench.screen_input_bps = 0;
    gui_bench_draw();
    scr = vid_get_viewport_fb();
    s = screen_width * vid_get_viewport_height() * 3;
    t = get_tick_count();
    for (n=0; n<64; ++n)
        for (i=0; i<s; ++i)
            c = scr[i];
    t = get_tick_count() - t;
    bench.screen_input_bps = s*64*100 / (t/10);
    bench_to_draw = 2;

    buf = malloc(0x10000);
    if (buf) {
        bench.memory_write_bps = 0;
        gui_bench_draw();
        t = get_tick_count();
        for (n=0; n<1024; ++n)
            for (i=0; i<0x10000/4; ++i)
                buf[i] = x;
        t = get_tick_count() - t;
        bench.memory_write_bps = 0x10000*100 / (t/10) * 1024;
        bench_to_draw = 2;

        bench.memory_read_bps = 0;
        gui_bench_draw();
        t = get_tick_count();
        for (n=0; n<1024; ++n)
            for (i=0; i<0x10000/4; ++i)
                x = buf[i];
        t = get_tick_count() - t;
        bench.memory_read_bps = 0x10000*100 / (t/10) * 1024;
        bench_to_draw = 2;
    }

    x = open("A/BENCH.TMP", O_WRONLY|O_CREAT, 0777);
    if (x>=0) {
        bench.disk_write_raw_bps = 0;
        gui_bench_draw();
        t = get_tick_count();
        s=write(x, hook_raw_image_addr(), hook_raw_size());
        t = get_tick_count() - t;
        close(x);
        bench.disk_write_raw_bps = s*100 / (t/10);
        bench_to_draw = 2;
    }

    x = open("A/BENCH.TMP", O_WRONLY|O_CREAT, 0777);
    if (x>=0) {
        bench.disk_write_mem_bps = 0;
        gui_bench_draw();
        t = get_tick_count();
        s=write(x, (void*)0x10000, 0xC00000);
        t = get_tick_count() - t;
        close(x);
        bench.disk_write_mem_bps = s*100 / (t/10);
        bench_to_draw = 2;
    }

    if (buf) {
        x = open("A/BENCH.TMP", O_WRONLY|O_CREAT, 0777);
        if (x>=0) {
            bench.disk_write_buf_bps = 0;
            gui_bench_draw();
            s = 0;
            t = get_tick_count();
            for (n=0; n<256; ++n)
                s+=write(x, buf, 0x10000);
            t = get_tick_count() - t;
            close(x);
            bench.disk_write_buf_bps = s*100 / (t/10);
            bench_to_draw = 2;
        }

        x = open("A/BENCH.TMP", O_RDONLY, 0777);
        if (x>=0) {
            bench.disk_read_buf_bps = 0;
            gui_bench_draw();
            s = 0;
            t = get_tick_count();
            for (n=0; n<256; ++n)
                s+=read(x, buf, 0x10000);
            t = get_tick_count() - t;
            close(x);
            bench.disk_read_buf_bps = s*100 / (t/10);
            bench_to_draw = 2;
        }
        free(buf);
    }
    remove("A/BENCH.TMP");
        
    gui_bench_draw();
}

//-------------------------------------------------------------------
void gui_bench_kbd_process() {
    switch (kbd_get_autoclicked_key()) {
    case KEY_SET:
        gui_bench_init();
        gui_bench_run();
        break;
    }
}

//-------------------------------------------------------------------

