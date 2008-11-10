--[[
@title lua lib test
@param a skip io
@default a 0
@param b skip all os
@default b 0
@param c skip os time
@default c 0
@param d skip os time fmt
@default d 0
@param e skip os filesystem
@default e 0
]]

do_io=a==0
do_os=b==0
do_time=c==0
do_fmtdump=d==0
do_dir=e==0

nfail=0
want_ok=true
no_rec=false

iotfnam="A/iotest0.txt"

-- we require minimal io functionality to run the test
if type(io) ~= "table" then
	error("missing io, aborting!")
end

function log(...)
	io.write(...)
-- most crashes leave no log even if we flush, and it's really slow :(
--	io.output():flush()
end
-- record result
function rec(r)
	local f
	if no_rec then
		return "NA"
	end
	if want_ok then
		f=not r
	else
		f=r
	end
	if f then
		nfail=nfail+1
		return "FAIL"
	end
	return "PASS"
end
function logrec(s,r,...)
	log(s)
	if ... then
		log(" ",...)
	end
	log(" ",rec(r))
	log("\n")
end
function logok(...)
	logrec("OK",true,...)
end
function logfail(...)
	logrec("ERR",false,...)
end
function logres(r)
	if r then
		logok()
	else
		logfail()
	end
	return r
end

function fpinfo(f,name)
	if type(name) ~= "string" then
		name="<unk>"
	end
	log("file info for ",name,": ")
	local t=io.type(f)
	if not t then
		log("not a file!\n")
	elseif t == "file" then
		log("valid file\n")
		log(" ptr: ",f:_getfptr())
		local fpv={}
		for i=0,8 do
			fpv[i]=peek(f:_getfptr() + i*4)
		end
		log(" fd: ",fpv[0])
		log(" len: ",fpv[1])
		log(" pos: ",fpv[3],"\n")
		log(" raw vals:")
		for i=0,8 do
			log(" ",i*4,":",fpv[i])
		end
		log("\n")
	else 
		log("closed file!\n")
	end
end

-- wrap file obj with logging
tfproto={
	fpinfo=function(self)
		fpinfo(self.f,self.name)
	end,
	open=function(self,name,mode)
		log('io.open("',tostring(name),'","',tostring(mode),'"): ')
		self.f,msg=io.open(name,mode)
		if self.f then
			self.name=name
			logok()
		else
			logfail('msg=',tostring(msg))
		end
		return self.f,msg
	end,
	rawtell=function(self)
		return peek(self.f:_getfptr() + 12)
	end,
	seek=function(self,whence,offset)
		log(self.name,':seek("',tostring(whence),'",',tostring(offset),'): ')
		if io.type(self.f) ~= "file" then
			log("not an open file!\n")
			return
		end
		local r=self.f:seek(whence,offset)
		if r then
			if r == self:rawtell() then
				logok(tostring(r))
			else
				logfail("\n position mismatch r ",tostring(r)," != ", tostring(self:rawtell()))
			end
		else
			logfail(tostring(r))
		end
		return r
	end,
	write=function(self,...)
		log(self.name,":write(...): ")
		return logres(self.f:write(...))
	end,
	read=function(self,...)
		log(self.name,":read(",...,"): ")
		local r={self.f:read(...)}
		if table.maxn(r) == 0 then
			log("<no results>")
		else
			for i=1,table.maxn(r) do
				log(type(r[i])," [",tostring(r[i]),"] ")
			end
		end
		log("\n")
		rec(r[1]) -- only useful if you use a single format in tests
		return unpack(r)
	end,
	flush=function(self)
		log(self.name,":flush(): ");
		return logres(self.f:flush())
	end,
	close=function(self)
		log(self.name,":close(): ");
		local r=self.f:close()
		self.f=nil
		self.name=nil
		return logres(r)
	end,
	new=function(self,name,mode)
		local tf={}
		for k,v in pairs(tfproto) do
			tf[k]=v
		end
		if name then
			tf:open(name,mode)
		end
		return tf
	end,
}

function test_readn(tf)
	local done
	local ns={}
	local want={1,2,3,1234567890}
	local c=1
	log('testing file:read("*n")\n')
	no_rec=true -- too complicated 
	while not done do
		local t=tf:read("*n")
		tf:seek() -- report pos
		if t then
			ns[c]=t
			c=c+1
		else
			t=tf:read(1)
			tf:seek()
			if not t then
				done=true
			end
		end
	end
	no_rec=false
	for i=1,c-1 do
		if ns[i] ~= want[i] then
			logfail(ns[i], " != ",want[i])
		end
	end
	if c ~= 5 then
		logfail("want 5 got ",c)
	end
end

function tstart(n)
	nfail=0
	want_ok=true
	no_rec=false
	log("***test ",n,"***\n")
end

function tend(n)
	s="***end "..n
	if nfail > 0 then
		s=s.." FAIL "..tostring(nfail)
	else
		s=s.." OK"
	end
	s=s.."***"
	log(s,"\n")
	print(s)
end

function io_test()
	tstart("io")
	fpinfo(io.input(),"io.input") -- expect closed
	fpinfo(io.output(),"io.output") -- expect open

	local tf=tfproto:new(iotfnam,"w+b")
	if not tf.f then
		log("aborting\n")
		return
	end
	tf:write("the slick brown fox jumps over the lazy dog\n")
	tf:seek("set",4)
	local s=tf:read(5)
	if s ~= "slick" then
		logfail("want [slick] got [",tostring(s),"]")
	end
	tf:seek() -- report pos
	tf:seek("cur",-5)
	tf:write("qu")
	tf:seek("end")
	tf:write(1,"\n",2,"a","   3"," 1234567890","       b");
	tf:flush()
	tf:seek("set")
	log("test file:lines()\n")
	local lnum=0
	for line in tf.f:lines() do 
		log(lnum,": [",line,"]\n")
		lnum=lnum + 1
	end
	tf:seek("set")
	tf:write("                                           \n")
	tf:seek("set")
	log('test file:read("*a")\n')
	tf:read("*a")
	tf:seek("set")
	test_readn(tf)
	tf:close();
	log('test open missing file\n')
	want_ok=false
	tf:open("A/bogus","r")
	if tf.f then
		tf:close()
	end
	log('test open dir\n')
	tf:open("A/CHDK","r")
	if tf.f then
		tf:close()
	end
	want_ok=true
	tf:open(iotfnam,"r")
	want_ok=false
	log('test invalid seeks\n')
	tf:seek("set",-1)
	tf:seek("end",100)
-- on a540 write succeeds, close fails 
--	log('testinvalid write\n')
--	tf:write("whee!")
	want_ok=true
	tf:close()
	tend("io")
	log("\n")
end

function ttime(t)
	log('os.time(')
	if type(t) == "table" then
		log('{')
		for k,v in pairs(t) do
			log(tostring(k),'=',tostring(v),",")
		end
		log('}')
	elseif type(t) ~= "nil" then
		log(type(t),"[",tostring(t),"]")
	end
	log('): ')
	local r=os.time(t)
	if r then
		logok(tostring(r))
	else
		logfail()
	end
	return r
end

function dump_date_fmts()
	local tm=os.time()
	-- fmts in vx docs
	-- dryos (sx100) seems to support all but Z
	-- dryos returns the partern if it isn't supported, vx returns ""
	local fdsc={
		"a","A","b","B","c","d","H","I","j","m","M",
		"p", -- vxworks docs say P but only p works
		"S","U","w","W","x","X","y","Y","Z","%",
	}
	local s
	for _,v in ipairs(fdsc) do
		s="%"..v
		log(s," [",os.date(s,tm),"]\n");
	end
end

function tren(from,to)
	log('os.rename("',tostring(from),'","',tostring(to),"): ")
	local r,msg = os.rename(from,to)
	if r then
		logok()
	else
		logfail(tostring(msg))
	end
end

function trem(name)
	log('os.remove("',tostring(name),"): ")
	local r,msg = os.remove(name)
	if r then
		logok()
	else
		logfail(tostring(msg))
	end
end

function tmd(name)
	log('os.mkdir("',tostring(name),'"): ')
	local r,msg = os.mkdir(name)
	if r then
		logok()
	else
		logfail(tostring(msg))
	end
end

function tstat(name)
	log('os.stat("',tostring(name),'"): ')
	local r,msg = os.stat(name)
	if r then
--		local keys={ "dev", "ino", "mode", "nlink", "uid", "gid", "rdev", "size", "atime", "mtime", "ctime", "blksize", "blocks", "attrib", "reserved1", "reserved2", "reserved3", "reserved4", "reserved5", "reserved6",}
		local keys={ "dev", "mode", "size", "atime", "mtime", "ctime", "blksize", "blocks", "attrib","is_dir","is_file",}
		logok()
		log("{\n")
		for _,v in ipairs(keys) do
			log(" ",tostring(v),"=",tostring(r[v]),"\n")
		end
		log("}\n")
	else
		logfail(tostring(msg))
	end
	return r
end

function tlistdir(name,showall)
	log('os.listdir("',tostring(name),'",',tostring(showall),'): ')
	local r,msg = os.listdir(name,showall)
	if r then
		logok()
		log("{\n")
		for k,v in ipairs(r) do
			log(' ',k,'="',tostring(v),'"\n')
		end
		log("}\n")
	else
		logfail(tostring(msg))
	end
	return r
end

function tutime(name,mtime,atime)
	log('os.utime("',tostring(name),'",',tostring(mtime),',',tostring(atime),'): ')
	local r,msg = os.utime(name,mtime,atime)
	if r then
		logok()
	else
		logfail(tostring(msg))
	end
end

function os_test()
	tstart("os")
	if type(os) ~= "table" then
		log("missing os aborting!\n")
		return
	end
	if do_time then
		local s=os.date()
		log("current date ",tostring(s),"\n");
		if not s then
			logfail("nil value\n")
		end
		ttime()
		local t={year=1980,month=1,day=1}
		local tm=ttime(t)
		if tm ~= 315576000 then
			logfail("want ",315576000," got ",tostring(tm))
		end
		want_ok=false
		t={year=1066,month=1,day=1}
		ttime(t)
		if do_fmtdump then
			dump_date_fmts()
		end
	end
	if do_dir then
		want_ok=true
		local tdir0,tdat0,tdat1="A/MDTST0","/TEST0.DAT","/TEST1.DAT"
		tmd(tdir0)
		local tf=tfproto:new(tdir0..tdat0,"wb")
		tf:write("data")
		tf:close()
		local fn=tdir0..tdat0
		tstat(fn)
		tutime(fn) -- utime, current
		tstat(fn)
		tutime(fn,os.time({year=1984,month=1,day=1}),os.time({year=1984,month=12,day=25}))
		tstat(fn)
		tstat(tdir0)
		tren(tdir0..tdat0,tdir0..tdat1)
		tlistdir(tdir0)
		tlistdir(tdir0,true)
-- NOTE invalid operations frequently leave the filesystem in a corrupt state
--		trename(tdir0,tdir1)
		want_ok=false
		trem(tdir0) --fail, not empty
		trem("A/bogus") --fail missing
		tlistdir("A/bogus") -- missing
		tlistdir("A/llibtst.log") -- not a directory
		tstat("A/bogus") -- fail missing
		tutime("A/bogus") -- fail missing
		tren("A/bogus","A/blah")--fail missing
		tmd("A/CHDK")--fail, exists
		want_ok=true
		trem(tdir0..tdat1)
		trem(tdir0)
		no_rec=true
		trem(iotfnam)--try to clean up from io
	end
	tend("os")
	log("\n")
end

testlog,msg=io.open("A/llibtst.log","wb")
if not testlog then
	error("open test log fail:"..tostring(msg))
end

io.output(testlog)
bi=get_buildinfo()
log("test log opened\n");
log("platform: ",bi.platform," ",bi.platsub,"\n")
log("version: ",bi.version," ",bi.build_number," built on ",bi.build_date," ",bi.build_time,"\n")
if do_io then
	io_test()
end

if do_os then
	os_test()
end
log("close test log\n");
io.close(testlog)
sleep(2000)
