#ifdef TEST

#include <stdio.h>

void ubasic_camera_click(const char *s)
{
    printf("***button %s***\n",s);
}

void ubasic_camera_sleep(int v)
{
    printf("***sleep %d***\n",v);
}

void ubasic_camera_shoot()
{
    printf("***shoot***\n");
}

void shooting_set_tv(int v)
{
    printf("***set tv %d***\n",v);
}

void shooting_set_tv_rel(int v)
{
    printf("***set tv rel %d***\n",v);
}

void shooting_set_av(int v)
{
    printf("***set av %d***\n",v);
}

void shooting_set_av_rel(int v)
{
    printf("***set av rel %d***\n",v);
}

int shooting_get_tv()
{
    return 0;
}

int shooting_get_av()
{
    return 0;
}


#endif
