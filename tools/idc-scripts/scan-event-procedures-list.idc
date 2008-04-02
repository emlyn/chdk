#include <idc.idc>
#include "scan-lib.idc"

/**
 * Common script to make a code.
 * Seems to make it too often and sometimes incorrectly.
 */

static main()
{
  auto sb, se, a, c, w, d, prevf, spaced;
  sb = ROM_START;
  se = GetSegmentAttr( sb, SEGATTR_END);

  c = 0;
  spaced = 0;

  w = fopen("stubs_entry_ida.S", "w");

  for (a=sb; a<se; a=a+4) {
    
                 //isCode(a) && 
    if ( GetFunctionAttr(a, FUNCATTR_START) == a )
    {
        d = GetFunctionName(a);

        if (strstr(d, "eventproc_") == 0) {
            Message(d+"\n");

            d = substr(d, strlen("eventproc_"), -1);

            fprintf(w, "NSTUB(eventproc_%s, 0x%x)\n", replace(d, ".", "_"), a);
//            a = GetFunctionAttr(a, FUNCATTR_END)-4;
            prevf = d;
            spaced = 0;
        }else{
            if (spaced == 0) fprintf(w, "\n");
            spaced = 1;
        }
    }

  }

  fclose(w);

}
