rem Zoom to object

@title Zoom and Shoot
@param a Shoot count
@default a 8
@param b Zoom step
@default b 1

if a<2 then let a=8
if b<1 then let b=1

sleep 500
print "Shoot 1 of", a
shoot

for s=2 to a
    for n=1 to b
        print "Zooming-in ", n; "..."
        click "zoom_in"
        sleep 600
    next n

    print "Shoot", s, "of", a
    shoot
next s

sleep 500
for s=1 to a*b-1
    print "Zooming-out ", s; "..."
    click "zoom_out"
    sleep 600
next s

end
