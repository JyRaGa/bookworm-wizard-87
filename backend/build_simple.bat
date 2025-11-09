@echo off
REM Simple build script without CMake for Windows
REM Requires: Visual Studio C++ compiler (cl.exe) or MinGW g++

echo Building BookWise Backend (without CMake)...

REM Create build directory
if not exist build mkdir build

REM Stop any running server first to avoid file lock
taskkill /F /IM BookWiseBackend.exe >nul 2>&1
if %errorlevel% equ 0 (
    echo Stopped running server, waiting 1 second...
    timeout /t 1 >nul
)

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

REM Try to find g++ compiler (preferred for this project)
set GPP=
where g++.exe >nul 2>&1
if %errorlevel% equ 0 (
    for /f "delims=" %%i in ('where g++.exe') do set GPP=%%i
    goto :found_gpp
)

REM Check common MinGW locations
if exist "C:\MinGW\bin\g++.exe" (
    set GPP=C:\MinGW\bin\g++.exe
    goto :found_gpp
)
if exist "C:\msys64\mingw64\bin\g++.exe" (
    set GPP=C:\msys64\mingw64\bin\g++.exe
    goto :found_gpp
)
if exist "C:\Program Files\mingw-w64\x86_64-8.1.0-posix-seh-rt_v6-rev0\mingw64\bin\g++.exe" (
    set GPP=C:\Program Files\mingw-w64\x86_64-8.1.0-posix-seh-rt_v6-rev0\mingw64\bin\g++.exe
    goto :found_gpp
)
if exist "C:\Program Files (x86)\mingw-w64\i686-8.1.0-posix-dwarf-rt_v6-rev0\mingw32\bin\g++.exe" (
    set GPP=C:\Program Files (x86)\mingw-w64\i686-8.1.0-posix-dwarf-rt_v6-rev0\mingw32\bin\g++.exe
    goto :found_gpp
)

REM Try to find in common user locations
for /d %%d in ("C:\Users\%USERNAME%\AppData\Local\Programs\*") do (
    if exist "%%d\mingw64\bin\g++.exe" (
        set GPP=%%d\mingw64\bin\g++.exe
        goto :found_gpp
    )
)

REM Try Visual Studio compiler as fallback
where cl.exe >nul 2>&1
if %errorlevel% equ 0 (
    echo Using Visual Studio C++ compiler...
    REM Setup Visual Studio environment (adjust path if needed)
    call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat" 2>nul
    if errorlevel 1 (
        call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat" 2>nul
    )
    
    cl /std:c++17 /O2 /EHsc /I..\include /I. ..\src\server.cpp ..\src\Book.cpp ..\src\User.cpp ..\src\ReadingList.cpp ..\src\Storage.cpp ..\src\AuthService.cpp ..\src\BookService.cpp ..\src\JsonHelper.cpp /Fe:BookWiseBackend.exe /link ws2_32.lib
    if errorlevel 1 (
        echo Build failed!
        pause
        exit /b 1
    )
    goto :build_success
)

REM No compiler found
echo Error: No C++ compiler found!
echo.
echo Please ensure g++ is installed and in your PATH, or install:
echo   1. MinGW-w64 from: https://www.mingw-w64.org/downloads/
echo   2. Visual Studio Community with C++ tools
echo.
echo If g++ is installed but not found, add it to your PATH or
echo specify the full path in this script.
pause
exit /b 1

:found_gpp
echo Using g++ compiler: %GPP%
"%GPP%" -std=c++17 -O2 -I..\include -I. ..\src\server.cpp ..\src\Book.cpp ..\src\User.cpp ..\src\ReadingList.cpp ..\src\Storage.cpp ..\src\AuthService.cpp ..\src\BookService.cpp ..\src\JsonHelper.cpp -o BookWiseBackend.exe -lws2_32 -lwsock32
if errorlevel 1 (
    echo Build failed!
    pause
    exit /b 1
)

:build_success

echo.
echo ========================================
echo Build successful!
echo ========================================
echo.
echo To run the server, use one of these:
echo   1. run_server.bat
echo   2. cd build && BookWiseBackend.exe
echo   3. .\build\BookWiseBackend.exe
echo.
pause

