#include <idc.idc>

/*
 * Searches for the references to strings
 */

static main()
{
  auto sb, se, a, c, cnt, w, d, str, isstr;
  sb = 0xFF800000;
  se = GetSegmentAttr( sb, SEGATTR_END);

  cnt = 0;
  for (a=sb; a<se; a=a+4) {

    //d = Dword(a);
    d = a;

    if (d > 0xFF800000 && d < 0xFFFF0000) {
      
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
        if (!((c >= 0x41 && c <= 0x5F) || (c >= 0x61 && c <= 0x7A) || (c >= 0x20 && c <= 0x3F))) break;
      }while(1);

      if (str - d > 4 && str - d < 100 && isstr == 1 && isUnknown(GetFlags(d))) {
          Message( "Str found: %x-%d\n", d, str-d);
          MakeUnkn(d, str-d);
          MakeStr(d, str);
          cnt = cnt+1;
          //if (cnt > 2)
          //  break;
      }

    }
  }
  Message( "Refs found %d times\n", cnt);
}
