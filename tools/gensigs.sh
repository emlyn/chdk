#!/bin/sh

VERSIONS="1 2"

echo

for v in $VERSIONS; do
    cat sig_ref_${v}.txt | \
    while read name addr length; do
	./gensig sig_ref_${v}.bin 0xffc00000 ${name}_${v} $addr ${length:-32}
    done
done

echo "FuncsList func_list[] = {"

for v in $VERSIONS; do
    cat sig_ref_${v}.txt | \
    awk -v v=${v} '{ printf("\t{ \"%s\", func_sig_%s_%d },\n",$1,$1,v)}'
done | sort

echo -e "\t{ NULL }\n};"