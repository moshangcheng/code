#!/bin/bash

value=hello
# $value equals to ${value}
echo $value


# single-quotes prevent variable expansion; a command such as echo '${location}' will print the actual string ${location}, rather than printing the value of a variable named location.
# It is generally a good idea to wrap variable expansions in double-quotes, because otherwise the results of variable expansion will undergo filename expansion, as well as word splitting (whereby white-space is used to separate the words that make up a command)
