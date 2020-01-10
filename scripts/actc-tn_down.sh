#!/bin/bash
#
# actc-tn_down.sh is used by the actc-tn_bounce.sh and actc-tn_roll.sh scripts.
# It is intended to terminate specific ACTC.IO daemon processes.
#


if [ "$PWD" != "$ACTC_HOME" ]; then
    echo $0 must only be run from $ACTC_HOME
    exit -1
fi

prog=nodactc

DD=var/lib/node_$ACTC_NODE
runtest=`cat $DD/$prog.pid`
echo runtest = $runtest
running=`ps -e | grep $runtest | grep -cv grep `

if [ $running -ne 0 ]; then
    echo killing $prog

    kill -15 $runtest

    for (( a = 1;11-$a; a = $(($a + 1)) )); do
        echo waiting for safe termination, pass $a
        sleep 2
        running=`ps -e | grep $runtest | grep -cv grep`
        echo running = $running
        if [ $running -eq 0 ]; then
            break;
        fi
    done
fi

if [ $running -ne 0 ]; then
    echo killing $prog with SIGTERM failed, trying with SIGKILL
    pkill -9 $runtest
fi
