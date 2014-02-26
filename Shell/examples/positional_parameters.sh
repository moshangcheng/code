#!/bin/bash

echo --- the number of arguments
echo "$#"


echo
echo --- list all arguments
echo "$@"

# difference between $@, $*, "$@" and "$*"
# When wrapped in double-quotes, as "$@", each argument becomes a separate word. (Note: the alternative $* is perhaps more common, but "$*" becomes a single word, with spaces in between the original parameters. "$@" is almost always preferable to either $@ or $*, which allow an argument to become split into multiple words if it contains whitespace, and to "$*", which combines multiple arguments into a single word.)
# http://en.wikibooks.org/wiki/Bash_Shell_Scripting#Positional_parameters
# http://stackoverflow.com/questions/9915610/the-difference-between-and

echo
echo --- difference between '$@', '$*', '"$@"' and '"$*"'
echo ------ '$@'
printf "%s\n" $@
echo ------ '"$@"'
printf "%s\n" "$@"
echo ------ '$*'
printf "%s\n" $*
echo ------ '"$*"'
printf "%s\n" "$*"

# Note that positional parameters beyond $9 require the curly braces; should you need to refer to the tenth argument, for example, you must write ${10} rather than $10. (The latter would be interpreted as ${1}0.) 

echo
echo --- get applicaton name
echo "$0"

echo
echo --- get first argument
echo "$1"


echo
echo --- call shift to remove first argument
shift
echo "$@"
