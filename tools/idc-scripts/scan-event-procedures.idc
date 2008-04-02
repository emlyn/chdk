#include <idc.idc>
#include "scan-lib.idc"

/*
 * Searches the interval of code for the invocation of RegisterEventProcedure or similar
 * Renames appropriate procedures with the full name of the event procedure (prefix eventproc_,
 */
 
static MakeEventProcedure(pname, paddr)
{
   if (strstr(pname, "EventProcedure") != -1) return;

   if (strstr(GetFunctionName(paddr), "eventproc_") != -1) return;
   
   MakeCode(paddr);
   MakeCode(paddr+4);
   MakeCode(paddr+8);
   MakeFunction(paddr, BADADDR);
   MakeNameEx(paddr, "eventproc_"+pname, SN_PUBLIC);
   Message("Renamed %x to %s\n", paddr, "eventproc_"+pname);
}


static Anasyze(a, opname)
{
   auto op, code, d;
   auto fstart;
   auto pname, paddr;
   auto table;

   pname = 0;
   paddr = 0;

   table = "";

   fstart = GetFunctionAttr(a, FUNCATTR_START);


   if (opname == "RegisterEventProcedureTable")
   {
       for (code = a; code >= a-20; code = code-4)
       {
           if (paddr == 0 && isCode(GetFlags(code)) && strstr(GetDisasm(code), "LDR") == 0 && (GetOpnd(code, 0) == "R0"))
           {
               d = Dword(GetOperandValue(code, 1));
               if (d != 0) {
                   paddr = d;
               }
           }
       }

       if (paddr == 0 || paddr < ROM_START) {
           Message( "    NOT parsed table: %x (table=%x)\n", a, paddr);
           return;
       }

       Message( "event proc table at:%x\n", paddr);
       
       for (table = paddr; 1 ;table = table+8)
       {
           if (Dword(table) == 0 || Dword(table) == 0xFFFFFFFF) return;

           MakeDword(table);
           MakeDword(table+4);

           MakeEventProcedure(getString(Dword(table)), Dword(table+4));

       }       

   }
   else if (strstr(opname, "RegisterEventProcedure") == 0 || opname == "ExportToEventProcedure")
   {
       for (code = a; code >= a-20; code = code-4) {
         
//         Message(GetDisasm(code)+"\n");
         if (pname == 0 && isCode(GetFlags(code)) && strstr(GetDisasm(code), "LDR") == 0 && (GetOpnd(code, 0) == "R0"))
         {
             d = Dword(GetOperandValue(code, 1));
             if (d > ROM_START) {
                 pname = getString(d);
             }
         }
         if (pname == 0 && isCode(GetFlags(code)) && strstr(GetDisasm(code), "ADR") == 0 && (GetOpnd(code, 0) == "R0"))
         {            
             d = GetOperandValue(code, 1);
             if (d > ROM_START) {
                 pname = getString(d);
             }
         }
         if (paddr == 0 && isCode(GetFlags(code)) && strstr(GetDisasm(code), "LDR") == 0 && (GetOpnd(code, 0) == "R1"))
         {             
             d = Dword(GetOperandValue(code, 1));
             if (d > ROM_START) {
                 paddr = d;
             }
         }
         if (paddr == 0 && isCode(GetFlags(code)) && strstr(GetDisasm(code), "ADR") == 0 && (GetOpnd(code, 0) == "R1"))
         {             
             d = GetOperandValue(code, 1);
             if (d > ROM_START) {
                 paddr = d;
             }
         }
       }

       if (pname == 0 || paddr == 0) {
           Message( "    NOT parsed: %x\n", a);
           return;
       }

       //Message( "    event proc %s at:%x\n", pname, paddr);
       if (opname == "ExportToEventProcedure") {
           pname = "export_" + pname;
       }
       MakeEventProcedure(pname, paddr);
   }

   return;

}


static main()
{
  auto sb, se, a, c, cnt, w, d, str, res, op, tname;
  sb = ROM_START;
  se = GetSegmentAttr( sb, SEGATTR_END);

  cnt = 0;
  for (a=sb; a<se; a=a+4) {
//  for (a=0xff81f5b4; a<0xff81f5b4+0x10; a=a+4) {
      
      if (a % 0x10000 == 0) Message("    scan: %x/%x\n", a, se);
      
      op = GetOpnd(a, 0);

      if (isCode(GetFlags(a)) && (op == "RegisterEventProcedure"
                               || op == "RegisterEventProcedure2"
                               || op == "RegisterEventProcedure3"
                               || op == "RegisterEventProcedureTable"
                               || op == "ExportToEventProcedure")
         )
      {

          Anasyze(a, op);
          
          cnt = cnt+1;
          tname = "";
      }

  }

  Message( "    Refs found %d times\n", cnt);

}


