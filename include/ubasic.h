#ifndef UBASIC_H
#define UBASIC_H

extern int ubasic_error;
extern int ubasic_line;

void ubasic_init(const char *program);
void ubasic_run(void);
int ubasic_finished(void);

int ubasic_get_variable(int varnum);
void ubasic_set_variable(int varum, int value);

#endif
