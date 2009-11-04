/*some utility functions for working with firmware dumps*/
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "dumputil.h"

// translate a pointer found in the dump to an index in the dump
unsigned ptr_to_offset(dump_t *dump,unsigned ptr) 
{
	if(ptr < dump->base) // warn
		return 0;
	return ptr - dump->base;
}

unsigned offset_to_ptr(dump_t *dump,unsigned off) 
{
	if(off >= dump->size) // warn
		return 0;
	return off + dump->base;
}

int find_cstring(dump_t *dump, unsigned *pos, const char *string)
{
	unsigned i;
	for(i=*pos; i<dump->size - strlen(string); i++) {
		if(strcmp(dump->pb+i,string)==0) {
			*pos = i;
			return 1;
		}
	}
	return 0;
}

int find_word_aligned(dump_t *dump, unsigned *index, uint32_t word)
{
	unsigned i;
	for(i=*index; i<dump->words - 1; i++) {
		if(dump->pw[i]==word) {
			*index = i;
			return 1;
		}
	}
	return 0;
}

// get an arbitrary unaligned word
uint32_t get_word(dump_t *dump,unsigned off)
{
	if(off > dump->size) // warn
		return 0;
	return *(unsigned *)(dump->pb+off);
}

// treat the value at off as a pointer in the dump, and return the word pointed to
uint32_t deref_word_ptr(dump_t *dump,unsigned off)
{
	uint32_t ptr=get_word(dump,off);
	return get_word(dump,ptr_to_offset(dump,ptr));
}

uint8_t deref_byte_ptr(dump_t *dump,unsigned off)
{
	uint32_t ptr=get_word(dump,off);
	return dump->pb[ptr_to_offset(dump,ptr)];
}

const char* deref_string_ptr(dump_t *dump,unsigned off)
{
	uint32_t ptr=get_word(dump,off);
	return (const char *)(dump->pb + ptr_to_offset(dump,ptr));
}

int load_dump(const char *dumpname,const char *base, dump_t *dump)
{
	FILE *dumpfile;
	uint8_t *p;
	struct stat st;
	size_t rcnt;

	dump->base=strtoul(base,NULL,0);
	if(dump->base != 0xFFC00000 && dump->base != 0xFF810000) {
		fprintf(stderr,"error base '%s' %x\n",base,dump->base);
		return 0;
	}

    if (stat(dumpname,&st) != 0) {
        fprintf(stderr,"error: unable to stat %s\n",dumpname);
		return 0;
	}

	if (st.st_size < MIN_DUMP_SIZE) {
        fprintf(stderr,"error: invalid dump %s\n",dumpname);
        return 0;
    }

    if ((p = malloc(st.st_size)) == NULL ) {
        fprintf(stderr,"error: unable to allocate %lu bytes\n",st.st_size);
        return 0;
    }

    dumpfile = fopen(dumpname, "rb");

    if (dumpfile == NULL) {
        fprintf(stderr,"error: unable to open %s\n",dumpname);
		free(p);
        return 0;
    }

    rcnt=fread(p, 1, st.st_size, dumpfile);
    fclose(dumpfile);

    if (rcnt != st.st_size) {
        fprintf(stderr,"error: unable to read %s\n",dumpname);
		free(p);
        return 0;
    }
	dump->pb=p;
	dump->size=st.st_size;
	dump->words = dump->size >> 2;
	// TODO is size is such that base + size > 0xFFFFFFFF should warn and trim size values
	// can also detect start sig ala dumpchk
	return 1;
}

