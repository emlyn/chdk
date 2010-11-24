@title Test Ev info

sleep 500
press "shoot_half"
sleep t
get_bv96 e
print "BV:", e
get_tv96 f
print "TV:", f
get_av96 g
print "AV:", g
sleep 5000
press "shoot_full"
release "shoot_full"
release "shoot_half"

end
