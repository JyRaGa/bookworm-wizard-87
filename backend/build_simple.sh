#!/bin/bash

# Simple build script without CMake
# Requires: g++ or clang++

echo "Building BookWise Backend (without CMake)..."

# Create build directory
mkdir -p build
cd build

# Download cpp-httplib header if not exists
if [ ! -f "httplib.h" ]; then
    echo "Downloading cpp-httplib..."
    curl -L -o httplib.h https://raw.githubusercontent.com/yhirose/cpp-httplib/master/httplib.h
    if [ $? -ne 0 ]; then
        echo "Error: Failed to download httplib.h"
        echo "Please download it manually from: https://github.com/yhirose/cpp-httplib"
        exit 1
    fi
fi

# Detect compiler
if command -v g++ &> /dev/null; then
    COMPILER="g++"
elif command -v clang++ &> /dev/null; then
    COMPILER="clang++"
else
    echo "Error: No C++ compiler found. Please install g++ or clang++"
    exit 1
fi

echo "Using compiler: $COMPILER"

# Compile
$COMPILER -std=c++17 -O2 -pthread \
    -I../include \
    -I. \
    ../src/server.cpp \
    ../src/Book.cpp \
    ../src/User.cpp \
    ../src/ReadingList.cpp \
    ../src/Storage.cpp \
    ../src/AuthService.cpp \
    ../src/BookService.cpp \
    ../src/JsonHelper.cpp \
    -o BookWiseBackend

if [ $? -eq 0 ]; then
    echo "Build successful! Run ./BookWiseBackend to start the server."
else
    echo "Build failed!"
    exit 1
fi

