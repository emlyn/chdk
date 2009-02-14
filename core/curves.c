#include "platform.h"
#include "conf.h"
#include "stdlib.h"
#include "raw.h"
#include "curves.h"

/*
	Expands curves features
	
	RGB curves:  	ouput = curve[input]
	L cruves: 		output = curve[L] *(input-black) + black
	RGB curves and L curves are 4 colors curves
	L curves contain multiplicator factor (value = multiplicator * 10^12)
	
	DR curves:		output = curve[L] *(input-black) + black
	DR curves are gray scale only
	There are 2 DR curves +1EV and +2EV gain
	
	Auto DR automatically calculate the +1EV or +2EV base on 
	EV under exposure selected by user to avoid highlight burnout 
	(using Zebra)
	
	External function added:  shooting_get_ev_correction1 (added in generic/shooting)
	Modified gui.c for curve enable
	
*/
unsigned short *curve_data = NULL;

#define CURVE_SIZE 1024
#define CURVE_BYTES (CURVE_SIZE*sizeof(unsigned short))

#define BLACK 32
#define LUM(a,b) (((a)+(b)) >> 1)
#define LIM( a ) (((a)>1023) ? 1023: a )
#define RBLACK( a ) (((a)>BLACK) ? ((a)-BLACK) : 0)

#define CURVE0( a, b ) (((a) * curve0[b]) >> 12)
#define CURVE1( a, b ) (((a) * curve1[b]) >> 12)
#define CURVE2( a, b ) (((a) * curve2[b]) >> 12)
#define CURVE3( a, b ) (((a) * curve3[b]) >> 12)

typedef enum {
	CURVE_NONE,
	CURVE_CUSTOM,
	CURVE_SYSTEM,
}CURVE_TYPE;

CURVE_TYPE current_curve_type = CURVE_NONE;

static void curve_free_data() {
	free(curve_data);
	curve_data = NULL;
	current_curve_type = CURVE_NONE;
}

// TODO we should avoid re-loading the same file
static int curve_load_data(const char *name,CURVE_TYPE curve_type) {
	unsigned size;
	FILE *fd;
	if (current_curve_type != curve_type) {
		curve_free_data();
	}

	if (curve_type == CURVE_NONE) {
		return 1;
	}

	if(!name || !*name) {
		curve_free_data();
		return 0;
	}

 	if( curve_type == CURVE_CUSTOM ) {
 		size = CURVE_BYTES*4;
	}
	else {
 		size = CURVE_BYTES*2;
	}
	
	if (!curve_data)
		curve_data=malloc(size);

	if(!curve_data) {
		curve_free_data();
		return 0;
	}
	fd = fopen(name, "r+b");
	if (!fd) {
		curve_free_data();
		return 0;
	}
	fread(curve_data, 1, size, fd);
	fclose(fd);
	current_curve_type = curve_type;
	return 1;
}

void curve_set_mode(int value) {
	if((value>=0) && (value<=4)) conf.curve_enable=value;
	curve_init_mode();
}

void curve_init_mode() {
	switch(conf.curve_enable) {
		case 1: // custom - ensure alloc and load conf.curve_file
			curve_load_data(conf.curve_file,CURVE_CUSTOM);
		break;
		case 2: // system - ensure alloc and load syscurve
		case 3:
		case 4:
			curve_load_data("A/CHDK/SYSCURVES.CVF",CURVE_SYSTEM);
		break;
		default:
			conf.curve_enable = 0;
		case 0: // disabled - free
			curve_free_data();
	}
}

// TODO border pixels should not be hard coded
void curveRGB_apply() {
	int i,j;
	unsigned short pixVal0, pixVal1, pixVal2, col;
	unsigned char *src;

	unsigned short *curve0 = curve_data;
	unsigned short *curve1 = curve0 + CURVE_SIZE;
	unsigned short *curve2 = curve1 + CURVE_SIZE;
	unsigned short *curve3 = curve2 + CURVE_SIZE;
	
	if (current_curve_type != CURVE_CUSTOM) 
		return;
	
	// Set pointer to picture raw data in memory
	src = (unsigned char *) hook_raw_image_addr();	
	
	// Loop through picture rows
	col = CAM_RAW_ROWPIX-48;
	src += 8 * (CAM_RAW_ROWPIX * 10 / 8);	// skip 8 first rows
	for (i=CAM_RAW_ROWS - 8; i;i-=2){		// skip 8 first rows
//	for (i=CAM_RAW_ROWS; i;i-=2){ 	// No skip 8 first rows
		// Loop through picture columns 
//		for (j=CAM_RAW_ROWPIX; j; j-=8, src+=10){ 	// No skip 8 first and 40 last columns
		src += 10;										// Skip columns
		for (j=col; j; j-=8, src+=10){	// Skip columns
			//Skip first 8 columns and 40 last columns
			pixVal0=((0x3fc&(((unsigned short)(src[1]))<<2)) | (src[0] >> 6));
			pixVal1=((0x3f0&(((unsigned short)(src[0]))<<4)) | (src[3] >> 4));
				pixVal0 = curve0[pixVal0];
				pixVal1 = curve1[pixVal1];
            *(src+1) = (unsigned char) ((pixVal0>>2)); // 0
            *src = (unsigned char) ((pixVal0<<6)|(pixVal1>>4)); //0, 1

			pixVal2=((0x3c0&(((unsigned short)(src[3]))<<6)) | (src[2] >> 2));
			pixVal0=((0x300&(((unsigned short)(src[2]))<<8)) | (src[5])); 
				pixVal2 = curve0[pixVal2];
				pixVal0 = curve1[pixVal0];
            *(src+3) = (unsigned char) ((pixVal1<<4)|(pixVal2>>6)); //1,2
            *(src+2) = (unsigned char) ((pixVal2<<2)|(pixVal0>>8)); //2,3 =>(2,0)
            *(src+5) = (unsigned char) ((pixVal0)); //3 (=>0)

			pixVal0=((0x3fc&(((unsigned short)(src[4]))<<2)) | (src[7] >> 6)); 
			pixVal1=((0x3f0&(((unsigned short)(src[7]))<<4)) | (src[6] >> 4)); 
				pixVal0 = curve0[pixVal0];
				pixVal1 = curve1[pixVal1];
            *(src+4) = (unsigned char) ((pixVal0>>2)); // 4 => 0
            *(src+7) = (unsigned char) ((pixVal0<<6)|(pixVal1>>4)); // 4,5 => (0,1)

			pixVal2=((0x3c0&(((unsigned short)(src[6]))<<6)) | (src[9] >> 2)); 
			pixVal0=((0x300&(((unsigned short)(src[9]))<<8)) | (src[8]));
				pixVal2 = curve0[pixVal2];
				pixVal0 = curve1[pixVal0];
            *(src+6) = (unsigned char) ((pixVal1<<4)|(pixVal2>>6)); // 5,6 => (1,2)
            *(src+9) = (unsigned char) ((pixVal2<<2)|(pixVal0>>8)); // 6,7 =>(2,0)
            *(src+8) = (unsigned char) ((pixVal0)); //7 (=>0)		}
		}
		src += 60;	// skip columns 40+8	
//		for (j=CAM_RAW_ROWPIX;j; j-=8, src+=10){ 	// No skip
		for (j=col; j; j-=8, src+=10){
			pixVal0=((0x3fc&(((unsigned short)(src[1]))<<2)) | (src[0] >> 6));
			pixVal1=((0x3f0&(((unsigned short)(src[0]))<<4)) | (src[3] >> 4));
				pixVal0 = curve2[pixVal0];
				pixVal1 = curve3[pixVal1];
            *(src+1) = (unsigned char) ((pixVal0>>2)); // 0
            *src = (unsigned char) ((pixVal0<<6)|(pixVal1>>4)); //0, 1

			pixVal2=((0x3c0&(((unsigned short)(src[3]))<<6)) | (src[2] >> 2));
			pixVal0=((0x300&(((unsigned short)(src[2]))<<8)) | (src[5])); 
				pixVal2 = curve2[pixVal2];
				pixVal0 = curve3[pixVal0];
            *(src+3) = (unsigned char) ((pixVal1<<4)|(pixVal2>>6)); //1,2
            *(src+2) = (unsigned char) ((pixVal2<<2)|(pixVal0>>8)); //2,3 =>(2,0)
            *(src+5) = (unsigned char) ((pixVal0)); //3 (=>0)

			pixVal0=((0x3fc&(((unsigned short)(src[4]))<<2)) | (src[7] >> 6)); 
			pixVal1=((0x3f0&(((unsigned short)(src[7]))<<4)) | (src[6] >> 4)); 
				pixVal0 = curve2[pixVal0];
				pixVal1 = curve3[pixVal1];
            *(src+4) = (unsigned char) ((pixVal0>>2)); // 4 => 0
            *(src+7) = (unsigned char) ((pixVal0<<6)|(pixVal1>>4)); // 4,5 => (0,1)

			pixVal2=((0x3c0&(((unsigned short)(src[6]))<<6)) | (src[9] >> 2)); 
			pixVal0=((0x300&(((unsigned short)(src[9]))<<8)) | (src[8]));
				pixVal2 = curve2[pixVal2];
				pixVal0 = curve3[pixVal0];
            *(src+6) = (unsigned char) ((pixVal1<<4)|(pixVal2>>6)); // 5,6 => (1,2)
            *(src+9) = (unsigned char) ((pixVal2<<2)|(pixVal0>>8)); // 6,7 =>(2,0)
            *(src+8) = (unsigned char) ((pixVal0)); //7 (=>0)
		}
		src += 50; // skip columns
	}
}


void curveL_apply(unsigned sys_index) {
	int i,j;
	unsigned short pixVal0, pixVal1, pixVal2, y, col;
	unsigned char *src;
	
	unsigned short *curve0;
	unsigned short *curve1;
	unsigned short *curve2;
	unsigned short *curve3;
	if (current_curve_type == CURVE_SYSTEM) {
		if (sys_index > 1) 
			return;
		curve0 = curve1 = curve2 = curve3 = curve_data + sys_index*CURVE_SIZE;
	}
	else if(current_curve_type == CURVE_CUSTOM) {
		curve0 = curve_data;
		curve1 = curve0 + CURVE_SIZE;
		curve2 = curve1 + CURVE_SIZE;
		curve3 = curve2 + CURVE_SIZE;
	} else {
		return;
	}


	// Set pointer to picture raw data in memory
	src = (unsigned char *) hook_raw_image_addr();	
	
	// Loop through picture rows
	col = CAM_RAW_ROWPIX-48;
	src += 8 * (CAM_RAW_ROWPIX * 10 / 8);	// skip 8 first rows
	for (i=CAM_RAW_ROWS - 8; i;i-=2){		// skip 8 first rows
//	for (i=CAM_RAW_ROWS; i;i-=2){ 	// No skip 8 first rows
		// Loop through picture columns 
//		for (j=CAM_RAW_ROWPIX; j; j-=8, src+=10){ 	// No skip 8 first and 40 last columns
		src += 10;										// Skip columns
		for (j=col; j; j-=8, src+=10){	// Skip columns
			//Skip first 8 columns and 40 last columns
			pixVal0=((0x3fc&(((unsigned short)(src[1]))<<2)) | (src[0] >> 6));
			pixVal1=((0x3f0&(((unsigned short)(src[0]))<<4)) | (src[3] >> 4));
				pixVal0 = RBLACK( pixVal0 );
				pixVal1 = RBLACK( pixVal1 );
				y = LUM(pixVal0,pixVal1);
				pixVal0 = CURVE0( pixVal0, y ) + BLACK;
				pixVal1 = CURVE1( pixVal1, y ) + BLACK;
				pixVal0 = LIM( pixVal0 );
				pixVal1 = LIM( pixVal1 );
            *(src+1) = (unsigned char) ((pixVal0>>2)); // 0
            *src = (unsigned char) ((pixVal0<<6)|(pixVal1>>4)); //0, 1

			pixVal2=((0x3c0&(((unsigned short)(src[3]))<<6)) | (src[2] >> 2));
			pixVal0=((0x300&(((unsigned short)(src[2]))<<8)) | (src[5])); 
				pixVal2 = RBLACK( pixVal2 );
				pixVal0 = RBLACK( pixVal0 );
				y = LUM(pixVal2,pixVal0);
				pixVal2 = CURVE0( pixVal2, y ) + BLACK;
				pixVal0 = CURVE1( pixVal0, y ) + BLACK;
				pixVal2 = LIM( pixVal2 );
				pixVal0 = LIM( pixVal0 );
            *(src+3) = (unsigned char) ((pixVal1<<4)|(pixVal2>>6)); //1,2
            *(src+2) = (unsigned char) ((pixVal2<<2)|(pixVal0>>8)); //2,3 =>(2,0)
            *(src+5) = (unsigned char) ((pixVal0)); //3 (=>0)

			pixVal0=((0x3fc&(((unsigned short)(src[4]))<<2)) | (src[7] >> 6)); 
			pixVal1=((0x3f0&(((unsigned short)(src[7]))<<4)) | (src[6] >> 4)); 
				pixVal0 = RBLACK( pixVal0 );
				pixVal1 = RBLACK( pixVal1 );
				y = LUM(pixVal0,pixVal1);
				pixVal0 = CURVE0( pixVal0, y ) + BLACK;
				pixVal1 = CURVE1( pixVal1, y ) + BLACK;
				pixVal0 = LIM( pixVal0 );
				pixVal1 = LIM( pixVal1 );
            *(src+4) = (unsigned char) ((pixVal0>>2)); // 4 => 0
            *(src+7) = (unsigned char) ((pixVal0<<6)|(pixVal1>>4)); // 4,5 => (0,1)

			pixVal2=((0x3c0&(((unsigned short)(src[6]))<<6)) | (src[9] >> 2)); 
			pixVal0=((0x300&(((unsigned short)(src[9]))<<8)) | (src[8]));
				pixVal2 = RBLACK( pixVal2 );
				pixVal0 = RBLACK( pixVal0 );
				y = LUM(pixVal2,pixVal0);
				pixVal2 = CURVE0( pixVal2, y ) + BLACK;
				pixVal0 = CURVE1( pixVal0, y ) + BLACK;
				pixVal2 = LIM( pixVal2 );
				pixVal0 = LIM( pixVal0 );
            *(src+6) = (unsigned char) ((pixVal1<<4)|(pixVal2>>6)); // 5,6 => (1,2)
            *(src+9) = (unsigned char) ((pixVal2<<2)|(pixVal0>>8)); // 6,7 =>(2,0)
            *(src+8) = (unsigned char) ((pixVal0)); //7 (=>0)		}
		}
		src += 60;	// skip columns 40+8	
//		for (j=CAM_RAW_ROWPIX;j; j-=8, src+=10){ 	// No skip
		for (j=col; j; j-=8, src+=10){
			pixVal0=((0x3fc&(((unsigned short)(src[1]))<<2)) | (src[0] >> 6));
			pixVal1=((0x3f0&(((unsigned short)(src[0]))<<4)) | (src[3] >> 4));
				pixVal0 = RBLACK( pixVal0 );
				pixVal1 = RBLACK( pixVal1 );
				y = LUM(pixVal0,pixVal1);
				pixVal0 = CURVE2( pixVal0, y ) + BLACK;
				pixVal1 = CURVE3( pixVal1, y ) + BLACK;
				pixVal0 = LIM( pixVal0 );
				pixVal1 = LIM( pixVal1 );
            *(src+1) = (unsigned char) ((pixVal0>>2)); // 0
            *src = (unsigned char) ((pixVal0<<6)|(pixVal1>>4)); //0, 1

			pixVal2=((0x3c0&(((unsigned short)(src[3]))<<6)) | (src[2] >> 2));
			pixVal0=((0x300&(((unsigned short)(src[2]))<<8)) | (src[5])); 
				pixVal2 = RBLACK( pixVal2 );
				pixVal0 = RBLACK( pixVal0 );
				y = LUM(pixVal2,pixVal0);
				pixVal2 = CURVE2( pixVal2, y ) + BLACK;
				pixVal0 = CURVE3( pixVal0, y ) + BLACK;
				pixVal2 = LIM( pixVal2 );
				pixVal0 = LIM( pixVal0 );
            *(src+3) = (unsigned char) ((pixVal1<<4)|(pixVal2>>6)); //1,2
            *(src+2) = (unsigned char) ((pixVal2<<2)|(pixVal0>>8)); //2,3 =>(2,0)
            *(src+5) = (unsigned char) ((pixVal0)); //3 (=>0)

			pixVal0=((0x3fc&(((unsigned short)(src[4]))<<2)) | (src[7] >> 6)); 
			pixVal1=((0x3f0&(((unsigned short)(src[7]))<<4)) | (src[6] >> 4)); 
				pixVal0 = RBLACK( pixVal0 );
				pixVal1 = RBLACK( pixVal1 );
				y = LUM(pixVal0,pixVal1);
				pixVal0 = CURVE2( pixVal0, y ) + BLACK;
				pixVal1 = CURVE3( pixVal1, y ) + BLACK;
				pixVal0 = LIM( pixVal0 );
				pixVal1 = LIM( pixVal1 );
            *(src+4) = (unsigned char) ((pixVal0>>2)); // 4 => 0
            *(src+7) = (unsigned char) ((pixVal0<<6)|(pixVal1>>4)); // 4,5 => (0,1)

			pixVal2=((0x3c0&(((unsigned short)(src[6]))<<6)) | (src[9] >> 2)); 
			pixVal0=((0x300&(((unsigned short)(src[9]))<<8)) | (src[8]));
				pixVal2 = RBLACK( pixVal2 );
				pixVal0 = RBLACK( pixVal0 );
				y = LUM(pixVal2,pixVal0);
				pixVal2 = CURVE2( pixVal2, y ) + BLACK;
				pixVal0 = CURVE3( pixVal0, y ) + BLACK;
				pixVal2 = LIM( pixVal2 );
				pixVal0 = LIM( pixVal0 );
            *(src+6) = (unsigned char) ((pixVal1<<4)|(pixVal2>>6)); // 5,6 => (1,2)
            *(src+9) = (unsigned char) ((pixVal2<<2)|(pixVal0>>8)); // 6,7 =>(2,0)
            *(src+8) = (unsigned char) ((pixVal0)); //7 (=>0)
		}
		src += 50; // skip columns
	}
}

void curve_apply() {
	short EVbias = shooting_get_ev_correction1();

	switch(conf.curve_enable) {
		case 0:
			break;
		case 1:		// Custom
			if (current_curve_type == CURVE_CUSTOM){
				if(curve_data[0] > 1023){ // L curve contains multiplicator factors (0 Luminance has factor 1)
					curveL_apply(0);
				} else {
					curveRGB_apply();
				}
			};
			break;
		case 2:
		case 3: // +1EV,  +2EV
			if (current_curve_type == CURVE_SYSTEM) curveL_apply( conf.curve_enable & 1 );
			break;
		case 4:		// Auto DR

			if (current_curve_type == CURVE_SYSTEM) {
				 if (EVbias <-128)  {  // x4 for Bias from "-1 2/3" and below 
					curveL_apply(1);
				} else if(EVbias<-32){ // x2 for Bias from "-1 1/3" to "-2/3"
					curveL_apply(0);
				}
			}
			break;
	}
	
}

