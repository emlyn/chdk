rem Author GrAnd
rem Enables zoom during video recording on A-series

@title Video with zoom

print "Half-press shoot button"
print "to stop video recording"
print ""

get_zoom z

click "shoot_full"

:loop
    wait_click

    is_key k "zoom_in"
    if k=1 then set_zoom_rel +1
    is_key k "zoom_out"
    if k=1 then set_zoom_rel -1
    is_key k "shoot_half"
    if k=1 then goto "end"
    goto "loop"

:end
click "shoot_full"
sleep 2000
set_zoom z

end
