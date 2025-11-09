#!/bin/bash

# Build script for BookWise C++ application

echo "Building BookWise..."

# Create build directory
mkdir -p build
cd build

# Configure CMake
cmake ..

# Build the project
make

echo "Build complete! Run ./build/BookWise to start the application."

