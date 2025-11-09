@echo off
REM Build script for BookWise C++ application (Windows)

echo Building BookWise...

REM Create build directory
if not exist build mkdir build
cd build

REM Configure CMake
cmake ..

REM Build the project
cmake --build . --config Release

echo Build complete! Run build\Release\BookWise.exe to start the application.

pause

