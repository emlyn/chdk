void __attribute__((naked,noinline)) init_file_modules_task(){
 asm volatile(
                "STMFD   SP!, {R4,LR}\n"
                "BL      _Unmount_FileSystem\n" // + 
                "BL      sub_FFAB1DA0\n"
                "SUBS    R4, R0, #0\n"
                "MOV     R0, #0x5000\n"
                "MOV     R1, #0\n"
                "ADD     R0, R0, #6\n"
                "BEQ     loc_FF987E88\n"
                "BL      sub_FF95C608\n"
"loc_FF987E88:\n"
                "BL      sub_FFAB1DC8_my\n"    //------------>
                "MOV     R0, #0x5000\n"
                "CMP     R4, #0\n"
                "MOV     R1, R4\n"
                "ADD     R0, R0, #6\n"
                "LDMNEFD SP!, {R4,PC}\n"
                "LDMFD   SP!, {R4,LR}\n"
                "B       sub_FF95C608\n"
 );
}

void __attribute__((naked,noinline)) sub_FFAB1DC8_my(){
//void __attribute__((naked,noinline)) sub_FFAB1A40_my(){
 asm volatile(
                "STR     LR, [SP,#-4]!\n"
                "BL      Mount_FileSystem_my\n"  //-------------->
				"B		sub_FFAB1DD0\n"
 );
}

void __attribute__((naked,noinline)) Mount_FileSystem_my(){
 asm volatile(
                 "STMFD   SP!, {R4-R6,LR}\n"
                 "MOV     R5, #0\n"
                 "LDR     R6, =0x2DF40\n"
                 "MOV     R0, R5\n"
                 "BL      sub_FF86E7FC\n"
                 "LDR     R0, [R6,#0x38]\n"
                 "BL      sub_FF86DEEC\n"
                 "SUBS    R1, R0, #0\n"
                 "MOV     R0, R5\n"
                 "BNE     loc_FF86EE04\n"
                 "LDR     R3, =0x2864\n"
                 "LDR     R2, =0x285C\n"
                 "STR     R1, [R3]\n"
                 "LDR     R3, =0x2860\n"
                 "STR     R1, [R2]\n"
                 "STR     R1, [R3]\n"

"loc_FF86EE04:\n"
                 "BL      sub_FF86E84C\n"
                 "MOV     R0, R5\n"
                 "BL      sub_FF86EB74_my\n" // ------>
                 "MOV     R4, R0\n"
                 "MOV     R0, R5\n"
                 "BL      sub_FF86EBFC\n"
                 "AND     R4, R4, R0\n"
                 "MOV     R2, R4\n"
                 "MOV     R0, R6\n"
                 "LDR     R1, [R6,#0x3C]\n"
                 "BL      sub_FF86ED74\n"
                 "STR     R0, [R6,#0x40]\n"
                 "LDMFD   SP!, {R4-R6,PC}\n"
);
}

void __attribute__((naked,noinline)) sub_FF86EB74_my(){
//void __attribute__((naked,noinline)) sub_FF86E7EC_my(){
 asm volatile(
                 "STMFD   SP!, {R4-R7,LR}\n"
                 "LDR     R7, =0x2860\n"
                 "LDR     R3, [R7]\n"
                 "MOV     R4, R0\n"
                 "CMP     R3, #0\n"
                 "ADD     R3, R4, R4,LSL#1\n"
                 "RSB     R3, R4, R3,LSL#3\n"
                 "LDR     R6, =0x2DF78\n"
                 "MOV     R5, R3,LSL#2\n"
                 "MOV     R1, R4\n"
                 "BNE     loc_FF86EBE8\n"
                 "LDR     R0, [R6,R5]\n"
                 "BL      sub_FF86E904_my\n"
                 "SUBS    R3, R0, #0\n"
                 "MOV     R1, R4\n"
                 "BEQ     loc_FF86EBC0\n"
                 "LDR     R0, [R6,R5]\n"
                 "BL      sub_FF86EA54\n"
                 "MOV     R3, R0\n"

"loc_FF86EBC0:                        \n"
                 "CMP     R3, #0\n"
                 "MOV     R0, R4\n"
                 "BEQ     loc_FF86EBD4\n"
                 "BL      sub_FF86DFC4\n"
                 "MOV     R3, R0\n"
"loc_FF86EBD4:                        \n"
                 "CMP     R3, #0\n"
                 "MOV     R0, R3\n"
                 "MOVNE   R3, #1\n"
                 "STRNE   R3, [R7]\n"
                 "LDMFD   SP!, {R4-R7,PC}\n"
 
"loc_FF86EBE8:  \n"
                 "MOV     R0, #1\n"
                 "LDMFD   SP!, {R4-R7,PC}\n"
);
}

void __attribute__((naked,noinline)) sub_FF86E904_my(){
//void __attribute__((naked,noinline)) sub_FF86E57C_my(){
 asm volatile(
                 "STMFD   SP!, {R4-R8,LR}\n"
                 "MOV     R5, R1\n"
                 "MOV     R8, R5,LSL#1\n"
                 "ADD     R3, R8, R5\n"
                 "LDR     R2, =0x2DF7C\n"
                 "SUB     SP, SP, #8\n"
                 "RSB     R3, R5, R3,LSL#3\n"
                 "LDR     R1, [R2,R3,LSL#2]\n"
                 "MOV     R6, #0\n"
                 "STR     R6, [SP]\n"
                 "MOV     R7, R0\n"
                 "STR     R6, [SP,#0x4]\n"
                 "CMP     R1, #5          \n"
                 "LDRLS   PC, [PC,R1,LSL#2] \n"
                 "B       loc_FF86EA00    \n"
 
                 ".long loc_FF86E9A4        \n"
                 ".long loc_FF86E958\n"
                 ".long loc_FF86E958\n"
                 ".long loc_FF86E958\n"
                 ".long loc_FF86E958\n"
                 ".long loc_FF86E9F0\n"
 

"loc_FF86E958:                            \n"
                                         
                 "MOV     R0, #3          \n"
                 "MOV     R1, #0x200\n"
                 "MOV     R2, #0\n"
                 "BL      sub_FF81295C\n" //AllocateExMem
                 "SUBS    R6, R0, #0\n"
                 "BEQ     loc_FF86EA38\n"
                 "ADD     R12, R8, R5\n"
                 "RSB     R12, R5, R12,LSL#3\n"
                 "LDR     R4, =0x2DF8C\n"
                 "MOV     R0, R7\n"
                 "MOV     R1, #0\n"
                 "MOV     R2, #1\n"
                 "MOV     R3, R6\n"
                 "MOV     LR, PC\n"
                 "LDR     PC, [R4,R12,LSL#2]\n"
                 "CMP     R0, #1\n"
                 "BNE     loc_FF86E9AC\n"
                 "MOV     R0, #3\n"
                 "BL      sub_FF8129A8\n" //FreeExMem\n"

"loc_FF86E9A4:                            \n"
                                         
                 "MOV     R0, #0          \n"
                 "B       loc_FF86EA38\n"
 

"loc_FF86E9AC:                            \n"
                 "MOV     R0, R7\n"
                 "BL      sub_FF87F0C0\n"
                 "MOV     R1, R0\n"
                 "ADD     R2, SP, #0x4\n"
                 "MOV     R3, SP\n"
                 "MOV     R0, R6\n"
                "STMFD   SP!, {R4-R11,LR}\n" // +
                "BL      mbr_read\n"    //-----------> 
                "LDMFD   SP!, {R4-R11,LR}\n" // +
//                 "BL      sub_FF86DD40\n"
                 "MOV     R4, R0\n"
                 "MOV     R0, #3\n"
				 "BL      sub_FF8129A8\n" //FreeExMem\n"
                 "CMP     R4, #0\n"
                 "BNE     loc_FF86EA10\n"
                 "MOV     R0, R7\n"
                 "STR     R4, [SP,#0x4]\n"
                 "BL      sub_FF87F0C0\n"
                 "STR     R0, [SP]\n"
                 "B       loc_FF86EA10\n"
 

"loc_FF86E9F0:                            \n"
                                         
                 "MOV     R3, #0          \n"
                 "MOV     R2, #0x40\n"
                 "STMEA   SP, {R2,R3}\n"
                 "B       loc_FF86EA10\n"
 

"loc_FF86EA00:                            \n"
                 "MOV     R1, #0x284      \n"
                 "LDR     R0, =0xFF86E6D4\n" //aMounter_c\n"
                 "ADD     R1, R1, #2\n"
                 "BL      sub_FF813BFC\n" //DebugAssert\n"

"loc_FF86EA10:                            \n"
                                         
                 "LDR     R2, =0x2DF40\n"
                 "ADD     R3, R8, R5\n"
                 "LDMFD   SP, {R0,R12}\n"
                 "RSB     R3, R5, R3,LSL#3\n"
                 "MOV     R3, R3,LSL#2\n"
                 "ADD     R1, R2, #0x48\n"
                 "ADD     R2, R2, #0x44\n"
                 "STR     R0, [R1,R3]\n"
                 "STR     R12, [R2,R3]\n"
                 "MOV     R0, #1\n"

"loc_FF86EA38:                            \n"
                                         
                 "ADD     SP, SP, #8\n"
                 "LDMFD   SP!, {R4-R8,PC}\n"

);
}

