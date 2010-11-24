@title Default script
@param a Shoot count
@default a 2
@param b Step
@default b 3

sleep 1000

if a<1 then let a=2
if b<1 then let b=3

for s=1 to a
    shoot
    for n=1 to b
        click "right"
    next n
next s

shoot

for n=1 to a*b
    click "left"
next n

end
