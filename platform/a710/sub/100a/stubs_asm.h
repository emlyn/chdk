    .text

#define DEF(n,a) \
    .globl n; n = a

#define NSTUB(name, addr)\
    .globl name ;\
    name: ;\
	ldr  pc, = ## addr

#define STUB(addr)\
    .globl sub_ ## addr ;\
    sub_ ## addr: ;\
	ldr  pc, =0x ## addr
