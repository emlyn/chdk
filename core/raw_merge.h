#ifndef RAW_MERGE_H
#define RAW_MERGE_H

#define RAW_OPERATION_SUM 0
#define RAW_OPERATION_AVERAGE 1

int raw_merge_start(int action);
void raw_merge_add_file(const char * filename);
void raw_merge_end(void);
int raw_subtract(const char *from, const char *sub, const char *dest); 
#endif
