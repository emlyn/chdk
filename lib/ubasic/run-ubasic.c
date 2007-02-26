/*
 * Copyright (c) 2006, Adam Dunkels
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the author nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 */

#include "ubasic.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

static const char program_static[] =
"sleep 1000\n\
 if a<1 then let a=2\n\
 if b<1 then let b=3\n\
 for s=1 to a\n\
   shoot\n\
   gosub \"incEv\"\n\
 next s\n\
 shoot\n\
end\n\
\n\
:incEv   \n\
\n\
for n=1 to b\n\
  click \"right\"\n\
next n\n\
return\n";

/*---------------------------------------------------------------------------*/
int
main(int argc, char * argv[])
{
    char *program;
    if (argc == 1) {
        // buildin program
        program = (char *) program_static;
    } else {
        assert(argc == 2);
        FILE * f = fopen(argv[1], "r");

        fseek(f,0, SEEK_END);
        int sz = ftell(f);
        fseek(f,0, SEEK_SET);
        program = (char *) malloc(sz+3);
        int szr = fread(program,1,sz, f);
        fclose(f);
        if (szr != sz) {
            perror("Error reading program");
        }
        printf("size: %d, read: %d \n", sz, szr); 
        program[sz] = '\n';
        program[sz+1] = 0;
    }

    printf("Program:\n%s", program);
    ubasic_init(program);
    do {
        ubasic_run();
    } while(!ubasic_finished());

    if (ubasic_error){
        const char *msg;
        if (ubasic_error >= UBASIC_E_ENDMARK) {
            msg = ubasic_errstrings[UBASIC_E_UNKNOWN_ERROR];
        } else {
            msg = ubasic_errstrings[ubasic_error];
        }
        fprintf(stderr, "Ubasic error in Line %d: %s\n", ubasic_linenumber(), msg);
    }

  return 0;
}
/*---------------------------------------------------------------------------*/

