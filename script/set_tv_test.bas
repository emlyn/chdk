@title Set TV APEX
sleep 500
set_tv96 576
sleep 500
shoot
sleep 2000
set_tv96 -224
get_tv96 f
print "TV:", f
sleep 2000
shoot
