#include "conf.h"

int *video_quality = &conf.video_quality;
int *video_mode    = &conf.video_mode;

long def_table1[9]={0x2000,0x38D,0x788,0x5800,0x9C5,0x14B8,0x10000,0x1C6A,0x3C45};
long def_table2[9]={0x1CCD,-0x2E1,-0x579,0x4F33,-0x7EB,-0xF0C,0xE666,-0x170A,-0x2BC6};

long table1[9], table2[9];

void change_video_tables(int a, int b){
 int i;
 for (i=0;i<9;i++) {table1[i]=(def_table1[i]*a)/b; table2[i]=(def_table2[i]*a)/b;}
}

long CompressionRateTable[]={0x60, 0x5D, 0x5A, 0x57, 0x54, 0x51, 0x4D, 0x48, 0x42, 0x3B, 0x32, 0x29, 0x22, 0x1D, 0x17, 0x14, 0x10, 0xE, 0xB, 9, 7, 6, 5, 4, 3, 2, 1};

void __attribute__((naked,noinline)) sub_FFE60F28_my(){
 asm volatile(
                "CMP     R2, #1\n"          
                "STMFD   SP!, {R4-R7,LR}\n" 
                "MOV     R6, R0\n"          
                "MOV     R7, R1\n"          
                "MOVEQ   R3, #0x79\n"       
                "STREQ   R3, [R7]\n"        
                "LDMEQFD SP!, {R4-R7,PC}\n" 
                "LDR     R12, =0x6E064\n"   
                "LDR     R0, [R12]\n"       
                "LDR     R3, =0x6E06C\n"    
                "CMP     R0, #0\n"          
                "LDR     R1, [R3]\n"        
                "BEQ     loc_FFE60F70\n"    
                "LDR     R2, =0x6E070\n"    
                "LDR     R3, [R2]\n"        
                "CMP     R3, #1\n"          
                "BNE     loc_FFE60F84\n"    
                "B       loc_FFE60F74\n"    


"loc_FFE60F70:\n"                           
                "LDR     R2, =0x6E070\n"    

"loc_FFE60F74:\n"                           
                "MOV     R3, #0\n"          
                "STR     R3, [R2]\n"        
                "STR     R6, [R12]\n"       
                "B       loc_FFE6103C\n"    


"loc_FFE60F84:\n"                           
                "LDR     R2, =0x6E068\n"    
                "LDR     R3, [R2]\n"        
                "LDR     R5, =table1\n"        //unk_FFE60E2C
                "ADD     R3, R3, R3,LSL#1\n" 
                "MOV     LR, R3,LSL#2\n"    
                "LDR     R2, [R5,LR]\n"     
                "LDR     R4, =table2\n"        //unk_FFE60E50
                "RSB     R12, R2, R0\n"     
                "LDR     R3, [R4,LR]\n"     
                "CMP     R12, #0\n"         
                "RSB     R0, R3, R0\n"      
                "BLE     loc_FFE60FE8\n"    
                "ADD     R3, R5, #4\n"      
                "LDR     R2, [R3,LR]\n"     
                "CMP     R2, R12\n"         
                "ADDGE   R1, R1, #1\n"      
                "BGE     loc_FFE60FDC\n"    
                "ADD     R3, R5, #8\n"      
                "LDR     R2, [R3,LR]\n"     
                "CMP     R2, R12\n"         
                "ADDGE   R1, R1, #2\n"      
                "ADDLT   R1, R1, #3\n"      

"loc_FFE60FDC:\n"                           
//             "CMP     R1, #0xE\n"  //-      
//             "MOVGE   R1, #0xE\n"  //-      

                "CMP     R1, #0x1A\n"  //+      
                "MOVGE   R1, #0x1A\n"  //+      

                "B       loc_FFE61020\n"    


"loc_FFE60FE8:\n"                           
                "CMP     R0, #0\n"          
                "BGE     loc_FFE61020\n"    
                "ADD     R3, R4, #4\n"      
                "LDR     R2, [R3,LR]\n"     
                "CMP     R2, R0\n"          
                "SUBLE   R1, R1, #1\n"      
                "BLE     loc_FFE61018\n"    
                "ADD     R3, R4, #8\n"      
                "LDR     R2, [R3,LR]\n"     
                "CMP     R2, R0\n"          
                "SUBLE   R1, R1, #2\n"      
                "SUBGT   R1, R1, #3\n"      

"loc_FFE61018:\n"                           
                "CMP     R1, #0\n"          
                "MOVLT   R1, #0\n"          

"loc_FFE61020:\n"                           
                                        
                "LDR     R0, =0x6E06C\n"    
                "LDR     R3, [R0]\n"        
                "CMP     R1, R3\n"          
                "LDRNE   R2, =0x6E070\n"    
                "MOVNE   R3, #1\n"          
                "STRNE   R1, [R0]\n"        
                "STRNE   R3, [R2]\n"        

"loc_FFE6103C:\n"                           
                "LDR     R3, =0x6E06C\n"    
                "LDR     R2, =CompressionRateTable\n" //unk_FFE60DF0
                "LDR     R1, [R3]\n"        
                "LDR     R0, =0x6E064\n"    
                "LDR     R3, [R2,R1,LSL#2]\n" 

                "LDR     R1, =video_mode\n"      // +
                "LDR     R1, [R1]\n"             // +
                "LDR     R1, [R1]\n"             // +
                "CMP     R1, #1\n"               // +
                "LDREQ   R1, =video_quality\n"   // +     
                "LDREQ   R1, [R1]\n"             // +     
                "LDREQ   R3, [R1]\n"             // +     

                "STR     R6, [R0]\n"        
                "STR     R3, [R7]\n"        
                "BL      mute_on_zoom\n"     // +
                "LDMFD   SP!, {R4-R7,PC}\n" 

 );
}


void __attribute__((naked,noinline)) sub_FFEEBED8_my(){
 asm volatile(
                "STMFD   SP!, {R4-R11,LR}\n" 
                "LDR     R5, =0x920A4\n"    
                "SUB     SP, SP, #0x14\n"   
                "LDR     LR, [R5]\n"        
                "LDR     R12, =0x920BC\n"   
                "ADD     LR, LR, #1\n"      
                "LDR     R4, [R12]\n"       
                "STR     LR, [R5]\n"        
                "LDR     R12, =0x9213C\n"   
                "STR     R0, [SP,#0x10]\n"  
                "STR     R1, [SP,#0xC]\n"   
                "STR     R2, [SP,#8]\n"     
                "STR     R3, [SP,#4]\n"     
                "CMP     LR, R4\n"          
                "LDR     R11, [R12]\n"      
                "MOVHI   R0, #0x80000001\n"  // remove frame
                "BHI     loc_FFEEC3C0\n"     // (time) limit
                "LDR     R3, =0x92120\n"    
                "MOV     R0, LR\n"          
                "LDR     R1, [R3]\n"        
                "BL      sub_FFCC0BFC\n" //__umodsi3      
                "CMP     R0, #1\n"          
                "BNE     loc_FFEEC0F8\n"    
                "LDR     R0, =0x92144\n"    
                "LDR     R1, =0x92090\n"    
                "LDR     R3, [R0]\n"        
                "LDR     R2, [R1]\n"        
                "CMP     R3, R2\n"          
                "LDREQ   R3, =0x92140\n"    
                "LDREQ   R5, [R3]\n"        
                "MOVNE   R5, R2\n"          
                "LDR     R3, =0x920A4\n"    
                "LDR     R2, =0x92120\n"    
                "LDR     R0, [R3]\n"        
                "LDR     R1, [R2]\n"        
                "BL      sub_FFCC0B64\n" //__udivsi3      
                "LDR     R3, =0x92098\n"    
                "ADD     R0, R0, #1\n"      
                "AND     R0, R0, #1\n"      
                "STR     R5, [R3,R0,LSL#2]\n" 
                "LDR     R3, =0x9208C\n"    
                "LDR     R2, [R3]\n"        
                "CMP     R5, R2\n"          
                "BHI     loc_FFEEBFA8\n"    
                "LDR     R4, =0x920DC\n"    
                "LDR     R3, [R4]\n"        
                "ADD     R3, R5, R3\n"      
                "ADD     R3, R3, #8\n"      
                "CMP     R2, R3\n"          
                "BCS     loc_FFEEBFAC\n"    

"loc_FFEEBFA0:\n"                            
                                        
                "MOV     R0, #0x80000003\n" 
                "B       loc_FFEEC3C0\n"    


"loc_FFEEBFA8:\n"                            
                "LDR     R4, =0x920DC\n"    

"loc_FFEEBFAC:\n"                            
                "LDR     R3, [R4]\n"        
                "LDR     R2, =0x92144\n"    
                "ADD     R1, R5, R3\n"      
                "LDR     R3, [R2]\n"        
                "ADD     R2, R1, #8\n"      
                "CMP     R2, R3\n"          
                "BLS     loc_FFEEBFF8\n"    
                "LDR     R2, =0x92140\n"    
                "LDR     R0, =0x9208C\n"    
                "RSB     R3, R3, R1\n"      
                "LDR     R1, [R2]\n"        
                "ADD     R3, R3, #8\n"      
                "LDR     R2, [R0]\n"        
                "ADD     R1, R1, R3\n"      
                "CMP     R2, R1\n"          
                "BCC     loc_FFEEBFA0\n"    
                "LDR     R3, =0x92090\n"    
                "STR     R1, [R3]\n"        
                "B       loc_FFEEC000\n"    


"loc_FFEEBFF8:\n"                            
                "LDR     R3, =0x92090\n"    
                "STR     R2, [R3]\n"        

"loc_FFEEC000:\n"                            
                "LDR     R3, [R4]\n"        
                "LDR     R12, =0x920F0\n"   
                "ADD     R3, R3, #0x18\n"   
                "LDR     R2, [R12,#4]\n"    
                "MOV     R0, R3\n"          
                "MOV     R1, #0\n"          
                "CMP     R1, R2\n"          
                "BHI     loc_FFEEC244\n"    
                "BNE     loc_FFEEC030\n"    
                "LDR     R3, [R12]\n"       
                "CMP     R0, R3\n"          
                "BHI     loc_FFEEC244\n"    

"loc_FFEEC030:\n"                            
                "LDR     R4, [R4]\n"        
                "LDR     LR, =0x920F8\n"    
                "STR     R4, [SP]\n"        
                "LDR     R12, =0x920F0\n"   
                "LDR     R3, =0x920A4\n"    
                "LDMIA   LR, {R7,R8}\n"     
                "LDMIA   R12, {R5,R6}\n"    
                "LDR     R10, [R3]\n"       
                "LDR     R2, =0x92120\n"    
                "MOV     R3, R4\n"          
                "MOV     R4, #0\n"          
                "ADDS    R7, R7, R3\n"      
                "ADC     R8, R8, R4\n"      
                "LDR     R9, [R2]\n"        
                "SUBS    R5, R5, R3\n"      
                "SBC     R6, R6, R4\n"      
                "MVN     R2, #0\n"          
                "MVN     R1, #0x17\n"       
                "ADDS    R5, R5, R1\n"      
                "MOV     R4, #0\n"          
                "MOV     R3, #0x18\n"       
                "ADC     R6, R6, R2\n"      
                "ADDS    R7, R7, R3\n"      
                "ADC     R8, R8, R4\n"      
                "STMIA   R12, {R5,R6}\n"    
                "SUB     R0, R10, #1\n"     
                "MOV     R1, R9\n"          
                "STMIA   LR, {R7,R8}\n"     
                "BL      sub_FFCC0B64\n" //__udivsi3      
                "CMP     R10, #1\n"         
                "MLA     R0, R9, R0, R0\n"  
                "BEQ     loc_FFEEC0F8\n"    
                "SUB     R3, R0, #1\n"      
                "MOV     R3, R3,LSL#4\n"    
                "ADD     R4, R11, #0x10\n"  
                "ADD     R5, R11, #0x14\n"  
                "LDR     R1, [R5,R3]\n"     
                "LDR     R2, [R4,R3]\n"     
                "LDR     LR, =0x62773130\n" 
                "ADD     R2, R2, R1\n"      
                "MOV     R3, R0,LSL#4\n"    
                "ADD     R2, R2, #8\n"      
                "MOV     R0, #0\n"          
                "ADD     R12, R11, #0xC\n"  
                "ADD     R1, R11, #8\n"     
                "STR     LR, [R1,R3]\n"     
                "STR     R0, [R12,R3]\n"    
                "STR     R2, [R4,R3]\n"     
                "LDR     R0, [SP]\n"        
                "STR     R0, [R5,R3]\n"     

"loc_FFEEC0F8:\n"                            
                                        
                "LDR     R2, =0x92090\n"    
                "LDR     R3, =0x92144\n"    
                "LDR     R1, [R2]\n"        
                "LDR     R0, [R3]\n"        
                "ADD     R3, R1, #9\n"      
                "CMP     R3, R0\n"          
                "BLS     loc_FFEEC134\n"    
                "LDR     R2, =0x92140\n"    
                "LDR     R3, [R2]\n"        
                "ADD     R3, R3, R1\n"      
                "RSB     R3, R0, R3\n"      
                "LDR     R0, [SP,#0x10]\n"  
                "ADD     R3, R3, #8\n"      
                "STR     R3, [R0]\n"        
                "B       loc_FFEEC140\n"    


"loc_FFEEC134:\n"                            
                "ADD     R3, R1, #8\n"      
                "LDR     R1, [SP,#0x10]\n"  
                "STR     R3, [R1]\n"        

"loc_FFEEC140:\n"                            
                "LDR     R2, [SP,#0x10]\n"  
                "LDR     R1, =0x920EC\n"    
                "LDR     R3, =0x92144\n"    
                "LDR     R12, [R2]\n"       
                "LDR     R2, [R1]\n"        
                "LDR     R0, [R3]\n"        
                "ADD     R3, R12, R2\n"     
                "CMP     R3, R0\n"          
                "BLS     loc_FFEEC194\n"    
                "LDR     R2, [SP,#0xC]\n"   
                "RSB     R0, R12, R0\n"     
                "STR     R0, [R2]\n"        
                "LDR     R2, =0x92140\n"    
                "LDR     R3, [R1]\n"        
                "LDR     R1, [R2]\n"        
                "RSB     R3, R0, R3\n"      
                "LDR     R0, [SP,#8]\n"     
                "STR     R1, [R0]\n"        
                "LDR     R1, [SP,#4]\n"     
                "STR     R3, [R1]\n"        
                "B       loc_FFEEC1B0\n"    


"loc_FFEEC194:\n"                            
                "LDR     R0, [SP,#0xC]\n"   
                "STR     R2, [R0]\n"        
                "LDR     R1, [SP,#4]\n"     
                "MOV     R3, #0\n"          
                "STR     R3, [R1]\n"        
                "LDR     R2, [SP,#8]\n"     
                "STR     R3, [R2]\n"        

"loc_FFEEC1B0:\n"                            
                "LDR     R0, =0x92090\n"    
                "LDR     R1, =0x9208C\n"    
                "LDR     R3, [R0]\n"        
                "LDR     R2, [R1]\n"        
                "CMP     R3, R2\n"          
                "BHI     loc_FFEEC1DC\n"    
                "LDR     R0, [SP,#0xC]\n"   
                "LDR     R3, [R0]\n"        
                "ADD     R3, R12, R3\n"     
                "CMP     R2, R3\n"          
                "BCC     loc_FFEEBFA0\n"    

"loc_FFEEC1DC:\n"                            
                "LDR     R1, [SP,#8]\n"     
                "LDR     R2, [R1]\n"        
                "CMP     R2, #0\n"          
                "BEQ     loc_FFEEC210\n"    
                "LDR     R3, =0x9208C\n"    
                "LDR     R1, [R3]\n"        
                "CMP     R2, R1\n"          
                "BHI     loc_FFEEC210\n"    
                "LDR     R0, [SP,#4]\n"     
                "LDR     R3, [R0]\n"        
                "ADD     R3, R2, R3\n"      
                "CMP     R1, R3\n"          
                "BCC     loc_FFEEBFA0\n"    

"loc_FFEEC210:\n"                            
                                        
                "LDR     R3, =0x920EC\n"    
                "LDR     R0, =0x920F0\n"    
                "LDR     R2, [R3]\n"        
                "LDR     R3, [R0,#4]\n"     
                "ADD     R2, R2, #0x18\n"   
                "MOV     R1, R2\n"          
                "MOV     R2, #0\n"          
                "CMP     R2, R3\n"          
                "BHI     loc_FFEEC244\n"    
                "BNE     loc_FFEEC24C\n"    
                "LDR     R3, [R0]\n"        
                "CMP     R1, R3\n"          
                "BLS     loc_FFEEC24C\n"    

"loc_FFEEC244:\n"                            
                                        
                "MOV     R0, #0x80000005\n" 
                "B       loc_FFEEC3C0\n"    


"loc_FFEEC24C:\n"                            
                                        
                "LDR     R1, =0x920D4\n"    
                "LDR     R0, =0x92120\n"    
                "LDR     R3, [R1]\n"        
                "LDR     R2, [R0]\n"        
                "ADD     R3, R3, R2,LSL#4\n" 
                "ADD     R3, R3, R3,LSL#2\n" 
                "LDR     R12, =0x920F0\n"   
                "MOV     R3, R3,LSL#1\n"    
                "ADD     R3, R3, #0xA0\n"   
                "LDR     R2, [R12,#4]\n"    
                "MOV     R0, R3\n"          
                "MOV     R1, #0\n"          
                "CMP     R1, R2\n"          
                "BHI     loc_FFEEC294\n"    
                "BNE     loc_FFEEC2B8\n"    
                "LDR     R3, [R12]\n"       
                "CMP     R0, R3\n"          
                "BLS     loc_FFEEC2B8\n"    

"loc_FFEEC294:\n"                            
                "LDR     R4, =0x92108\n"    
                "LDR     R1, [R4]\n"        
                "CMP     R1, #0\n"          
                "BNE     loc_FFEEC2B8\n"    
                "MOV     R0, #0x3140\n"     
                "ADD     R0, R0, #8\n"      
                "BL      sub_FFEA2288\n" //PostLogicalEventToUI   
                "MOV     R3, #1\n"          
                "STR     R3, [R4]\n"        

"loc_FFEEC2B8:\n"                            
                                        
                "LDR     R1, =0x920D4\n"    
                "LDR     R0, =0x92120\n"    
                "LDR     R2, [R1]\n"        
                "LDR     R3, [R0]\n"        
                "LDR     R0, =0x920F8\n"    
                "ADD     R2, R2, R3,LSL#4\n" 
                "MVN     R3, #0x9F\n"       
                "ADD     R2, R2, R2,LSL#2\n" 
                "ADD     R3, R3, #0x40000000\n" 
                "SUB     R3, R3, R2,LSL#1\n" 
                "LDR     R1, [R0,#4]\n"     
                "MOV     R4, R3\n"          
                "MOV     R5, #0\n"          
                "CMP     R1, R5\n"          
                "BHI     loc_FFEEC304\n"    
                "BNE     loc_FFEEC328\n"    
                "LDR     R3, [R0]\n"        
                "CMP     R3, R4\n"          
                "BLS     loc_FFEEC328\n"    

"loc_FFEEC304:\n"                            
                "LDR     R4, =0x92108\n"    
                "LDR     R1, [R4]\n"        
                "CMP     R1, #0\n"          
                "BNE     loc_FFEEC328\n"    
                "MOV     R0, #0x3140\n"     
                "ADD     R0, R0, #8\n"      
                "BL      sub_FFEA2288\n" //PostLogicalEventToUI   
                "MOV     R3, #1\n"          
                "STR     R3, [R4]\n"        

"loc_FFEEC328:\n"                            
                                        
                "LDR     R3, =0x92120\n"    
                "LDR     R0, =0x920BC\n"    
                "LDR     R2, [R3]\n"        
                "LDR     R12, =0x920A4\n"   
                "LDR     R1, [R0]\n"        
                "ADD     R3, R2, R2,LSL#2\n" 
                "ADD     R2, R2, R3,LSL#1\n" 
                "LDR     R0, [R12]\n"       
                "RSB     R1, R2, R1\n"      
                "CMP     R0, R1\n"          
                "BLS     loc_FFEEC378\n"    
                "LDR     R4, =0x92108\n"    
                "LDR     R1, [R4]\n"        
                "CMP     R1, #0\n"          
                "BNE     loc_FFEEC378\n"    
                "MOV     R0, #0x3140\n"     
                "ADD     R0, R0, #8\n"      
                "BL      sub_FFEA2288\n" //PostLogicalEventToUI   
                "MOV     R3, #1\n"          
                "STR     R3, [R4]\n"        

"loc_FFEEC378:\n"                            
                                        
                "LDR     R3, =0x920F8\n"    
                "LDR     R12, =0x920EC\n"   
                "LDMIA   R3, {R1,R2}\n"     
                "LDR     R0, [R12]\n"       
                "MOV     R4, #0\n"          
                "MOV     R3, #0x18\n"       
                "ADDS    R1, R1, R0\n"      
                "ADC     R2, R2, #0\n"      
                "ADDS    R1, R1, R3\n"      
                "ADC     R2, R2, R4\n"      
                "CMP     R2, #0\n"          
                "BHI     loc_FFEEC3B4\n"    
                "BNE     loc_FFEEC3BC\n"    
                "CMP     R1, #0x40000000\n" 
//                "BLS     loc_FFEEC3BC\n"    
                 "B       loc_FFEEC3BC\n"    // bypass 1GB limit ?

"loc_FFEEC3B4:\n"                            
                "MOV     R0, #0x80000007\n" 
                "B       loc_FFEEC3C0\n"    


"loc_FFEEC3BC:\n"                            
                                        
                "MOV     R0, #0\n"          

"loc_FFEEC3C0:\n"                            
                                        
                "ADD     SP, SP, #0x14\n"   
                "LDMFD   SP!, {R4-R11,PC}\n" 
 );
}



void __attribute__((naked,noinline)) sub_FFEEABA0_my(){
 asm volatile(
                "STMFD   SP!, {R4-R11,LR}\n" 
                "LDR     R5, =0x91D54\n"    
                "SUB     SP, SP, #0x3C\n"   
                "LDR     R3, [R5]\n"        
                "CMP     R3, #3\n"          
                "MOV     R4, R0\n"          
                "MOVEQ   R3, #4\n"          
                "STREQ   R3, [R5]\n"        
                "LDR     R3, =0x91E14\n"    
                "MOV     LR, PC\n"          
                "LDR     PC, [R3]\n"        
                "LDR     R2, [R5]\n"        
                "CMP     R2, #4\n"          
                "BNE     loc_FFEEAD78\n"    
                "ADD     R0, SP, #0x38\n"   
                "ADD     R1, SP, #0x34\n"   
                "ADD     R2, SP, #0x30\n"   
                "ADD     R3, SP, #0x2C\n"   
                "BL      sub_FFEEBED8_my\n"   //----------------> 
                "CMP     R0, #0\n"          
                "BNE     loc_FFEEAC1C\n"    
                "LDR     R3, =0x91D40\n"    
                "LDR     R2, [R3]\n"        
                "CMP     R2, #1\n"          
                "BNE     loc_FFEEAC30\n"    
                "LDR     R2, =0x91D98\n"    
                "LDR     R1, =0x91D6C\n"    
                "LDR     R12, [R2]\n"       
                "LDR     R3, [R1]\n"        
                "CMP     R12, R3\n"         
                "BCC     loc_FFEEAC30\n"    

"loc_FFEEAC1C:\n"                           
                "BL      sub_FFEEADC4\n"    
                "BL      sub_FFEEAFC4\n"    
                "MOV     R3, #5\n"          
                "STR     R3, [R5]\n"        
                "B       loc_FFEEAD78\n"    

"loc_FFEEAC30:\n"                           
                                        
                "LDR     R1, =0x91DA0\n"   
                "LDR     R10, [R1]\n"
                "LDR     R1, =0x91DAC\n"   
                "LDR     R2, [R4,#0xC]\n"
                "LDMIB   R4, {R0,R9}\n"     
                "ADD     R4, SP, #0x24\n"      
                "LDR     R8, [R1]\n"       
                "LDR     R5, [SP,#0x34]\n"  
                "LDR     R6, [SP,#0x30]\n"  
                "LDR     R7, [SP,#0x2C]\n"  
                "STR     R4, [SP,#0x20]\n"    
                "LDR     R4, =0x91D44\n"  
                "ADD     R12, SP, #0x28\n"  
                "MOV     LR, #0\n"   
                "MOV     R11, #1\n"          
                "LDR     R3, [SP,#0x38]\n"
                "STMEA   SP, {R5-R7,R12}\n" 
                "STR     R10, [SP,#0x10]\n" 
                "STR     R8, [SP,#0x14]\n"  
                "STR     LR, [SP,#0x18]\n"  
                "MOV     R1, R9\n"
                "STR     R11, [R4]\n"        
                "STR     R9, [SP,#0x1C]\n"
                "BL      sub_FFEEDFF4\n"    
                "LDR     R3, =0x91C58\n"    
                "MOV     R1, #0x3E8\n"      
                "LDR     R0, [R3]\n"        
                "BL      sub_FFE82F14\n"
                "CMP     R0, #9\n"          
                "BNE     loc_FFEEACB8\n"    
                "BL      sub_FFEEC6E8\n"    
                "LDR     R3, =0x91D54\n"    
                "LDR     R0, =0xFFEEAB88\n" //aJpegtimeout_1
                "B       loc_FFEEACD0\n"    

"loc_FFEEACB8:\n"                           
                "LDR     R5, [SP,#0x24]\n"  
                "CMP     R5, #0\n"          
                "BEQ     loc_FFEEACDC\n"    
                "BL      sub_FFEEC6E8\n"    
                "LDR     R3, =0x91D54\n"    
                "LDR     R0, =0xFFEEAB94\n" //aJpegicerror_2

"loc_FFEEACD0:\n"                           
                "STR     R11, [R3]\n"        
                "BL      sub_FFEA6988\n" //HardwareDefect   
                "B       loc_FFEEAD78\n"    

"loc_FFEEACDC:\n"                           
                "BL      sub_FFEEE164\n"    
                "LDR     R0, [SP,#0x38]\n"  
                "LDR     R1, [SP,#0x28]\n"  
                "BL      sub_FFEEC40C\n"    
                "LDR     R4, =0x91D98\n"    
                "LDR     R3, [R4]\n"        
                "ADD     R3, R3, #1\n"      
                "LDR     R0, [SP,#0x28]\n"  
                "LDR     R1, =0x91DAC\n"         
                "STR     R3, [R4]\n"        
                "MOV     R2, R5\n"          
                "BL      sub_FFE60F28_my\n"    //--------------->
                "LDR     R3, =0x91DB8\n"    
                "LDR     R1, [R4]\n"        
                "LDR     R2, [R3]\n"        
                "LDR     R12, =0x91DB4\n"   
                "MUL     R0, R2, R1\n"      
                "LDR     R1, [R12]\n"       
                "BL      sub_FFCC0B64\n" //__udivsi3      
                "LDR     R7, =0x91DB0\n"    
                "LDR     R3, [R7]\n"        
                "MOV     R4, R0\n"          
                "CMP     R3, R4\n"          
                "BNE     loc_FFEEAD50\n"    
                "LDR     R6, =0x91D48\n"    
                "LDR     R3, [R6]\n"        
                "CMP     R3, #1\n"          
                "BNE     loc_FFEEAD6C\n"    
                "B       loc_FFEEAD54\n"    

"loc_FFEEAD50:\n"                           
                "LDR     R6, =0x91D48\n"    

"loc_FFEEAD54:\n"                           
                "LDR     R3, =0x91DF8\n"    
                "MOV     R0, R4\n"          
                "MOV     LR, PC\n"          
                "LDR     PC, [R3]\n"        
                "STR     R5, [R6]\n"        
                "STR     R4, [R7]\n"        

"loc_FFEEAD6C:\n"                           
                "LDR     R2, =0x91D44\n"    
                "MOV     R3, #0\n"          
                "STR     R3, [R2]\n"        

"loc_FFEEAD78:\n"                           
                                        
                "ADD     SP, SP, #0x3C\n"   
                "LDMFD   SP!, {R4-R11,PC}\n" 

//                "MOV     PC, LR\n"
 );
}


void __attribute__((naked,noinline)) movie_record_task(){

 asm volatile(
                "STMFD   SP!, {R4,LR}\n"    
                "SUB     SP, SP, #4\n"      
                "MOV     R4, SP\n"          
                "B       loc_FFEEA4CC\n"    

"loc_FFEEA428:\n"                           
                "LDR     R3, =0x91D38\n"    
                "LDR     R2, [R3]\n"        
                "CMP     R2, #0\n"          
                "BNE     loc_FFEEA4B8\n"    
                "SUB     R3, R12, #2\n"     
                "CMP     R3, #9\n"          
                "LDRLS   PC, [PC,R3,LSL#2]\n" 
                "B       loc_FFEEA4B8\n"    

                ".long loc_FFEEA478\n"
                ".long loc_FFEEA490\n"
                ".long loc_FFEEA498\n"
                ".long loc_FFEEA4A0\n"
                ".long loc_FFEEA480\n"
                ".long loc_FFEEA4A8\n"
                ".long loc_FFEEA488\n"
                ".long loc_FFEEA4B8\n"
                ".long loc_FFEEA4B0\n"
                ".long loc_FFEEA470\n"

"loc_FFEEA470:\n"                           
                                        
                "BL      sub_FFEEA568\n"    
                "B       loc_FFEEA4B4\n"    

"loc_FFEEA478:\n"
                           
                "BL      unlock_optical_zoom\n"                        
                "BL      sub_FFEEA71C\n"    
                "B       loc_FFEEA4B4\n"    

"loc_FFEEA480:\n"                           
                                        
                "BL      sub_FFEEABA0_my\n"   //----------------> 
                "B       loc_FFEEA4B4\n"    

"loc_FFEEA488:\n"                           
                                        
                "BL      sub_FFEEAFE8\n"    
                "B       loc_FFEEA4B4\n"    

"loc_FFEEA490:\n"                           
                                        
                "BL      sub_FFEEAE4C\n"    
                "B       loc_FFEEA4B4\n"    

"loc_FFEEA498:\n"                           
                                        
                "BL      sub_FFEEB158\n"    
                "B       loc_FFEEA4B4\n"    

"loc_FFEEA4A0:\n"                           
                                        
                "BL      sub_FFEEB320\n"    
                "B       loc_FFEEA4B4\n"    

"loc_FFEEA4A8:\n"                           
                                        
                "BL      sub_FFEEB070\n"    
                "B       loc_FFEEA4B4\n"    

"loc_FFEEA4B0:\n"                           
                                        
                "BL      sub_FFEEAE9C\n"    

"loc_FFEEA4B4:\n"                           
                                        
                "LDR     R1, [SP]\n"        

"loc_FFEEA4B8:\n"                           
                                        
                "LDR     R3, =0x91C68\n"    
                "MOV     R2, #0\n"          
                "STR     R2, [R1]\n"        
                "LDR     R0, [R3]\n"        
                "BL      sub_FFE82764\n" //PostMessageQueue

"loc_FFEEA4CC:\n"                           
                "LDR     R3, =0x91C64\n"    
                "MOV     R1, R4\n"          
                "LDR     R0, [R3]\n"        
                "MOV     R2, #0\n"          
                "BL      sub_FFE8234C\n" //ReceiveMessageQueue
                "LDR     R0, [SP]\n"        
                "LDR     R12, [R0]\n"       
                "CMP     R12, #0xC\n"       
                "MOV     R1, R0\n"          
                "BNE     loc_FFEEA428\n"    
                "LDR     R3, =0x91C60\n"    
                "LDR     R0, [R3]\n"        
                "BL      sub_FFE8311C\n" //GiveSemaphore  
                "BL      sub_FFE83910\n"
                "ADD     SP, SP, #4\n"      
                "LDMFD   SP!, {R4,PC}\n"    

 );
}

