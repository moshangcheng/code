#!/bin/bash

# The construction [[ condition ]] returns an exit status of zero (success) if condition is true, and a nonzero exit status (failure) if condition is false. 

# for more file test operators, see http://tldp.org/LDP/abs/html/fto.html
# -d file 
#    True if file exists and is a directory.
# -f file 
#    True if file exists and is a regular file.
# string1 = string2 
#    True if string1 and string2 are equal.
# string == pattern 
#    True if string matches pattern. (pattern has the same form as a pattern in filename expansion; for example, unquoted * means "zero or more characters".)
# string != pattern 
#    True if string does not match pattern. 
if [[ -e if.sh ]]; then
    echo 'of course, i am here'
else
    echo 'what happened, you changed my name?'
fi
