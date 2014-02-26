#!/bin/bash

echo --- try to remove a file doesn\'t exist and get exit code
rm I_do_not_exist.txt
echo $?

echo
echo --- try to remove a file doesn\'t exist
rm I_do_not_exist.txt || echo remvoe file failure
echo $?
