#!/bin/bash

echo --- print number sequence
for i in {1..20} ; do
    echo "$i"
done


echo
echo --- print arguments
for arg in "$@" ; do
    echo "$arg"
done
