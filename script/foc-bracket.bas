@title Focus
@param a begin from
@default a 30
@param b Step size
@default b 10
@param c Steps count
@default c 10

sleep 500
get_focus f

for s=1 to c
    g=a+s*b
    print "Shoot", s, "(", g, ")"
    set_focus g
    shoot
next s

end
