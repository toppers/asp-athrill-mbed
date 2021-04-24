#!/bin/bash

if [ $# -ne 1 ]
then
    echo "Usage: $0 <ecu-num>"
    exit 1
fi
ECU_NUM=$1

bash perf.bash ${ECU_NUM} &
PERF_PID=$!

while [ 1 ]
do
    N=`hkw-ls | wc -l`
    if [ $N -ge $ECU_NUM ]
    then
        hkw-ls
        break;
    fi
done


hkw-reset
hkw-start
sleep 12 
hkw-stop 

kill -s TERM ${PERF_PID}
