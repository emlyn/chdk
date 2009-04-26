//code from sx10
//adapted to sx110

#include "conf.h"

/*void change_video_tables(int a, int b){
}


void  set_quality(int *x){ // -17 highest; +12 lowest
 if (conf.video_mode) *x=12-((conf.video_quality-1)*(12+17)/(99-1));
}

*/
int *video_quality = &conf.video_quality;
int *video_mode    = &conf.video_mode;

long def_table[24]={0x2000, 0x38D, 0x788, 0x5800, 0x9C5, 0x14B8, 0x10000, 0x1C6A, 0x3C45, 0x8000, 0xE35, 0x1E23,
           0x1CCD, -0x2E1, -0x579, 0x4F33, -0x7EB, -0xF0C, 0xE666, -0x170A, -0x2BC6, 0x7333, -0xB85, -0x15E3};

long table[24];

void change_video_tables(int a, int b){
 int i;
 for (i=0;i<24;i++) table[i]=(def_table[i]*a)/b; 
}

long CompressionRateTable[]={0x60, 0x5D, 0x5A, 0x57, 0x54, 0x51, 0x4D, 0x48, 0x42, 0x3B, 0x32, 0x29, 0x22, 0x1D, 0x17, 0x14, 0x10, 0xE, 0xB, 9, 7, 6, 5, 4, 3, 2, 1};


//JS
void __attribute__((naked,noinline)) movie_record_task(){ 
 asm volatile(
			"STMFD 	SP!, {R2-R8,LR}\n"
			"LDR 	R8, =0x332\n"
			"LDR 	R7, =0x2710\n"
			"LDR 	R4, =0x5240\n"
			"MOV 	R6, #0\n"
			"MOV 	R5, #1\n"
				
		"loc_FFC4CCA4:\n"		
			"LDR 	R0, [R4,#0x18]\n"
			"MOV 	R2, #0\n"
			"ADD 	R1, SP, #0x20-0x1c\n"
			"BL 	sub_FFC16FF0\n"
			"LDR 	R0, [R4,#0x20]\n"
			"CMP 	R0, #0\n"
			"BNE 	loc_FFC4CD74\n"
			"LDR 	R0, [SP,#0x20-0x1c]\n"
			"LDR 	R1, [R0]\n"
			"SUB 	R1, R1, #2\n"
			"CMP 	R1, #9\n"
			"ADDLS 	PC, PC, R1,LSL#2\n"
			"B 	loc_FFC4CD74\n"
				
		"loc_FFC4CCD8:\n"		
			"B 	loc_FFC4CD28\n"
				
		"loc_FFC4CCDC:\n"		
			"B 	loc_FFC4CD48\n"
				
		"loc_FFC4CCE0:\n"		
			"B 	loc_FFC4CD58\n"
				
		"loc_FFC4CCE4:\n"		
			"B 	loc_FFC4CD60\n"
				
		"loc_FFC4CCE8:\n"		
			"B 	loc_FFC4CD30\n"
				
		"loc_FFC4CCEC:\n"		
			"B 	loc_FFC4CD68\n"
				
		"loc_FFC4CCF0:\n"		
			"B 	loc_FFC4CD38\n"
				
		"loc_FFC4CCF4:\n"		
			"B 	loc_FFC4CD74\n"
				
		"loc_FFC4CCF8:\n"		
			"B 	loc_FFC4CD70\n"
				
		"loc_FFC4CCFC:\n"		
			"B 	loc_FFC4CD00\n"
				
		"loc_FFC4CD00:\n"		
				
			"STR 	R6, [R4,#0x34]\n"
			"LDR 	R0, =0xFFC4C988\n"
			"LDR 	R2, =0xFFC4C320\n"
			"LDR 	R1, =0x19074\n"
			"STR 	R0, [R4,#0xA0]\n"
			"LDR 	R0, =0xFFC4C404\n"
			"STR 	R6, [R4,#0x24]\n"
			"BL 	sub_FFC2A4C0\n"
			"STR 	R5, [R4,#0x38]\n"
			"B 	loc_FFC4CD74\n"
				
		"loc_FFC4CD28:\n"		
				
            "BL      unlock_optical_zoom\n" 		//  -----------> inserted
			"BL 	sub_FFC4CA80\n"
			"B 	loc_FFC4CD74\n"
				
		"loc_FFC4CD30:\n"		
				
				
			"BL 	sub_0xFFC4C788_my\n"			// ------------> changed
			"B 	loc_FFC4CD74\n"
				
		"loc_FFC4CD38:\n"		
				
				
			"LDR 	R1, [R0,#0x10]\n"
			"LDR 	R0, [R0,#4]\n"
			"BL 	sub_FFD16958\n"
			"B 	loc_FFC4CD74\n"
				
		"loc_FFC4CD48:\n"		
				
				
			"LDR 	R0, [R4,#0x38]\n"
			"CMP 	R0, #5\n"
			"STRNE 	R5, [R4,#0x28]\n"
			"B 	loc_FFC4CD74\n"
				
		"loc_FFC4CD58:\n"		
				
				
			"BL 	sub_FFC4C594\n"
			"B 	loc_FFC4CD74\n"
				
		"loc_FFC4CD60:\n"		
				
				
			"BL 	sub_FFC4C450\n"
			"B 	loc_FFC4CD74\n"
				
		"loc_FFC4CD68:\n"		
				
				
			"BL 	sub_FFC4C2AC\n"
			"B 	loc_FFC4CD74\n"
				
		"loc_FFC4CD70:\n"		
				
				
			"BL 	sub_FFC4CEDC\n"
				
		"loc_FFC4CD74:\n"		
				
				
				
			"LDR 	R1, [SP,#0x20-0x1C]\n"
			"LDR 	R3, =0xFFC4C10C\n"
			"STR 	R6, [R1]\n"
			"STR 	R8, [SP,#0x20-0x20]\n"
			"LDR 	R0, [R4,#0x1C]\n"
			"MOV 	R2, R7\n"
			"BL 	sub_FFC0BCD8\n"
			"B 	loc_FFC4CCA4\n"
 );
}
//JSE

void __attribute__((naked,noinline)) sub_0xFFC4C788_my(){ 
 asm volatile(
			"STMFD 	SP!, {R4-R8,LR}\n"
			"SUB 	SP, SP, #0x40\n"
			"MOV 	R6, #0\n"
			"LDR 	R5, =0x5240\n"
			"MOV 	R4, R0\n"
			"STR 	R6, [SP,#0x58-0x28]\n"
			"STR 	R6, [SP,#0x58-0x30]\n"
			"LDR 	R0, [R5,#0x38]\n"
			"MOV 	R8, #4\n"
			"CMP 	R0, #3\n"
			"STREQ 	R8, [R5,#0x38]\n"
			"LDR 	R0, [R5,#0xA0]\n"
//			"BLX 	R0\n"			// !! Workaround !!
		"MOV 	LR, PC\n"			// gcc won't compile "BLX 	R0" nor "BL	R0".
		"MOV 	PC, R0\n"			// workaround: make your own "BL" and hope we don't need the change to thumb-mode
			
			"LDR 	R0, [R5,#0x38]\n"
			"CMP 	R0, #4\n"
			"BNE 	loc_FFC4C860\n"
			"ADD 	R3, SP, #0x58-0x30\n"
			"ADD 	R2, SP, #0x58-0x30+4\n"
			"ADD 	R1, SP, #0x58-0x28\n"
			"ADD 	R0, SP, #0x58-0x24\n"
			"BL 	sub_FFD16AEC\n"
			"CMP 	R0, #0\n"
			"MOV 	R7, #1\n"
			"BNE 	loc_FFC4C804\n"
			"LDR 	R1, [R5,#0x28]\n"
			"CMP 	R1, #1\n"
			"BNE 	loc_FFC4C868\n"
			"LDR 	R1, [R5,#0x50]\n"
			"LDR 	R2, [R5,#0x3C]\n"
			"CMP 	R1, R2\n"
			"BCC 	loc_FFC4C868\n"
				
		"loc_FFC4C804:\n"		
			"CMP 	R0, #0x80000001\n"
			"STREQ 	R8, [R5,#0x54]\n"
			"BEQ 	loc_FFC4C83C\n"
			"CMP 	R0, #0x80000003\n"
			"STREQ 	R7, [R5,#0x54]\n"
			"BEQ 	loc_FFC4C83C\n"
			"CMP 	R0, #0x80000005\n"
			"MOVEQ 	R0, #2\n"
			"BEQ 	loc_FFC4C838\n"
			"CMP 	R0, #0x80000007\n"
			"STRNE 	R6, [R5,#0x54]\n"
			"BNE 	loc_FFC4C83C\n"
			"MOV 	R0, #3\n"
				
		"loc_FFC4C838:\n"		
			"STR 	R0, [R5,#0x54]\n"
				
		"loc_FFC4C83C:\n"		
				
			"LDR 	R0, =0x190A4\n"
			"LDR 	R0, [R0,#8]\n"
			"CMP 	R0, #0\n"
			"BEQ 	loc_FFC4C854\n"
			"BL 	sub_FFC37750\n"
			"B 	loc_FFC4C858\n"
				
		"loc_FFC4C854:\n"		
			"BL 	sub_FFC4C2AC\n"
				
		"loc_FFC4C858:\n"		
			"MOV 	R0, #5\n"
			"STR 	R0, [R5,#0x38]\n"
				
		"loc_FFC4C860:\n"		
				
			"ADD 	SP, SP, #0x40\n"
			"LDMFD 	SP!, {R4-R8,PC}\n"
				
		"loc_FFC4C868:\n"		
				
			"LDR 	LR, [SP,#0x58-0x28]\n"
			"CMP 	LR, #0\n"
			"BEQ 	loc_FFC4C930\n"
			"STR 	R7, [R5,#0x2C]\n"
			"LDR 	R0, [R5,#0x6C]\n"
			"LDR 	R1, [R4,#0x14]\n"
			"LDR 	R2, [R4,#0x18]\n"
			"LDR 	R12, [R4,#0xC]\n"
			"ADD 	R3, SP, #0x58-0x20\n"
			"ADD 	R8, SP, #0x58-0x44\n"
			"STMIA 	R8, {R0-R3}\n"
			"LDR 	R3, [R5,#0x58]\n"
			"ADD 	R2, SP, #0x58-0x1C\n"
			"ADD 	R8, SP, #0x58-0x50\n"

			//			"LDRD 	R0, [SP,#0x58-0x30]\n"		//Workaround, selected processor does not support `ldrd R0,[SP,#0x58-0x30]'
			".long   0xE1CD02D8\n" //binary representation of instruction above
			
			"STMIA 	R8, {R0,R2,R3}\n"
			"STR 	R1, [SP,#0x58-0x54]\n"
			"STR 	LR, [SP,#0x58-0x58]\n"
			"LDMIB 	R4, {R0,R1}\n"
			"LDR 	R3, [SP,#0x58-0x24]\n"
			"MOV 	R2, R12\n"
			"BL 	sub_FFCDBF24\n"
			"LDR 	R0, [R5,#0x10]\n"
			"MOV 	R1, #0x3E8\n"
			"BL 	sub_FFC0B74C \n"
			"CMP 	R0, #9\n"
			"BNE 	loc_FFC4C8E4\n"
			"BL 	sub_FFD170C8\n"
			"MOV 	R0, #0x90000\n"
			"STR 	R7, [R5,#0x38]\n"
			"B 	loc_FFC4C8FC\n"
				
		"loc_FFC4C8E4:\n"		
			"LDR 	R0, [SP,#0x58-0x20]\n"
			"CMP 	R0, #0\n"
			"BEQ 	loc_FFC4C904\n"
			"BL 	sub_FFD170C8\n"
			"MOV 	R0, #0xA0000\n"
			"STR 	R7, [R5,#0x38]\n"
				
		"loc_FFC4C8FC:\n"		
			"BL 	sub_FFC6403C\n"
			"B 	loc_FFC4C860\n"
				
		"loc_FFC4C904:\n"		
			"BL 	sub_FFCDBFE8\n"
			"LDR 	R0, [SP,#0x58-0x24]\n"
			"LDR 	R1, [SP,#0x58-0x1C]\n"
			"BL 	sub_FFD16E70\n"
			"LDR 	R0, [R5,#0x4C]\n"
			"LDR 	R1, =0x52AC\n"		//-------> see later
			"ADD 	R0, R0, #1\n"
			"STR 	R0, [R5,#0x4C]\n"
			"LDR 	R0, [SP,#0x58-0x1C]\n"
			"MOV 	R2, #0\n"

			"BL 	sub_FFD14CE8_my\n"
			
//			"BL 	sub_FFD14CE8\n"

//            "LDR     R0, =0x52AC\n"  	// -<----	     // inserted
//            "BL 	set_quality\n"                 	 // inserted
			
		"loc_FFC4C930:\n"		
			"LDR 	R0, [R5,#0x50]\n"
			"ADD 	R0, R0, #1\n"
			"STR 	R0, [R5,#0x50]\n"
			"LDR 	R1, [R5,#0x78]\n"
			"MUL 	R0, R1, R0\n"
			"LDR 	R1, [R5,#0x74]\n"
			"BL 	sub_FFE90A04\n"
			"MOV 	R4, R0\n"
			"BL 	sub_FFD17100\n"
			"LDR 	R1, [R5,#0x70]\n"
			"CMP 	R1, R4\n"
			"BNE 	loc_FFC4C96C\n"
			"LDR 	R0, [R5,#0x30]\n"
			"CMP 	R0, #1\n"
			"BNE 	loc_FFC4C980\n"
				
		"loc_FFC4C96C:\n"		
			"LDR 	R1, [R5,#0x84]\n"
			"MOV 	R0, R4\n"
//			"BLX 	R1\n"			// !! Workaround !!
		"MOV 	LR, PC\n"			// gcc won't compile "BLX 	R1" nor "BL 	R1".
		"MOV 	PC, R1\n"			// workaround: make your own "BL" and hope we don't need the change to thumb-mode
			
			"STR 	R4, [R5,#0x70]\n"
			"STR 	R6, [R5,#0x30]\n"
				
		"loc_FFC4C980:\n"		
			"STR 	R6, [R5,#0x2C]\n"
			"B 	loc_FFC4C860\n"
 );
}

void __attribute__((naked,noinline)) sub_FFD14CE8_my(){ 
 asm volatile(
	"STMFD 	SP!, {R4-R8,LR} \n"
	"LDR 	R4, =0x8764 \n"
	"LDR 	LR, [R4] \n"
	"LDR 	R2, [R4,#8] \n"
	"CMP 	LR, #0 \n"
	"LDRNE 	R3, [R4,#0xC] \n"
	"MOV 	R5, R2 \n"
	"CMPNE 	R3, #1 \n"
	"MOVEQ 	R2, #0 \n"
	"STREQ 	R0, [R4] \n"
	"STREQ 	R2, [R4,#0xC] \n"
	"BEQ 	loc_FFD14DB4 \n"
	"LDR 	R3, [R4,#4] \n"
//	"LDR 	R7, =0xFFEB2548 \n"
	"LDR 	R7, =table\n"			// -----> changed
	"ADD 	R12, R3, R3,LSL#1 \n"
	"LDR 	R3, [R7,R12,LSL#2] \n"
	"ADD 	R6, R7, #0x30 \n"
	"LDR 	R8, [R6,R12,LSL#2] \n"
	"SUB 	R3, LR, R3 \n"
	"CMP 	R3, #0 \n"
	"SUB 	LR, LR, R8 \n"
	"BLE 	loc_FFD14D70 \n"
	"ADD 	R12, R7, R12,LSL#2 \n"
	"LDR 	LR, [R12,#4] \n"
	"CMP 	LR, R3 \n"
	"ADDGE 	R2, R2, #1 \n"
	"BGE 	loc_FFD14D64 \n"
	"LDR 	R12, [R12,#8] \n"
	"CMP 	R12, R3 \n"
	"ADDLT 	R2, R2, #3 \n"
	"ADDGE 	R2, R2, #2 \n"
		
"loc_FFD14D64:\n"		
//	"CMP 	R2, #0x17 \n"
//	"MOVGE 	R2, #0x16 \n"
	"CMP     R2, #0x1A\n"   // ---------> changed
	"MOVGE   R2, #0x19\n"   // ---------> changed
	"B 	loc_FFD14DA4 \n"
		
"loc_FFD14D70:\n"		
	"CMP 	LR, #0 \n"
	"BGE 	loc_FFD14DA4 \n"
	"ADD 	R3, R6, R12,LSL#2 \n"
	"LDR 	R12, [R3,#4] \n"
	"CMP 	R12, LR \n"
	"SUBLE 	R2, R2, #1 \n"
	"BLE 	loc_FFD14D9C \n"
	"LDR 	R3, [R3,#8] \n"
	"CMP 	R3, LR \n"
	"SUBGT 	R2, R2, #3 \n"
	"SUBLE 	R2, R2, #2 \n"
		
"loc_FFD14D9C:\n"		
	"CMP 	R2, #0 \n"
	"MOVLT 	R2, #0 \n"
		
"loc_FFD14DA4:\n"		
		
	"CMP 	R2, R5 \n"
	"STRNE 	R2, [R4,#8] \n"
	"MOVNE 	R2, #1 \n"
	"STRNE 	R2, [R4,#0xC] \n"
		
"loc_FFD14DB4:\n"		
//	"LDR 	R2, =0xFFEB24EC \n"			
	"LDR 	R2, =CompressionRateTable\n"			//----------> changed
	"LDR 	R3, [R4,#8] \n"
	"LDR 	R2, [R2,R3,LSL#2] \n"

                "LDR     R3, =video_mode\n"      // --------> inserted
                "LDR     R3, [R3]\n"             // --------> inserted
                "LDR     R3, [R3]\n"             // --------> inserted
                "CMP     R3, #1\n"               // --------> inserted
                "LDREQ   R3, =video_quality\n"   // --------> inserted    
                "LDREQ   R3, [R3]\n"             // --------> inserted     
                "LDREQ   R2, [R3]\n"             // --------> inserted     

	"STR 	R2, [R1] \n"
	"STR 	R0, [R4] \n"

		"BL      mute_on_zoom\n"         // --------> inserted 

	"LDMFD 	SP!, {R4-R8,PC} \n"
 );
} 
