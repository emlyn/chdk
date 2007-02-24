#!/bin/sh

FUNCS="$1"
PRIM="$2"
BASE="$3"

echo

cat "$FUNCS" | \
while read name addr; do
    ./gensig $PRIM $BASE $name $addr 32
done

cat "$FUNCS" | \
awk 'BEGIN {print "FuncsList func_list[] = {"}
    { printf("\t{ \"%s\", func_sig_%s },\n",$1,$1)}
    END {print "\t{ NULL }\n};"}
'
