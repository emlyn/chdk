/*
unsigned call_func_ptr(void *func, const unsigned *args, unsigned n_args)
call a function using arguments specified in a buffer

See 
 ARM IHI 0042D Procedure Call Standard for the ARM Architecture
 ARM DUI 0056D ARM Developer Suite Developer Guide 
for information on calling conventions

Note that the latter mentions different calling conventions for variadic and
standard functions, but gcc appears to use the variadic form for all C functions

WARNING:
	NO effort is made to follow the rules for values larger than 32 bits as
	either arguments or returns. Handling this is up to the caller.

Uses:
	call ARM vararg functions from thumb
	construct the argument list at runtime, i.e. for lua
	call functions without a stub

func 
    Address of the function to call. This may be an ARM or Thumb function

args
    Array of 32 bit words to be treated as arguments to the function. 
    Per the normal ARM calling convention, bytes or shorts should be promoted to
    words before calling.
    Ignored if n_args is 0

n_args 
    Number of elements in args


*/
.text
.global call_func_ptr
call_func_ptr:
    STMFD   SP!, {R4-R5,LR}
    MOV     R12, R0             // function to call
    MOV     R4, SP              // save SP

    ADD     R5, R1, R2,LSL #2   // end = args + n_nargs*4
    RSBS    R0, R2, #4          // R0 = 4 - R2
    BLO     stack_setup
    ADD     PC, PC, R0,LSL #2   // skip over 4-n_args
    NOP                         // reading PC adds +8
    LDR     R3, [R5,#-4]!       // fourth arg
    LDR     R2, [R5,#-4]!       // third arg
    LDR     R1, [R5,#-4]!       // second arg
    LDR     R0, [R5,#-4]!       // first arg
    B       do_call             // regs done

stack_setup:
    SUB     R2, R2, #4          // number of stack args
    SUB     R2, R5, R2,LSL #2   // last = src - (n_stack_args)*4
    
stack_setup_loop:
    LDR     R0, [R5,#-4]!       // t=*(--src)
    STR     R0, [SP,#-4]!       // push t
    CMP     R5, R2
    BNE     stack_setup_loop    // while (src != last)

    LDMIA   R1, {R0-R3}         // if we had any stack args, need to load all 4 regs

do_call:
    BLX     R12                 // call the function
    MOV     SP, R4              // clean up stack
    LDMFD   SP!, {R4-R5,LR}
    BX      LR

