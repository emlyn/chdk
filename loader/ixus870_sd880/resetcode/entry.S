	.section .entry

        // N.B.: This code silently passes arguments to copy_and_restart().
        // (See also the comment in my_restart() in ../main.c)
	MOV     SP, #0x1900
	MOV     R11, #0
	B	copy_and_restart

