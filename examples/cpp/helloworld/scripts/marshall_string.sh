#!/bin/bash
OUTFILE="out/marshall_out_string_2^20"

#pre commands
rm $OUTFILE
touch $OUTFILE

for i in {1..8}; do
  for j in {1..3}; do
    ./greeter_client $((i*4)) >> $OUTFILE
  done
done
