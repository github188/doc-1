#!/bin/bash

if [ $# != 2 ]; then
    echo "Usage: $0 cmd try-times"
    echo "$#"
    return 2
fi
cmd=$1
n=$2
ret=-1

for i in `seq 1 $n`; do
    eval $cmd
done




