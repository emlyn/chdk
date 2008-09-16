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


void __attribute__((naked,noinline)) sub_FFD4A69C_my(){
 asm volatile(
                "STMFD   SP!, {R4-R11,LR}\n"          
                "LDR     R5, =0x66A24\n"              
                "SUB     SP, SP, #0x14\n"             
                "LDR     LR, [R5]\n"                  
                "LDR     R12, =0x66A3C\n"             
                "ADD     LR, LR, #1\n"                
                "LDR     R4, [R12]\n"                 
                "STR     LR, [R5]\n"                  
                "LDR     R12, =0x66ABC\n"             
                "STR     R0, [SP,#0x10]\n"            
                "STR     R1, [SP,#0xC]\n"             
                "STR     R2, [SP,#8]\n"               
                "STR     R3, [SP,#4]\n"               
                "CMP     LR, R4\n"                    
                "LDR     R11, [R12]\n"                
                "MOVHI   R0, #0x80000001\n"           
                "BHI     loc_FFD4AB84\n"              
                "LDR     R3, =0x66AA0\n"              
                "MOV     R0, LR\n"                    
                "LDR     R1, [R3]\n"                  
                "BL      sub_FFEE753C\n"                 
                "CMP     R0, #1\n"                    
                "BNE     loc_FFD4A8BC\n"              
                "LDR     R0, =0x66AC4\n"              
                "LDR     R1, =0x66A10\n"              
                "LDR     R3, [R0]\n"                  
                "LDR     R2, [R1]\n"                  
                "CMP     R3, R2\n"                    
                "LDREQ   R3, =0x66AC0\n"              
                "LDREQ   R5, [R3]\n"                  
                "MOVNE   R5, R2\n"                    
                "LDR     R3, =0x66A24\n"              
                "LDR     R2, =0x66AA0\n"              
                "LDR     R0, [R3]\n"                  
                "LDR     R1, [R2]\n"                  
                "BL      sub_FFEE6EAC\n"                 
                "LDR     R3, =0x66A18\n"              
                "ADD     R0, R0, #1\n"                
                "AND     R0, R0, #1\n"                
                "STR     R5, [R3,R0,LSL#2]\n"         
                "LDR     R3, =0x66A0C\n"              
                "LDR     R2, [R3]\n"                  
                "CMP     R5, R2\n"                    
                "BHI     loc_FFD4A76C\n"              
                "LDR     R4, =0x66A5C\n"              
                "LDR     R3, [R4]\n"                  
                "ADD     R3, R5, R3\n"                
                "ADD     R3, R3, #8\n"                
                "CMP     R2, R3\n"                    
                "BCS     loc_FFD4A770\n"              

"loc_FFD4A764:\n"                                     
                                                  
                "MOV     R0, #0x80000003\n"           
                "B       loc_FFD4AB84\n"              


"loc_FFD4A76C:\n"                                     
                "LDR     R4, =0x66A5C\n"              

"loc_FFD4A770:\n"                                     
                "LDR     R3, [R4]\n"                  
                "LDR     R2, =0x66AC4\n"              
                "ADD     R1, R5, R3\n"                
                "LDR     R3, [R2]\n"                  
                "ADD     R2, R1, #8\n"                
                "CMP     R2, R3\n"                    
                "BLS     loc_FFD4A7BC\n"              
                "LDR     R2, =0x66AC0\n"              
                "LDR     R0, =0x66A0C\n"              
                "RSB     R3, R3, R1\n"                
                "LDR     R1, [R2]\n"                  
                "ADD     R3, R3, #8\n"                
                "LDR     R2, [R0]\n"                  
                "ADD     R1, R1, R3\n"                
                "CMP     R2, R1\n"                    
                "BCC     loc_FFD4A764\n"              
                "LDR     R3, =0x66A10\n"              
                "STR     R1, [R3]\n"                  
                "B       loc_FFD4A7C4\n"              


"loc_FFD4A7BC:\n"                                     
                "LDR     R3, =0x66A10\n"              
                "STR     R2, [R3]\n"                  

"loc_FFD4A7C4:\n"                                     
                "LDR     R3, [R4]\n"                  
                "LDR     R12, =0x66A70\n"             
                "ADD     R3, R3, #0x18\n"             
                "LDR     R2, [R12,#4]\n"              
                "MOV     R0, R3\n"                    
                "MOV     R1, #0\n"                    
                "CMP     R1, R2\n"                    
                "BHI     loc_FFD4AA08\n"              
                "BNE     loc_FFD4A7F4\n"              
                "LDR     R3, [R12]\n"                 
                "CMP     R0, R3\n"                    
                "BHI     loc_FFD4AA08\n"              

"loc_FFD4A7F4:\n"                                     
                "LDR     R4, [R4]\n"                  
                "LDR     LR, =0x66A78\n"              
                "STR     R4, [SP]\n"                  
                "LDR     R12, =0x66A70\n"             
                "LDR     R3, =0x66A24\n"              
                "LDMIA   LR, {R7,R8}\n"               
                "LDMIA   R12, {R5,R6}\n"              
                "LDR     R10, [R3]\n"                 
                "LDR     R2, =0x66AA0\n"              
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
                "BL      sub_FFEE6EAC\n"                 
                "CMP     R10, #1\n"                   
                "MLA     R0, R9, R0, R0\n"            
                "BEQ     loc_FFD4A8BC\n"              
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

"loc_FFD4A8BC:\n"                                     
                                                  
                "LDR     R2, =0x66A10\n"              
                "LDR     R3, =0x66AC4\n"              
                "LDR     R1, [R2]\n"                  
                "LDR     R0, [R3]\n"                  
                "ADD     R3, R1, #9\n"                
                "CMP     R3, R0\n"                    
                "BLS     loc_FFD4A8F8\n"              
                "LDR     R2, =0x66AC0\n"              
                "LDR     R3, [R2]\n"                  
                "ADD     R3, R3, R1\n"                
                "RSB     R3, R0, R3\n"                
                "LDR     R0, [SP,#0x10]\n"            
                "ADD     R3, R3, #8\n"                
                "STR     R3, [R0]\n"                  
                "B       loc_FFD4A904\n"              


"loc_FFD4A8F8:\n"                                     
                "ADD     R3, R1, #8\n"                
                "LDR     R1, [SP,#0x10]\n"            
                "STR     R3, [R1]\n"                  

"loc_FFD4A904:\n"                                     
                "LDR     R2, [SP,#0x10]\n"            
                "LDR     R1, =0x66A6C\n"              
                "LDR     R3, =0x66AC4\n"              
                "LDR     R12, [R2]\n"                 
                "LDR     R2, [R1]\n"                  
                "LDR     R0, [R3]\n"                  
                "ADD     R3, R12, R2\n"               
                "CMP     R3, R0\n"                    
                "BLS     loc_FFD4A958\n"              
                "LDR     R2, [SP,#0xC]\n"             
                "RSB     R0, R12, R0\n"               
                "STR     R0, [R2]\n"                  
                "LDR     R2, =0x66AC0\n"              
                "LDR     R3, [R1]\n"                  
                "LDR     R1, [R2]\n"                  
                "RSB     R3, R0, R3\n"                
                "LDR     R0, [SP,#8]\n"               
                "STR     R1, [R0]\n"                  
                "LDR     R1, [SP,#4]\n"               
                "STR     R3, [R1]\n"                  
                "B       loc_FFD4A974\n"              


"loc_FFD4A958:\n"                                     
                "LDR     R0, [SP,#0xC]\n"             
                "STR     R2, [R0]\n"                  
                "LDR     R1, [SP,#4]\n"               
                "MOV     R3, #0\n"                    
                "STR     R3, [R1]\n"                  
                "LDR     R2, [SP,#8]\n"               
                "STR     R3, [R2]\n"                  

"loc_FFD4A974:\n"                                     
                "LDR     R0, =0x66A10\n"              
                "LDR     R1, =0x66A0C\n"              
                "LDR     R3, [R0]\n"                  
                "LDR     R2, [R1]\n"                  
                "CMP     R3, R2\n"                    
                "BHI     loc_FFD4A9A0\n"              
                "LDR     R0, [SP,#0xC]\n"             
                "LDR     R3, [R0]\n"                  
                "ADD     R3, R12, R3\n"               
                "CMP     R2, R3\n"                    
                "BCC     loc_FFD4A764\n"              

"loc_FFD4A9A0:\n"                                     
                "LDR     R1, [SP,#8]\n"               
                "LDR     R2, [R1]\n"                  
                "CMP     R2, #0\n"                    
                "BEQ     loc_FFD4A9D4\n"              
                "LDR     R3, =0x66A0C\n"              
                "LDR     R1, [R3]\n"                  
                "CMP     R2, R1\n"                    
                "BHI     loc_FFD4A9D4\n"              
                "LDR     R0, [SP,#4]\n"               
                "LDR     R3, [R0]\n"                  
                "ADD     R3, R2, R3\n"                
                "CMP     R1, R3\n"                    
                "BCC     loc_FFD4A764\n"              

"loc_FFD4A9D4:\n"                                     
                                                  
                "LDR     R3, =0x66A6C\n"              
                "LDR     R0, =0x66A70\n"              
                "LDR     R2, [R3]\n"                  
                "LDR     R3, [R0,#4]\n"               
                "ADD     R2, R2, #0x18\n"             
                "MOV     R1, R2\n"                    
                "MOV     R2, #0\n"                    
                "CMP     R2, R3\n"                    
                "BHI     loc_FFD4AA08\n"              
                "BNE     loc_FFD4AA10\n"              
                "LDR     R3, [R0]\n"                  
                "CMP     R1, R3\n"                    
                "BLS     loc_FFD4AA10\n"              

"loc_FFD4AA08:\n"                                     
                                                  
                "MOV     R0, #0x80000005\n"           
                "B       loc_FFD4AB84\n"              


"loc_FFD4AA10:\n"                                     
                                                  
                "LDR     R1, =0x66A54\n"              
                "LDR     R0, =0x66AA0\n"              
                "LDR     R3, [R1]\n"                  
                "LDR     R2, [R0]\n"                  
                "ADD     R3, R3, R2,LSL#4\n"          
                "ADD     R3, R3, R3,LSL#2\n"          
                "LDR     R12, =0x66A70\n"             
                "MOV     R3, R3,LSL#1\n"              
                "ADD     R3, R3, #0xA0\n"             
                "LDR     R2, [R12,#4]\n"              
                "MOV     R0, R3\n"                    
                "MOV     R1, #0\n"                    
                "CMP     R1, R2\n"                    
                "BHI     loc_FFD4AA58\n"              
                "BNE     loc_FFD4AA7C\n"              
                "LDR     R3, [R12]\n"                 
                "CMP     R0, R3\n"                    
                "BLS     loc_FFD4AA7C\n"              

"loc_FFD4AA58:\n"                                     
                "LDR     R4, =0x66A88\n"              
                "LDR     R1, [R4]\n"                  
                "CMP     R1, #0\n"                    
                "BNE     loc_FFD4AA7C\n"              
                "MOV     R0, #0x3140\n"               
                "ADD     R0, R0, #8\n"                
                "BL      sub_FFD63E6C\n"              
                "MOV     R3, #1\n"                    
                "STR     R3, [R4]\n"                  

"loc_FFD4AA7C:\n"                                     
                                                  
                "LDR     R1, =0x66A54\n"              
                "LDR     R0, =0x66AA0\n"              
                "LDR     R2, [R1]\n"                  
                "LDR     R3, [R0]\n"                  
                "LDR     R0, =0x66A78\n"              
                "ADD     R2, R2, R3,LSL#4\n"          
                "MVN     R3, #0x9F\n"                 
                "ADD     R2, R2, R2,LSL#2\n"          
                "ADD     R3, R3, #0x40000000\n"       
                "SUB     R3, R3, R2,LSL#1\n"          
                "LDR     R1, [R0,#4]\n"               
                "MOV     R4, R3\n"                    
                "MOV     R5, #0\n"                    
                "CMP     R1, R5\n"                    
                "BHI     loc_FFD4AAC8\n"              
                "BNE     loc_FFD4AAEC\n"              
                "LDR     R3, [R0]\n"                  
                "CMP     R3, R4\n"                    
                "BLS     loc_FFD4AAEC\n"              

"loc_FFD4AAC8:\n"                                     
                "LDR     R4, =0x66A88\n"              
                "LDR     R1, [R4]\n"                  
                "CMP     R1, #0\n"                    
                "BNE     loc_FFD4AAEC\n"              
                "MOV     R0, #0x3140\n"               
                "ADD     R0, R0, #8\n"                
                "BL      sub_FFD63E6C\n"              
                "MOV     R3, #1\n"                    
                "STR     R3, [R4]\n"                  

"loc_FFD4AAEC:\n"                                     
                                                  
                "LDR     R3, =0x66AA0\n"              
                "LDR     R0, =0x66A3C\n"              
                "LDR     R2, [R3]\n"                  
                "LDR     R12, =0x66A24\n"             
                "LDR     R1, [R0]\n"                  
                "ADD     R3, R2, R2,LSL#2\n"          
                "ADD     R2, R2, R3,LSL#1\n"          
                "LDR     R0, [R12]\n"                 
                "RSB     R1, R2, R1\n"                
                "CMP     R0, R1\n"                    
                "BLS     loc_FFD4AB3C\n"              
                "LDR     R4, =0x66A88\n"              
                "LDR     R1, [R4]\n"                  
                "CMP     R1, #0\n"                    
                "BNE     loc_FFD4AB3C\n"              
                "MOV     R0, #0x3140\n"               
                "ADD     R0, R0, #8\n"                
                "BL      sub_FFD63E6C\n"              
                "MOV     R3, #1\n"                    
                "STR     R3, [R4]\n"                  

"loc_FFD4AB3C:\n"                                     
                                                  
                "LDR     R3, =0x66A78\n"              
                "LDR     R12, =0x66A6C\n"             
                "LDMIA   R3, {R1,R2}\n"               
                "LDR     R0, [R12]\n"                 
                "MOV     R4, #0\n"                    
                "MOV     R3, #0x18\n"                 
                "ADDS    R1, R1, R0\n"                
                "ADC     R2, R2, #0\n"                
                "ADDS    R1, R1, R3\n"                
                "ADC     R2, R2, R4\n"                
                "CMP     R2, #0\n"                    
                "BHI     loc_FFD4AB78\n"              
                "BNE     loc_FFD4AB80\n"              
                "CMP     R1, #0x40000000\n"
         //     "BLS     loc_FFD4AB80\n"  //-
                "B       loc_FFD4AB80\n"  //+      

"loc_FFD4AB78:\n"                                     
                "MOV     R0, #0x80000007\n"           
                "B       loc_FFD4AB84\n"              


"loc_FFD4AB80:\n"                                     
                                                  
                "MOV     R0, #0\n"                    

"loc_FFD4AB84:\n"                                     
                                                  
                "ADD     SP, SP, #0x14\n"             
                "LDMFD   SP!, {R4-R11,PC}\n"          
 );
}

void __attribute__((naked,noinline)) sub_FFD49A8C_my(){
 asm volatile(
                "CMP     R2, #1\n"                    
                "STMFD   SP!, {R4-R7,LR}\n"           
                "MOV     R7, R0\n"                    
                "MOV     R6, R1\n"                    
                "MOVEQ   R3, #0x79\n"                 
                "STREQ   R3, [R6]\n"                  
                "LDMEQFD SP!, {R4-R7,PC}\n"           
                "LDR     R12, =0x66788\n"             
                "LDR     R0, [R12]\n"                 
                "LDR     R3, =0x66790\n"              
                "CMP     R0, #0\n"                    
                "LDR     R1, [R3]\n"                  
                "BEQ     loc_FFD49AD4\n"              
                "LDR     R2, =0x66794\n"              
                "LDR     R3, [R2]\n"                  
                "CMP     R3, #1\n"                    
                "BNE     loc_FFD49AE8\n"              
                "B       loc_FFD49AD8\n"              


"loc_FFD49AD4:\n"                                     
                "LDR     R2, =0x66794\n"              

"loc_FFD49AD8:\n"                                     
                "MOV     R3, #0\n"                    
                "STR     R3, [R2]\n"                  
                "STR     R7, [R12]\n"                 
                "B       loc_FFD49BA0\n"              


"loc_FFD49AE8:\n"                                     
                "LDR     R2, =0x6678C\n"              
                "LDR     R3, [R2]\n"                  
                "LDR     R5, =table1\n"  //+ 0xFFD498FC       
                "ADD     R3, R3, R3,LSL#1\n"          
                "MOV     LR, R3,LSL#2\n"              
                "LDR     R2, [R5,LR]\n"               
                "LDR     R4, =table2\n" //+  0xFFD49920      
                "RSB     R12, R2, R0\n"               
                "LDR     R3, [R4,LR]\n"               
                "CMP     R12, #0\n"                   
                "RSB     R0, R3, R0\n"                
                "BLE     loc_FFD49B4C\n"              
                "ADD     R3, R5, #4\n"                
                "LDR     R2, [R3,LR]\n"               
                "CMP     R2, R12\n"                   
                "ADDGE   R1, R1, #1\n"                
                "BGE     loc_FFD49B40\n"              
                "ADD     R3, R5, #8\n"                
                "LDR     R2, [R3,LR]\n"               
                "CMP     R2, R12\n"                   
                "ADDGE   R1, R1, #2\n"                
                "ADDLT   R1, R1, #3\n"                

"loc_FFD49B40:\n"                                     
        //      "CMP     R1, #0xE\n" //-               
        //      "MOVGE   R1, #0xE\n" //-               
                "CMP     R1, #0x1A\n" //+               
                "MOVGE   R1, #0x1A\n" //+               

                "B       loc_FFD49B84\n"              


"loc_FFD49B4C:\n"                                     
                "CMP     R0, #0\n"                    
                "BGE     loc_FFD49B84\n"              
                "ADD     R3, R4, #4\n"                
                "LDR     R2, [R3,LR]\n"               
                "CMP     R2, R0\n"                    
                "SUBLE   R1, R1, #1\n"                
                "BLE     loc_FFD49B7C\n"              
                "ADD     R3, R4, #8\n"                
                "LDR     R2, [R3,LR]\n"               
                "CMP     R2, R0\n"                    
                "SUBLE   R1, R1, #2\n"                
                "SUBGT   R1, R1, #3\n"                

"loc_FFD49B7C:\n"                                     
                "CMP     R1, #0\n"                    
                "MOVLT   R1, #0\n"                    

"loc_FFD49B84:\n"                                     
                                                  
                "LDR     R0, =0x66790\n"              
                "LDR     R3, [R0]\n"                  
                "CMP     R1, R3\n"                    
                "LDRNE   R2, =0x66794\n"              
                "MOVNE   R3, #1\n"                    
                "STRNE   R1, [R0]\n"                  
                "STRNE   R3, [R2]\n"                  

"loc_FFD49BA0:\n"                                     
                "LDR     R3, =0x66790\n"              
       //       "LDR     R1, =0x6194\n"  //-         
                "LDR     R1, =video_mode\n"  //+
                "LDR     R0, [R3]\n"                  
                "LDR     R2, =CompressionRateTable\n"    //+ 0xFFD498C0
                "LDR     R12, [R1]\n"
                "LDR     R12, [R12]\n"    //+                 
                "LDR     LR, [R2,R0,LSL#2]\n"         
                "LDR     R3, =0x66788\n"              
                "CMP     R12, #1\n"                   
                "STR     R7, [R3]\n"                  
                "STR     LR, [R6]\n"                  
       //       "MOVEQ   R3, #0xB\n"    // -

                "LDREQ   R3, =video_quality\n"       // +
                "LDREQ   R3, [R3]\n"           // +
                "LDREQ   R3, [R3]\n"           // +

                "STREQ   R3, [R6]\n"                  
                "BL      mute_on_zoom\n"     // +
                "LDMFD   SP!, {R4-R7,PC}\n"           
 );
}


void __attribute__((naked,noinline)) sub_FFD48FC8_my(){
 asm volatile(
                "STMFD   SP!, {R4-R11,LR}\n"          
                "LDR     R5, =0x666CC\n"              
                "SUB     SP, SP, #0x34\n"             
                "LDR     R3, [R5]\n"                  
                "CMP     R3, #3\n"                    
                "MOV     R4, R0\n"                    
                "MOVEQ   R3, #4\n"                    
                "STREQ   R3, [R5]\n"                  
                "LDR     R3, =0x6677C\n"              
                "MOV     LR, PC\n"                    
                "LDR     PC, [R3]\n"                  
                "LDR     R2, [R5]\n"                  
                "CMP     R2, #4\n"                    
                "BNE     loc_FFD4918C\n"              
                "ADD     R0, SP, #0x30\n"             
                "ADD     R1, SP, #0x2C\n"             
                "ADD     R2, SP, #0x28\n"             
                "ADD     R3, SP, #0x24\n"             
                "BL      sub_FFD4A69C_my\n"  //--------->           
                "CMP     R0, #0\n"                    
                "BNE     loc_FFD49044\n"              
                "LDR     R3, =0x666B8\n"              
                "LDR     R2, [R3]\n"                  
                "CMP     R2, #1\n"                    
                "BNE     loc_FFD49058\n"              
                "LDR     R2, =0x66710\n"              
                "LDR     R1, =0x666E4\n"              
                "LDR     R12, [R2]\n"                 
                "LDR     R3, [R1]\n"                  
                "CMP     R12, R3\n"                   
                "BCC     loc_FFD49058\n"              

"loc_FFD49044:\n"                                     
                "BL      sub_FFD491D8\n"              
                "BL      sub_FFD493D8\n"              
                "MOV     R3, #5\n"                    
                "STR     R3, [R5]\n"                  
                "B       loc_FFD4918C\n"              


"loc_FFD49058:\n"                                     
                                                  
                "LDR     R12, =0x66718\n"             
                "LDR     R11, =0x66724\n"             
                "LDMIB   R4, {R0-R2}\n"               
                "LDR     R10, [R12]\n"                
                "LDR     R7, [R11]\n"                 
                "LDR     R4, [SP,#0x2C]\n"            
                "LDR     R5, [SP,#0x28]\n"            
                "LDR     R6, [SP,#0x24]\n"            
                "LDR     R8, =0x666BC\n"              
                "LDR     R3, [SP,#0x30]\n"            
                "ADD     R12, SP, #0x20\n"            
                "ADD     LR, SP, #0x1C\n"             
                "MOV     R9, #1\n"                    
                "STMEA   SP, {R4-R6,R12}\n"           
                "STR     R10, [SP,#0x10]\n"           
                "STR     R7, [SP,#0x14]\n"            
                "STR     LR, [SP,#0x18]\n"            
                "STR     R9, [R8]\n"                  
                "BL      sub_FFC88214\n"              
                "LDR     R3, =0x665D4\n"              
                "MOV     R1, #0x3E8\n"                
                "LDR     R0, [R3]\n"                  
                "BL      sub_FFC114CC\n"             
                "CMP     R0, #9\n"                    
                "BNE     loc_FFD490CC\n"              
                "BL      sub_FFD4AEAC\n"              
                "LDR     R3, =0x666CC\n"              
                "LDR     R0, =0xFFD48FB0\n"       
                "B       loc_FFD490E4\n"              


"loc_FFD490CC:\n"                                     
                "LDR     R5, [SP,#0x1C]\n"            
                "CMP     R5, #0\n"                    
                "BEQ     loc_FFD490F0\n"              
                "BL      sub_FFD4AEAC\n"              
                "LDR     R3, =0x666CC\n"              
                "LDR     R0, =0xFFD48FBC\n"       

"loc_FFD490E4:\n"                                     
                "STR     R9, [R3]\n"                  
                "BL      sub_FFD5F5EC\n"              
                "B       loc_FFD4918C\n"              


"loc_FFD490F0:\n"                                     
                "BL      sub_FFC88380\n"              
                "LDR     R0, [SP,#0x30]\n"            
                "LDR     R1, [SP,#0x20]\n"            
                "BL      sub_FFD4ABD0\n"              
                "LDR     R4, =0x66710\n"              
                "LDR     R3, [R4]\n"                  
                "ADD     R3, R3, #1\n"                
                "LDR     R0, [SP,#0x20]\n"            
                "MOV     R1, R11\n"                   
                "STR     R3, [R4]\n"                  
                "MOV     R2, R5\n"                    
                "BL      sub_FFD49A8C_my\n"         //-------------->     
                "LDR     R3, =0x66730\n"              
                "LDR     R1, [R4]\n"                  
                "LDR     R2, [R3]\n"                  
                "LDR     R12, =0x6672C\n"             
                "MUL     R0, R2, R1\n"                
                "LDR     R1, [R12]\n"                 
                "BL      sub_FFEE6EAC\n"                 
                "LDR     R7, =0x66728\n"              
                "LDR     R3, [R7]\n"                  
                "MOV     R4, R0\n"                    
                "CMP     R3, R4\n"                    
                "BNE     loc_FFD49164\n"              
                "LDR     R6, =0x666C0\n"              
                "LDR     R3, [R6]\n"                  
                "CMP     R3, #1\n"                    
                "BNE     loc_FFD49180\n"              
                "B       loc_FFD49168\n"              


"loc_FFD49164:\n"                                     
                "LDR     R6, =0x666C0\n"              

"loc_FFD49168:\n"                                     
                "LDR     R3, =0x66760\n"              
                "MOV     R0, R4\n"                    
                "MOV     LR, PC\n"                    
                "LDR     PC, [R3]\n"                  
                "STR     R5, [R6]\n"                  
                "STR     R4, [R7]\n"                  

"loc_FFD49180:\n"                                     
                "LDR     R2, =0x666BC\n"              
                "MOV     R3, #0\n"                    
                "STR     R3, [R2]\n"                  

"loc_FFD4918C:\n"                                     
                                                  
                "ADD     SP, SP, #0x34\n"             
                "LDMFD   SP!, {R4-R11,PC}\n"          
 );
}




void __attribute__((naked,noinline)) movie_record_task(){
 asm volatile(
                "STMFD   SP!, {R4,LR}\n"              
                "SUB     SP, SP, #4\n"                
                "MOV     R4, SP\n"                    
                "B       loc_FFD488F0\n"              


"loc_FFD4884C:\n"                                      
                "LDR     R3, =0x666B0\n"              
                "LDR     R2, [R3]\n"                  
                "CMP     R2, #0\n"                    
                "BNE     loc_FFD488DC\n"              
                "SUB     R3, R12, #2\n"               
                "CMP     R3, #9\n"                    
                "LDRLS   PC, [PC,R3,LSL#2]\n"         
                "B       loc_FFD488DC\n"              

                ".long loc_FFD4889C\n"
                ".long loc_FFD488B4\n"
                ".long loc_FFD488BC\n"
                ".long loc_FFD488C4\n"
                ".long loc_FFD488A4\n"
                ".long loc_FFD488CC\n"
                ".long loc_FFD488AC\n"
                ".long loc_FFD488DC\n"
                ".long loc_FFD488D4\n"
                ".long loc_FFD48894\n"


"loc_FFD48894:\n"                                      
                                                  
                "BL      sub_FFD48988\n"              
                "B       loc_FFD488D8\n"              


"loc_FFD4889C:\n"
        
                "BL      unlock_optical_zoom\n"                                  
                "BL      sub_FFD48B3C\n"  
                "B       loc_FFD488D8\n"              


"loc_FFD488A4:\n"                                      
                                                  
                "BL      sub_FFD48FC8_my\n"   // --------->                      
                "B       loc_FFD488D8\n"              


"loc_FFD488AC:\n"                                      
                                                  
                "BL      sub_FFD493FC\n"              
                "B       loc_FFD488D8\n"              


"loc_FFD488B4:\n"                                      
                                                  
                "BL      sub_FFD49260\n"              
                "B       loc_FFD488D8\n"              


"loc_FFD488BC:\n"                                      
                                                  
                "BL      sub_FFD4956C\n"              
                "B       loc_FFD488D8\n"              


"loc_FFD488C4:\n"                                      
                                                  
                "BL      sub_FFD49730\n"              
                "B       loc_FFD488D8\n"              


"loc_FFD488CC:\n"                                      
                                                  
                "BL      sub_FFD49484\n"              
                "B       loc_FFD488D8\n"              


"loc_FFD488D4:\n"                                      
                                                  
                "BL      sub_FFD492B0\n"              

"loc_FFD488D8:\n"                                      
                                                  
                "LDR     R1, [SP]\n"                  

"loc_FFD488DC:\n"                                      
                                                  
                "LDR     R3, =0x665E4\n"              
                "MOV     R2, #0\n"                    
                "STR     R2, [R1]\n"                  
                "LDR     R0, [R3]\n"                  
                "BL      sub_FFC10D38\n"          

"loc_FFD488F0:\n"                                      
                "LDR     R3, =0x665E0\n"              
                "MOV     R1, R4\n"                    
                "LDR     R0, [R3]\n"                  
                "MOV     R2, #0\n"                    
                "BL      sub_FFC10920\n"       
                "LDR     R0, [SP]\n"                  
                "LDR     R12, [R0]\n"                 
                "CMP     R12, #0xC\n"                 
                "MOV     R1, R0\n"                    
                "BNE     loc_FFD4884C\n"              
                "LDR     R3, =0x665DC\n"              
                "LDR     R0, [R3]\n"                  
                "BL      sub_FFC116B4\n"             
                "BL      sub_FFC11E7C\n"                  
                "ADD     SP, SP, #4\n"                
                "LDMFD   SP!, {R4,PC}\n"              
 );
}

