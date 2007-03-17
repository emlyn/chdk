#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>


typedef struct {
    uint32_t inst;
    uint32_t mask;
    uint32_t ignore;
} Instr;

Instr instrs[] = {
//    {0x00000000 , 0x00000000, 0x00000000 },	// adc
    {0x00800000 , 0x0df00000, 0x02000000 },	// add
    {0x00000000 , 0x0de00000, 0x02000000 },	// and
    {0x0a000000 , 0x0e000000, 0x00ffffff },	// b, bl
    {0x01c00000 , 0x0de00000, 0x02000000 },	// bic
//    {0x00000000 , 0x00000000, 0x00000000 },	// bkpt
//    {0x00000000 , 0x00000000, 0x00000000 },	// blx
//    {0x00000000 , 0x00000000, 0x00000000 },	// blx
//    {0x00000000 , 0x00000000, 0x00000000 },	// bx
//    {0x00000000 , 0x00000000, 0x00000000 },	// cdp
//    {0x00000000 , 0x00000000, 0x00000000 },	// clz
    {0x01700000 , 0x0df00000, 0x02000000 },	// cmn
    {0x01500000 , 0x0df00000, 0x02000000 },	// cmp
//    {0x00000000 , 0x00000000, 0x00000000 },	// eor
//    {0x00000000 , 0x00000000, 0x00000000 },	// ldc
//    {0x00000000 , 0x00000000, 0x00000000 },	// ldm
//    {0x00000000 , 0x00000000, 0x00000000 },	// ldm
//    {0x00000000 , 0x00000000, 0x00000000 },	// ldm
/// {0x00000000 , 0x00000000, 0x00000000 },	// ldr
/// {0x00000000 , 0x00000000, 0x00000000 },	// ldrb
/// {0x00000000 , 0x00000000, 0x00000000 },	// ldrbt
/// {0x00000000 , 0x00000000, 0x00000000 },	// ldrh
/// {0x00000000 , 0x00000000, 0x00000000 },	// ldrsb
/// {0x00000000 , 0x00000000, 0x00000000 },	// ldrsh
/// {0x00000000 , 0x00000000, 0x00000000 },	// ldrt
//    {0x00000000 , 0x00000000, 0x00000000 },	// mcr
//    {0x00000000 , 0x00000000, 0x00000000 },	// mla
    {0x01a00000 , 0x0de00000, 0x02000000 },	// mov
//    {0x00000000 , 0x00000000, 0x00000000 },	// mrc
//    {0x00000000 , 0x00000000, 0x00000000 },	// mrs
//    {0x00000000 , 0x00000000, 0x00000000 },	// msr
//    {0x00000000 , 0x00000000, 0x00000000 },	// mul
//    {0x00000000 , 0x00000000, 0x00000000 },	// mvn
//    {0x00000000 , 0x00000000, 0x00000000 },	// orr
//    {0x00000000 , 0x00000000, 0x00000000 },	// rsb
//    {0x00000000 , 0x00000000, 0x00000000 },	// rsc
//    {0x00000000 , 0x00000000, 0x00000000 },	// scb
//    {0x00000000 , 0x00000000, 0x00000000 },	// smlal
//    {0x00000000 , 0x00000000, 0x00000000 },	// smull
//    {0x00000000 , 0x00000000, 0x00000000 },	// src
//    {0x00000000 , 0x00000000, 0x00000000 },	// stm
//    {0x00000000 , 0x00000000, 0x00000000 },	// stm
/// {0x00000000 , 0x00000000, 0x00000000 },	// str
/// {0x00000000 , 0x00000000, 0x00000000 },	// strb
/// {0x00000000 , 0x00000000, 0x00000000 },	// strbt
/// {0x00000000 , 0x00000000, 0x00000000 },	// strh
/// {0x00000000 , 0x00000000, 0x00000000 },	// strt
    {0x00400000 , 0x0de00000, 0x02000000 },	// sub
//    {0x00000000 , 0x00000000, 0x00000000 },	// swi
//    {0x00000000 , 0x00000000, 0x00000000 },	// swp
//    {0x00000000 , 0x00000000, 0x00000000 },	// swpb
//    {0x00000000 , 0x00000000, 0x00000000 },	// teq
    {0x01100000 , 0x0df00000, 0x02000000 },	// tst
//    {0x00000000 , 0x00000000, 0x00000000 },	// umlal
//    {0x00000000 , 0x00000000, 0x00000000 },	// umull

    { 0, 0, 0 }
};

void usage()
{
    printf("gensig <primary> <base> <proc_name> <proc_vaddr> <proc_size>\n");
    exit(1);
}

int main(int argc, char **argv)
{
    char *proc_name;
    uint32_t buf[1024];
    FILE *f;
    int base;
    int pos;
    int size;
    int i,j;
    int wcount;
    int finish;

    if (argc != 6)
	usage();

    f = fopen(argv[1], "r+b");

    if (f == NULL)
	usage();

    base = strtol(argv[2], NULL, 0);
    proc_name = argv[3];
    pos = strtol(argv[4], NULL, 0) - base;
    size = strtol(argv[5], NULL, 0);
    wcount = 0;


    fseek(f, pos, SEEK_SET);
    fread(buf, 4, size, f);

    printf("static FuncSig func_sig_%s[] = {\n",proc_name);
    finish = 0;
    for (i=0;i<size;i++){
	for (j=0;instrs[j].inst | instrs[j].mask;j++){
	    if ((buf[i] & instrs[j].mask) == instrs[j].inst){
		printf("\t{ %3d, 0x%08x, 0x%08x },\n", i,
		    buf[i] & ~instrs[j].ignore, ~instrs[j].ignore);
		wcount++;
		if ((buf[i] == 0xe1a0f00e) /* "mov pc,lr" aka "ret" */
		    && (size*100/wcount) > 75){
		    printf("\t/* RET found, stopping... */\n");
		    finish = 1;
		}
		break;
	    }
	}
	if (finish)
	    break;
    }
    printf("\t{ -1, -1, -1 },\n");
    printf("\t/* %d/%d */\n",wcount, size);
    printf("};\n\n");

    return 0;
}

