@title Tv test
@param a 1 counter
@default a 1
@param b begin from
@default b 0

b=b*10

for a=1 to 4
    d=b+32*5*a

    set_tv96_direct d

    rem sleep 2000

    shoot
next a

end
