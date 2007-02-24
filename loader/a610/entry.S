    .text
    .org 0
    .globl _start

_start:
	MOV     SP, #0x1900
	MOV     R11, #0
	B	my_restart

.fill 8,4,0
