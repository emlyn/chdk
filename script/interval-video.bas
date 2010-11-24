@title Interval VIDEO

@param a Number of Videos
@default a 5

@param b Video length (min)
@default b 0
@param c Video length (sec)
@default c 10

@param d Interval (min)
@default d 0
@param e Interval (sec)
@default e 10

t=60000*b+1000*c
i=60000*d+1000*e

if a<2 then let a=5
if t<1000 then let t=1000
if i<2000 then let i=2000

sleep 1000

print "Video 1 of",a
click "shoot_full"
sleep t
click "shoot_full"

for s=2 to a
    print "Waiting",d;"min",e;"sec"
    sleep i

    print "Video",s,"of",a
    click "shoot_full"
    sleep t
    click "shoot_full"
next s

end
