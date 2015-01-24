@echo off

REM %comspec% /c ""C:\Program Files (x86)\Microsoft Visual Studio 11.0\VC\vcvarsall.bat""

echo Set Environment for MSBuild
call "C:\Program Files (x86)\Microsoft Visual Studio 11.0\VC\vcvarsall.bat"

echo Enter bash
sh --login -i
echo Exit bash
