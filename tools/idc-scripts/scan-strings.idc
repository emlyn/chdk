#include <idc.idc>
#include "scan-lib.idc"

/**
 * Searches for the strings in the area. IDA sometimes incorrectly detects strings as a code
 */

static main()
{
  auto sb, se, a, c, cnt, w, d, str, isstr, res;
  sb = ROM_START;
  se = GetSegmentAttr( sb, SEGATTR_END);

  cnt = 0;
  for (a=sb; a<se; a=a+4) {

    //d = Dword(a);
    d = a;

    if (d > ROM_START && d < 0xFFFF0000) {
      
      str = d;
      
      isstr = 0;
      do{
        c = Byte(str);
        str = str+1;
        if (str - d > 100) break;
        if (c == 0){
          isstr = 1;
          break;
        }
        if (!(  (c >= 0x20 && c <= 0x7F) || (c == 0x0A)  )) break;
      }while(1);

      if (str - d > 4 && str - d < 100 && isstr == 1) {
          MakeUnkn(d, str-d);
          res = MakeStr(d, str);

          Message( "Str found: %x-%d (%d)\n", d, str-d, res);

          cnt = cnt+1;
          a = (str & ~0x3);
          if (a != str) a = a+4;
          a = a-4;
          //if (cnt > 2)
          //  break;
      }

    }
  }
  Message( "Refs found %d times\n", cnt);
}
