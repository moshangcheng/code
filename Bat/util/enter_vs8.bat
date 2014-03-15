@echo off

echo Set Environment for MSBuild
call "C:\VS8\VC\vcvarsall.bat"

echo Enter bash
sh --login -i
echo Exit bash
