    .section .entry

// SD card off stuff doesn't appear to be needed

// for testing, blink red LED 10 times at boot
/*
	LDR     R3, =0xC0220130
	MOV		R1,#10
2:
	MOV     R2, #0x46
	STR     R2, [R3]
	MOV     R0, #0x8000
1:
	SUB R0,R0,#1
	CMP R0,#0
	BNE 1b
	MOV     R2, #0x44
	STR     R2, [R3]
	MOV     R0, #0x8000
1:
	SUB R0,R0,#1
	CMP R0,#0
	BNE 1b

	SUB R1,R1,#1
	CMP R1,#0
	BNE 2b
*/
// ordinary startup...

	MOV     SP, #0x1900
	MOV     R11, #0
	B	my_restart
