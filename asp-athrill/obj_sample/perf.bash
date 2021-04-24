#!/bin/bash

if [ $# -ne 1 ]
then
    echo "Usage: $0 <ecu-num>"
    exit 1
fi
ECU_NUM=${1}

function trap_func()
{
    echo "trap"
    ps axu | grep -v grep | grep proxy | awk '{print $2}' | xargs kill -9
    exit 0
}

trap trap_func INT TERM

function activate()
{
    ecu=$1
    cd $ecu
    hkw-proxy &
    cd ..
}

CNT=0
while [ 1 ]
do
    CNT=`expr $CNT \+ 1`
    echo "wakeup proxy ecu$CNT"
    activate ecu$CNT
    if [ $CNT -ge $ECU_NUM ]
    then
        break;
    fi
done

echo "waiting for end"

while [ 1 ]
do
	sleep 10
done
