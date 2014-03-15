#!/bin/bash
# http://stackoverflow.com/questions/18351198/what-is-the-use-of-exec-command-in-the-shell-scripting
# exec replaces the current program in the current process, without forking a new process

echo before call exec
exec echo hello
# this line is not executed
echo after call exec
