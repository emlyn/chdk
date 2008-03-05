#include <idc.idc>
#include "scan-lib.idc"

#define TRACE 0

/*
 * Searches recursively up the current function and finds all the tasks
 * this function is invoked from
 * scan-tasks.idc should be used first
 */

static searchTask(start, arr, calleeHash)
{
  auto x,y, fname;
  
  x = GetFunctionAttr(start, FUNCATTR_START);

  fname = GetFunctionName(x);

  if (GetHashLong(arr, atoa(x)) != 0){
     return;
  }
	

  SetHashLong(arr, atoa(x), 1);
  if (TRACE) Message("*** " + atoa(start) + "  " + atoa(x) + " - "+ fname + "\n");

  if (strstr(fname, "task_") == 0)
  {
     SetHashLong(calleeHash, fname, 1);
     return;
  }

  for( y=RfirstB(x); y != BADADDR; y=RnextB(x,y) )
  {
      searchTask(y, arr, calleeHash);
  }

}

static ResolveTask(a)
{
  auto t, fname, ea, arrId, calleeHash;

  fname = GetFunctionName(a);

  ea = GetFunctionAttr(a, FUNCATTR_START);
  
  DeleteArray( GetArrayId("visited") );
  DeleteArray( GetArrayId("found") );

  arrId = CreateArray("visited");
  calleeHash = CreateArray("found");
  
  searchTask(ea, arrId, calleeHash);

  fname = "Called tasks:\n";
  for (t = GetFirstHashKey(calleeHash); t != 0; t = GetNextHashKey(calleeHash, t)) {
      fname = fname + "    " + t + "\n";
  }

  Message("Found:"+fname);
//  SetFunctionCmt(ea, fname, 1);
  SetFunctionCmt(ea, fname, 0);

}



static main()
{

    
    ResolveTask(ScreenEA());
          
}

static test()
{

    auto at;

    DeleteArray( GetArrayId("attt") );

    at = CreateArray("attt");

    
    
    DelHashElement(at, "sss");

    SetHashLong(at, "sss", 234);

    Message(atoa(GetHashLong(at, "sss")));

    DeleteArray(at);

}


