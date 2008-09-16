#ifndef LANG_H
#define LANG_H

//-------------------------------------------------------------------
extern void lang_init(int num);

extern void lang_load_from_mem(char *buf);
extern void lang_load_from_file(const char *filename);

extern char* lang_str(int str);

//-------------------------------------------------------------------
#endif
