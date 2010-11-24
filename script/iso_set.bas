@title Set ISO
@param a koef1
@default a 10
@param b Koef2
@default b 10
@param c koef3
@default c 1
@param d Sleep Interval (*100)
@default d 20

sleep 500

t=d*100

g=a*b*c

press "shoot_half"
set_iso_real g
get_iso_real e
get_iso_market f
print "ISO:", e, "(", f, ")"
press "shoot_full"
release "shoot_full"
release "shoot_half"

end
