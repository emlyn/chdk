#include "raw_merge.h"
#include "stdlib.h"
#include "platform.h"
#include "gui_mpopup.h"
#include "gui_mbox.h"
#include "raw.h"
#include "gui_lang.h"
#include "lang.h"

#define TEMP_FILE        "raw16.tmp"
#define TEMP_FILE_NAME   "A/raw16.tmp"
#define TEMP_FILE_NAME_1 "A/raw16_1.tmp"

static int raw_action;
static int raw_count;
static unsigned short *row;
static unsigned char *rawrow;
static char namebuf[100];


int raw_merge_start(int action){
 unsigned int req, avail;
 req=((CAM_RAW_ROWPIX*CAM_RAW_ROWS)>>18)+1;
 avail=GetFreeCardSpaceKb()>>10;
 if (avail<req) {
  sprintf(namebuf,lang_str(LANG_AVERAGE_NO_CARD_SPACE),req,avail);
  gui_mbox_init((int)"", (int)namebuf, MBOX_BTN_OK|MBOX_TEXT_CENTER, NULL);
  return 0;
 }
 raw_action=action;
 raw_count=0;
 row=malloc(CAM_RAW_ROWPIX*sizeof(unsigned short));
 if (!row) return 0;
 rawrow=malloc(RAW_ROWLEN);
 if (!rawrow) { free(row); return 0;}
 return 1;
}

void raw_merge_add_file(char * filename){
    int  fbrawin,fbrawout,t,fcraw,src,i,j,nrow;
    struct stat st;

    if (!filename) return;
    stat(filename,&st);
    if (st.st_size!=hook_raw_size()) return;

    started();
    fbrawin=0;

    fcraw=fopen(filename,"rb");
    if (fcraw) {
     if (raw_count) fbrawin=fopen(TEMP_FILE_NAME,"rb");
     if (!raw_count || fbrawin){
       fbrawout=fopen(TEMP_FILE_NAME_1,"w+b");
        if (fbrawout){
         fread(rawrow, 1, RAW_ROWLEN, fcraw);
         if (raw_count) fread(row, 1, CAM_RAW_ROWPIX*sizeof(unsigned short), fbrawin); else for (i=0;i<CAM_RAW_ROWPIX;i++) row[i]=0;

         for (nrow=0,j=0;nrow<CAM_RAW_ROWS;nrow++,j++){
         
         for (i=0,src=0; i<CAM_RAW_ROWPIX; i+=8, src+=10){

           row[i+0]+=((0x3fc&(((unsigned short)rawrow[src+1])<<2)) | (rawrow[src+0] >> 6));
           row[i+1]+=((0x3f0&(((unsigned short)rawrow[src+0])<<4)) | (rawrow[src+3] >> 4));
           row[i+2]+=((0x3c0&(((unsigned short)rawrow[src+3])<<6)) | (rawrow[src+2] >> 2));
           row[i+3]+=((0x300&(((unsigned short)rawrow[src+2])<<8)) | (rawrow[src+5])); 
           row[i+4]+=((0x3fc&(((unsigned short)rawrow[src+4])<<2)) | (rawrow[src+7] >> 6)); 
           row[i+5]+=((0x3f0&(((unsigned short)rawrow[src+7])<<4)) | (rawrow[src+6] >> 4)); 
           row[i+6]+=((0x3c0&(((unsigned short)rawrow[src+6])<<6)) | (rawrow[src+9] >> 2)); 
           row[i+7]+=((0x300&(((unsigned short)rawrow[src+9])<<8)) | (rawrow[src+8])); 
          
         }
	 fwrite(row, 1, CAM_RAW_ROWPIX*sizeof(unsigned short), fbrawout);
         if (raw_count) fread(row, 1, CAM_RAW_ROWPIX*sizeof(unsigned short), fbrawin); else for (i=0;i<CAM_RAW_ROWPIX;i++) row[i]=0;
	 fread(rawrow, 1, RAW_ROWLEN, fcraw);
	 if (j>=CAM_RAW_ROWS/10) {j-=CAM_RAW_ROWS/10; gui_browser_progress_show(filename, nrow*100/CAM_RAW_ROWS);}
       }
     raw_count++;
     strcpy(namebuf,filename);
     fclose(fbrawout);
     }
    if (fbrawin) fclose(fbrawin);
    }
   fclose(fcraw);
  } 
  remove(TEMP_FILE_NAME);
  rename(TEMP_FILE_NAME_1,TEMP_FILE);
  finished();
}

void raw_merge_end(void){
    int  fbraw,fcraw,src,i,j,nrow;
    static struct utimbuf t;
    #define BLACK_LEVEL 32 
    if (!raw_count) return;
    i=strlen(namebuf)-3;
    if (strncmp(namebuf+i,"CR",2)==0) strcpy(namebuf+i,"WAV"); else strcpy(namebuf+i,"CRW");
    started();
    fbraw=fopen(TEMP_FILE_NAME,"r+b");
    if (fbraw) {
     fcraw=fopen(namebuf,"w+b");
     if (fcraw) {
        fread(row, 1, CAM_RAW_ROWPIX*sizeof(unsigned short), fbraw);
        for (nrow=0,j=0;nrow<CAM_RAW_ROWS;nrow++,j++){
         for (i=0;i<CAM_RAW_ROWPIX;i++){
          if (raw_action==RAW_OPERATIOM_AVERAGE) row[i]/=raw_count; else {
           if (row[i]>BLACK_LEVEL*(raw_count-1)) row[i]-=BLACK_LEVEL*(raw_count-1); else row[i]=0;
           if (row[i]>0x3FF) row[i]=0x3FF;
         }
        }
         
         for (i=0,src=0;i<CAM_RAW_ROWPIX;i+=8,src+=10) {
            rawrow[src+0]=(row[i+0]<<6)|(row[i+1]>>4);
            rawrow[src+1]=(row[i+0]>>2);
            rawrow[src+2]=(row[i+2]<<2)|(row[i+3]>>8);
            rawrow[src+3]=(row[i+1]<<4)|(row[i+2]>>6);
            rawrow[src+4]=(row[i+4]>>2);
            rawrow[src+5]=(row[i+3]);
            rawrow[src+6]=(row[i+5]<<4)|(row[i+6]>>6);
            rawrow[src+7]=(row[i+4]<<6)|(row[i+5]>>4);
            rawrow[src+8]=(row[i+7]);
            rawrow[src+9]=(row[i+6]<<2)|(row[i+7]>>8);
         }
         fwrite(rawrow, 1, RAW_ROWLEN, fcraw);
         fread(row, 1, CAM_RAW_ROWPIX*sizeof(unsigned short), fbraw);
         if (j>=CAM_RAW_ROWS/5) {j-=CAM_RAW_ROWS/5; gui_browser_progress_show(namebuf, nrow*100/CAM_RAW_ROWS);}
        }
    fclose(fcraw);
    }
    fclose(fbraw);
    }

 t.actime = t.modtime = time(NULL);
 utime(namebuf, &t);
 remove(TEMP_FILE_NAME);

 finished();
 free(rawrow);
 free(row);
}

