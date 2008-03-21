
#include <stdlib.h>
#include <conf.h>

void dbg_log(char *str);

#define LED_PR 0xc0220084

static void blink(int cnt)
{
	volatile long *p=(void*)LED_PR;
	int i;

	for(;cnt>0;cnt--){
		p[0]=0x46;

		for(i=0;i<0x200000;i++){
			asm ("nop\n");
			asm ("nop\n");
		}
		p[0]=0x44;
		for(i=0;i<0x200000;i++){
			asm ("nop\n");
			asm ("nop\n");
		}
	}
}

#define ROMSIZE (4*1024*1024)

static int dbg_fh = 0;

void dbg_start() {
  if (0 == dbg_fh) {
    if ((dbg_fh = open("A/MISC/DEBUG.LOG", O_WRONLY|O_CREAT, 0777)) > 0) {
      lseek(dbg_fh, 0, SEEK_END);
    }
  }
}

void dbg_stop() {
/*
  static int mem_dmp = 0;
  if (0 == mem_dmp) {
    dbg_log("Memdump: 0x00001900 - (0x02000000-0x1900) -> A/MISC/MEMDMP01.BIN\n");
    if ((mem_dmp = open("A/MISC/MEMDMP01.BIN", O_WRONLY|O_CREAT, 0777)) > 0) {
      lseek(mem_dmp, 0, SEEK_SET);
      write(mem_dmp, (char*)0x00001900, 32*1024*1024-0x1900);
      close(mem_dmp);
    }
    dbg_log("Memdump: 0x10000000 - 0x01000000 -> A/MISC/MEMDMP02.BIN\n");
    if ((mem_dmp = open("A/MISC/MEMDMP02.BIN", O_WRONLY|O_CREAT, 0777)) > 0) {
      lseek(mem_dmp, 0, SEEK_SET);
      write(mem_dmp, (char*)0x10000000, 0x01000000);
      close(mem_dmp);
    }
  }
*/
  
  if (dbg_fh > 0) {
    close(dbg_fh);
    dbg_fh = 0;
  }
}

void dbg_log(char *str) {
  if (dbg_fh > 0) {
    write(dbg_fh, str, strlen(str));
  }
}

static int dump_rom() {
  volatile int ret = 0;
  volatile int fd;

  if ((fd  = open("A/MISC/FW_FFC0.DMP", O_WRONLY|O_CREAT, 0777)) > 0) {
    write(fd, (char*)0xFFC00000, ROMSIZE);
    close(fd);
    ret = 1;
  }

  return ret;
}

void go_debug(long kbd_state[]) {
/*
  long ckey = kbd_state[2];
  for (; 0 != ckey; ckey /= 2) {
    blink(1);
  }
*/

/*
  blink(2);
  if (1 == dump_rom()) {
    blink(3);
  }
  blink(1);
*/
}


