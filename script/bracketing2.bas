@title bracketing2
@param a Number of steps 
@default a 2
@param b Step size
@default b 3
@param c (0.1 sec)
@default c 5

if a<1 then let a=2
if b<1 then let b=3
if c<1 then let c=1

c=c*100

sleep 1000

print "Preparing..."
for n=1 to a*b
    click "left"
next n

for s=1 to a*2
    print "Shoot", s, "of", a*2+1
    shoot
    sleep c
    for n=1 to b
        click "right"
    next n
next s

print "Shoot", a*2+1, "of", a*2+1
shoot

sleep c

print "Finalizing..."
for n=1 to a*b
    click "left"
next n

end
