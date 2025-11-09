@echo off
REM Simple script to run the backend server

if not exist "build\BookWiseBackend.exe" (
    echo Error: BookWiseBackend.exe not found!
    echo Please build the project first using: build_simple.bat
    pause
    exit /b 1
)

echo Starting BookWise Backend Server...
echo Server will run on http://localhost:8080
echo Press Ctrl+C to stop the server
echo.

cd build
BookWiseBackend.exe

