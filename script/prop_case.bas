@title propcase
@param a propid
@default a 5
@param b value
@default b 0

:loop
    wait_click
    is_key k "left"
    if k=1 then get_prop a b
    is_key k "set"
    if k=1 then goto "lend"
    print a,b
    goto "loop"

:lend
end
