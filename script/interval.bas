rem Interval shooting

@title Interval shooting
@param a Shoot count
@default a 10
@param b Interval (Minutes)
@default b 0
@param c Interval (Seconds)
@default c 10

t=b*60000+c*1000
if a<2 then let a=10
if t<1000 then let t=1000

print "Total time:", t*a/60000; "min", t*a%60000/1000; "sec"

sleep 1000

print "Shoot 1 of", a
shoot

for n=2 to a
    sleep t
    print "Shoot", n, "of", a
    shoot
next n

end
