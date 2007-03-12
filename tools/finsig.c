#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>

typedef struct {
    uint32_t ptr;
    uint32_t fail;
    uint32_t success;
} Match;

typedef struct {
    uint32_t offs;
    uint32_t value;
    uint32_t mask;
} FuncSig;

typedef struct {
    const char *name;
    FuncSig *sig;
} FuncsList;

#include "signatures.h"

int match_compare(const Match *p1, const Match *p2)
{
    if (p1->success > p2->success){
	return -1;
    } else
    if (p1->success < p2->success){
	return 1;
    } else {
	if (p1->fail < p2->fail){
	    return -1;
	} else
	if (p1->fail > p2->fail){
	    return 1;
	}
    }

    return 0;
}

void usage()
{
    printf("finsig <primary> <base>\n");
    exit(1);
}

int main(int argc, char **argv)
{
    Match matches[64];
    uint32_t *buf;
    FILE *f;
    int size;
    int i,j,k;
    int fail, success;
    int base = 0xffc00000;
    FuncSig *sig;
    int count;
    int ret = 0;

    if (argc != 3)
	usage();

    f = fopen(argv[1], "r+b");

    if (f == NULL)
	usage();

    base = strtol(argv[2], NULL, 0);

    printf("// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!\n");
    printf("#include \"stubs_asm.h\"\n\n");

    fseek(f,0,SEEK_END);
    size=ftell(f)/4;
    fseek(f,0,SEEK_SET);

    buf=malloc(size*4);
    fread(buf, 4, size, f);

    for (k=0;func_list[k].name;k++){
	sig = func_list[k].sig;
	count = 0;
	for (i=0;i<size-32;i++){
	    fail = 0;
	    success = 0;
	    for (j=0;sig[j].offs!=-1;j++){
		if ((buf[i+sig[j].offs] & sig[j].mask) != sig[j].value){
		    fail++;
		    // prioritize first instr.
		    if (j==0)
			fail+=5;
		} else {
		    success++;
		}
	    }
	    if (success > fail){
		matches[count].ptr = base+i*4;
		matches[count].success = success;
		matches[count].fail = fail;
		count ++;
	    }
	}


	if (count == 0 ){
	    printf("// ERROR: %s is not found!\n", func_list[k].name);
	    ret = 1;
	} else {
	    if (count > 1){
		qsort(matches, count, sizeof(Match), (void*)match_compare);
	    }

	    if (matches->fail > 0)
		printf("// Best match: %d%%\n", matches->success*100/(matches->success+matches->fail));

	    printf("NSTUB(%s, 0x%x)\n", func_list[k].name, matches->ptr);

	    for (i=1;i<count && matches[i].fail==matches[0].fail;i++){
		printf("// ALT: NSTUB(%s, 0x%x) // %d/%d\n", func_list[k].name, matches[i].ptr, matches[i].success, matches[i].fail);
	    }

	}
    }

    return ret;
}

