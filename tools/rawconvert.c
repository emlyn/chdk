/*
A small tools to convert CHDK 10 and 12 bit raws to 8 or 16 bit grayscale for inspection
Can also covert to CHDK formats

Usage:
rawconvert -<op> -w=<width> -h=<height> [-noshift] [-pgm] <infile> <outfile>
where <op> is XtoY with X and Y being the source and destination BPP
by default
 converting to lower BPP discards the lower bits of the input value.
 converting to higher BPP shifts the input so the a max value input pixel will be a max value output pixel
if -noshift is specified
 converting to a lower BPP discards the upper bits
 converting to a higher BPP leaves the values unchanged

 NOTES: 
 Host is assumed to be little endian!
 This is a debugging tool not an imaging tool.
 
LINKS:
CHDK wikia article: 	http://chdk.wikia.com/wiki/CHDK_Tools#rawconvert.c

REVISIONS:
1. Initial release. Author: reyalP (28-Oct-2009)
    CHDK trunk SVN changeset #823 --> http://tools.assembla.com/chdk/changeset/823
    Forum link: http://chdk.setepontos.com/index.php/topic,2509.msg42402.html#msg42402

2. Portable Gray Map support added by cppasm (21-May-2010)
    Forum link: http://chdk.setepontos.com/index.php/topic,5207.msg50599.html#msg50599
    Changes:
	 Added support PGM (portable graymap) file format
     8 and 16 bits per pixel supported, but 16 bit is supported by limited subset of viewers so it's better to use 8 bit PGM
     PGM output is enabled with -pgm option, and you must specify .PGM extension to output file.
     example:  rawconvert.exe -10to8 -pgm -w=2672 -h=1968 CRW_0005.RAW IMG_0005.PGM
*/
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <assert.h>

typedef unsigned (*get_pixel_func_t)(uint8_t *p, unsigned row_bytes, unsigned x, unsigned y);
typedef void (*set_pixel_func_t)(uint8_t *p, unsigned row_bytes, unsigned x, unsigned y, unsigned value);
typedef unsigned (*convert_pixel_func_t)(unsigned value);

typedef struct {
	const char *name;
	unsigned ibpp;
	unsigned obpp;
	get_pixel_func_t get_pixel;
	set_pixel_func_t set_pixel;
} op_def_t;

void set_12_pixel(uint8_t *p,unsigned row_bytes, unsigned x, unsigned y, unsigned value)
{
 uint8_t* addr=p+y*row_bytes+(x>>2)*6;
 switch (x%4) {
  case 0: 
   addr[0] = (addr[0]&0x0F) | (unsigned char)(value << 4);
   addr[1] = (unsigned char)(value >> 4);
   break;
  case 1: 
   addr[0] = (addr[0]&0xF0) | (unsigned char)(value >> 8);
   addr[3] = (unsigned char)value;
   break;
  case 2: 
   addr[2] = (unsigned char)(value >> 4);
   addr[5] = (addr[5]&0x0F) | (unsigned char)(value << 4);
   break;
  case 3: 
   addr[4] = (unsigned char)value;
   addr[5] = (addr[5]&0xF0) | (unsigned char)(value >> 8);
   break;
 }
}

unsigned get_12_pixel(uint8_t *p, unsigned row_bytes, unsigned x, unsigned y)
{
 uint8_t* addr = p + y * row_bytes + (x>>2) * 6;
 switch (x&3) {
  case 0: return ((unsigned short)(addr[1]) << 4) | (addr[0] >> 4);
  case 1: return ((unsigned short)(addr[0] & 0x0F) << 8) | (addr[3]);
  case 2: return ((unsigned short)(addr[2]) << 4) | (addr[5] >> 4);
  case 3: return ((unsigned short)(addr[5] & 0x0F) << 8) | (addr[4]);
 }
 return 0;
}

unsigned get_10_pixel(uint8_t *p, unsigned row_bytes, unsigned x, unsigned y)
{
	uint8_t* addr = p + y * row_bytes + (x>>3) * 10;
	switch (x&7) {
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

void set_10_pixel(uint8_t *p, unsigned row_bytes, unsigned x, unsigned y, unsigned value)
{
	uint8_t* addr = p + y*row_bytes + (x>>3)*10;
	switch (x&7) {
		case 0:
			addr[0] = (addr[0]&0x3F)|(value<<6); 
			addr[1] = value>>2;
		break;
		case 1:
			addr[0] = (addr[0]&0xC0)|(value>>4);
			addr[3] = (addr[3]&0x0F)|(value<<4);
		break;
		case 2:
			addr[2] = (addr[2]&0x03)|(value<<2);
			addr[3] = (addr[3]&0xF0)|(value>>6);
		break;
		case 3:
			addr[2] = (addr[2]&0xFC)|(value>>8); 
			addr[5] = value;
		break;
		case 4:
			addr[4] = value>>2;
			addr[7] = (addr[7]&0x3F)|(value<<6);
		break;
		case 5:
			addr[6] = (addr[6]&0x0F)|(value<<4);
			addr[7] = (addr[7]&0xC0)|(value>>4);
		break;
		case 6:
			addr[6] = (addr[6]&0xF0)|(value>>6);
			addr[9] = (addr[9]&0x03)|(value<<2);
		break;
		case 7:
			addr[8] = value;
			addr[9] = (addr[9]&0xFC)|(value>>8);
		break;
	}
}

unsigned get_8_pixel(uint8_t *buf, unsigned row_bytes, unsigned x, unsigned y)
{
	return buf[row_bytes*y+x];
}

void set_8_pixel(uint8_t *buf, unsigned row_bytes, unsigned x, unsigned y, unsigned value)
{
	buf[row_bytes*y+x] = (uint8_t)value;
}

unsigned get_16_pixel(uint8_t *buf, unsigned row_bytes, unsigned x, unsigned y)
{
	return ((uint16_t *)buf)[(row_bytes/2)*y + x];
}

void set_16_pixel(uint8_t *buf, unsigned row_bytes, unsigned x, unsigned y, unsigned value)
{
	((uint16_t *)buf)[(row_bytes/2)*y + x] = (uint16_t)value;
}

void swap_bytes(unsigned char *src, unsigned char *dst, size_t size)
{
    unsigned char c1, c2;
	while(size>1)
	{
		c1=*src++;
		c2=*src++;
		*dst++=c2;
		*dst++=c1;
		size-=2;
	}
}

#define OP_DEF(X,Y) {#X "to" #Y, X, Y, get_##X##_pixel, set_##Y##_pixel},
op_def_t op_defs[]={
	OP_DEF(8,10)
	OP_DEF(8,12)
	OP_DEF(8,16)
	OP_DEF(10,8)
	OP_DEF(10,12)
	OP_DEF(10,16)
	OP_DEF(12,8)
	OP_DEF(12,10)
	OP_DEF(12,16)
	OP_DEF(16,8)
	OP_DEF(16,10)
	OP_DEF(16,12)
};

#define NUM_OP_DEFS (sizeof(op_defs)/sizeof(op_def_t))

const op_def_t *find_op(const char *name)
{
	unsigned i;
	for( i=0; i < NUM_OP_DEFS; i++) {
		if(strcmp(name,op_defs[i].name) == 0)
			return op_defs+i;
	}
	return NULL;
}

void usage()
{
	unsigned i;
	fprintf(stderr,"Usage: -<op> -w=<width> -h=<height> [-pgm] [-noshift] <infile> <outfile>\n");
	fprintf(stderr," op one of:");
	for( i=0; i < NUM_OP_DEFS; i++) {
		fprintf(stderr," %s",op_defs[i].name);
	}
	fprintf(stderr,"\n");
	exit(1);
}

int main(int argc, char**argv)
{
	uint8_t *in_data;
	uint8_t *out_data;
	FILE *fp;
	char *iname=NULL;
	char *oname=NULL;

	const op_def_t *op=NULL;

	unsigned height=0;
	unsigned width=0;
	unsigned npixels;
	unsigned osize;

	unsigned pixel_shift=1;
	unsigned pgm_format=0;
	int bpp_diff;

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
		else if ( strcmp(argv[i],"-noshift") == 0 ) {
			pixel_shift=0;
		}
		else if( strcmp(argv[i],"-pgm") == 0 ) {
			pgm_format=1;
		}
		else if ( argv[i][0]=='-' ) {
			if( !(op = find_op(argv[i]+1))) {
				fprintf(stderr,"%s: unknown option %s\n",argv[0],argv[i]);
				usage();
			}
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
	if(!op) {
		fprintf(stderr,"%s: no op given\n",argv[0]);
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

	if((width*op->ibpp)%8 != 0) {
		fprintf(stderr,"WARNING: width %u not an integral number of bytes at %u bpp\n",width,op->ibpp);
	}
	if((width*op->obpp)%8 != 0) {
		fprintf(stderr,"WARNING: width %u not an integral number of bytes at %u bpp\n",width,op->obpp);
	}
	if(pgm_format && op->obpp!=8 && op->obpp!=16) {
		fprintf(stderr,"WARNING: Portable Gray Map (PGM) format supports only 8 or 16 bpp.\n");
		pgm_format=0;
	}

	in_data=malloc(st.st_size);
	assert(in_data);

	fp=fopen(iname,"rb");
	assert(fp);

	rcount=fread(in_data,1,st.st_size,fp);
	assert(rcount==st.st_size);

	fclose(fp);

	npixels=height*width;
	if((npixels*op->ibpp) >> 3 != st.st_size) {
		fprintf(stderr,"%s: %s mismatched size (%u*%u*%u)/8 -> %u != %u\n",
					argv[0], iname, width, height, op->ibpp, (npixels*op->ibpp) >> 3, (unsigned)st.st_size);
		exit(1);
	}
	osize = (npixels*op->obpp) >> 3;
	out_data=malloc(osize);
	assert(out_data);

	fprintf(stderr,"input:  %s %ux%u %u bpp %u bytes\n",iname, width, height, op->ibpp, (unsigned)(st.st_size));
	fprintf(stderr,"output: %s %u bpp %u bytes\n", oname, op->obpp, osize);

	bpp_diff = op->obpp - op->ibpp;
	if(pixel_shift) {
		if(bpp_diff < 0) 
			fprintf(stderr," discard lower %d bits\n",-bpp_diff);
		else
			fprintf(stderr," multiply pixel values %d\n",1 << bpp_diff);
	} 
	else if(bpp_diff < 0) {
		fprintf(stderr," discard upper %d bits\n",-bpp_diff);
	}
	
	{
		unsigned pixel_value;
		unsigned in_row_bytes=(width*op->ibpp)>>3;
		unsigned out_row_bytes=(width*op->obpp)>>3;
		for(i=0; i<npixels; i++) {
			pixel_value = op->get_pixel(in_data, in_row_bytes, i%width, i/width);
			if (pixel_shift) {
				if (bpp_diff < 0) {
					pixel_value >>= -bpp_diff;
				}
				else if (bpp_diff > 0) {
					pixel_value <<= bpp_diff;
				}
			}
			op->set_pixel(out_data, out_row_bytes, i%width, i/width, pixel_value);
		}
	}

	fp=fopen(oname,"wb");
	assert(fp);
	if(pgm_format)
	{
		fprintf(fp, "P5\n%d\n%d\n%d\n", width, height, (1 << op->obpp)-1);
		if(op->obpp==16) swap_bytes(out_data, out_data, osize);
	}
	fwrite(out_data, 1, osize, fp);
	fclose(fp);

	free(in_data);
	free(out_data);
	fprintf(stderr,"done\n");
	return 0;
}
