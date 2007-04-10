    .text
    .org 0
    .globl _start

_start:

// LED on (debug indicator)
	LDR     R3, =0xc0220084
	MOV     R2, #0x46
	STR     R2, [R3]


// Turn OFF SD Card power
// to support autostart

	LDR     R3, =0xC02200BC
	MOV     R2, #0x44
	STR     R2, [R3]


// looks like idle cycle is required for proper shutdown
	MOV     R3, #0x8000
wait1:
	SUB	R3, R3, #1
	CMP	R3, #0
	BNE	wait1

// LED off
	LDR     R3, =0xc0220084
	MOV     R2, #0x44
	STR     R2, [R3]

	MOV     SP, #0x1900
	MOV     R11, #0
	B	my_restart

.fill 8,4,0
