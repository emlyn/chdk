    .section .entry
// Turn OFF SD Card power
// to support autostart
LDR     R3, =0xC0220018 // s95-100e @FF876F20
MOV     R2, #0x44
STR     R2, [R3]



// af on
//LDR     R3, =0xC0223030
//MOV     R2, #0x46
//STR     R2, [R3]



// looks like idle cycle is required for proper shutdown
MOV     R3, #0xF0000   // increased from 8000 to F0000 for extra delay
1:
SUB R3, R3, #1
CMP R3, #0
BNE 1b

// ordinary startup...

	MOV     SP, #0x1900
	MOV     R11, #0
	B	my_restart
