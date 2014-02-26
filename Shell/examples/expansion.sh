#!/bin/bash

# http://en.wikibooks.org/wiki/Bash_Shell_Scripting


echo expansion in shell

# filename expansion

# If any filenames begin with a hyphen -, then filename-expansion can sometimes have surprising consequences. For example, if a directory contains two files, named -n and tmp.txt, then cat * expands to cat -n tmp.txt, and cat will interpret -n as an option rather than a filename; instead, it is better to write cat ./* or cat -- *, which expand to cat ./-n ./tmp.txt or cat -- -n tmp.txt, removing this problem.

echo
echo --- list all files in home directory start with dot
echo ~/.*



# brace expansion
# Brace expansion, like filename expansion, can be disabled by any of the quoting mechanisms; '{', "{", or \{ produces an actual literal curly-brace.
echo
echo --- number sequence
echo {1..10..2}

