#define PARAM_FILE_COUNTER      0x34

#include "../generic/shooting.c"

const int dof_tbl[] = {7300, 8460, 9565, 10835, 12565, 14926, 17342, 21709, 29200};
const int dof_tbl_size = sizeof(dof_tbl)/sizeof(dof_tbl[0]);

long get_next_photo_dirfile_num()
{
    long tmp;
    long dirnum, filenum;

    tmp = get_file_next_counter();

    dirnum = (tmp>>18)&0x3FF;
    filenum = ((tmp>>4)&0x3FFF);

    if ((filenum % 100) == 0){
	dirnum++;
    }

    return (dirnum << 16) | (filenum);
}

long get_file_next_counter()
{
    return get_file_counter();
}
