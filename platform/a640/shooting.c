#define PARAM_FILE_COUNTER      0x34

#include "../generic/shooting.c"

long get_next_photo_dirfile_num()
{
    long tmp;
    long dirnum, filenum;

    get_parameter_data(0x2f, &tmp, 4);

    dirnum = (tmp>>18)&0x3FF;
    filenum = ((tmp>>4)&0x3FFF) + 1;

    if ((filenum % 100) == 0){
	dirnum++;
    }

    return (dirnum << 16) | (filenum);
}

long get_file_next_counter()
{
    return get_file_counter();
}
