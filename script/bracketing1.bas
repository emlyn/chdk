@title EXP bracketing 
@param a Number of steps
@default a 2
@param b Step size (1/3EV)
@default b 3

if a<1 then let a=2
if b<1 then let b=3

sleep 1000

print "Preparing..."
click "erase"
for n=1 to a*b
    click "left"
next n

for s=1 to a*2
    print "Shoot", s, "of", a*2+1
    shoot
    for n=1 to b
        click "right"
    next n
next s

print "Shoot", a*2+1, "of", a*2+1
shoot

print "Finalizing..."
for n=1 to a*b
    click "left"
next n
click "erase"

end
