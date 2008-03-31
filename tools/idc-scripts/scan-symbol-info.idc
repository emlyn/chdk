#include <idc.idc>
#include "scan-lib.idc"

static main()
{
  auto sb, se, a, c, w, d, code, pname, fstart, lno;
  sb = ROM_START;
  se = GetSegmentAttr( sb, SEGATTR_END);

  c = 0;
  for (a = sb; a < se; a = a + 4)
  {
      
      if (a % 0x10000 == 0) Message("    scan: %x/%x\n", a, se);

      if (strstr(GetDisasm(a), "DebugAssert") != -1)
      {
          
          pname = 0;
          lno = 0;

          for (code = a; code >= a-0x20; code = code-4)
          {
              if (pname == 0 && isCode(GetFlags(code)) && strstr(GetDisasm(code), "LDR") == 0 && (GetOpnd(code, 0) == "R0"))
              {
                  d = Dword(GetOperandValue(code, 1));
                  if (d > ROM_START)
                  {
                      pname = getString(d);
                  }
              }
              if (pname == 0 && isCode(GetFlags(code)) && strstr(GetDisasm(code), "ADR") == 0 && (GetOpnd(code, 0) == "R0"))
              {            
                  d = GetOperandValue(code, 1);
                  if (d > ROM_START)
                  {
                      pname = getString(d);
                  }
              }
              if (lno == 0 && isCode(GetFlags(code)) && strstr(GetDisasm(code), "MOV") == 0 && (GetOpnd(code, 0) == "R1"))
              {
                  lno = GetOperandValue(code, 1);
              }
          }

          if (pname == 0) continue;
          
          fstart = GetFunctionAttr(a, FUNCATTR_START);
          if (fstart == 0xFFFFFFFF) continue;

          // making a comment
          if (strstr(GetFunctionCmt(fstart, 1), "LOCATION:") == -1)
          {
              SetFunctionCmt(fstart, form("LOCATION: %s:%d", pname, lno), 1);
          }

          // renaming SUB
          if (strstr(GetFunctionName(fstart), "sub_") == 0 && strlen(GetFunctionName(fstart)) == 12)
          {
              auto pref;

              pref = "";
              if (strstr(GetFunctionName(fstart), "sub_") == 0) pref = "_";

              pname = form("%s%s__%s__%d", pref, GetFunctionName(fstart), pname, lno);
              MakeNameEx(fstart, pname, SN_PUBLIC);
              Message("Renamed %x to %s\n", fstart, pname);
          }

          c = c+1;
      }
  }

  Message( "Refs found %d times\n", c);
}
