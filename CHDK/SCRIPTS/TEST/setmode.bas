@title set mode test
@param a 0=by prop val 1=by CHDK val
@default a 1
@param b Value to set
@default b 0

gosub "update_mode_vals"
gosub "status"

if r=0 then print "warning: not in rec"

if a=0 then goto "byprop"

rem by chdk
if is_capture_mode_valid b then
	print m, "->", b
else
	print m, "-> invalid mode ", b
endif

set_capture_mode b
gosub "update_mode_vals"
if m <> b then
	print "fail req", b, "got", m
else
	print "ok"
endif

goto "done"

rem by prop val
:byprop
print p, "->", b
set_capture_mode_canon b
gosub "update_mode_vals"
if p <> b then
	print "fail req", b, "got", p
else
	print "ok"
endif

goto "done"

rem set p=PROPCASE_SHOOTING_MODE, m=CHDK mode r=rec/play
:update_mode_vals
if get_propset = 1 then
	p=get_prop 0
else
	p=get_prop 49
endif

p = p&65535
m = get_capture_mode

if get_mode = 1 then 
	r=0
else
	r=1
endif

return

:status
print "prop", p, "mode", m, "rec", r
return

:done
gosub "status"
wait_click 10000

end
