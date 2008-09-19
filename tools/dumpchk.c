/*
Find the code normally found at the start of ROM.
Default mode detects dryos or vxworks.
If -fix is given, re-write the dump file after removing anything before
the start sig

If -vxworks or -dryos is given, just check that the corresponding sig is
found at the start of the dump, and print a message/return status
-quiet will suppress the message and only return status.

If you have a tree full of dumps you want to check/fix, use find, e.g.
*/
//find . -path ./*sub/* \! -path *.svn* -type d -exec dumpchk '{}/primary.bin' \;
/*
will check primary.bin in each of the platform/sub directories, skipping .svn,
reporting missing or zero sized files. 

You can use -fix with the above command if you feel lucky.

Note that -fix DOES NOT MAKE ANY BACKUP, and is NOT PARTICULARLY SAFE.

The two start sigs work for all dumps I have tested, which includes
almost every camera supported by chdk and some that aren't*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void usage(void) {
	fprintf(stderr,"usage: dumpchk [-vxworks|-dryos|-fix] [-quiet] <dump>\n");
	exit(1);
}

// MOV R0, 2
// B +...
// Copyright 1992...
const char vxworks_start_sig[] = {
	0x02, 0x00, 0xA0, 0xE3,
	0x12, 0x00, 0x00, 0xEA,
	'C', 'o', 'p', 'y', 'r', 'i', 'g', 'h'
};
// B +...
// gaonisoy
const char dryos_start_sig[] = {
	0x01, 0x00, 0x00, 0xEA,
	'g', 'a','o', 'n', 'i', 's', 'o' ,'y'
};


#define CHECK_FIND 0
#define CHECK_VXWORKS 1
#define CHECK_DRYOS 2
int main(int argc, char **argv) {
	int retval = 0;
	int checkmode = CHECK_FIND;
	int fix = 0;
	int quiet = 0;
	char *dumpname = NULL;
	FILE *dumpfile;
	int i,size;
	for(i = 1; i < argc; i++) {
		if ( strcmp(argv[i],"-vxworks") == 0 ) {
			checkmode = CHECK_VXWORKS;
		}
		else if (strcmp(argv[i],"-dryos") == 0 ) {
			checkmode = CHECK_DRYOS;
		}
		else if (strcmp(argv[i],"-fix") == 0 ) {
			fix = 1;
		}
		else if (strcmp(argv[i],"-quiet") == 0 ) {
			quiet = 1;
		}
		else if ( argv[i][0] == '-' ) {
			fprintf(stderr,"%s unknown option %s\n",argv[0],argv[i]);
			usage();
		}
		else {
			if (!dumpname)
				dumpname=argv[i];
			else {
				fprintf(stderr,"%s unexpected %s\n",argv[0],argv[i]);
				usage();
			}
		}
	}
	if(!dumpname) {
		usage();
	}
	dumpfile = fopen(dumpname,"rb");
	if(!dumpfile) {
		fprintf(stderr,"%s unable to open %s\n",argv[0],dumpname);
		usage();
	}
    fseek(dumpfile,0,SEEK_END);
    size=ftell(dumpfile);
    fseek(dumpfile,0,SEEK_SET);

	if( checkmode == CHECK_FIND) {
		char *buf;
		const char *found=NULL;
		if(size < sizeof(vxworks_start_sig) || size < sizeof(dryos_start_sig)) {
			printf("%s TOO SMALL: 0x%X (%d) bytes\n",dumpname,size,size);
			fclose(dumpfile);
			return 1;
		}
		buf=malloc(size);
		if(!buf) {
			fprintf(stderr,"%s out of memory\n",argv[0]);
			fclose(dumpfile);
			exit(2);
		}
		fread(buf, 1, size, dumpfile);
		for(i=0; i<size; i++) {
			if( i+sizeof(vxworks_start_sig) < size) {
				if(memcmp(buf+i,vxworks_start_sig,sizeof(vxworks_start_sig)) == 0) {
					found = "VXWORKS";
				}
			}
			if( i+sizeof(dryos_start_sig) < size) {
				if(memcmp(buf+i,dryos_start_sig,sizeof(dryos_start_sig)) == 0) {
					found = "DRYOS";
				}
			}
			if(found) {
				printf("%s %s ",dumpname,found);
				if(i) {
					printf("@0x%X (%d) REMAINING 0x%X (%d) bytes\n",i,i,size-i,size-i);
				}
				else {
					printf("@Start SIZE 0x%X (%d)\n",size,size);
				}
				break;
			}
		}
		if(i==size) {
			printf("%s 0x%X (%d) bytes no sig found\n",dumpname,size,size);
			retval = 0;
		}
		fclose(dumpfile);
		if(fix && i && i < size) {
			dumpfile = fopen(dumpname,"wb");
			printf("fix: %s trim 0x%X (%d) ...",dumpname,i,i);
			if(!dumpfile) {
				fprintf(stderr,"\n%s unable to open %s for write\n",argv[0],dumpname);
			}
			else {
				fwrite(buf+i,1,size-i,dumpfile);
				printf(" wrote 0x%X (%d)\n",size-i,size-i);
			}
		}
		free(buf);
	}
	else {
		const char *sig=vxworks_start_sig,*osname = "VXWORKS";
		char *buf;
		int sigsize = sizeof(vxworks_start_sig);
		
		if (checkmode == CHECK_DRYOS) {
			sig = dryos_start_sig;
			sigsize = sizeof(dryos_start_sig);
			osname = "DRYOS";
		}
		buf = malloc(sigsize);
		if(!buf) {
			fprintf(stderr,"%s out of memory\n",argv[0]);
			fclose(dumpfile);
			exit(2);
		}
		if( fread(buf,1,sigsize,dumpfile) != sigsize) {
			retval = 0;
		}
		else {
			retval = (memcmp(buf,sig,sigsize) == 0);
		}
		free(buf);

		if(!quiet) {
			if(retval) {
				printf("%s valid %s 0x%X (%d) bytes\n",dumpname,osname,size,size);
			}
			else {
				printf("%s NOT valid %s 0x%X (%d) bytes\n",dumpname,osname,size,size);
			}
		}
	}
	fclose(dumpfile);
	return retval == 0;
}
