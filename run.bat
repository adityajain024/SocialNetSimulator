@echo off
title SocialNet Compile + Run

echo Compiling socialnet.cpp...
g++ socialnet.cpp -std=c++17 -O2 -Wall -o socialnet.exe

if %errorlevel% neq 0 (
    echo.
    echo *** compile failed ***
    pause
    exit /b
)

echo.
echo Running...
echo ------------------------------------
socialnet.exe
echo ------------------------------------
echo.
echo Type more commands below if you want
cmd /k
