#include "console.h"
#include "stdlib.h"
#include "platform.h"
#include "camera.h"
#include "gui.h"
#include "gui_draw.h"

static char **console_buf = NULL;
static int console_line_start; // oldest valid line in console
static int console_max_lines; // total number of lines in console
static int console_num_lines; // number of valid lines
static int console_line_length;
static int console_x;
static int console_y;
static int console_autoredraw = 1;
static long console_last_drawn;

static int console_is_inited()
{
    return (console_buf != NULL);
}

static void console_ensure_inited()
{
    if (!console_is_inited())
        console_init(5, 25, 0, MAX_CONSOLE_LINES - 5);
}

static inline int console_line_index(int i)
{
    return i % console_max_lines;
}

static void console_start_line()
{
    if (console_max_lines == console_num_lines)
        console_line_start = console_line_index(console_line_start + 1);
    else
        ++console_num_lines;
    
     console_buf[console_line_index(console_line_start + console_num_lines - 1)][0]=0;
}

static void console_add_text(const char *str)
{
    console_ensure_inited();

    char *cur;
    int curlen;
    int left;
    
    do
    {
        cur = console_buf[console_line_index(console_line_start + console_num_lines - 1)];
        curlen = strlen(cur);
        left = console_line_length - curlen;
        if(strlen(str) > left)
        {
            strncpy(cur + curlen, str, left);
            cur[console_line_length] = 0;
            console_start_line();
            str += left;
        }
        else
        {
            strcat(cur, str);
            break;
        }
    } while(1);
}

void console_close()
{
    if (console_buf != NULL)
    {
        int i;
        for (i = 0; i < console_num_lines; ++i)
        { 
            free(console_buf[i]);
        }
        free(console_buf);

        console_buf = NULL;
    }
}

void console_init(int num_lines, int line_length, int x_pos, int y_pos)
{
    int i;
    
    console_close();
    
    console_max_lines = num_lines;
    console_line_length = line_length;
    console_y = y_pos;
    console_x = x_pos;
    
    console_buf = malloc(console_max_lines*sizeof(char*));
    for (i = 0; i < console_max_lines; ++i)
        console_buf[i] = malloc(console_line_length * sizeof(char) + 1); 

    console_line_start = 0;
    console_num_lines = 0;
    console_last_drawn = 0;
}

void console_clear()
{
    console_ensure_inited();

    register int i;

    for (i = 0; i < console_max_lines; ++i)
        console_buf[i][0] = 0;
    
    console_num_lines = console_line_start = 0;
    
	if(console_autoredraw) {
		console_redraw();
	}
}

void console_draw()
{
    console_ensure_inited();

    int i, c, l;

    long t = get_tick_count();
    if (t <= console_last_drawn + CONSOLE_HIDE_TIMEOUT)
    {
        for(c = 0; c < console_num_lines; ++c)
        {
            i = console_line_index(console_line_start + c);
            l = strlen(console_buf[i]);
            
            draw_txt_string(console_x, console_y + console_max_lines - console_num_lines + c,
                            console_buf[i], MAKE_COLOR(COLOR_BG, COLOR_FG));

            for (; l < console_line_length; ++l)
                draw_txt_char(console_x + l, console_y + console_max_lines - console_num_lines + c,
                              ' ', MAKE_COLOR(COLOR_BG, COLOR_FG));
        }
    }
}

void console_add_line(const char *str)
{
    console_ensure_inited();

    console_start_line();
    console_add_text(str);
    
    console_last_drawn = get_tick_count();
	if(console_autoredraw) {
		console_draw();
	}
}

void console_set_layout(int x1, int y1, int x2, int y2) //untere linke Ecke(x1,y1), obere reche Ecke(x2,y2) - lower left corner (x1,y1), upper right corner(x2,y2)
{
    console_ensure_inited();

    int i, len, newLinesCount, newLineLength, newNumLines, lineDelta, idx;
    char **tmp;
    
    if( (x1>=0) && (x1<x2) && (x1<=MAX_CONSOLE_LINE_LENGTH) && (y1>=0) && (y1<y2) && (y1<=MAX_CONSOLE_LINES) && (x2<=MAX_CONSOLE_LINE_LENGTH) && (y2<=MAX_CONSOLE_LINES))
    {
        //In neuen Puffer kopieren - copy to new buffer
        newLineLength = x2 - x1;
        newLinesCount = y2 - y1;
        if((newLineLength != console_line_length) || (newLinesCount != console_max_lines))
        {
            lineDelta = console_num_lines - newLinesCount;
            if(lineDelta < 0)
                lineDelta=0;
    
            newNumLines=0;
            tmp = malloc(newLinesCount * sizeof(char*)); //realloc Nachbildung - realloc emulation
            for(i = 0; i < newLinesCount; ++i)
            {
                tmp[i] = malloc(newLineLength * sizeof(char) + 1);
                if(i < console_num_lines)
                {
                    ++newNumLines;
                    idx = console_line_index(console_line_start + i + lineDelta);
                    len = strlen(console_buf[idx]);
                    if(len > newLineLength)
                        len = newLineLength;
            
                    strncpy(tmp[i], console_buf[idx], len);
                    tmp[i][len] = 0x0;
                } else
                tmp[i][0] = 0x0;
            }
            //Speicher freigeben - free memory
            console_close();

            //neue Werte setzten - set new values
            console_buf = tmp;
            console_line_start = 0;
            console_num_lines = newNumLines;
            console_max_lines = newLinesCount;
            console_line_length = newLineLength;
        }
        
        console_x = x1;
        console_y = MAX_CONSOLE_LINES - y2;
		if(console_autoredraw) {
			console_redraw();
		}
    }
}

void console_set_autoredraw(int val) {
	console_autoredraw = val;
}

void console_redraw()
{
	draw_restore();
	console_last_drawn = get_tick_count();
	console_draw();
}

