#ifdef TEST
void ubasic_camera_click(const char *s)
{
    printf("***button %s***\n",s);
}

void ubasic_camera_sleep(long v)
{
    printf("***sleep %d***\n",v);
}

void ubasic_camera_shot()
{
    printf("***shot***\n");
}

//#####################################
#if 0
const char *ub_script =
    "10 sleep 3000\n"

    "20 shot\n"

    "30 click \"right\"\n"
    "40 click \"right\"\n"
    "50 click \"right\"\n"

    "60 shot\n"

    "70 click \"right\"\n"
    "80 click \"right\"\n"
    "90 click \"right\"\n"

    "100 shot\n"

    "110 click \"right\"\n"
    "120 click \"right\"\n"
    "130 click \"right\"\n"

    "140 shot\n"

    "500 end\n"
    ;
#elif 0
const char *ub_script =
    "10 sleep 1000\n"
    "20 for s = 1 to 5\n"
    "30 shot\n"
    "40 for n = 1 to 3\n"
    "50 click \"right\"\n"
    "60 next n\n"
    "70 next s\n"
    "80 end\n"
    ;
#else
const char *ub_script =
    "10 sleep 1000\n"
    "11 let a = 0\n"
    "12 let b = 2\n"
    "12 if a < 1 then let a = 3\n"
    "20 for s = 1 to a\n"
    "30 shot\n"
    "40 for n = 1 to b\n"
    "50 click \"right\"\n"
    "60 next n\n"
    "70 next s\n"
    "80 end\n";
#endif

int main()
{
    ubasic_init(ub_script);
    do {
	ubasic_run();
    } while(!ubasic_finished());

}
#endif
