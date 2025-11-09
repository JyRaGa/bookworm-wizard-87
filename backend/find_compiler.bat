@echo off
REM Helper script to find your C++ compiler

echo Searching for C++ compilers...
echo.

REM Check for g++
echo Checking for g++...
where g++.exe >nul 2>&1
if %errorlevel% equ 0 (
    echo [FOUND] g++ in PATH:
    where g++.exe
    echo.
) else (
    echo [NOT FOUND] g++ in PATH
    echo.
)

REM Check common locations
echo Checking common MinGW locations:
if exist "C:\MinGW\bin\g++.exe" (
    echo [FOUND] C:\MinGW\bin\g++.exe
) else (
    echo [NOT FOUND] C:\MinGW\bin\g++.exe
)

if exist "C:\msys64\mingw64\bin\g++.exe" (
    echo [FOUND] C:\msys64\mingw64\bin\g++.exe
) else (
    echo [NOT FOUND] C:\msys64\mingw64\bin\g++.exe
)

REM Check for Visual Studio
echo.
echo Checking for Visual Studio C++ compiler...
where cl.exe >nul 2>&1
if %errorlevel% equ 0 (
    echo [FOUND] cl.exe in PATH
    where cl.exe
) else (
    echo [NOT FOUND] cl.exe in PATH
)

echo.
echo If g++ is found, you can use build_simple.bat
echo If not found, please install MinGW-w64 or add g++ to your PATH
pause

