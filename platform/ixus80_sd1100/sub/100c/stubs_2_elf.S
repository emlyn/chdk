.text
.org 0
.align 2
.globl _start

// stubs_2_elf.S
// (c) 2008 chr
// GPL v3+
// create elf file from a binary blob
// and mix with symbols from stubs files

// compile with:
// arm-linux-gnu-gcc -Wl,-N,-Ttext,0xff810000 -nostdlib stubs_2_elf.S -o rom.elf


// cheat around gdb ignoring absolute symbols
here = .
#define offs 0xff810000
#define NSTUB(name, addr) name = here + addr - offs
#define NHSTUB NSTUB
#define __STUBS_ASM__H__
#include "stubs_entry.S"
#include "stubs_entry_2.S"
#include "stubs_bonus.S"

// test test ...
NSTUB(Jump, 0xff81000c)
NSTUB(Whatever, 0xff810164)

// include rom dump
_start:
.text

blob_start:
.incbin "PRIMARY.BIN"
blob_end:

