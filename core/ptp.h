#ifndef __PTP_H
#define __PTP_H
#define PTP_CHDK_VERSION_MAJOR 1  // increase only with backwards incompatible changes (and reset minor)
#define PTP_CHDK_VERSION_MINOR 0  // increase with extensions of functionality
/*
protocol version history
0.1 - initial proposal from mweerden, + luar
0.2 - Added ScriptStatus and ScriptSupport, based on work by ultimA
1.0 - removed old script result code (luar), replace with message system
*/

#define PTP_OC_CHDK 0x9999

#define PTP_RC_OK 0x2001
#define PTP_RC_GeneralError 0x2002
#define PTP_RC_ParameterNotSupported 0x2006
#define PTP_RC_InvalidParameter 0x201D

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
                            // return param1 is script id, like a process id
                            // return param2 is status, PTP_CHDK_S_ERRTYPE*
  PTP_CHDK_ScriptStatus,    // Script execution status
                            // return param1 bits
                            // CHDK_PTP_SCRIPT_STATUS_RUN is set if a script running, cleared if not
                            // CHDK_PTP_SCRIPT_STATUS_MSG is set if script messages from script waiting to be read
                            // all other bits and params are reserved for future use
  PTP_CHDK_ScriptSupport,   // Which scripting interfaces are supported in this build
                            // param1 CHDK_PTP_SUPPORT_LUA is set if lua is supported, cleared if not
                            // all other bits and params are reserved for future use
  PTP_CHDK_ReadScriptMsg,   // read next message from camera script system
                            // return param1 is chdk_ptp_s_msg_type
                            // return param2 is message subtype:
                            //   for script return and users this is ptp_chdk_script_data_type
                            //   for error it may be an error ptp_chdk_script_error_type
                            // return param3 is script id of script that generated the message
                            // return param4 is length of the message data
                            // return data is message.
                            // A minimum of 4 bytes of zeros is returned if there would not be data otherwise
  PTP_CHDK_WriteScriptMsg,  // write a message for scripts running on camera
                            // input param2 is target script id, 0=don't care. Messages for a non-running script will be discarded
                            // data length is handled by ptp data phase
                            // input messages do not have type or subtype, they are always a string destined for the script (similar to USER/string)
                            // output param1 is ptp_chdk_script_msg_status
} ptp_chdk_command;

// data types as used by ReadScriptMessage
enum {
  PTP_CHDK_TYPE_UNSUPPORTED = 0, // type name will be returned in data
  PTP_CHDK_TYPE_NIL,
  PTP_CHDK_TYPE_BOOLEAN,
  PTP_CHDK_TYPE_INTEGER,
  PTP_CHDK_TYPE_STRING, // NOTE tables currently returned as string
} ptp_chdk_script_data_type;

// TempData flags
#define PTP_CHDK_TD_DOWNLOAD  0x1  // download data instead of upload
#define PTP_CHDK_TD_CLEAR     0x2  // clear the stored data; with DOWNLOAD this
                                   // means first download, then clear and
                                   // without DOWNLOAD this means no uploading,
                                   // just clear

// Script Languages - for execution only lua is supported for now
#define PTP_CHDK_SL_LUA    0
#define PTP_CHDK_SL_UBASIC 1

// bit flags for script status
#define PTP_CHDK_SCRIPT_STATUS_RUN   0x1 // script running
#define PTP_CHDK_SCRIPT_STATUS_MSG   0x2 // messages waiting
// bit flags for scripting support
#define PTP_CHDK_SCRIPT_SUPPORT_LUA  0x1

// message types
enum {
    PTP_CHDK_S_MSGTYPE_NONE = 0, // no messages waiting
    PTP_CHDK_S_MSGTYPE_ERR,         // error message
    PTP_CHDK_S_MSGTYPE_RET,      // script return value
    PTP_CHDK_S_MSGTYPE_USER,     // message queued by script
// TODO chdk console data ?
} ptp_chdk_script_msg_type;

// error subtypes for PTP_CHDK_S_MSGTYPE_ERR and script startup status
enum {
    PTP_CHDK_S_ERRTYPE_NONE = 0,
    PTP_CHDK_S_ERRTYPE_COMPILE,
    PTP_CHDK_S_ERRTYPE_RUN,
} ptp_chdk_script_error_type;

// message status
enum {
    PTP_CHDK_S_MSGSTATUS_OK = 0, // queued ok
    PTP_CHDK_S_MSGSTATUS_NOTRUN, // no script is running
    PTP_CHDK_S_MSGSTATUS_QFULL,  // queue is full
    PTP_CHDK_S_MSGSTATUS_BADID,  // specified ID is not running
} ptp_chdk_script_msg_status;
#endif // __PTP_H
