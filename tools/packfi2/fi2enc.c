// fi2encdec v1.0

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
//#include <malloc.h>
#include <memory.h>
#include <string.h>
#include <ctype.h>
#include "zlib.h"

#include "aes128.h"

static const char *g_str_err_malloc = "memory allocation error (requested %d bytes)\n";
static const char *g_str_shorthelp = "Usage: fi2encdec [-p PID] [-key KEY -iv IV] in.file out.file\n";

char *_strlwr(char *moep) {
     char *tmp = moep;
     while((*tmp = tolower(*tmp)))  tmp++;
     return moep;
} 

// FI2 block record
struct fi2_rec_s {
	uint32_t	offset;		// Offset in data block
	uint32_t	upklen;		// Real (unpacked) size of data block
	uint32_t	len;		// Length of compressed and padded data block
	uint32_t	addr;		// target address for data block
	uint32_t	uf1;		// unknown flag 1
	uint32_t	fmain;		// Main FW block flag
	uint32_t	fboot;		// Bootloader block flag
	uint32_t	uf2;		// unknown flag 2
} fi2_rec_s;

// FI2 header (with size field)
typedef struct fi2_header_s {
	uint32_t	hlen_be;	// Header length in big endian
	uint32_t	hwid;		// Hardware ID
	uint32_t	unk1;		// unk1 field (0x02230000)
	uint32_t	id;			// ID field   (0x01000000)
	uint32_t	ch;			// Ch field   (0x00000000)
	uint32_t	unk2;		// unk2 field (0x00000001)
	uint32_t	nblk;		// number of blocks & records
	uint32_t	datacs;		// checksum of encrypted data block
} fi2_hdr_t, *pfi2_hdr_t; 

static uint32_t read32_be( const void *src_buffer )
{
	unsigned char *b = (unsigned char *)src_buffer;
	return (b[0]<<24) | (b[1] << 16) | (b[2] << 8) | b[3];
}

static void store32_be( void *dst_buffer, uint32_t value )
{
	unsigned char *b = (unsigned char *)dst_buffer;
	b[0] = ( value >> 24 ) & 0xFF;
	b[1] = ( value >> 16 ) & 0xFF;
	b[2] = ( value >>  8 ) & 0xFF;
	b[3] = ( value >>  0 ) & 0xFF;
}

static uint32_t align128( uint32_t value )
{
	return ( (value + 16 - 1) & 0xFFFFFFF0ul );
}

static int get_hexstring( void *dst, const char *str, int len )
{
	int i;
	unsigned char c;
	unsigned char *p = (unsigned char *)dst;

	if( !str ){
		printf( "No hex string supplied!\n" );
		return -1;
	}
	if( !p ) return -1;
	if( strlen( str ) != len*2 ){
		printf( "Hex length mismatch in \"%s\"!\n", str );
		return -1;
	}
	for( i = 0; i < len*2; i++ ){
		c = str[i];
		if( c < ('9'+1) && c >= '0' ) c-= 0x30;
		else if( c < 'G' && c >= 'A' ) c -= ('A' - 0x0A);
		else if( c < 'g' && c >= 'a' ) c -= ('a' - 0x0A);
		else {
			printf("Non-nex character \'%c\' at %d in string %s\n", c, i+1, str );
			return -1;
		}
		p[i/2] = i & 1 ? p[i/2] | c : c << 4;
	}
	return 0;
}

static int fi2enc( char *infname, char *outfname, uint32_t *key, uint32_t *iv , uint32_t pid)
{
	unsigned long i;
	size_t hdrsize, flen;
	uint32_t cs;
	FILE *fi, *fo;
	fi2_hdr_t hdr;
	struct fi2_rec_s  fi2rec;
	unsigned char *buf = NULL;
	unsigned char *upkbuf = NULL;
	unsigned char exkey[176];
	unsigned char *pblk;

	if( !infname ){
		printf("Please supply input file name.\n");
		return -1;
	}
	if( !outfname ){
		printf("Please supply target file name.\n");
		return -1;
	}
	aes128_expandkey( exkey, key );
	hdrsize = 0;
	cs = 0;
	memset(&hdr, 0, sizeof (hdr));
	memset(&fi2rec, 0, sizeof (fi2rec));
	hdr.hwid=pid;
	hdr.unk1=0x02230000;
        hdr.id=0x01010000;
        hdr.ch=0;
        hdr.unk2=1;
	hdrsize = 32;
	fi2rec.addr=0;
	fi2rec.fboot = 1;
	if ( !(fi = fopen(infname, "rb")) ){
		printf( "Can't open data file %s\n", infname );
		return -1;
	}
	fseek( fi, 0, SEEK_END );
	flen = ftell( fi );
	fseek( fi, 0, SEEK_SET );

	if( flen <= 0 || flen > (256  << 20) ){				// file size sanity check (256MB max)
		printf( "Data file %s have unacceptable file size (%ld)\n", infname, (unsigned long) flen );
		return -1;
	}
	upkbuf = (unsigned char*)malloc( flen );			// allocate buffer for data file
	if( !upkbuf ){
		printf( g_str_err_malloc, flen );
		return -1;
	}
	if( flen > fread( upkbuf, 1, flen, fi ) ){
		printf( "Error reading data file\n" );
		return -1;
	}
	fclose( fi );
	i = align128( 4 + compressBound( flen ) );			// determine upper bound for compressed block buffer
	buf = (unsigned char*)malloc( i );					// allocate buffer for compressed block + blocksize
	if( !buf ){
		printf( g_str_err_malloc, i );
		return -1;
	}
	memset( buf, 0xFF, i );
	i -= 4;
	if( Z_OK !=    compress( buf + 4, (uLongf*)&i, upkbuf, flen ) ){ 
		printf( "Data compression error\n" );
		return -1;
	}
	store32_be( buf, i );								// store real compressed block size
	fi2rec.upklen = flen;
	fi2rec.offset = 0;						// save data block offset
	fi2rec.len = align128( i + 4 );
	// encrypt data block
	aes128_cbc_encrypt( buf, exkey, iv, fi2rec.len );
	pblk = buf;									
	for( i = 0; i < (int)fi2rec.len; i++) cs += buf[i];	// update block checksum
	free( upkbuf ); upkbuf = NULL;
	// process next block
	// finalize header
	i = 32 + sizeof (fi2rec);
	store32_be( &hdr.hlen_be, i - 4 );
	hdr.nblk = 1;
	hdr.datacs = cs;
	buf = (unsigned char*)malloc( i );							// allocate buffer for encrypted header
	if( !buf ){
		printf( g_str_err_malloc, i );
		return -1;
	}
	memcpy( buf, &hdr, 32 );
	memcpy( buf+32, &fi2rec, sizeof(fi2rec));
	aes128_cbc_encrypt( buf, exkey, iv, i );

	// ---------------------------- save results ------------------------------
	// open target file
	printf( "Saving %s\n", outfname );
	fo = fopen(outfname,"wb");
	if(!fo){
		printf("Can't open file %s for writing\n", outfname);
		return(-1);
	}
	// save header
	if ( i != fwrite(buf, 1, i, fo ) ){
		printf("\nError writing header to %s (%ld bytes)\n", outfname, i);
		return(-1);
	}
	free( buf );
	// save data blocks
		if (fi2rec.len != fwrite( pblk, 1, fi2rec.len, fo ) ){
			printf("\nError writing data block to %s (%d bytes)\n", outfname, fi2rec.len);
			return(-1);
		}
		free( pblk );
	fclose( fo );
	return 0;
}

int main( int argc, char **argv )
{
	int i;
	uint32_t key_buf[4];
	uint32_t iv_buf[4];
	uint32_t *key = NULL;
	uint32_t *iv = NULL;
	char *fni = NULL, *fno = NULL;
	uint32_t pid=0;

	// parse command line
	for( i = 1; i < argc; i++){
		if( argv[i][0] == '/' || argv[i][0] == '-' ){	// ---- arg is option
			
			if( !strcmp( "key", _strlwr(argv[i]+1) ) ){						// opt: key
				if ( get_hexstring( key_buf, argv[++i], sizeof key_buf ) ) return -1;
				else key = key_buf;
			}
			else if( !strcmp( "iv", _strlwr(argv[i]+1) ) ){							// opt: iv
				if ( get_hexstring( iv_buf, argv[++i], sizeof iv_buf ) ) return -1;
				else iv = iv_buf;
			}
			else if( !strcmp( "p", _strlwr(argv[i]+1) ) ){						// opt: pid
			        char *err=NULL;
			        pid = strtoul(argv[++i], &err, 0);
				if (*err) return -1;
			}
			else {
				printf("Unexpected option: %s\n", argv[i]);
				return -1;
			}
		} else {	// ---- arg is not an option
			if( !fni ) fni = argv[i];		// 1st non-option is input file name
			else if( !fno ) fno = argv[i];	// 2nd non-option is output file name
			else {
				printf("Unexpected parameter: %s\n", argv[i]);
				return -1;
			}
		}
	}
	if( !key || !iv || !pid){
		fputs( g_str_shorthelp, stdout );
		return -1;
	}
	for( i = 0; i < 4; i ++ )  key[i] = read32_be( key+i );
        i = fi2enc( fni, fno, key, iv , pid);
	if ( !i ) printf( "Done\n" );	else printf( "Failed!\n" );
	return i;
}
