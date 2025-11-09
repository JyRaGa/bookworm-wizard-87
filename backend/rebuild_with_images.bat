@echo off
REM Rebuild backend and regenerate data with images

echo Rebuilding backend with image support...

REM Stop any running server first
echo Checking for running server...
taskkill /F /IM BookWiseBackend.exe >nul 2>&1
if %errorlevel% equ 0 (
    echo Stopped running server.
    timeout /t 1 >nul
)

call build_simple.bat

if errorlevel 1 (
    echo Build failed!
    pause
    exit /b 1
)

echo.
echo Regenerating data with images...
if exist "data\books.txt" (
    del "data\books.txt"
    echo Deleted old books.txt
)

echo.
echo Backend rebuilt! Now run: run_server.bat
pause

