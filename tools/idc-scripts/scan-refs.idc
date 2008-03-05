#include <idc.idc>

static main()
{
  auto sb, se, a, c, w, d;
  sb = 0xFF810000;
  se = GetSegmentAttr( sb, SEGATTR_END);

  c = 0;
  for (a=sb; a<se; a=a+4) {
    d = Dword(a);
    if (d > 0xFF800000 && d < 0xFFFF0000 && isData(GetFlags(a)) && strstr(GetDisasm(a), "DCB") != -1 ) {
      MakeUnkn(a, 4);
      MakeDword(a);
      Message( "Ref found: %x=%s\n", a, GetDisasm(a));
      c = c+1;
    }
  }
  Message( "Refs found %d times\n", c);
}
