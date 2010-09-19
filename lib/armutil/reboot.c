#include "platform.h"
#include "stdlib.h"
#define LOW_LEVEL
#include "lolevel.h"
/*
 shut down the display and reboot the camera. 
 bootfile is the name of the file to boot.
  Must be an unencoded ARM binary, will be loaded at 0x1900
  For cameras which use encoded diskboot, loader/<camera>/main.bin may be used
  For cameras which do not use encoded diskboot, DISKBOOT.BIN may be used
  No sanity checking is performed on the binary, except that the size is >= 4 bytes
 If bootfile is NULL, camera firmware is rebooted. DISKBOOT.BIN will be loaded or not according to normal rules
 returns 0 on failure, does not return on success
 does NOT save camera settings to flash
 does NOT retract lens before rebooting
 calling from playback mode is recommended
*/
int reboot(const char *bootfile) {
	if(bootfile == NULL) {
		if(_ExecuteEventProcedure("DispDev_EnableEventProc") == -1) {
			return 0;
		}
		if(_ExecuteEventProcedure("DispCon_TurnOffDisplay") == -1) {
			return 0;
		}
		_Restart(0);
	}

	int fd;
	int size;
	int rcnt;
	char *buf;
	unsigned data_tcm;
    void __attribute__((noreturn)) (*canon_copy_and_restart)(char *dst, char *src, unsigned length,char *start);

	// use open/read etc since it takes less mem, boot image might be large
	fd = open(bootfile,O_RDONLY,0);
	if(fd == -1) {
		return 0;
	}
	size = lseek(fd,0,SEEK_END);
	// error or less than 1 instruction
	if(size < 4) {
		return 0;
	}
	buf = umalloc(size);
	if(!buf) {
		close(fd);
		return 0;
	}
	lseek(fd,0,SEEK_SET);
	rcnt = read(fd, buf, size);
	close(fd);
	if(rcnt != size) {
		ufree(buf);
		return 0;
	}
	asm volatile(
		"MRC		p15, 0, %0, c9, c1, 0\n"
		: "=r" (data_tcm)
	); 
	data_tcm &= 0xFFFFF000;
	canon_copy_and_restart = (void *)(*(unsigned *)data_tcm);
	if( ((unsigned)canon_copy_and_restart & 0xFFFF0000) != 0xFFFF0000) {
		ufree(buf);
		return 0;
	}
	if(_ExecuteEventProcedure("DispDev_EnableEventProc") == -1) {
		ufree(buf);
		return 0;
	}
	if(_ExecuteEventProcedure("DispCon_TurnOffDisplay") == -1) {
		ufree(buf);
		return 0;
	}
	_Restart(7);
	canon_copy_and_restart((void *)0x1900,buf,size,(void *)0x1900);
}


