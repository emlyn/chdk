#include "platform.h"

void *hook_raw_fptr()
{
    return (void*)0x367D0;
}

void *hook_raw_ret_addr()
{
    return (void*)0xFFCB4C5C;
}

char *hook_raw_image_addr()
{
    return (char*)0x1058EBD4;
}

long hook_raw_size()
{
    return 0x644C40;
}

void *vid_get_viewport_live_fb()
{
    return (void*)0x10670d50;
}

void *get_parameter_data_magic_pointer()
{
    return (void*)0x785C0;
}

