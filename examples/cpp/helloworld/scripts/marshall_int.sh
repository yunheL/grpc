#!/bin/bash
OUTFILE="output/marshall_out_int"

#pre commands
rm $OUTFILE
touch $OUTFILE

for i in {1..100}; do
  ./greeter_client >> $OUTFILE
done
