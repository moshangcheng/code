#!/bin/bash

# The construction [[ condition ]] returns an exit status of zero (success) if condition is true, and a nonzero exit status (failure) if condition is false. 
if [[ -e if.sh ]]; then
    echo 'of course, i am here'
else
    echo 'what happened, you changed my name?'
fi
