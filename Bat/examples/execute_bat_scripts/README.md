### Various ways to call Windows batch script

1. direct call, the batch file will be executed by the current cmd.exe instance

2. using call command, same as #1, only has an effect when used inside a batch/cmd file. In a batch file, without 'call', the parent batch file ends and control passes to the called batch file; with 'call' runs the child batch file, and the parent batch file continues with statements following call. 

3. using cmd command, runs the batch file in a new cmd.exe instance. 

4. using start command, run the batch file in a new cmd.exe instance in a new window, and the caller will not wait for completion.

[Question on stackoverflow][1]

[1]:http://stackoverflow.com/questions/2607856/several-ways-to-call-a-windows-batch-file-from-another-one-or-from-prompt-which

