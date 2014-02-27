#!/bin/bash
 
# A subshell receives a copy of the surrounding context's "execution environment", which includes any variables, among other things; but any changes that the subshell makes to the execution environment are not copied back when the subshell completes.

foo=bar
echo "$foo" # prints 'bar'
 
# subshell:
(
  echo "$foo" # prints 'bar' - the subshell inherits its parents' variables
  baz=bip
  echo "$baz" # prints 'bip' - the subshell can create its own variables
  foo=foo
  echo "$foo" # prints 'foo' - the subshell can modify inherited variables
)
 
echo "$baz" # prints nothing (just a newline) - the subshell's new variables are lost
echo "$foo" # prints 'bar' - the subshell's changes to old variables are lost
