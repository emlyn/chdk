// Multiple Partition support, used if CAM_MULTIPART enabled

// ROM:FF9D32AC
void __attribute__((naked,noinline)) init_file_modules_task() {
    asm volatile(
            "STMFD   SP!, {R4,LR}\n"

            "BL      _Unmount_FileSystem\n"   // +

            "BL      sub_FFB3B500\n"
            "SUBS    R4, R0, #0\n"
            "MOV     R0, #0x5000\n"
            "MOV     R1, #0\n"
            "ADD     R0, R0, #6\n"
            "BEQ     loc_FF9D32CC\n"
            "BL      sub_FF9A42AC\n"   // PostLogicalEventToUI
        "loc_FF9D32CC:\n"

            //"BL      sub_FFB3B52C\n"   // orginal
            "BL      sub_FFB3B52C_my\n"   // + --->

            "MOV     R0, #0x5000\n"
            "CMP     R4, #0\n"
            "MOV     R1, R4\n"
            "ADD     R0, R0, #6\n"
            "LDMNEFD SP!, {R4,PC}\n"
            "LDMFD   SP!, {R4,LR}\n"
    );

    //debug_led(1);   // DEBUG help (check if code gets executed)

    asm volatile(
            "B       sub_FF9A42AC\n"   // PostLogicalEventToUI
    );
}

// ROM:FFB3B52C
void __attribute__((naked,noinline)) sub_FFB3B52C_my() {
    asm volatile(
            "STR     LR, [SP,#-4]!\n"

            //"BL      Mount_FileSystem\n"   // orginal
            "BL      Mount_FileSystem_my\n"   // +

            "LDR     R3, =0xBDDC\n"
            "LDR     R2, [R3]\n"
            "CMP     R2, #0\n"
            "BNE     loc_FFB3B568\n"
            "BL      sub_FF9F5044\n"
            "AND     R0, R0, #0xFF\n"
            "BL      sub_FF835A3C\n"
            "BL      sub_FF9F5044\n"
            "AND     R0, R0, #0xFF\n"
            "BL      sub_FF86F738\n"
            "BL      sub_FF9F5054\n"
            "AND     R0, R0, #0xFF\n"
            "BL      sub_FF835B18\n"
        "loc_FFB3B568:\n"
            "LDR     R2, =0xBDD8\n"
            "MOV     R3, #1\n"
            "STR     R3, [R2]\n"
            "LDR     PC, [SP],#4\n"
    );
}

// ROM:FF87A8AC
void __attribute__((naked,noinline)) Mount_FileSystem_my() {
    asm volatile(
            "STMFD   SP!, {R4-R6,LR}\n"
            "MOV     R5, #0\n"
            "LDR     R6, =0x2DA00\n"
            "MOV     R0, R5\n"
            "BL      sub_FF87A294\n"
            "LDR     R0, [R6,#0x38]\n"
            "BL      sub_FF879954\n"
            "SUBS    R1, R0, #0\n"
            "MOV     R0, R5\n"
            "BNE     loc_FF87A8EC\n"
            "LDR     R3, =0x27EC\n"
            "LDR     R2, =0x27E4\n"
            "STR     R1, [R3]\n"
            "LDR     R3, =0x27E8\n"
            "STR     R1, [R2]\n"
            "STR     R1, [R3]\n"
        "loc_FF87A8EC:\n"
            "BL      sub_FF87A2E4\n"
            "MOV     R0, R5\n"

            //"BL      sub_FF87A60C\n"   // orginal
            "BL      sub_FF87A60C_my\n"   // + --->

            "MOV     R4, R0\n"
            "MOV     R0, R5\n"
            "BL      sub_FF87A694\n"   // Mounter.c:808
            "AND     R4, R4, R0\n"
            "MOV     R2, R4\n"
            "MOV     R0, R6\n"
            "LDR     R1, [R6,#0x3C]\n"
            "BL      sub_FF87A85C\n"
            "STR     R0, [R6,#0x40]\n"
            "LDMFD   SP!, {R4-R6,PC}\n"
    );
}

// ROM:FF87A60C
void __attribute__((naked,noinline)) sub_FF87A60C_my() {
    asm volatile(
            "STMFD   SP!, {R4-R7,LR}\n"
            "LDR     R7, =0x27E8\n"
            "LDR     R3, [R7]\n"
            "MOV     R4, R0\n"
            "CMP     R3, #0\n"
            "ADD     R3, R4, R4,LSL#1\n"
            "RSB     R3, R4, R3,LSL#3\n"
            "LDR     R6, =0x2DA38\n"
            "MOV     R5, R3,LSL#2\n"
            "MOV     R1, R4\n"

            //"BNE     loc_FF87A680\n"   // gcc: loc_FF87A680 not found
            "BNE     sub_FF87A680\n"   // +

            "LDR     R0, [R6,R5]\n"

            //"BL      sub_FF87A3A0\n"   // orginal, Mounter.c:692
            "BL      sub_FF87A3A0_my\n"   // + --->

            "SUBS    R3, R0, #0\n"
            "MOV     R1, R4\n"
            "BEQ     loc_FF87A658\n"
            "LDR     R0, [R6,R5]\n"
            "BL      sub_FF87A4EC\n"   // Mounter.c:728
            "MOV     R3, R0\n"
        "loc_FF87A658:\n"
            "CMP     R3, #0\n"
            "MOV     R0, R4\n"
            "BEQ     loc_FF87A66C\n"
            "BL      sub_FF879A2C\n"
            "MOV     R3, R0\n"
        "loc_FF87A66C:\n"
            "CMP     R3, #0\n"
            "MOV     R0, R3\n"
            "MOVNE   R3, #1\n"
            "STRNE   R3, [R7]\n"
            "LDMFD   SP!, {R4-R7,PC}\n"
        "loc_FF87A680:\n"
            "MOV     R0, #1\n"
            "LDMFD   SP!, {R4-R7,PC}\n"
    );
}

// ROM:FF87A3A0
void __attribute__((naked,noinline)) sub_FF87A3A0_my() {
    asm volatile(
            "STMFD   SP!, {R4-R8,LR}\n"
            "MOV     R5, R1\n"
            "MOV     R8, R5,LSL#1\n"
            "ADD     R3, R8, R5\n"
            "LDR     R2, =0x2DA3C\n"
            "SUB     SP, SP, #8\n"
            "RSB     R3, R5, R3,LSL#3\n"
            "LDR     R1, [R2,R3,LSL#2]\n"
            "MOV     R6, #0\n"
            "STR     R6, [SP]\n"
            "MOV     R7, R0\n"
            "STR     R6, [SP,#4]\n"
            "CMP     R1, #5\n"
            "LDRLS   PC, [PC,R1,LSL#2]\n"
            "B       loc_FF87A49C\n"
            ".long loc_FF87A440\n"
            ".long loc_FF87A3F4\n"
            ".long loc_FF87A3F4\n"
            ".long loc_FF87A3F4\n"
            ".long loc_FF87A3F4\n"
            ".long loc_FF87A48C\n"
        "loc_FF87A3F4:\n"
            "MOV     R0, #3\n"
            "MOV     R1, #0x200\n"
            "MOV     R2, #0\n"
            "BL      sub_FF812834\n"
            "SUBS    R6, R0, #0\n"

            //"BEQ     loc_FF87A4D0\n"   // gcc: loc_FF87A4D0 not found
            "BEQ     sub_FF87A4D0\n"   // +

            "ADD     R12, R8, R5\n"
            "RSB     R12, R5, R12,LSL#3\n"
            "LDR     R4, =0x2DA4C\n"
            "MOV     R0, R7\n"
            "MOV     R1, #0\n"
            "MOV     R2, #1\n"
            "MOV     R3, R6\n"
            "MOV     LR, PC\n"
            "LDR     PC, [R4,R12,LSL#2]\n"
            "CMP     R0, #1\n"
            "BNE     loc_FF87A448\n"
            "MOV     R0, #3\n"
            "BL      sub_FF812904\n"
        "loc_FF87A440:\n"
            "MOV     R0, #0\n"

            //"B       loc_FF87A4D0\n"   // original
            "B       sub_FF87A4D0\n"   // +

        "loc_FF87A448:\n"
            "MOV     R0, R7\n"
            "BL      sub_FF88AD88\n"
            "MOV     R1, R0\n"
            "ADD     R2, SP, #4\n"
            "MOV     R3, SP\n"
            "MOV     R0, R6\n"

            //"BL      sub_FF879B30\n"   // original
            "STMFD   SP!, {R4-R11,LR}\n"   // + save registers to stack
            "BL      mbr_read\n"    // + --->
            "LDMFD   SP!, {R4-R11,LR}\n"   // + restore registers from stack

            "MOV     R4, R0\n"
            "MOV     R0, #3\n"
            "BL      sub_FF812904\n"
            "CMP     R4, #0\n"
            "BNE     loc_FF87A4A8\n"
            "MOV     R0, R7\n"
            "STR     R4, [SP,#4]\n"
            "BL      sub_FF88AD88\n"
            "STR     R0, [SP]\n"
            "B       loc_FF87A4A8\n"
        "loc_FF87A48C:\n"
            "MOV     R3, #0\n"
            "MOV     R2, #0x40\n"
            "STMEA   SP, {R2,R3}\n"
            "B       loc_FF87A4A8\n"
        "loc_FF87A49C:\n"
            "LDR     R0, =0xFF879010\n"   // aMounter_c (default)
            "MOV     R1, #0x2B4\n"
            "BL      sub_FF813D70\n"   // DebugAssert
        "loc_FF87A4A8:\n"
            "LDR     R2, =0x2DA00\n"
            "ADD     R3, R8, R5\n"
            "LDMFD   SP, {R0,R12}\n"
            "RSB     R3, R5, R3,LSL#3\n"
            "MOV     R3, R3,LSL#2\n"
            "ADD     R1, R2, #0x48\n"
            "ADD     R2, R2, #0x44\n"
            "STR     R0, [R1,R3]\n"
            "STR     R12, [R2,R3]\n"
            "MOV     R0, #1\n"
        "loc_FF879358:\n"
            "ADD     SP, SP, #8\n"
            "LDMFD   SP!, {R4-R8,PC}\n"
    );
}
