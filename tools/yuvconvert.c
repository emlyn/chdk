/*
A small tools to convert/debug CHDK live view dumps.

REVISIONS:
1. Initial release. Author: reyalP (04-Jul-2010)

code borrowed from motion_detector.c, rawconvert.c and ewavrs ptpcam
*/
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <assert.h>


void usage()
{
	fprintf(stderr,"Usage: -w=<width> -h=<height> [-split] [-rgb] [-skipy] <infile> <outbasename>\n");
	fprintf(stderr,"infile: dump of live viewport data, assumed UYVYYY with 8 bit elements.\n"
					"outbasename: base name to use for various output files\n"
					"-w=,-h=\n"
					"  real width and height of input. Width is by counting Y values.\n"
					"-rgb:\n"
					"  Output packed 24 bit RGB outbasename-<output width>.RGB\n"
					"-skipy:\n"
					"  skip 50%% of Y values in each row when making RGB\n"
					"  to give correct aspect ratio on older cameras\n"
					"-split:\n"
					"  produces outbasename.Y outbasename.U and outbasename.V as 8 bit greyscale\n"
					"  .Y will be full resolution, .U and .V will be 1/4 width of Y\n");
	exit(1);
}

static uint8_t clip(int v) {
	if (v<0) return 0;
	if (v>255) return 255;
	return v;
}

void yuv_to_rgb(uint8_t **dest, uint8_t y, int8_t u, int8_t v)
{
	*((*dest)++) = clip(((y<<12) +          v*5743 + 2048)>>12);
	*((*dest)++) = clip(((y<<12) - u*1411 - v*2925 + 2048)>>12);
	*((*dest)++) = clip(((y<<12) + u*7258          + 2048)>>12);
}

int main(int argc, char**argv)
{
	int8_t *in_data;
	uint8_t *out_data;
	uint8_t *prgb_data;
	int8_t *y_data,*py_data;
	int8_t *u_data,*pu_data;
	int8_t *v_data,*pv_data;
	FILE *fp;
	char *iname=NULL;
	char *oname=NULL;

	unsigned height=0;
	unsigned width=0;
	unsigned npixels;
	unsigned isize;
	unsigned osize;

	unsigned split_yuv=0;
	unsigned skipy=0;
	unsigned rgb=0;

	struct stat st;

	size_t rcount;

	unsigned i;

	for(i = 1; i < argc; i++) {
		if ( strncmp(argv[i],"-h=",3) == 0 ) {
			height=atoi(argv[i]+3);
		}
		else if ( strncmp(argv[i],"-w=",3) == 0 ) {
			width=atoi(argv[i]+3);
		}
		else if( strcmp(argv[i],"-split") == 0 ) {
			split_yuv=1;
		}
		else if( strcmp(argv[i],"-skipy") == 0 ) {
			skipy=1;
		}
		else if( strcmp(argv[i],"-rgb") == 0 ) {
			rgb=1;
		}
		else {
			if(!iname) {
				iname=argv[i];
			}
			else if (!oname) {
				oname=argv[i];
			}
			else {
				fprintf(stderr,"%s: unknown option %s\n",argv[0],argv[i]);
				usage();
			}
		}
	}
	if(!iname) {
		fprintf(stderr,"%s: missing input file\n",argv[0]);
		usage();
	}
	if(!oname) {
		fprintf(stderr,"%s: missing output file\n",argv[0]);
		usage();
	}
	if(!height || !width) {
		fprintf(stderr,"%s: invalid dimensions\n",argv[0]);
		usage();
	}

	if(stat(iname,&st) != 0) {
		fprintf(stderr,"%s: bad input file %s\n",argv[0],iname);
		exit(1);
	}

	if((width*12)%8 != 0) {
		fprintf(stderr,"WARNING: width %u not an integral number of bytes at 12 bpp\n",width);
	}


	npixels=height*width;
	isize = (npixels*12)/8;
	if(isize > st.st_size) {
		fprintf(stderr,"%s: ERROR: dimensions too large for input file (%u*%u*12)/8=%u > %lu\n", 
				argv[0],width,height,isize,st.st_size);
		exit(1);
	} else if ( isize < st.st_size) {
		fprintf(stderr,"%s: WARNING: dimensions smaller than input file (%u*%u*12)/8=%u < %lu\n", 
				argv[0],width,height,isize,st.st_size);
	}

	if(!rgb && !split_yuv) {
		fprintf(stderr,"nothing to do!\n");
		usage();
		return 0;
	}

	in_data=malloc(isize);
	assert(in_data);

	fp=fopen(iname,"rb");
	assert(fp);

	rcount=fread(in_data,1,isize,fp);
	assert(rcount==isize);

	fclose(fp);

	fprintf(stderr,"input:  %s %ux%u UYVYYY %u bytes\n",iname, width, height, isize);

	if(split_yuv) {
		fprintf(stderr,"output: %s.Y %ux%u %s.U,V %ux%u\n", oname, width, height,oname,width/4,height);
		char splitname[256];
		py_data = y_data=malloc(npixels);
		assert(y_data);
		pu_data = u_data=malloc(npixels/4);
		assert(u_data);
		pv_data = v_data=malloc(npixels/4);
		assert(v_data);
		for (i=0;i<isize; i+=6) {
			*py_data++ = in_data[i+1];
			*py_data++ = in_data[i+3];
			*py_data++ = in_data[i+4];
			*py_data++ = in_data[i+5];
			*pu_data++ = in_data[i];
			*pv_data++ = in_data[i+2];

		}
		sprintf(splitname,"%s.Y",oname);
		fp=fopen(splitname,"wb");
		assert(fp);
		fwrite(y_data, 1, npixels, fp);
		fclose(fp);
		free(y_data);
		
		sprintf(splitname,"%s.U",oname);
		fp=fopen(splitname,"wb");
		assert(fp);
		fwrite(u_data, 1, npixels/4, fp);
		fclose(fp);
		free(u_data);

		sprintf(splitname,"%s.V",oname);
		fp=fopen(splitname,"wb");
		assert(fp);
		fwrite(v_data, 1, npixels/4, fp);
		fclose(fp);
		free(v_data);
	}
	if (rgb) {
		unsigned owidth; 
		uint8_t *p_yuv;
		char rgbname[256];

		if(skipy) {
			owidth = width/2;
		} else {
			owidth = width;
		}
		osize = (owidth*height)*3;
		out_data=malloc(osize);
		assert(out_data);

		prgb_data = out_data;
		p_yuv = in_data;

		sprintf(rgbname,"%s-%d.RGB",oname,owidth);

		fprintf(stderr,"output: %s %ux%u RGB8 %u bytes\n", rgbname, owidth, height, osize);

		for (i=0;i<npixels; i+=4, p_yuv+=6) {
			yuv_to_rgb(&prgb_data,p_yuv[1],p_yuv[0],p_yuv[2]);
			yuv_to_rgb(&prgb_data,p_yuv[3],p_yuv[0],p_yuv[2]);
			if(skipy) 
				continue;
			yuv_to_rgb(&prgb_data,p_yuv[4],p_yuv[0],p_yuv[2]);
			yuv_to_rgb(&prgb_data,p_yuv[5],p_yuv[0],p_yuv[2]);
		}

		fp=fopen(rgbname,"wb");
		assert(fp);
		fwrite(out_data, 1, osize, fp);
		fclose(fp);

		free(in_data);
		free(out_data);
		fprintf(stderr,"done\n");
	}
	return 0;
}

