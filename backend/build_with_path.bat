@echo off
REM Build script that allows you to specify the g++ path manually
REM Usage: build_with_path.bat [path-to-g++]

setlocal

if "%1"=="" (
    echo Usage: build_with_path.bat "C:\path\to\g++.exe"
    echo.
    echo Or if g++ is in PATH, just run: build_simple.bat
    echo.
    echo To find your compiler, run: find_compiler.bat
    pause
    exit /b 1
)

set GPP=%1

if not exist "%GPP%" (
    echo Error: Compiler not found at: %GPP%
    pause
    exit /b 1
)

echo Using compiler: %GPP%
echo.

REM Create build directory
if not exist build mkdir build
cd build

REM Download cpp-httplib header if not exists
if not exist httplib.h (
    echo Downloading cpp-httplib...
    powershell -Command "Invoke-WebRequest -Uri 'https://raw.githubusercontent.com/yhirose/cpp-httplib/master/httplib.h' -OutFile 'httplib.h'"
    if errorlevel 1 (
        echo Error: Failed to download httplib.h
        echo Please download it manually from: https://github.com/yhirose/cpp-httplib
        pause
        exit /b 1
    )
)

REM Compile
"%GPP%" -std=c++17 -O2 -I..\include -I. ..\src\server.cpp ..\src\Book.cpp ..\src\User.cpp ..\src\ReadingList.cpp ..\src\Storage.cpp ..\src\AuthService.cpp ..\src\BookService.cpp ..\src\JsonHelper.cpp -o BookWiseBackend.exe -lws2_32 -lwsock32

if errorlevel 1 (
    echo Build failed!
    pause
    exit /b 1
)

echo.
echo Build successful! Run BookWiseBackend.exe to start the server.
pause

