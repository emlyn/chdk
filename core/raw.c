#include "platform.h"
#include "conf.h"
#include "stdlib.h"
#include "raw.h"
#if CURVES
	#include "curves.h"
#endif
#include "shot_histogram.h"

//-------------------------------------------------------------------
#define RAW_TARGET_DIRECTORY    "A/DCIM/%03dCANON"
//#define RAW_TMP_FILENAME        "HDK_RAW.TMP"
#define RAW_TARGET_FILENAME     "%s%04d%s"

//-------------------------------------------------------------------
static char fn[64];
static char dir[32];
static int develop_raw=0;
//-------------------------------------------------------------------
void raw_prepare_develop(char* filename){
 develop_raw=1; 
 strcpy(fn,filename);
}

//-------------------------------------------------------------------
void patch_bad_pixels(void);
//-------------------------------------------------------------------
int raw_savefile() {
		int fd, m=(mode_get()&MODE_SHOOTING_MASK);
    static struct utimbuf t;

    if (state_kbd_script_run && shot_histogram_enabled) build_shot_histogram();

    if (develop_raw) {
     started();
     fd = open(fn, O_RDONLY, 0777);
     if (fd>=0) {
      read(fd, hook_raw_image_addr(), hook_raw_size());
      close(fd);
      }
#if CURVES
     if (conf.curve_enable) curve_apply();
#endif
     finished();
     develop_raw=0;
     return 0;
    }

    if (conf.bad_pixel_removal) patch_bad_pixels();

    shooting_bracketing();

    // got here second time in a row. Skip second RAW saving.
    if (conf.raw_save_first_only && state_shooting_progress == SHOOTING_PROGRESS_PROCESSING) {
        return 0;
    }
    
    state_shooting_progress = SHOOTING_PROGRESS_PROCESSING;

     if (conf.save_raw && (!((movie_status > 1) && conf.save_raw_in_video   )) && (!((m==MODE_SPORTS) && conf.save_raw_in_sports)) && (!((shooting_get_prop(PROPCASE_DRIVE_MODE)==1) && conf.save_raw_in_burst && !(m==MODE_SPORTS))) && (!((shooting_get_prop(PROPCASE_DRIVE_MODE)>=2) && conf.save_raw_in_timer)) && (!((shooting_get_prop(PROPCASE_BRACKET_MODE)==1) && conf.save_raw_in_ev_bracketing)) ) {
        long v;
        
        started();

        t.actime = t.modtime = time(NULL);

        mkdir("A/DCIM");
        sprintf(dir, RAW_TARGET_DIRECTORY, (conf.raw_in_dir)?get_target_dir_num():100);
        mkdir(dir);

        sprintf(fn, "%s/", dir);
        sprintf(fn+strlen(fn), RAW_TARGET_FILENAME, img_prefixes[conf.raw_prefix], get_target_file_num(), img_exts[conf.raw_ext]);

        fd = open(fn, O_WRONLY|O_CREAT, 0777);
        if (fd>=0) {
            write(fd, hook_raw_image_addr(), hook_raw_size());
            close(fd);
            utime(fn, &t);
        }

        finished();

        return (fd >= 0);
    }

#if CURVES
    if (conf.curve_enable) curve_apply();
#endif
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

//-------------------------------------------------------------------

void set_raw_pixel(unsigned int x, unsigned int y, unsigned short value){
 unsigned char* addr=hook_raw_image_addr()+y*RAW_ROWLEN+(x/8)*10;
 switch (x%8) {
  case 0: addr[0]=(addr[0]&0x3F)|(value<<6); addr[1]=value>>2;                  break;
  case 1: addr[0]=(addr[0]&0xC0)|(value>>4); addr[3]=(addr[3]&0x0F)|(value<<4); break;
  case 2: addr[2]=(addr[2]&0x03)|(value<<2); addr[3]=(addr[3]&0xF0)|(value>>6); break;
  case 3: addr[2]=(addr[2]&0xFC)|(value>>8); addr[5]=value;                     break;
  case 4: addr[4]=value>>2;                  addr[7]=(addr[7]&0x3F)|(value<<6); break;
  case 5: addr[6]=(addr[6]&0x0F)|(value<<4); addr[7]=(addr[7]&0xC0)|(value>>4); break;
  case 6: addr[6]=(addr[6]&0xF0)|(value>>6); addr[9]=(addr[9]&0x03)|(value<<2); break;
  case 7: addr[8]=value;                     addr[9]=(addr[9]&0xFC)|(value>>8); break;
 }
}

//-------------------------------------------------------------------
unsigned short get_raw_pixel(unsigned int x,unsigned  int y){
 unsigned char* addr=hook_raw_image_addr()+y*RAW_ROWLEN+(x/8)*10;
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
 if ((x>=2) && (x<CAM_RAW_ROWPIX-2) && (y>=2) && (y<CAM_RAW_ROWS-2)) { 
  if (conf.bad_pixel_removal==1)   // interpolation 
   set_raw_pixel(x,y,(get_raw_pixel(x-2,y)+get_raw_pixel(x+2,y)+get_raw_pixel(x,y-2)+get_raw_pixel(x,y+2))/4); 
  else if (conf.bad_pixel_removal==2)  // or this makes RAW converter (internal/external) 
   set_raw_pixel(x,y,0);   
 }
}

struct point{
 int x;
 int y;
 struct point *next;
} *pixel_list=NULL;

void patch_bad_pixels(void){
 struct point *pixel=pixel_list;
 while (pixel){
  patch_bad_pixel((*pixel).x,(*pixel).y);
  pixel=(*pixel).next;
 }
}

void make_pixel_list(char * ptr){
 int x,y;
 struct point *pixel;
 char *endptr;
 while(*ptr){
  while (*ptr==' ' || *ptr=='\t') ++ptr; // whitespaces
   x=strtol(ptr, &endptr, 0);
   if (endptr != ptr) { 
    ptr = endptr;
    if (*ptr++==',') {
     while (*ptr==' ' || *ptr=='\t') ++ptr; // whitespaces
     if (*ptr!='\n' && *ptr!='\r'){
      y=strtol(ptr, &endptr, 0);
      if (endptr != ptr) { 
       ptr = endptr;
       pixel=malloc(sizeof(struct point));
       if (pixel) {
        (*pixel).x=x;
        (*pixel).y=y;
        (*pixel).next=pixel_list;
        pixel_list=pixel;
       }
      }
     }
    }
   }
   while (*ptr && *ptr!='\n') ++ptr; // unless end of line
   if (*ptr) ++ptr;
 }
}

#define PIXELS_BUF_SIZE 4096
void load_bad_pixels_list(char* filename){
    char *buf;
    int fd;

    if (filename) {
        buf = umalloc(PIXELS_BUF_SIZE);
        if (!buf) return;

        fd = open(filename, O_RDONLY, 0777);
        if (fd>=0) {
            int rcnt = read(fd, buf, PIXELS_BUF_SIZE);
            if (rcnt > 0) {
                if (rcnt == PIXELS_BUF_SIZE) 
        	    buf[PIXELS_BUF_SIZE-1] = 0;
                else
        	    buf[rcnt] = 0;
            }
            close(fd);
        }
        make_pixel_list(buf);    
        ufree(buf);
    }

}
