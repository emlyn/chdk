--[[
@title save ROM crash log to ROMLOG.LOG
requires CHDK built with native function call support
@param a remove old files 1=yes, 0=no
@default a 1
--]]

LOG_NAME="A/ROMLOG.LOG"
ERR_NAME="A/RomLogErr.txt"

function printf(...)
    print(string.format(...))
end

if (type(call_event_proc) ~= "function") then
    error("ERROR: your CHDK does not support native function calls")
end

if (call_event_proc("SystemEventInit") == -1) then
    -- Newest cams (DryOS rel 43 and later) only have System.Create()
    -- on older dryos cams SystemEventInit is an alias for System.Create()
    if (call_event_proc("System.Create") == -1) then
        error("ERROR: SystemEventInit and System.Create failed")
    end
end

if a ~= 0 then
    if (os.stat(LOG_NAME)) then
        printf("rm %s: %s",LOG_NAME,tostring(os.remove(LOG_NAME)));
    end
    if (os.stat(ERR_NAME)) then
        printf("rm %s: %s",ERR_NAME,tostring(os.remove(ERR_NAME)));
    end
end

-- first arg: filename, NULL for ROMLOG.TXT (dryos) or ROMLOG (vxworks)
-- second arg: if 0, shutdown camera after writing log
-- note, on vxworks the exception code, registers and stack trace are binary
r=call_event_proc("GetLogToFile",LOG_NAME,1) 

if r ~= 0 then
    printf("GetLogToFile return %d",r)
end

if (os.stat(ERR_NAME)) then
    if a ~= 0 then
        printf("FAIL check %s",ERR_NAME)
    else
        printf("%s exists",ERR_NAME)
    end
end

if (os.stat(LOG_NAME)) then
    printf("%s exists",LOG_NAME)
else
    printf("%s not written",LOG_NAME)
end

sleep(2000)
