@title Bracketing 
@param a Number of ñsteps 
@default a 2
@param b Step size
@default b 2

if a<1 then let a=2
if b<1 then let b=2

sleep 1000

print "Preparing..."
for n=1 to a*b
    click "left"
next n

print "Shoot 1 of", a*2+1
shoot
for s=1 to a*2
    for n=1 to b
        click "right"
    next n
    print "Shoot", s+1, "of", a*2+1
    shoot
next s

print "Finalizing..."
for n=1 to a*b
    click "left"
next n

end
