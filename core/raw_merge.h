#ifndef RAW_MERGE_H
#define RAW_MERGE_H

#define RAW_OPERATIOM_SUM 0
#define RAW_OPERATIOM_AVERAGE 1

int raw_merge_start(int action);
void raw_merge_add_file(char * filename);
void raw_merge_end(void);

#endif
