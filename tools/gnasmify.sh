#!/bin/sh

# script to convert GNU tools asm dump (from chr's disassemble.pl) to something similar to gcc's inline asm

sed -E -e 's/^[[:xdigit:]]+:[[:blank:]]+[[:xdigit:]]+ ?//' \
 -e 's/(^.*[[:blank:]][Mm]([Cc][Rr]|[Rr][Cc]).*){(.*)}$/\1\3/' \
 -e 's/(^.*[[:blank:]][Ll][Dd][Rr][[:alpha:]]*[[:blank:]]+[[:alnum:]]+, )(\[pc, #-?[[:digit:]]+\][[:blank:]]*;[[:blank:]]*[[:xdigit:]]+):[[:blank:]]*\(([[:xdigit:]]+)\)/\1=0x\3 ; was: "\2"/' \
 -e 's/(^.*[[:blank:]])[Mm][Oo][Vv]([[:alpha:]]*[[:blank:]]+[[:alnum:]]+, )(#-?[[:digit:]]+)[[:blank:]]*;[[:blank:]]*(0x[[:xdigit:]]+)/\1ldr\2=\4 ; was: "mov ..., \3"/' \
 -e 's/(^.*[[:blank:]])([Aa][Dd][Dd]|[Ss][Uu][Bb])([[:alpha:]]*[[:blank:]]+[[:alnum:]]+, )(pc, #-?[[:digit:]]+)[[:blank:]]*;[[:blank:]]*([[:xdigit:]]+):[[:blank:]]*\([[:xdigit:]]+\)(.*$)/\1ldr\3=0x\5 ; was: "\2\3\4" \6/' \
 -e 's/(^.*[[:blank:]][Bb][Ll][[:alpha:]]*[[:blank:]]+)loc(_.*$)/\1sub\2/' \
 -e 's/(^[[:blank:]]+)([^;]*$)/\1"\2\\n"/' \
 -e 's|(^[[:blank:]]+)([^;]*[^;[:blank:]])([[:blank:]]*);(.*)|\1"\2\\n"\3//\4|' \
 -e 's/^loc_[[:xdigit:]]+:/"&\\n"/' \
 -e 's|(^"loc_.*") ?;(.*$)|\1 //\2|' \
 -e '/^".*":$/s/ /_/g' \
 -e 's/^"(.*)":/"a\1:\\n"/'
