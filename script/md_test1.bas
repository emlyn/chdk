@title mdt1
@param a Columns
@default a 3
@param b Rows
@default b 3
@param c Threshold
@default c 10
@param d Measure Interval (millisec)
@default d 100
@param e Delay (seconds)
@default e 0

if a<1 then let a=1
if b<1 then let b=1
if c<0 then let c=0

let e=e*1000

sleep e

print_screen 1

for i=0 to 10
    let f=0
    md_detect_motion a, b, 1, 30000, d, c, 0, f

    rem if f>0 then shoot else print "Timeout"

    print "cells: ", f

    for g=1 to b
        for x=1 to a
            md_get_cell_diff x, g, f
            print "[",x,",",g,"]=",f
        next x
    next g
next i

end
