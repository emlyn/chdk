#include <idc.idc>

/**
 * Common script to make a code.
 * Seems to make it too often and sometimes incorrectly.
 */

static main()
{
  auto sb, se, a, c, w, d;
  sb = 0xFF800000;
  se = GetSegmentAttr( sb, SEGATTR_END);

  c = 0;
  for (a=sb; a<se; a=a+4) {
    w = Word(a+2);
    d = Dword(a);
    if ((d==0xE1A0F00E ||  w == 0xE92D || w == 0xE52D) && isUnknown(GetFlags(a))) {
      MakeCode(a);
      c = c+1;
    }
  }
  Message( "Code found %d times\n", c);
}
