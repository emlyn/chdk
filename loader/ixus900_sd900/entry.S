    .section .entry

// start point of chdk ( execution of code begins at this file)

// Turn OFF SD Card power to support autostart
LDR     R3, =0xC0220048   // 0xC02200BC , 0xC0220068 , 0xC0220048 , 0xC022009c
MOV     R2, #0x44
STR     R2, [R3]

// looks like idle cycle is required for proper shutdown
MOV     R3, #0x8000
1:
   SUB  R3, R3, #1
   CMP  R3, #0
   BNE  1b

// ordinary startup...
// calls my_restart() in loader/ixus900_sd900/main.c
MOV     SP, #0x1900
MOV     R11, #0
B       my_restart

// next: loader/ixus900_sd900/main.c
