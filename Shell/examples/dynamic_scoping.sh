#!/bin/bash
 
# In programming language theory, a variable like $foo is said to be "dynamically scoped" rather than "lexically scoped".

foo=bar
 
function f1 ()
{
  echo "$foo"
}
 
function f2 ()
{
  local foo=baz
  f1 # prints 'baz'
}
 
f2
