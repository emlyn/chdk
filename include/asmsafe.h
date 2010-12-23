#ifndef ASMSAFE_H
#define ASMSAFE_H

/*
macros to safely call C functions from most inline ASM
these should replace the use of __attribute__((naked)) functions for C code,
because C code is not actually legal in naked functions and can break in obscure ways.
see http://chdk.wikia.com/wiki/CHDK_Coding_Guidelines#Naked_functions
usage
    asm volatile (
        ...
        ASM_SAFE("BL my_func\n")
        ...
    )

you can set up arguments for the function inside the ASM_SAFE without worrying about preserving values
e.g
    ASM_SAFE(
        "MOV R0,#1\n"
        "BL my_func\n"
    )
*/

// push all regs except SP and PC
// push CSPR via R0
// restore value for R0 from stack
#define ASM_SAFE_ENTER \
    "STMFD SP!, {R0-R12,LR}\n" \
    "MRS R0, CPSR\n" \
    "STR R0,[SP,#-4]!\n" \
    "LDR R0,[SP,#4]\n"

// pop CSPR via R0
// pop all regs except SP and PC
#define ASM_SAFE_LEAVE \
    "LDR R0,[SP],#4\n" \
    "MSR CPSR_cxsf,R0\n" \
    "LDMFD SP!, {R0-R12,LR}\n"

#define ASM_SAFE(asmcode) \
    ASM_SAFE_ENTER \
    asmcode \
    ASM_SAFE_LEAVE

#endif    // ASMSAFE_H
