#!/bin/bash

# In many commonly-used programming languages, zero is considered "false" and nonzero values are considered "true". Even in Bash, this is true within arithmetic expressions (which we'll see later on). But at the level of commands, the reverse is true: an exit status of zero means "successful" or "true" and a nonzero exit status means "failure" or "false".

echo --- try to remove a file doesn\'t exist and get exit code
rm I_do_not_exist.txt
echo $?

echo
echo --- try to remove a file doesn\'t exist
rm I_do_not_exist.txt || echo remvoe file failure
echo $?
