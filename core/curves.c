#include "platform.h"
#include "conf.h"
#include "stdlib.h"
#include "raw.h"
#include "curves.h"


unsigned short curve0[CURVE_SIZE];
unsigned short curve1[CURVE_SIZE];
unsigned short curve2[CURVE_SIZE];
unsigned short curve3[CURVE_SIZE];

unsigned char curve_loaded;


//-------------------------------------------------------------------
// Curve to be loaded upon power up if active
void curve_load(const char *fn) {
	int fd;
	
    if (!fn[0]) { // no curev defined
		curve_loaded = 0;
		return;
    } else {
        fd = fopen(fn, "r+b");
        if (!fd) {
            conf.curve_file[0]=0;
			curve_loaded = 0;
			return;
       }
    }
	
	fread(curve0, 1, CURVE_SIZE*sizeof(unsigned short), fd);
	fread(curve1, 1, CURVE_SIZE*sizeof(unsigned short), fd);
	fread(curve2, 1, CURVE_SIZE*sizeof(unsigned short), fd);
	fread(curve3, 1, CURVE_SIZE*sizeof(unsigned short), fd);

	strcpy(conf.curve_file, fn);
	fclose(fd);
	curve_loaded = 1;
}

void curve_apply() {
	short i,j;
	unsigned short pixVal0, pixVal1, pixVal2;
	unsigned char *src;
	
	if (!curve_loaded) return;
	//if (!conf.curve_enable) return;

	// Set pointer to picture raw data in memory
	src = (unsigned char *) hook_raw_image_addr();	
	
	// Loop through picture rows
	for (i=CAM_RAW_ROWS; i;i-=2){
		// Loop through picture columns 
		for (j=CAM_RAW_ROWPIX; j; j-=8, src+=10){
			pixVal0=curve0[((0x3fc&(((unsigned short)(*(src+1)))<<2)) | (*(src+0) >> 6))];
            *(src+1) = (unsigned char) ((pixVal0>>2)); // 0
			pixVal1=curve1[((0x3f0&(((unsigned short)(*(src+0)))<<4)) | (*(src+3) >> 4))];
            *(src+0) = (unsigned char) ((pixVal0<<6)|(pixVal1>>4)); //0, 1
			pixVal2=curve0[((0x3c0&(((unsigned short)(*(src+3)))<<6)) | (*(src+2) >> 2))];
            *(src+3) = (unsigned char) ((pixVal1<<4)|(pixVal2>>6)); //1,2
			pixVal0=curve1[((0x300&(((unsigned short)(*(src+2)))<<8)) | (*(src+5)))]; 
            *(src+2) = (unsigned char) ((pixVal2<<2)|(pixVal0>>8)); //2,3 =>(2,0)
            *(src+5) = (unsigned char) ((pixVal0)); //3 (=>0)

			pixVal0=curve0[((0x3fc&(((unsigned short)(*(src+4)))<<2)) | (*(src+7) >> 6))]; 
            *(src+4) = (unsigned char) ((pixVal0>>2)); // 4 => 0
			pixVal1=curve1[((0x3f0&(((unsigned short)(*(src+7)))<<4)) | (*(src+6) >> 4))]; 
            *(src+7) = (unsigned char) ((pixVal0<<6)|(pixVal1>>4)); // 4,5 => (0,1)
			pixVal2=curve0[((0x3c0&(((unsigned short)(*(src+6)))<<6)) | (*(src+9) >> 2))]; 
            *(src+6) = (unsigned char) ((pixVal1<<4)|(pixVal2>>6)); // 5,6 => (1,2)
			pixVal0=curve1[((0x300&(((unsigned short)(*(src+9)))<<8)) | (*(src+8)))];
            *(src+9) = (unsigned char) ((pixVal2<<2)|(pixVal0>>8)); // 6,7 =>(2,0)
            *(src+8) = (unsigned char) ((pixVal0)); //7 (=>0)
		}
		
		for (j=CAM_RAW_ROWPIX; j; j-=8, src+=10){
			pixVal0=curve2[((0x3fc&(((unsigned short)(*(src+1)))<<2)) | (*(src+0) >> 6))];
            *(src+1) = (unsigned char) ((pixVal0>>2)); // 0
			pixVal1=curve3[((0x3f0&(((unsigned short)(*(src+0)))<<4)) | (*(src+3) >> 4))];
            *(src+0) = (unsigned char) ((pixVal0<<6)|(pixVal1>>4)); //0, 1
			pixVal2=curve2[((0x3c0&(((unsigned short)(*(src+3)))<<6)) | (*(src+2) >> 2))];
            *(src+3) = (unsigned char) ((pixVal1<<4)|(pixVal2>>6)); //1,2
			pixVal0=curve3[((0x300&(((unsigned short)(*(src+2)))<<8)) | (*(src+5)))]; 
            *(src+2) = (unsigned char) ((pixVal2<<2)|(pixVal0>>8)); //2,3 =>(2,0)
            *(src+5) = (unsigned char) ((pixVal0)); //3 (=>0)

			pixVal0=curve2[((0x3fc&(((unsigned short)(*(src+4)))<<2)) | (*(src+7) >> 6))]; 
            *(src+4) = (unsigned char) ((pixVal0>>2)); // 4 => 0
			pixVal1=curve3[((0x3f0&(((unsigned short)(*(src+7)))<<4)) | (*(src+6) >> 4))]; 
            *(src+7) = (unsigned char) ((pixVal0<<6)|(pixVal1>>4)); // 4,5 => (0,1)
			pixVal2=curve2[((0x3c0&(((unsigned short)(*(src+6)))<<6)) | (*(src+9) >> 2))]; 
            *(src+6) = (unsigned char) ((pixVal1<<4)|(pixVal2>>6)); // 5,6 => (1,2)
			pixVal0=curve3[((0x300&(((unsigned short)(*(src+9)))<<8)) | (*(src+8)))];
            *(src+9) = (unsigned char) ((pixVal2<<2)|(pixVal0>>8)); // 6,7 =>(2,0)
            *(src+8) = (unsigned char) ((pixVal0)); //7 (=>0)
		}
	}
}
