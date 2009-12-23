.text
.global reverse_bytes_order
// void reverse_bytes_order(char* start, int count)
// quickly reverse the order of a large number of bytes
// NOTE we will go to count rounded up to the nearest 32
reverse_bytes_order:
	STMFD   SP!, {R4-R11,LR}
	ldr	r2, =0xFF00FF	// r2 = mask
	add	r1, r0, r1		// r1 = start + count
loop:
	ldm	r0, {R4-R11}		// load 8 words
	
	// out = ((in>>8) & 0xFF00FF) | ((in&0xFF00FF) << 8);
	mov	r3, r4, lsr #8	// r3 = in >> 8
	and	r3, r3, r2		// r3 &= 0xFF00FF
	and	r4, r4, r2		// r4 = in & 0xFF00FF
	orr	r4, r3, r4, asl #8 // out = r3 | (r4 << 8)

	mov	r3, r5, lsr #8
	and	r3, r3, r2
	and	r5, r5, r2
	orr	r5, r3, r5, asl #8

	mov	r3, r6, lsr #8
	and	r3, r3, r2
	and	r6, r6, r2
	orr	r6, r3, r6, asl #8

	mov	r3, r7, lsr #8
	and	r3, r3, r2
	and	r7, r7, r2
	orr	r7, r3, r7, asl #8

	mov	r3, r8, lsr #8
	and	r3, r3, r2
	and	r8, r8, r2
	orr	r8, r3, r8, asl #8

	mov	r3, r9, lsr #8
	and	r3, r3, r2
	and	r9, r9, r2
	orr	r9, r3, r9, asl #8

	mov	r3, r10, lsr #8
	and	r3, r3, r2
	and	r10, r10, r2
	orr	r10, r3, r10, asl #8

	mov	r3, r11, lsr #8
	and	r3, r3, r2
	and	r11, r11, r2
	orr	r11, r3, r11, asl #8

	stmia	r0!, {r4-r11}	// store and increment

	cmp	r0, r1
	bcc	loop
	LDMFD  SP!, {R4-R11,LR}
	bx lr
