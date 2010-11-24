@title DOF test

do
    f=f+100
    set_focus f
    print "dist: ", f
    get_far_limit l
    shoot
    print "far: ", l
until F > 1000

end
