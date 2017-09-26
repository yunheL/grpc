#!/bin/bash
OUTFILE="output/experiment1_separate"

#pre commands
rm $OUTFILE
touch $OUTFILE

for i in {1..100}; do
  ./greeter_client >> $OUTFILE
done
