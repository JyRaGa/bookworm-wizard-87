@echo off
REM Stop the backend server if it's running

echo Stopping BookWise Backend Server...
taskkill /F /IM BookWiseBackend.exe >nul 2>&1

if %errorlevel% equ 0 (
    echo Server stopped successfully.
) else (
    echo No server was running.
)

pause

