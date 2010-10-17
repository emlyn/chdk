int kbd_is_blocked();

// Extracted method: task_TouchW (FF8E6DC0-FF8E6DF8)
// Overridden calls:
void __attribute__((naked,noinline)) task_TouchW_my() {
    asm volatile (
        "     STMFD   SP!, {R4-R6,LR}\n"
        "     BL         sub_FF8E79C4\n"
        "     LDR     R5, =0xFFAA0D8C\n"    // off_FFAA0D8C
        "     LDR     R4, =0x9C10\n"

    "loc_FF8E6DD0:\n"    // CODE XREF: task_TouchW+38
        "     LDR     R0, [R4,#0x1C]\n"
        "     MOV     R3, #0x1D0\n"
        "     LDR     R2, =0xFF8E6FE0\n"    // aTouchwheel_c = "TouchWheel.c"
        "     MOV     R1, #0\n"
        "     BL         sub_FF81BF78\n"
        "     LDR     R0, [R4,#0x24]\n"
        "     LDR     R1, [R4,#0x28]\n"
	
		"     MOV     R2, R0\n"
		"     BL      kbd_is_blocked\n"
		"     CMP     R0, #0\n"
		"     MOV     R0, R2\n"
		"     BEQ     bypass_skip_touch\n"

		// if kbd is blocked, skip touch events (jump table entry 9, sub_FF8E71F4)
		"     CMP     R0, #2\n"
		"     CMPEQ   R1, #1\n"
        "     BEQ     loc_FF8E6DD0\n"

	"bypass_skip_touch:\n"
        "     ADD     R0, R5, R0,LSL#4\n"   // *16
        "     LDR     R0, [R0,R1,LSL#2]\n"  // *4
    ".long   0xE12FFF30\n"    // 	     BLX     R0
        "     B         loc_FF8E6DD0\n"
    );
}

// Extracted method: taskcreate_TouchW (FF8E6DFC-FF8E6ED8)
// Overridden calls:
//     task_TouchW
void __attribute__((naked,noinline)) taskcreate_TouchW_my() {
    asm volatile (

    "var_10         = -0x10\n"

        "     STMFD   SP!, {R3-R5,LR}\n"
        "     LDR     R4, =0x9C10\n"
        "     LDR     R1, [R4,#8]\n"
        "     CMP     R1, #1\n"
        "     BEQ     locret_FF8E6ED8\n"
        "     LDRB    R1, [R0]\n"
        "     ADD     R3, R4, #0x50\n"
        "     MOV     R5, #1\n"
        "     STRB    R1, [R3]\n"
        "     LDRB    R1, [R0,#1]\n"
        "     STRB    R1, [R3,#1]\n"
        "     LDRB    R1, [R0,#2]\n"
        "     STRB    R1, [R3,#2]\n"
        "     LDRB    R2, [R0,#3]\n"
        "     MOV     R1, #4\n"
        "     STRB    R2, [R3,#3]\n"
        "     LDRB    R0, [R0,#4]\n"
        "     STRB    R0, [R3,#4]\n"
        "     MOV     R0, #0\n"
        "     STR     R0, [R4,#0x20]\n"

    "loc_FF8E6E4C:\n"    // CODE XREF: taskcreate_TouchW+68
        "     LDRB    R0, [R3,R1]\n"
        "     LDR     R2, [R4,#0x20]\n"
        "     SUBS    R1, R1, #1\n"
        "     AND     R0, R0, #0x1F\n"
        "     ORR     R0, R2, R5,LSL R0\n"
        "     STR     R0, [R4,#0x20]\n"
        "     BPL     loc_FF8E6E4C\n"
        "     LDR     R1, =0xFFAA0D5C\n"    // unk_FFAA0D5C
        "     LDR     R0, =0x429B8\n"
        "     LDMIA   R1, {R2,R3,R12}\n"
        "     STMIA   R0, {R2,R3,R12}\n"
        "     LDR     R1, =0xFFAA0D68\n"    // unk_FFAA0D68
        "     LDR     R0, =0x429C4\n"
        "     LDMIA   R1, {R2,R3,R12}\n"
        "     STMIA   R0, {R2,R3,R12}\n"
        "     LDR     R1, =0xFFAA0D74\n"    // unk_FFAA0D74
        "     LDR     R0, =0x429D0\n"
        "     LDMIA   R1, {R2,R3,R12}\n"
        "     STMIA   R0, {R2,R3,R12}\n"
        "     LDR     R1, =0xFFAA0D50\n"    // unk_FFAA0D50
        "     LDR     R0, =0x429DC\n"
        "     LDMIA   R1, {R2,R3,R12}\n"
        "     STMIA   R0, {R2,R3,R12}\n"
        "     LDR     R1, =0xFFAA0D80\n"    // unk_FFAA0D80
        "     LDR     R0, =0x429E8\n"
        "     LDMIA   R1, {R2,R3,R12}\n"
        "     STMIA   R0, {R2,R3,R12}\n"
        "     MOV     R3, #0\n"
        "     STR     R3, [SP,#0x10+var_10]\n"
        "     ADR     R3, task_TouchW_my\n"    //   --------------->
        "     MOV     R2, #0x800\n"
        "     LDR     R0, =0xFF8E7018\n"    // aTouchw = "TouchW"
        "     MOV     R1, #0x17\n"
        "     BL         _KernelCreateTask\n"
        "     STR     R5, [R4,#8]\n"

    "locret_FF8E6ED8:\n"    // CODE XREF: taskcreate_TouchW+10
        "     LDMFD   SP!, {R3-R5,PC}\n"
    );
}

// Extracted method: calls_taskcreate_TouchW (FF843EF4-FF843F58)
// Overridden calls:
//     taskcreate_TouchW
void __attribute__((naked,noinline)) calls_taskcreate_TouchW_my() {
    asm volatile (

    "var_10         = -0x10\n"
    "var_F         = -0xF\n"
    "var_E         = -0xE\n"
    "var_D         = -0xD\n"
    "var_C         = -0xC\n"

        "     STMFD   SP!, {R2-R4,LR}\n"
        "     LDR     R2, =0x12498\n"
        "     MOV     R1, #2\n"

    "loc_FF843F00:\n"    // CODE XREF: calls_taskcreate_TouchW+20
        "     LDR     R3, [R0,R1,LSL#2]\n"
        "     STR     R3, [R2,R1,LSL#2]\n"
        "     SUB     R1, R1, #1\n"
        "     MOV     R1, R1,LSL#24\n"
        "     MOVS    R1, R1,ASR#24\n"
        "     BPL     loc_FF843F00\n"
        "     BL         sub_FF8E6BF8\n"
        "     LDR     R1, =0x23E0\n"
        "     MOV     R0, #2\n"
        "     STRB    R0, [R1]\n"
        "     MOV     R0, #0x47\n"
        "     STRB    R0, [SP,#0x10+var_10]\n"
        "     MOV     R0, #0x44\n"
        "     STRB    R0, [SP,#0x10+var_F]\n"
        "     MOV     R0, #0x46\n"
        "     STRB    R0, [SP,#0x10+var_E]\n"
        "     MOV     R0, #0x45\n"
        "     STRB    R0, [SP,#0x10+var_D]\n"
        "     MOV     R0, #0x48\n"
        "     STRB    R0, [SP,#0x10+var_C]\n"
        "     MOV     R0, SP\n"
        "     BL         taskcreate_TouchW_my\n"    //   --------------->
        "     LDMFD   SP!, {R2-R4,PC}\n"
    );
}

// Extracted method: calls_calls_taskcreate_TouchW (FF82292C-FF822A18)
// Overridden calls:
//     calls_taskcreate_TouchW
void __attribute__((naked,noinline)) calls_calls_taskcreate_TouchW_my() {
    asm volatile (

    "var_6C         = -0x6C\n"

        "     STMFD   SP!, {R4,R5,LR}\n"
        "     LDR     R4, =0x1C98\n"
        "     SUB     SP, SP, #0x64\n"
        "     LDR     R0, [R4,#0xC]\n"
        "     CMP     R0, #1\n"
        "     BEQ     loc_FF822A14\n"
        "     LDR     R2, =0x113F0\n"
        "     SUB     R1, R2, #0xC\n"
        "     SUB     R0, R2, #0x18\n"
        "     BL         sub_FF843B6C\n"
        "     BL         sub_FF8443D8\n"
        "     BL         _kbd_read_keys\n"
        "     LDR     R1, =0x113FC\n"
        "     MOV     R0, #2\n"
        "     SUB     R2, R1, #0x18\n"
        "     ADD     R3, R2, #0xC\n"
        "     ADD     R5, R3, #0x18\n"

    "loc_FF822970:\n"    // CODE XREF: calls_calls_taskcreate_TouchW+60
        "     LDR     R12, [R1,R0,LSL#2]\n"
        "     LDR     LR, [R2,R0,LSL#2]\n"
        "     AND     R12, R12, LR\n"
        "     LDR     LR, [R3,R0,LSL#2]\n"
        "     EOR     R12, R12, LR\n"
        "     STR     R12, [R5,R0,LSL#2]\n"
        "     SUBS    R0, R0, #1\n"
        "     BPL     loc_FF822970\n"
        "     LDR     R0, =0x11408\n"
        "     BL         calls_taskcreate_TouchW_my\n"    //   --------------->
        "     LDR     R2, =0x1CAC\n"
        "     LDR     R0, =0x11408\n"
        "     ADD     R1, SP, #0x70+var_6C\n"
        "     BL         sub_FF844124\n"
        "     MOV     R1, R0\n"
        "     ADD     R0, SP, #0x70+var_6C\n"
        "     BL         sub_FF86CAF0\n"
        "     LDR     R0, =0x11420\n"
        "     BL         sub_FF843CF8\n"
        "     LDR     R12, =0x11420\n"
        "     MOV     R0, #2\n"
        "     MOV     LR, R5\n"

    "loc_FF8229C8:\n"    // CODE XREF: calls_calls_taskcreate_TouchW+DC
        "     LDR     R2, [LR,R0,LSL#2]\n"
        "     MOV     R1, #2\n"

    "loc_FF8229D0:\n"    // CODE XREF: calls_calls_taskcreate_TouchW+B8
        "     ADD     R3, R1, R1,LSL#1\n"
        "     ADD     R3, R12, R3,LSL#2\n"
        "     ADD     R3, R3, R0,LSL#2\n"
        "     SUBS    R1, R1, #1\n"
        "     STR     R2, [R3,#0xC]\n"
        "     BPL     loc_FF8229D0\n"
        "     MOV     R1, #0\n"

    "loc_FF8229EC:\n"    // CODE XREF: calls_calls_taskcreate_TouchW+D4
        "     RSB     R3, R1, R1,LSL#3\n"
        "     ADD     R3, R12, R3,LSL#2\n"
        "     ADD     R3, R3, R0,LSL#2\n"
        "     SUBS    R1, R1, #1\n"
        "     STR     R2, [R3,#0x44]\n"
        "     BPL     loc_FF8229EC\n"
        "     SUBS    R0, R0, #1\n"
        "     BPL     loc_FF8229C8\n"
        "     MOV     R0, #1\n"
        "     STR     R0, [R4,#0xC]\n"

    "loc_FF822A14:\n"    // CODE XREF: calls_calls_taskcreate_TouchW+14
        "     ADD     SP, SP, #0x64\n"
        "     LDMFD   SP!, {R4,R5,PC}\n"
    );
}

// Extracted method: sub_FF82BCAC (FF82BCAC-FF82BD20)
// Overridden calls:
//     calls_calls_taskcreate_TouchW
void __attribute__((naked,noinline)) sub_FF82BCAC_my() {
    asm volatile (
        "     STMFD   SP!, {R4,LR}\n"
        "     MOV     R1, #4\n"
        "     MOV     R0, #2\n"
        "     BL         _taskcreate_WdtReset\n"
        "     BL         sub_FF868080\n"    // StartWDT
        "     BL         _EventProcedure\n"
        "     BL         sub_FF86376C\n"
        "     BL         sub_FF840AF8\n"
        "     BL         sub_FF8684DC\n"
        "     LDR     R2, =0x12CEA600\n"
        "     LDR     R1, =0x7FE8177F\n"
        "     BL         sub_FF829624\n"
        "     BL         sub_FF842BAC\n"
        "     BL         calls_calls_taskcreate_TouchW_my\n"    //   --------------->
        "     BL         sub_FF847CBC\n"
        "     BL         sub_FF847600\n"
        "     MOV     R0, #1\n"
        "     BL         _taskcreate_AudioTsk\n"
        "     BL         sub_FF83F560\n"
        "     BL         sub_FF837628\n"
        "     BL         sub_FF842244\n"
        "     BL         sub_FF842230\n"
        "     BL         sub_FF841FF4\n"
        "     BL         sub_FF8422FC\n"
        "     BL         _taskcreate_Thermometer\n"
        "     BL         sub_FF854428\n"
        "     BL         _taskcreate_LEDCon\n"
        "     BL         sub_FF86910C\n"
        "     LDMFD   SP!, {R4,LR}\n"
        "     B         sub_FF82BC90\n"
    );
}
