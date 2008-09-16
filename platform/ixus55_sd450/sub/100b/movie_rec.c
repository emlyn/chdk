#include "conf.h"

int *video_quality = &conf.video_quality;
int *video_mode    = &conf.video_mode;

long def_table1[56]={
0x10000,0xC000,0x5800, 0x2000, 0x1C6A, 0x1550,0x9C5,  0x38D,  0x3C45, 0x2D34, 0x14B8, 0x788,  0x5F60, 0x4788,
0x20C9, 0xBE1, 0x8661, 0x64C9, 0x2E31, 0x10CB,0xB21A, 0x8594, 0x3D39, 0x1642, 0xE249, 0xA9B8, 0x4DC9, 0x1C48,
0x117D2,0xD1DF,0x6030, 0x22F9, 0x153D5,0xFEE1,0x74D1, 0x2A79, 0x195F8,0x1307C,0x8B8D, 0x32AA, 0x1E01C,0x16817,
0xA509, 0x3C01,0x2328E,0x1A5ED,0xC160, 0x4637,0x28C99,0x1E975,0xE054, 0x5190, 0x2F08B,0x2346B,0x102AF,0x5E0E
};

long def_table2[12]={0xE666,0xACCD,0x4F33,0x1CCD,-0x170A,-0x1148,-0x7EB,-0x2E1,-0x2BC6,-0x20D5,-0xF0C,-0x579};

long table1[56], table2[12];

void change_video_tables(int a, int b){
 int i;
 for (i=0;i<56;i++) table1[i]=(def_table1[i]*a)/b;
 for (i=0;i<12;i++) table2[i]=(def_table2[i]*a)/b;
}

long CompressionRateTable[]={0x60, 0x5D, 0x5A, 0x57, 0x54, 0x51, 0x4D, 0x48, 0x42, 0x3B, 0x32, 0x29, 0x22, 0x1D, 0x17, 0x14, 0x10, 0xE, 0xB, 9, 7, 6, 5, 4, 3, 2, 1};


void __attribute__((naked,noinline)) movie_record_task(){
 asm volatile(
                "STMFD   SP!, {R4,LR}\n"
                "SUB     SP, SP, #4\n"
                "MOV     R4, SP\n"
                "B       loc_FF9432F4\n"
"loc_FF943244:\n" 
                "LDR     R3, =0x7CDA0\n"
                "LDR     R2, [R3]\n"
                "CMP     R2, #0\n"
                "BNE     loc_FF9432E0\n"  
                "SUB     R3, R12, #1\n"
                "CMP     R3, #0xA\n"     
                "LDRLS   PC, [PC,R3,LSL#2]\n" 
                "B       loc_FF9432E0\n"   
                ".long loc_FF943290\n"    
                ".long loc_FF943298\n"
                ".long loc_FF9432B0\n"
                ".long loc_FF9432B8\n"
                ".long loc_FF9432C0\n"
                ".long loc_FF9432A0\n"
                ".long loc_FF9432C8\n"
                ".long loc_FF9432A8\n"
                ".long loc_FF9432E0\n"
                ".long loc_FF9432D8\n"
                ".long loc_FF9432D0\n"
"loc_FF943290:\n"                      
                "BL      sub_FF943374\n"    
                "B       loc_FF9432DC\n"
"loc_FF943298:\n"
                "BL      unlock_optical_zoom\n"  
                "BL      sub_FF9435A8\n"  
                "B       loc_FF9432DC\n"
"loc_FF9432A0:\n"    
                "BL      sub_FF943A38_my\n" // redirect ---->  
                "B       loc_FF9432DC\n"
"loc_FF9432A8:\n"                       
                "BL      sub_FF943E8C\n"    
                "B       loc_FF9432DC\n"
"loc_FF9432B0:\n"                         
                "BL      sub_FF943CB0\n"  
                "B       loc_FF9432DC\n"
"loc_FF9432B8:\n"          
                "BL      sub_FF944098\n" 
                "B       loc_FF9432DC\n"
"loc_FF9432C0:\n"                   
                "BL      sub_FF94425C\n"    
                "B       loc_FF9432DC\n"
"loc_FF9432C8:\n"     
                "BL      sub_FF943F4C\n"  
                "B       loc_FF9432DC\n"
"loc_FF9432D0:\n"                            
                "BL      sub_FF94402C\n"  
                "B       loc_FF9432DC\n"
"loc_FF9432D8:\n"         
                "BL      sub_FF943D00\n"   
"loc_FF9432DC:\n"      
                "LDR     R1, [SP]\n"
"loc_FF9432E0:\n"                   
                "LDR     R3, =0x7CCD0\n"   
                "MOV     R2, #0\n"
                "STR     R2, [R1]\n"
                "LDR     R0, [R3]\n"
                "BL      sub_FF820818\n" //  PostMessageQueue
"loc_FF9432F4:\n"  
                "LDR     R3, =0x7CCCC\n"
                "MOV     R1, R4\n"
                "LDR     R0, [R3]\n"
                "MOV     R2, #0\n"
                "BL      sub_FF820400\n"  // ReceiveMessageQueue
                "LDR     R0, [SP]\n"
                "LDR     R12, [R0]\n"
                "CMP     R12, #0xC\n"
                "MOV     R1, R0\n"
                "BNE     loc_FF943244\n"
                "LDR     R3, =0x7CCC4\n"
                "LDR     R0, [R3]\n"
                "BL      sub_FF8211D4\n" // GiveSemaphore
                "BL      sub_FF82199C\n" // ExitTask
                "ADD     SP, SP, #4\n"
                "LDMFD   SP!, {R4,PC}\n"
 );
}


void __attribute__((naked,noinline)) sub_FF943A38_my(){
 asm volatile(
				"STMFD   SP!, {R4-R11,LR}\n"
                "LDR     R5, =0x7CDBC\n"
                "SUB     SP, SP, #0x34\n"
                "LDR     R3, [R5]\n"
                "CMP     R3, #3\n"
                "MOV     R4, R0\n"
                "MOVEQ   R3, #4\n"
                "STREQ   R3, [R5]\n"
                "LDR     R3, =0x7CE64\n"
                "MOV     LR, PC\n"
                "LDR     PC, [R3]\n"
                "LDR     R2, [R5]\n"
                "CMP     R2, #4\n"
                "BNE     loc_FF943BE4\n"
                "ADD     R0, SP, #0x30\n"
                "ADD     R1, SP, #0x2C\n"
                "ADD     R2, SP, #0x28\n"
                "ADD     R3, SP, #0x24\n"
                "BL      sub_FF9451F8\n"
                "CMP     R0, #0\n"
                "BNE     loc_FF943AB4\n"
                "LDR     R3, =0x7CDA8\n"
                "LDR     R2, [R3]\n"
                "CMP     R2, #1\n"
                "BNE     loc_FF943AC8\n"
                "LDR     R2, =0x7CDF8\n"
                "LDR     R1, =0x7CDD0\n"
                "LDR     R12, [R2]\n"
                "LDR     R3, [R1]\n"
                "CMP     R12, R3\n"
                "BCC     loc_FF943AC8\n"
"loc_FF943AB4:\n"       
                "BL      sub_FF943C28\n"
                "BL      sub_FF943E5C\n"
                "MOV     R3, #5\n"
                "STR     R3, [R5]\n"
                "B       loc_FF943BE4\n"
"loc_FF943AC8:\n"        
                "LDR     R12, =0x7CE00\n"
                "LDR     R11, =0x7CE0C\n"
                "LDMIB   R4, {R0-R2}\n"
                "LDR     R10, [R12]\n"
                "LDR     R7, [R11]\n"
                "LDR     R4, [SP,#0x2C]\n"
                "LDR     R5, [SP,#0x28]\n"
                "LDR     R6, [SP,#0x24]\n"
                "LDR     R8, =0x7CDAC\n"
                "LDR     R3, [SP,#0x30]\n"
                "ADD     R12, SP, #0x20\n"
                "ADD     LR, SP, #0x1C\n"
                "MOV     R9, #1\n"
                "STMEA   SP, {R4-R6,R12}\n"
                "STR     R10, [SP,#0x10]\n"
                "STR     R7, [SP,#0x14]\n"
                "STR     LR, [SP,#0x18]\n"
                "STR     R9, [R8]\n"
                "BL      sub_FF895768\n"
                "LDR     R3, =0x7CCC4\n"
                "MOV     R1, #0x3E8\n"
                "LDR     R0, [R3]\n"
                "BL      sub_FF820FEC\n"  // TakeSemaphore
                "CMP     R0, #9\n"
                "BNE     loc_FF943B3C\n"
                "BL      sub_FF9459B8\n"
                "LDR     R3, =0x7CDBC\n"
                "LDR     R0, =0xFF943a20\n"  // aJpegtimeout_2
                "B       loc_FF943B54\n"
"loc_FF943B3C:\n"       
                "LDR     R5, [SP,#0x1C]\n"
                "CMP     R5, #0\n"
                "BEQ     loc_FF943B60\n"
                "BL      sub_FF9459B8\n"
                "LDR     R3, =0x7CDBC\n"
                "LDR     R0, =0xFF943A2C\n" // aJpegicerror_3
"loc_FF943B54:\n"  
                "STR     R9, [R3]\n"
                "BL      sub_FF9578DC\n"  // HardwareDefect
                "B       loc_FF943BE4\n"
"loc_FF943B60:\n"     
                "BL      sub_FF8958DC\n"
                "LDR     R0, [SP,#0x30]\n"
                "LDR     R1, [SP,#0x20]\n"
                "BL      sub_FF9456DC\n"
                "LDR     R4, =0x7CDF8\n"
                "LDR     R3, [R4]\n"
                "ADD     R3, R3, #1\n"
                "LDR     R0, [SP,#0x20]\n"
                "MOV     R1, R11\n"
                "STR     R3, [R4]\n"
                "MOV     R2, R5\n"
                "BL      sub_FF9445C0_my\n"
                "LDR     R3, =0x7CDE4\n"
                "LDR     R4, [R4]\n"
                "LDR     R1, [R3]\n"
                "MOV     R0, R4\n"
                "BL      sub_FFAC9880\n"  // __umodsi3
                "CMP     R0, #0\n"
                "BEQ     loc_FF943BC0\n"
                "LDR     R6, =0x7CDB0\n"
                "LDR     R3, [R6]\n"
                "CMP     R3, #1\n"
                "BNE     loc_FF943BD8\n"
                "B       loc_FF943BC4\n"
"loc_FF943BC0:\n"    
                "LDR     R6, =0x7CDB0\n"
"loc_FF943BC4:\n"       
                "MOV     R0, R4\n"
                "LDR     R3, =0x7CE40\n"
                "MOV     LR, PC\n"
                "LDR     PC, [R3]\n"
                "STR     R5, [R6]\n"
"loc_FF943BD8:\n"             
                "LDR     R2, =0x7CDAC\n"
                "MOV     R3, #0\n"
                "STR     R3, [R2]\n"
"loc_FF943BE4:\n"     
                "ADD     SP, SP, #0x34\n"
                "LDMFD   SP!, {R4-R11,PC}\n"
 );
}


void __attribute__((naked,noinline)) sub_FF9445C0_my(){
 asm volatile(
                "CMP     R2, #1\n"
                "STMFD   SP!, {R4-R7,LR}\n"
                "MOV     R7, R0\n"
                "MOV     R6, R1\n"
				
            //    "MOVEQ   R3, #0x79\n"               // -
			//    "STREQ   R3, [R6]\n"                // -
                "LDREQ   R3, =CompressionRateTable\n" // +
                "LDREQ   R2, [R3,#0x18]\n"            // +
                "STREQ   R2, [R6]\n"				  // +
				
                "LDMEQFD SP!, {R4-R7,PC}\n"
                "LDR     R12, =0x7CE70\n"
                "LDR     R0, [R12]\n"
                "LDR     R3, =0x7CE78\n"
                "CMP     R0, #0\n"
                "LDR     R1, [R3]\n"
                "BEQ     loc_FF944608\n"
                "LDR     R2, =0x7CE7C\n"
                "LDR     R3, [R2]\n"
                "CMP     R3, #1\n"
                "BNE     loc_FF94461C\n"
                "B       loc_FF94460C\n"
"loc_FF944608:\n"    
                "LDR     R2, =0x7CE7C\n"
"loc_FF94460C:\n"      
                "MOV     R3, #0\n"
                "STR     R3, [R2]\n"
                "STR     R7, [R12]\n"
                "B       loc_FF9446D0\n"
"loc_FF94461C:\n"   
                "LDR     R3, =0x7CE74\n"
                "LDR     R2, [R3]\n"
                "LDR     R5, =table1\n" // + 0xFF94428
                "MOV     LR, R2,LSL#2\n"
                "LDR     R3, [R5,LR]\n"
                "LDR     R4, =table2\n" // + 0xFF944464
                "RSB     R12, R3, R0\n"
                "LDR     R2, [R4,LR]\n"
                "CMP     R12, #0\n"
                "RSB     R0, R2, R0\n"
                "BLE     loc_FF94467C\n"
                "ADD     R3, R5, #0x14\n"
                "LDR     R2, [R3,LR]\n"
                "CMP     R2, R12\n"
                "ADDGE   R1, R1, #1\n"
                "BGE     loc_FF944670\n"
                "ADD     R3, R5, #0x28\n"
                "LDR     R2, [R3,LR]\n"
                "CMP     R2, R12\n"
                "ADDGE   R1, R1, #2\n"
                "ADDLT   R1, R1, #3\n"
"loc_FF944670:\n"     
           //     "CMP     R1, #0xE\n"    // -
           //     "MOVGE   R1, #0xE\n"    // -
				"CMP     R1, #0x1A\n"    // +
                "MOVGE   R1, #0x1A\n"    // +
					   
                "B       loc_FF9446B4\n"
"loc_FF94467C:\n"       
                "CMP     R0, #0\n"
                "BGE     loc_FF9446B4\n"
                "ADD     R3, R4, #0x14\n"
                "LDR     R2, [R3,LR]\n"
                "CMP     R2, R0\n"
                "SUBLE   R1, R1, #1\n"
                "BLE     loc_FF9446AC\n"
                "ADD     R3, R4, #0x28\n"
                "LDR     R2, [R3,LR]\n"
                "CMP     R2, R0\n"
                "SUBLE   R1, R1, #2\n"
                "SUBGT   R1, R1, #3\n"
"loc_FF9446AC:\n"  
                "CMP     R1, #0\n"
                "MOVLT   R1, #0\n"
"loc_FF9446B4:\n" 
                "LDR     R0, =0x7CE78\n"
                "LDR     R3, [R0]\n"
                "CMP     R1, R3\n"
                "LDRNE   R2, =0x7CE7C\n"
                "MOVNE   R3, #1\n"
                "STRNE   R1, [R0]\n"
                "STRNE   R3, [R2]\n"
"loc_FF9446D0:\n"  
                "LDR     R3, =0x7CE78\n"
           //     "LDR     R1, =0x6CF8\n"  // -
		        "LDR     R1, =video_mode\n"  // +
                "LDR     R0, [R3]\n"
                "LDR     R2, =CompressionRateTable\n"
                "LDR     R12, [R1]\n"
                "LDR     LR, [R2,R0,LSL#2]\n"
                "LDR     R3, =0x7CE70\n"
                "CMP     R12, #1\n"
                "STR     R7, [R3]\n"
                "STR     LR, [R6]\n"
            //    "MOVEQ   R3, #0xB\n"   // -

                "LDREQ   R3, =video_quality\n"          // +
                "LDREQ   R3, [R3]\n"                    // +
                "LDREQ   R3, [R3]\n"                    // +				
				
                "STREQ   R3, [R6]\n"
                "LDMFD   SP!, {R4-R7,PC}\n"
 );
}
