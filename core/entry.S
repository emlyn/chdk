    .text
    .org 0
    .globl _start

_start:
	MOV	R0, #2
	TEQ     R0, #2
	LDR     SP, =0x1900
	MOV     R11, #0

	B	startup

.fill 32,4,0
