#include "platform.h"
#include "conf.h"
#include "stdlib.h"
#include "raw.h"

//-------------------------------------------------------------------
#define RAW_TARGET_DIRECTORY    "A/DCIM/%03dCANON"
//#define RAW_TMP_FILENAME        "HDK_RAW.TMP"
#define RAW_TARGET_FILENAME     "%s_%04d.%s"

//-------------------------------------------------------------------
static char fn[64];
static char dir[32];
static char prefixes[][4] = { "IMG", "CRW", "SND" };
static char exts[][4] = { "JPG", "CRW", "CR2", "THM", "WAV" };
static int develop_raw=0;
//-------------------------------------------------------------------
void raw_prepare_develop(char* filename){
 develop_raw=1; 
 strcpy(fn,filename);
}

//-------------------------------------------------------------------
int raw_savefile() {
    int fd;
    static struct utimbuf t;

    // got here second time in a row. Skip second RAW saving.
    if (conf.raw_save_first_only && state_shooting_progress == SHOOTING_PROGRESS_PROCESSING) {
        return 0;
    }
    
    if (develop_raw) {
     started();
     fd = open(fn, O_RDONLY, 0777);
     if (fd>=0) {
      read(fd, hook_raw_image_addr(), hook_raw_size());
      close(fd);
      }
     finished();
     develop_raw=0;
     return 0;
    }

    shooting_bracketing();
    
    state_shooting_progress = SHOOTING_PROGRESS_PROCESSING;

    if (conf.save_raw) {
        long v;
        
        started();

        t.actime = t.modtime = time(NULL);

        mkdir("A/DCIM");
        sprintf(dir, RAW_TARGET_DIRECTORY, (conf.raw_in_dir)?get_target_dir_num():100);
        mkdir(dir);

        sprintf(fn, "%s/", dir);
        sprintf(fn+strlen(fn), RAW_TARGET_FILENAME, prefixes[conf.raw_prefix], get_target_file_num(), exts[conf.raw_ext]);

        fd = open(fn, O_WRONLY|O_CREAT, 0777);
        if (fd>=0) {
            write(fd, hook_raw_image_addr(), hook_raw_size());
            close(fd);
            utime(fn, &t);
        }

        finished();

        return (fd >= 0);
    }

    return 0;
}

//-------------------------------------------------------------------
void raw_postprocess() {
/*
//    int fd;
    long v=get_file_counter();
    static struct utimbuf t;

    started();

//    sprintf(fn, RAW_TARGET_FILENAME, (v>>18)&0x3FF, (v>>4)&0x3FFF);
    sprintf(fn, RAW_TARGET_FILENAME, prefixes[conf.raw_prefix], (v>>4)&0x3FFF, exts[conf.raw_ext]);
    chdir(dir);
    rename(RAW_TMP_FILENAME, fn);

    t.actime = t.modtime = time(NULL);
    utime(fn, &t);

//        chdir("A/DCIM");
//    fd = open( "A/1", O_RDONLY, 0 );
//    eeee = fd;
//    xxxx = ((int (*)(int fd, int function, int arg))(0xFFEBBF9C))(fd, 47, (int)"A/DCIM/1"); //move
//    close(fd);
//    xxxx=rename("1", "DCIM/1");
//    eeee=*((int*)0xA021C); //errno

    finished();
 */
}
/*
//-------------------------------------------------------------------

void set_raw_pixel(unsigned int x, unsigned int y, unsigned short value){
 char* addr=hook_raw_image_addr()+y*ROWLEN+(x/8)*10;
 switch (x%8) {
  case 0: addr[0]=(addr[0]&0xC0)|(value<<6); addr[1]=value>>2;                  break;
  case 1: addr[0]=(addr[0]&0x3F)|(value>>4); addr[3]=(addr[3]&0xF0)|(value<<4); break;
  case 2: addr[2]=(addr[2]&0xFC)|(value<<2); addr[3]=(addr[3]&0x0F)|(value>>6); break;
  case 3: addr[2]=(addr[2]&0x03)|(value>>8); addr[5]=value;                     break;
  case 4: addr[4]=value>>2;                  addr[7]=(addr[7]&0xC0)|(value<<6); break;
  case 5: addr[6]=(addr[6]&0xF0)|(value<<4); addr[7]=(addr[7]&0x3F)|(value>>4); break;
  case 6: addr[6]=(addr[6]&0x0F)|(value>>6); addr[9]=(addr[9]&0xFC)|(value<<2); break;
  case 7: addr[8]=value;                     addr[9]=(addr[9]&0x03)|(value>>8); break;
 }
}

//-------------------------------------------------------------------
unsigned short get_raw_pixel(unsigned int x,unsigned  int y){
 char* addr=hook_raw_image_addr()+y*ROWLEN+(x/8)*10;
 switch (x%8) {
  case 0: return ((0x3fc&(((unsigned short)addr[1])<<2)) | (addr[0] >> 6));
  case 1: return ((0x3f0&(((unsigned short)addr[0])<<4)) | (addr[3] >> 4));
  case 2: return ((0x3c0&(((unsigned short)addr[3])<<6)) | (addr[2] >> 2));
  case 3: return ((0x300&(((unsigned short)addr[2])<<8)) | (addr[5])); 
  case 4: return ((0x3fc&(((unsigned short)addr[4])<<2)) | (addr[7] >> 6)); 
  case 5: return ((0x3f0&(((unsigned short)addr[7])<<4)) | (addr[6] >> 4)); 
  case 6: return ((0x3c0&(((unsigned short)addr[6])<<6)) | (addr[9] >> 2)); 
  case 7: return ((0x300&(((unsigned short)addr[9])<<8)) | (addr[8])); 
 }
 return 0;
}

//-------------------------------------------------------------------
void patch_bad_pixel(unsigned int x,unsigned  int y){
 set_raw_pixel(x,y,(get_raw_pixel(x-2,y)+get_raw_pixel(x+2,y)+get_raw_pixel(x,y-2)+get_raw_pixel(x,y+2))/4);
}
*/
