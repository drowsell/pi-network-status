#!/bin/bash

# Pings telus to check if the wifi is connected to the internet 
# The > /dev/null 2>&1 just suppresses the output - it can be removed
ping -c 1 telus.com > /dev/null 2>&1
rc=$?

# Checks if the ping was successful
if [[ $rc -eq 0 ]] ; then
	echo "UP"
else
	echo "DOWN"
fi

