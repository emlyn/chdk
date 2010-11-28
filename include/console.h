#ifndef _CONSOLE_H
#define _CONSOLE_H

#define MAX_CONSOLE_LINES        14
#define MAX_CONSOLE_LINE_LENGTH  45
#define CONSOLE_HIDE_TIMEOUT     3000

void console_close();
void console_init(int num_lines, int line_length, int x_pos, int y_pos);
void console_clear();
void console_add_line(const char *str);
void console_draw();
void console_set_layout(int x1, int y1, int x2, int y2);
void console_redraw();
void console_set_autoredraw(int val);

#endif // _CONSOLE_H

