@title Iso Bracket Real
@param a counter begin
@default a 1
@param b Step size
@default b 200
@param c Steps count
@default c 10

sleep 500

for i=a to c
    g=i*b
    press "shoot_half"
    sleep 2000
    set_focus g
    get_focus e
    print "FOC:", e
    sleep 2000
    press "shoot_full"
    release "shoot_full"
    release "shoot_half"
next i

end
