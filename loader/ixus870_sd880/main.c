extern long *blob_chdk_core;
extern long *blob_copy_and_reset;
extern long blob_chdk_core_size;
extern long blob_copy_and_reset_size;

void __attribute__((noreturn)) my_restart() 
{
    void __attribute__((noreturn)) (*copy_and_restart)(char *dst, char *src, long length);
    int i;

    for (i=0; i<(blob_copy_and_reset_size/sizeof(long)); i++){
	((long*)(RESTARTSTART))[i] = blob_copy_and_reset[i];
    }

    // Note that this doesn't really call the copy_and_restart() function
    // directly. At RESTARTSTART we first have the code in entry.S, but that
    // code silently passes the arguments to the real copy_and_restart()
    copy_and_restart = (void*)RESTARTSTART;
    copy_and_restart((void*)MEMISOSTART, (char*)blob_chdk_core, blob_chdk_core_size);
}
