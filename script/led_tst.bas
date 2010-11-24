rem led/batt tester 
@title led/batt tester 
@param b brightness
@default b 200

rem LED_GREEN       4
rem LED_YELLOW      5
rem not used        6
rem LED_ORANGE      7
rem LED_BLUE        8
rem LED_AF_BEAM     9
rem LED_TIMER       10

b=200

do
    wait_click

    if is_key "up"    then gosub "show_led"
    if is_key "down"  then print get_vbatt
    if is_key "display"  then cls
    if is_key "right" then b=b-10
    if is_key "left" then gosub "light"
until is_key "set"

goto "the_end"

:light
for c=0 to 20
    for x=200 to 0 step -110
        set_led 8 1 b
        sleep 10
    next x
    for x=0 to 200 step 10
        set_led 8 1 b
        sleep 10
    next x
next c
return

:show_led
for x=4 to 10
    set_led x 1 
    sleep 1000
    set_led x 0
next x
return

:the_end
end
