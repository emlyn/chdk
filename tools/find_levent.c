#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "dumputil.h"

int opt_def;
int opt_full;

void usage()
{
    fprintf(stderr,"find_levent [-full] [-def] <dumpfile.bin> <base address>\n");
    exit(1);
}

void dump_levent_table(dump_t *dump,unsigned index)
{
	int i;
	printf("id hex, id dec, name, param\n");
	for(i=index; i < dump->words - 3 && dump->pw[i]; i+=3) {
		printf("0x%04x, %5d, %s, %d\n",dump->pw[i+1],
								dump->pw[i+1],
								(*(deref_string_ptr(dump,i*4)))?deref_string_ptr(dump,i*4):"(none)",
								dump->pw[i+2]);
	}
}

int process_dump(dump_t *dump)
{
	const char *sig_str="PressRightButton";
	unsigned mark_offset=0;
	unsigned mark_addr=0;
	unsigned i,j;
	while(find_cstring(dump,&mark_offset,sig_str)) {
		mark_addr=offset_to_ptr(dump,mark_offset);
	// find {char *->"PressRightButton,x,0}
		i=0;
		while(find_word_aligned(dump,&i,mark_addr)) {
			if( dump->pw[i+1] > 0x800 && 
				dump->pw[i+1] < 0xFFFF &&
				dump->pw[i+2] == 0) {
				// now work backwards to try to find start: p->"",0x800,
				for (j=i; j > 3; j-=3) {
					if(dump->pw[j+1]==0x800 && deref_byte_ptr(dump,j*4) == 0 ) {
						if(opt_def) {
							printf("DEF(levent_table,0x%X)\n",j*4+dump->base);
						}
						else {
							printf("levent_table 0x%X\n",j*4+dump->base);
						}
						if(opt_full) {
							dump_levent_table(dump,j);
						}
						return 1;
					}
				}
			}
			i++;
		}
		mark_offset += strlen(sig_str);
	}
	if(!mark_offset) {
		fprintf(stderr,"error: \"%s\" not found\n",sig_str);
	}
	else {
		fprintf(stderr,"error: event table not found\n");
	}
	return 0;
}

int main(int argc, char **argv)
{

	dump_t dump;	
	int i;
	const char *dumpname=NULL;
	const char *base=NULL;

	for(i = 1; i < argc; i++) {
		if ( strcmp(argv[i],"-def") == 0 ) {
			opt_def = 1;
		}
		else if (strcmp(argv[i],"-full") == 0 ) {
			opt_full = 1;
		}
		else if ( argv[i][0] == '-' ) {
			fprintf(stderr,"%s unknown option %s\n",argv[0],argv[i]);
			usage();
		}
		else {
			if (!dumpname) {
				dumpname=argv[i];
			} else if(!base) {
				base=argv[i];
			} else {
				fprintf(stderr,"%s unexpected %s\n",argv[0],argv[i]);
				usage();
			}
		}
	}
	if(!dumpname || !base) {
		usage();
	}

	if(!load_dump(dumpname,base,&dump))
		return 1;

	if(!process_dump(&dump))
		return 1;

	return 0;
}
