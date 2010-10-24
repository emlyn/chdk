#include "lolevel.h"
#include "stdlib.h"
//#include "core.h"
#include "script.h"

// A550
/*
static int dump_rom() {
  volatile int ret = 0;
  volatile int fd;

  if ((fd  = open("A/MISC/FW_FFC0.DMP", O_WRONLY|O_CREAT, 0777)) > 0) {
    //write(fd, (char*)0xFFC00000, ROMSIZE);
    write(fd, (char*)0xFF810000, ROMSIZE);
    close(fd);
    ret = 1;
  }

  return ret;
}
*/

/*
// tty_Init() (console log)
void __attribute__((naked,noinline)) sub_FF811A0C_my(){
    asm volatile (
        "MOV     R0, #0x1000\n"
        "STR     LR, [SP]!\n"
        "BL      sub_FF811474\n"   // tty_StartMsg
        "MOV     R1, #0x32\n"
        "LDR     R2, =aNull\n"   // change console target ?
        "MOV     R0, #0x14\n"
        "BL      iosInit\n"
        "BL      ttyDrv\n"
        "LDR     LR, [SP],#arg_4\n"
        "B       sub_FF811874\n"
    );
*/

#if 0
//#if CAM_CONSOLE_LOG_ENABLED
    extern void msleep(long);

    typedef struct {
        long dev_hdr[4];
        long opened;
        long fill[64];
    } MY_DEV;

    #define CONS_W (45)
    #define CONS_H (128)

    char console_buf[CONS_H][CONS_W];
    long console_buf_line = 0;
    long console_buf_line_ptr = 0;

    char cmd[100] = "ShowCameraLog\n\0";
    int cons_cmd_ptr = -1;

    void mytty_putc(char c);

    int ttyRead(MY_DEV* tty,  char* buffer, int nBytes) {
        int r = 1;

        if (cons_cmd_ptr == -1) {
            msleep(2000);
            cons_cmd_ptr = 0;
        }

        mytty_putc('r');

        if (cmd[cons_cmd_ptr] != 0) {
            *buffer = cmd[cons_cmd_ptr];
            cons_cmd_ptr++;
        } else {
            while (cons_cmd_ptr != 0) {
                msleep(10);
            }
            *buffer = cmd[cons_cmd_ptr];
            cons_cmd_ptr++;
        }

        return r;
    }

    void mytty_nextline() {
        int i;

        console_buf_line_ptr=0;
        console_buf_line++;
        if (console_buf_line>=CONS_H) {
            console_buf_line = 0;
        }
        for (i=0;i<15;i++) {
            int l=i+console_buf_line;
            if (l>=CONS_H)
                l-=CONS_H;
            console_buf[l][0] = 0;
        }
    }

    void mytty_putc(char c) {
        if (c == 0xa) {
            mytty_nextline();
        } else {
            if (console_buf_line_ptr>=(CONS_W-1)){
                mytty_nextline();
            }

            console_buf[console_buf_line][console_buf_line_ptr++] = c;
            console_buf[console_buf_line][console_buf_line_ptr] = 0;
        }
    }
    //int tyWrite = 0xffcddc40;   // A570IS
    int tyWrite = 0xFFB5EC84;   // ROM:FFB5EC84

    //ttyWrite seems to work, Read might be broken
    int ttyWrite(MY_DEV* tty,  char* buffer, int nBytes) {
        int i;

        for (i=0;i<nBytes;i++){
            mytty_putc(buffer[i]);
        }

        return ((int(*)(void *p, void *p2, int l))tyWrite)(tty, buffer, nBytes);
        //return nBytes;
    }

    /*
    Referenced from ttyDrv_init as
    LDR     R11, =TTY_DRV_NUM
    and ttyDevCreate as
    LDR     R9, =TTY_DRV_NUM
    */
    int *TTY_DRV_NUM = (int*)0x00011a44;   // A570IS
    //int *TTY_DRV_NUM = (int*)0x876A8;   // ??? ROM:FFB5DC20

    static void replaceConsoleDriver() {
        // These function addresses are from ttyDrv_init function call
        int f0 = 0xffcdccd0;
        int f1 = 0;
        int f2 = 0xffcdccd0;
        int f3 = 0xffcdcd10;
        int f6 = 0xffcdcd54;
        int fRead = (int)&ttyRead;
        int fWrite = (int)&ttyWrite;
        int newdriver_id = _iosDrvInstall((void*)f0, (void*)f1, (void*)f2, (void*)f3, (void*)fRead, (void*)fWrite, (void*)f6);

        *TTY_DRV_NUM = newdriver_id;
    }

    // ROM:FF811A0C
    void h_ios_tty_Init() {
        /*
        asm volatile (
            "MOV     R0, #0x1000"
            "BL      sub_FF811474"

            "MOV     R1, #0x32"
            "LDR     R2, =aNull"
            "MOV     R0, #0x14"
            "BL      iosInit"
        );
        */
        _iosInit(0x14, 0x32, "/null");
        replaceConsoleDriver();
        /*
        asm volatile (
            "BL      sub_FF811874"
        );
        */
    }
#endif
