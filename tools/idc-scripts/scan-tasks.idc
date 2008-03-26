#include <idc.idc>
#include "scan-lib.idc"


#define ROM_START   0xFF800000


/*
 * Searches the interval of code for the invocation of CreateTask or CreateTaskStrictly
 * Renames appropriate task procedures with the full name of the task,
 * Also tries to rename task-related message queues
 */
 
static AnasyzeTask(a)
{
   auto op, tname, code, d;
   auto fstart;

   tname = "";

   fstart = GetFunctionAttr(a, FUNCATTR_START);

   for (code = a; code >= a-20; code = code-4) {
     
     if (isCode(GetFlags(code)) && strstr(GetDisasm(code), "LDR") == 0 && (GetOpnd(code, 0) == "R0"))
     {
         d = Dword(GetOperandValue(code, 1));
         if (d > ROM_START) {
             tname = getString(d);
         }
         break;
     }
     if (isCode(GetFlags(code)) && strstr(GetDisasm(code), "ADR") == 0 && (GetOpnd(code, 0) == "R0"))
     {
         d = GetOperandValue(code, 1);
         if (d > ROM_START) {
             tname = getString(d);
         }
         break;
     }

   }

   if (tname == "") return;

   Message( "task %s at:%x\n", tname, a);

   
   // Rename Callee function

   if (strstr(GetFunctionName(fstart), "sub_") == 0) {
       MakeNameEx(fstart, "taskcreate_"+tname, SN_PUBLIC);
       Message("Renamed %x to %s\n", fstart, GetFunctionName(fstart));
   }

   // Searching task start function
   d = 0;
   for (code = a; code >= a-40; code = code-4) {
     
     if (isCode(GetFlags(code)) && strstr(GetDisasm(code), "LDR") == 0 && (GetOpnd(code, 0) == "R3"))
     {
         d = Dword(GetOperandValue(code, 1));
         break;
     }
     if (isCode(GetFlags(code)) && strstr(GetDisasm(code), "ADR") == 0 && (GetOpnd(code, 0) == "R3"))
     {
         d = GetOperandValue(code, 1);
         break;
     }
   }
   if (d > ROM_START)
   {
       MakeNameEx(d, "task_"+tname, SN_PUBLIC);
       Message("Renamed %x to %s\n", d, GetFunctionName(d));
   }

   return;


   // Searching for CreateMessageQueue
   d = 0;
   for (code = a; code >= a-200; code = code-4) {
     
     if (isCode(GetFlags(code)) && strstr(GetDisasm(code), "BL") == 0 && (GetOpnd(code, 0) == "CreateMessageQueue"))
     {
         d = Dword(GetOperandValue(code+4, 1));
         break;
     }
   }
   // static RAM address
   if (d < 0x200000)
   {
       MakeNameEx(d, "task_"+tname+"_queue", SN_PUBLIC);
       MakeDword(d);
       Message("Renamed %x to %s\n", d, NameEx(BADADDR, d));
   }
   

}


static main()
{
  auto sb, se, a, c, cnt, w, d, str, res, op, tname;
  sb = ROM_START;
  se = GetSegmentAttr( sb, SEGATTR_END);

  cnt = 0;
  for (a=sb; a<se; a=a+4) {
//  for (a=0xff81f5b4; a<0xff81f5b4+0x10; a=a+4) {
      
      op = GetOpnd(a, 0);

      if (isCode(GetFlags(a)) && (op == "CreateTask" || op == "CreateTaskStrictly")) {

          AnasyzeTask(a);
          
          cnt = cnt+1;
          tname = "";
      }

  }

  Message( "Refs found %d times\n", cnt);

}


