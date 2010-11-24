@title White Balance
@param a propid
@default a 5
@param b value
@default b 5

sleep 2000
set_prop a 2
print "Cloudy"

sleep 2000
set_prop a 3
print "Tungsten"

sleep 2000
set_prop a 4
print "Fluorescent"

sleep 2000
set_prop a 5
print "Fluorescent H"

sleep 2000
set_prop a 10
print "Underwater"

sleep 2000
set_prop a 7
print "Custom"

sleep 2000
set_prop a 1
print "Daylight"

end
