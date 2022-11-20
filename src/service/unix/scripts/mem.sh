#!/bin/sh

# get the memory usage in kb of a given process id (pid)
# usage: mem.sh pid
# returns: memory usage in kb

# get the pid
pid=$1

# get the memory usage in kb
mem=`ps -p $pid -o rss | tail -1`

# return the memory usage in kb
echo $mem