@title Shutter TEST

for a=1 to 3
    if a = 1 then d = 1
    if a = 2 then d = 100000
    if a = 3 then d = 1000000

    if a = 1 then print d, " t=1/100000"
    if a = 2 then print d, " t=1"
    if a = 3 then print d, " t=10"

    set_shutter_speed d

    shoot
next a

end
