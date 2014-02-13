#!/bin/bash
# http://stackoverflow.com/questions/2398388/is-it-possible-for-bash-commands-to-continue-before-the-result-of-the-previous-c

echo before non-block sleep
sleep 2 &
echo after non-block sleep

# wait until all the child processes have exited
wait

echo before sleep
sleep 2
echo after sleep

