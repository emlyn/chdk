@title Iso Bracket Real
@param a counter begin
@default a 1
@param b Step size
@default b 30
@param c Steps count
@default c 10
@param d Sleep Interval (*100)
@default d 20

sleep 500

t=d*100

for i=a to c
    g=i*b
    press "shoot_half"
    sleep t
    set_iso_real g
    get_iso_real e
    get_iso_market f
    print "ISO:", e, "(", f, ")"
    sleep 500
    press "shoot_full"
    release "shoot_full"
    release "shoot_half"
next i

end
