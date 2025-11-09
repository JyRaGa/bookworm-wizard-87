# Quick Start (No CMake Required)

## Windows Users

1. **Find your compiler first:**
   ```
   find_compiler.bat
   ```

2. **If g++ is found, build:**
   ```
   build_simple.bat
   ```
   
   **OR if g++ is not in PATH, specify the path:**
   ```
   build_with_path.bat "C:\path\to\g++.exe"
   ```

3. **If successful, run the server:**
   ```
   run_server.bat
   ```
   
   Or manually:
   ```
   cd build
   BookWiseBackend.exe
   ```
   
   Or from the backend directory:
   ```
   .\build\BookWiseBackend.exe
   ```

## Linux/macOS Users

1. Open Terminal in the `backend` folder
2. Run:
   ```bash
   chmod +x build_simple.sh
   ./build_simple.sh
   ```
3. If successful, run:
   ```bash
   ./build/BookWiseBackend
   ```

## What the Script Does

1. Creates a `build` directory
2. Downloads the `httplib.h` header file automatically
3. Compiles all C++ source files
4. Creates the `BookWiseBackend` executable

## Requirements

- **Windows**: Visual Studio C++ tools OR MinGW-w64
- **Linux**: g++ compiler (`sudo apt install build-essential`)
- **macOS**: Xcode Command Line Tools (`xcode-select --install`)

## Troubleshooting

If the build fails:
1. Check that you have a C++ compiler installed
2. Make sure you have internet connection (to download httplib.h)
3. See `BUILD_INSTRUCTIONS.md` for detailed help

