#include "platform.h"

void *hook_raw_fptr()
{
    return (void*)0x36A90;
}

void *hook_raw_ret_addr()
{
    return (void*)0xFFCB4C5C;
}

char *hook_raw_image_addr()
{
    return (char*)0x10563980;
}

long hook_raw_size()
{
    return 0x8CAE10;
}
