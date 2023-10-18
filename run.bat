@echo off
color 07


:main
cls
if exist src/main.o del src/main.o
if exist src/main.d del src/main.d
mingw32-make run
pause 
goto:main