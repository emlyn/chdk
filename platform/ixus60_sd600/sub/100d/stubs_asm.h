    .text

#define DEF(n,a) \
    .globl n; n = a

#define NSTUB(name, addr)\
    .globl _##name ;\
    .globl name ;\
    .weak _##name ;\
    .weak name ;\
    _##name: ;\
    name: ;\
	ldr  pc, = ## addr

#define NHSTUB(name, addr)\
    .globl _##name ;\
    _##name: ;\
	ldr  pc, = ## addr

#define STUB(addr)\
    .globl sub_ ## addr ;\
    sub_ ## addr: ;\
	ldr  pc, =0x ## addr

#define STUB_DIR(name, addr)\
    .globl name ;\
    name: ;\
	ldr  pc, = addr
