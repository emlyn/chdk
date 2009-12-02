@title set rec/play demo
@param a 0=play 1=rec
@default a 0

gosub "getrec"
print "rec mode",m
print "new rec mode",a
sleep 1000
set_record a
sleep 2000
gosub "getrec"
print "rec mode",m
sleep 1000
end

rem note get_mode returns 0 for rec, 1 for play 2 for movie
:getrec
if get_mode=1 then 
	m=0
else
	m=1
endif
return

