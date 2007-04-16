#define PARAM_FILE_COUNTER      0x34

#include "../generic/shooting.c"

const int dof_tbl[] = {5800, 6420, 7060, 7700, 8340, 9950, 11550, 13160, 14750, 17150, 19570, 22760, 26750, 30750, 34800};
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
