@if "%1" == "" @echo off
set PCACHE=%PATH%

del /S /Q debug\
del /S /Q release\

del /Q ui_*.h

set DIRCACHE=%cd%
call vcvarsall.bat amd64
cd %DIRCACHE%

qmake Draughts.pro -spec win32-msvc
jom qmake_all
jom Debug
jom Release

set PATH=%PCACHE%
del /Q ui_*.h
