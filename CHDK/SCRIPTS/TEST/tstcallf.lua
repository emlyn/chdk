--[[
@title test native func interface
@param a 0 = event only 1 = unsafe!
@default a 0
--]]
logfile,msg=io.open("A/TSTCALLF.LOG","wb")
if not logfile then
	error(msg)
end

fail_count = 0
function log(status,fmt,...)
	local status_str
	if status then
		status_str=" OK\n"
	else
		status_str=" FAIL\n"
		fail_count = fail_count+1
	end
	logfile:write(string.format(fmt,...),status_str)
	return status
end

function want(vals)
	local t={want=true}
	for _,v in ipairs(vals) do
		t[v] = true
	end
	return t
end

function notwant(vals)
	local t={notwant=true}
	for _,v in ipairs(vals) do
		t[v] = true
	end
	return t
end

function log_evp(check,evp_name,...)
	local ret = call_event_proc(evp_name,...)
	local status = true
	if check.want then
		if not check[ret] then
			status = false
		end
	elseif check[ret] then
		status = false
	end
	log(status,"%s: %d",evp_name,ret)
	return ret,status
end

function log_cmp(name, expect, val)
	log(expect == val,"%s: [%s]==[%s]?",name,tostring(expect),tostring(val))
end

function log_printf(fmt,...)
	logfile:write(string.format(fmt,...))
end

-- note, this includes the terminating \0, which just another character in the string to lua
function bytes_from_cstring(bufptr,max)
	local bytes={}
	local i=0
	if max <= 0 then
		return bytes
	elseif not max then
		max=64*1024
	end
	repeat
		bytes[i+1]=peek(bufptr+i,1)
		i=i+1
	until(bytes[i] == 0 or i >= max)
	return bytes
end

function restore()
	if logfile then
		logfile:close()
		logfile = nil
	end
end

--[[
 example of writing machine code and executing it
 Note may crash without proper cache control
--]]
test_func_1_ops={
   0xe3a0007b, -- mov	r0, #123	; 0x7b
   0xe12fff1e, -- bx	lr
}

function func_to_buf(opcodes,buf)
	for i,v in ipairs(opcodes) do
		poke(buf+i*4,v)
	end
end

function do_test()
	if type(call_func_ptr) ~= "function" or type(call_event_proc) ~= "function"  then
		logfile:write("native call interface not found, aborting!\n")
		fail_count = 1
		return
	end
	-- load the functions we will use
	-- also test event proc with 0 args (1 arg to call_func_ptr)
	log_evp(notwant{-1},"SystemEventInit")


	-- get some memory to play with
	-- also test event proc with 1 args (2 arg to call_func_ptr)
	buf,status=log_evp(notwant{-1,0},"AllocateMemory",1024)

	if not status then
		logfile:write("Cannot continue!\n")
		return
	end

	-- evp name + dest + fmt = 3 args
	log_evp(want{2},"sprintf",buf,"hi")
	s=string.char(unpack(bytes_from_cstring(buf,32)))
	log_cmp("evp sprintf","hi\0",s)

	-- evp name + dest + fmt + 1 args = 4 args (boundery case low)
	log_evp(want{3},"sprintf",buf,"1:%d",1)
	s=string.char(unpack(bytes_from_cstring(buf,32)))
	log_cmp("evp sprintf","1:1\0",s)
	-- evp name + dest + fmt + 2 args = 5 args (boundery case high)
	log_evp(want{7},"sprintf",buf,"1:%d 2:%d",1,2)
	s=string.char(unpack(bytes_from_cstring(buf,32)))
	log_cmp("evp sprintf","1:1 2:2\0",s)
	-- evp name + dest + fmt + 6 args (stack test)
	log_evp(want{23},"sprintf",buf,"1:%d 2:%d 3:%d 4:%d 5:%d 6:%d",1,2,3,4,5,6)
	s=string.char(unpack(bytes_from_cstring(buf,32)))
	log_cmp("evp sprintf","1:1 2:2 3:3 4:4 5:5 6:6\0",s)
	if a>0 then
		func_to_buf(test_func_1_ops,buf)
		-- we're not being cache safe here, this gives it a chance to get evicted
		-- on a540, crashes without, works with. Could peek() a large range of mem
		sleep(10) 
		-- 0 args case
		r=call_func_ptr(buf)
		log_cmp("f()",r,123)
	end
	log_evp(notwant{-1},"FreeMemory",buf)
end

do_test()

if fail_count > 0 then
	print(fail_count,"FAILED")
	log_printf("%d FAILED\n",fail_count)
else
	print("OK")
	log_printf("OK\n")
end

restore()
