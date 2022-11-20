#!/bin/sh

# get the cpu usage in percent of a given process id (pid)
# usage: cpu.sh pid
# returns: cpu usage in percent

# get the pid
pid=$1

# get the cpu usage in percent
cpu=`ps -p $pid -o %cpu | tail -1`

# return the cpu usage in percent
echo $cpu