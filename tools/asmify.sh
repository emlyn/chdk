#!/bin/sh

# script to convert IDAs asm dump to something similar to gcc's inline asm

sed 's/^ROM:[0-9A-F]* \?//' | sed 's/[[:space:]]*;.*$//' | grep -v '^$' | \
sed 's/^\\(loc_[0-9A-F]*\\)$/\\1:/' | \
sed 's/^\\([[:space:]]*\\)DCD/\\1.long/' | \
sed 's/^\\([[:space:]]*\\)\\(.*\\)$/\\1\ \"\\2\\\n\"/' | \
sed -e 's/^loc_[0-9A-F]*/&:/' -e 's/[ ]*/&"/' -e 's/$/\\n"&/'