@title Focus bracketing
@param a focus shift
@default a 1

if a<1 then let a=1
sleep 500

for s=1 to a
    click "left"
    sleep 100
next s

print "Shoting", 1; " shot"
shoot

for s=1 to a*2
    print "Shooting", s+1; " shot"
    click "right"
    shoot
    sleep 1000
next s

end
