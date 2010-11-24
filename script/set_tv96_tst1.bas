@title Tv TEST

for a=1 to 4
    if a = 1 then d = 0
    if a = 2 then d = -320
    if a = 3 then d = 320
    if a = 4 then d = 576
    if a = 4 then d = 2000

    if a = 1 then print d, " t=1"
    if a = 2 then print d, " T=10"
    if a = 3 then print d, " t=1/10"
    if a = 4 then print d, " t=1/...."

    set_tv96_direct d

    shoot
next a

end
