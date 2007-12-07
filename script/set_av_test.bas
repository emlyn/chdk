@title Set AV APEX
sleep 500
set_av96 576
sleep 500
shoot
sleep 2000
set_av96 288
get_av96 g
print "AV:", g
sleep 2000
shoot
