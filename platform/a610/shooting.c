#define PARAM_FILE_COUNTER      0x2F

#include "../generic/shooting.c"

const int dof_tbl[] = {7300, 8460, 9565, 10835, 12565, 14926, 17342, 21709, 29200};
const int dof_tbl_size = sizeof(dof_tbl)/sizeof(dof_tbl[0]);

static long get_file_next_counter() {
    return ((get_file_counter()>>4)+1)<<4;
}

long get_target_file_num() {
    long n;
    
    n = get_file_next_counter();
    n = (n>>4)&0x3FFF;
    return n;
}

long get_target_dir_num() {
    long n;
    
    n = get_file_next_counter();
    n = (n>>18)&0x3FF;
    if (get_target_file_num()%100 == 1) ++n;
    return n;
}
