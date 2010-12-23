#ifndef __PTP_H
#define __PTP_H

// N.B.: not checking to see if CAM_CHDK_PTP is set as ptp.h is currently
// only included by ptp.c (which already checks this before including ptp.h)

#define PTP_CHDK_VERSION_MAJOR 0  // increase only with backwards incompatible changes (and reset minor)
#define PTP_CHDK_VERSION_MINOR 2  // increase with extensions of functionality
/*
protocol version history
0.1 - initial proposal from mweerden, + luar
0.2 - Added ScriptStatus and ScriptSupport, based on work by ultimA
*/

#define PTP_OC_CHDK 0x9999

#define PTP_RC_OK 0x2001
#define PTP_RC_GeneralError 0x2002
#define PTP_RC_ParameterNotSupported 0x2006

// N.B.: unused parameters should be set to 0
enum {
  PTP_CHDK_Version = 0,     // return param1 is major version number
                            // return param2 is minor version number
  PTP_CHDK_GetMemory,       // param2 is base address (not NULL; circumvent by taking 0xFFFFFFFF and size+1)
                            // param3 is size (in bytes)
                            // return data is memory block
  PTP_CHDK_SetMemory,       // param2 is address
                            // param3 is size (in bytes)
                            // data is new memory block
  PTP_CHDK_CallFunction,    // data is array of function pointer and (long) arguments  (max: 10 args)
                            // return param1 is return value
  PTP_CHDK_TempData,        // data is data to be stored for later
                            // param2 is for the TD flags below
  PTP_CHDK_UploadFile,      // data is 4-byte length of filename, followed by filename and contents
  PTP_CHDK_DownloadFile,    // preceded by PTP_CHDK_TempData with filename
                            // return data are file contents
  PTP_CHDK_ExecuteScript,   // data is script to be executed
                            // param2 is language of script
                            // param3 is for the ES flags below
  PTP_CHDK_ScriptStatus,	// Script execution status
                            // param1 CHDK_PTP_SCRIPT_STATUS_RUN is set if a script running, cleared if not
							// all other bits and params are reserved for future use
  PTP_CHDK_ScriptSupport,   // Which scripting interfaces are supported in this build
                            // param1 CHDK_PTP_SUPPORT_LUA is set if lua is supported, cleared if not
							// all other bits and params are reserved for future use
} ptp_chdk_command;

// data types as used by TempData and ExecuteScript
enum {
  PTP_CHDK_TYPE_NOTHING = 0,
  PTP_CHDK_TYPE_NIL,
  PTP_CHDK_TYPE_BOOLEAN,
  PTP_CHDK_TYPE_INTEGER,
  PTP_CHDK_TYPE_STRING
} ptp_chdk_type;

// TempData flags
#define PTP_CHDK_TD_DOWNLOAD  0x1  // download data instead of upload
#define PTP_CHDK_TD_CLEAR     0x2  // clear the stored data; with DOWNLOAD this
                                   // means first download, then clear and
                                   // without DOWNLOAD this means no uploading,
                                   // just clear

// ExecuteScript flags
#define PTP_CHDK_ES_WAIT      0x1  // do not return after script initialisation
                                   // but wait until execution has finished
                                   // (should only be used with short execution
                                   // times)
#define PTP_CHDK_ES_RESULT    0x2  // only in combination with WAIT; return
                                   // param1 will be the ptp_chdk_type of the
                                   // code result and param2 the value (booleans
                                   // and integers) or length (strings)

// Script Languages - for execution
#define PTP_CHDK_SL_LUA    0
#define PTP_CHDK_SL_UBASIC 1

// bit flags for script status
#define PTP_CHDK_SCRIPT_STATUS_RUN   0x1
// bit flags for scripting support
#define PTP_CHDK_SCRIPT_SUPPORT_LUA  0x1

#endif // __PTP_H
