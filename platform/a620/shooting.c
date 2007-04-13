#define PARAM_FILE_COUNTER      0x2F

#include "../generic/shooting.c"

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
    return ((get_file_counter()>>4)+1)<<4;
}
