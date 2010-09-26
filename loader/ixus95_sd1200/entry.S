    .section .entry

// Turn OFF SD Card power
// to support autostart
// not known if needed on this cam
	LDR     R3, =0xC0220018 // sub_FFC40150 near  task_SD1stInit
	MOV     R2, #0x44
	STR     R2, [R3]

// idle cycle
	MOV     R3, #0x8000
1:
	SUB	R3, R3, #1
	CMP	R3, #0
	BNE	1b

// ordinary startup...

	MOV     SP, #0x1900
	MOV     R11, #0
	B	my_restart
