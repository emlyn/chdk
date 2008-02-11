#!/bin/sh

VERSIONS="1 2 3"

echo

for v in $VERSIONS; do
    cat sig_ref_${v}.txt | \
    while read line; do
    	# workaround - multiword read does not work in Windows shell!
    	line=($line)
        name=${line[0]}
        addr=${line[1]}
        length=${line[2]}
	./gensig sig_ref_${v}.bin 0xffc00000 ${name}_${v} $addr ${length:-32}
    done
done

echo "FuncsList func_list[] = {"

for v in $VERSIONS; do
    cat sig_ref_${v}.txt | \
    awk -v v=${v} '{ printf("\t{ \"%s\", func_sig_%s_%d },\n",$1,$1,v)}'
done | "$1"

echo -e "\t{ NULL }\n};"