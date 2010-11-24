@title Av TEST

for a=1 to 6
    if a = 1 then d = 608
    if a = 2 then d = 640
    if a = 3 then d = 672
    if a = 4 then d = 704
    if a = 5 then d = 736
    if a = 6 then d = 768

    if a = 1 then print d, "-9"
    if a = 2 then print d, "-10.1"
    if a = 3 then print d, "-11.3"
    if a = 4 then print d, "-12.7"
    if a = 5 then print d, "-14.3"
    if a = 6 then print d, "-16.0"

    set_av96_direct d

    shoot
next a

end
