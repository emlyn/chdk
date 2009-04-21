    .section .entry

// Turn OFF SD Card power
// to support autostart
//	LDR     R3, =0xC0220048
	LDR     R3, =0xC0220018 // sd990: from sub_FFFF1390, also ref SdPower.c
	MOV     R2, #0x44
	STR     R2, [R3]

// looks like idle cycle is required for proper shutdown
	MOV     R3, #0x8000
1:
	SUB	R3, R3, #1
	CMP	R3, #0
	BNE	1b

// ordinary startup...

	MOV     SP, #0x1900
	MOV     R11, #0
	B	my_restart
