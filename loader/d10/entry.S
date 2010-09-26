    .section .entry

// SD card off stuff doesn't appear to be needed

// ordinary startup...

	MOV     SP, #0x1900
	MOV     R11, #0
	B	my_restart
