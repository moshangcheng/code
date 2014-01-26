@echo off
rem set delayed expansion http://ss64.com/nt/delayedexpansion.html
SETLOCAL EnableExtensions EnableDelayedExpansion

set IndentSymbol=--
set IndentString=

call :ProcessFolder %1
goto :EOF

:ProcessFolder
	rem Changing working directory to '%1'
	echo %IndentString%%1
	set OldIndentString=%IndentString%
	set IndentString=%IndentString%%IndentSymbol%
	rem test whether it's a folder, http://stackoverflow.com/a/1466528
	if exist %1\ (
		pushd %1		
		rem "dir /A" will show hidden system protected files
		for /F "delims=" %%b in ('dir /B') do (
			call :ProcessFolder "%%b"
		)
		popd
	)
	set IndentString=%OldIndentString%
	goto :EOF