@title mdt2
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

for i=0 to 100000
    let f=0
    md_detect_motion a, b, 1, 30000, d, c, 0, f

    if f>0 then shoot else print "Timeout"

    rem print "cells: ", f

    rem for g=1 to b
    rem for x=1 to a
    rem md_get_cell_diff x, g, f
    rem print "[",x,",",g,"]=",f
    rem next x
    rem next g
next i

end
