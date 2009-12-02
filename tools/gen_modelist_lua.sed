1 i\
--[[\
!!! THIS FILE IS GENERATED. DO NOT EDIT. !!!\
array of mode names indexed by their mode number from include/modelist.h\
you may want to use LUALIB/capmode.lua instead\
--]]\
return {
/^[[:space:]]*MODE_[A-Z0-9_]\+/ { 
 s/^[[:space:]]*MODE_\([A-Z0-9_]\+\)\([[:space:]]*\)\(=1\)\?,\?/  "\1",/;
 s/\/\// --/;
 p;
}
$ i\
}
