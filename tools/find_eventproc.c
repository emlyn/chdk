/* find char* name, f_funcptr pair in dump from string,
   output suitable for stubs_entry_2.s*/
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "dumputil.h"

void usage()
{
    fprintf(stderr,"find_eventproc <dumpfile.bin> <base address> <name1> <name1> ...\n");
    exit(1);
}

int find_event_proc(dump_t *dump,char *name)
{
	unsigned str_offset=0;
	unsigned str_addr=0;
	unsigned found=0;
	while(find_cstring(dump,&str_offset,name)) {
		str_addr=offset_to_ptr(dump,str_offset);
		int i=0;
		while(find_word_aligned(dump,&i,str_addr)) {
			uint32_t pfunc = dump->pw[i+1];
			// TODO better check for valid code, or even check against ref dump
			if(pfunc > dump->base && deref_word_ptr(dump,i*4+4) != 0) {
//				printf("%s candidate %08X val %08X\n",name,pfunc,deref_word_ptr(dump,i*4+4));
				printf("NHSTUB(%s,0x%08X) // by find_eventproc name @ 0x%08X\n",name,pfunc,offset_to_ptr(dump,i*4));
				found++;
			}
			i++;
		}
		str_offset+=strlen(name);
	}
	return found;
}

int process_dump(dump_t *dump,char **names,unsigned num_procs)
{
	unsigned i;
	unsigned found;
	for(i=0,found=0; i<num_procs; i++) {
//		printf("searching for '%s'\n",names[i]);
		if(find_event_proc(dump,names[i]))
			found++;
	}
	return found;
}

int main(int argc, char **argv)
{

	dump_t dump;	
	unsigned i;
	const char *dumpname=NULL;
	const char *base=NULL;
	unsigned num_procs=0;

	for(i = 1; i < argc; i++) {
		if ( argv[i][0] == '-' ) {
			fprintf(stderr,"%s unknown option %s\n",argv[0],argv[i]);
			usage();
		}
		else {
			if (!dumpname) {
				dumpname=argv[i];
			} else if(!base) {
				base=argv[i];
			}
		}
	}
	num_procs = argc-3;

	if(!dumpname || !base || !num_procs) {
		usage();
	}

	if(!load_dump(dumpname,base,&dump))
		return 1;

	if(!process_dump(&dump,argv+3,num_procs))
		return 1;

	return 0;
}

