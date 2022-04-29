#!/bin/bash

cd bin/database

day=`date +"%Y-%m-%d"`
time=`date +"%H:%M:%S"`
# Pings telus to check if the wifi is connected to the internet 
# The > /dev/null 2>&1 just suppresses the output - it can be removed
ping -c 1 telus.com > /dev/null 2>&1
rc=$?

# Checks if the ping was successful
if [[ $rc -eq 0 ]] ; then
	./insert ${day} ${time} UP
else
	./insert ${day} ${time} DOWN
fi
