.text
// function name changed to support DNG double buffering (when there are two RAW buffers)
.global reverse_bytes_order2
// void reverse_bytes_order2(char* from, char*to, int count)
// quickly reverse the order of a large number of bytes
// NOTE we will go to count rounded up to the nearest 32
reverse_bytes_order2:
	STMFD   SP!, {R4-R12,LR}
	ldr	r12, =0xFF00FF		// r12 = mask, r0 = from, r1 = to, r2 = count
loop:
	ldmia	r0!, {r4-r11}		// load 8 words and increment
	
	// out = ((in>>8) & 0xFF00FF) | ((in&0xFF00FF) << 8);
	and	r3, r12, r4, lsr #8		// r3 = 0xFF00FF & (in >> 8)
	and	r4, r4, r12				// r4 = in & 0xFF00FF
	orr	r4, r3, r4, asl #8		// out = r3 | (r4 << 8)

	and	r3, r12, r5, lsr #8
	and	r5, r5, r12
	orr	r5, r3, r5, asl #8

	and	r3, r12, r6, lsr #8
	and	r6, r6, r12
	orr	r6, r3, r6, asl #8

	and	r3, r12, r7, lsr #8
	and	r7, r7, r12
	orr	r7, r3, r7, asl #8

	and	r3, r12, r8, lsr #8
	and	r8, r8, r12
	orr	r8, r3, r8, asl #8

	and	r3, r12, r9, lsr #8
	and	r9, r9, r12
	orr	r9, r3, r9, asl #8

	and	r3, r12, r10, lsr #8
	and	r10, r10, r12
	orr	r10, r3, r10, asl #8

	and	r3, r12, r11, lsr #8
	and	r11, r11, r12
	orr	r11, r3, r11, asl #8

	stmia	r1!, {r4-r11}	// store and increment

	subs	r2, r2, #32
	bgt	loop
	LDMFD  SP!, {R4-R12,LR}
	bx lr
