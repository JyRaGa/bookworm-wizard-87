# Build Instructions (Without CMake)

If you don't have CMake installed, you can build the project using these alternative methods:

## Option 1: Simple Build Scripts (Recommended)

### Windows

1. **First, find your compiler:**
   ```batch
   find_compiler.bat
   ```
   This will show you where g++ is located (if installed).

2. **If g++ is found, build normally:**
   ```batch
   build_simple.bat
   ```

3. **If g++ is NOT in PATH but you know its location:**
   ```batch
   build_with_path.bat "C:\path\to\g++.exe"
   ```
   Example:
   ```batch
   build_with_path.bat "C:\MinGW\bin\g++.exe"
   ```

**Requirements:**
- MinGW-w64 (g++.exe) - **Recommended**
- Visual Studio with C++ tools (cl.exe) - Fallback

### Linux/macOS

1. Open Terminal in the `backend` directory
2. Make the script executable:
   ```bash
   chmod +x build_simple.sh
   ```
3. Run:
   ```bash
   ./build_simple.sh
   ```

**Requirements:**
- g++ or clang++ compiler
- curl (for downloading httplib.h)

## Option 2: Using Makefile (Linux/macOS)

1. Open Terminal in the `backend` directory
2. Run:
   ```bash
   make
   ```

This will automatically download the httplib header and compile the project.

## Option 3: Manual Compilation

If the scripts don't work, you can compile manually:

### Step 1: Download httplib.h

Download the header file from:
https://raw.githubusercontent.com/yhirose/cpp-httplib/master/httplib.h

Save it as `backend/build/httplib.h`

### Step 2: Compile

**Linux/macOS:**
```bash
cd backend/build
g++ -std=c++17 -O2 -pthread \
    -I../include -I. \
    ../src/server.cpp \
    ../src/Book.cpp \
    ../src/User.cpp \
    ../src/ReadingList.cpp \
    ../src/Storage.cpp \
    ../src/AuthService.cpp \
    ../src/BookService.cpp \
    ../src/JsonHelper.cpp \
    -o BookWiseBackend
```

**Windows (MinGW):**
```batch
cd backend\build
g++ -std=c++17 -O2 -I..\include -I. ..\src\server.cpp ..\src\Book.cpp ..\src\User.cpp ..\src\ReadingList.cpp ..\src\Storage.cpp ..\src\AuthService.cpp ..\src\BookService.cpp ..\src\JsonHelper.cpp -o BookWiseBackend.exe -lws2_32 -lwsock32
```

**Windows (Visual Studio):**
```batch
cd backend\build
cl /std:c++17 /O2 /EHsc /I..\include /I. ..\src\server.cpp ..\src\Book.cpp ..\src\User.cpp ..\src\ReadingList.cpp ..\src\Storage.cpp ..\src\AuthService.cpp ..\src\BookService.cpp ..\src\JsonHelper.cpp /Fe:BookWiseBackend.exe /link ws2_32.lib
```

## Option 4: Install CMake (Alternative)

If you prefer to use CMake:

### Windows
1. Download from: https://cmake.org/download/
2. Install and select "Add CMake to system PATH"
3. Use the original CMake build:
   ```batch
   cd backend
   mkdir build
   cd build
   cmake ..
   cmake --build . --config Release
   ```

### Linux
```bash
sudo apt update
sudo apt install cmake  # Ubuntu/Debian
# or
sudo dnf install cmake  # Fedora
```

### macOS
```bash
brew install cmake
```

## Running the Server

After building, run:

**Windows:**
```batch
build\BookWiseBackend.exe
```

**Linux/macOS:**
```bash
build/BookWiseBackend
```

The server will start on `http://localhost:8080`

## Troubleshooting

### "No compiler found"
- **Windows**: Install Visual Studio Community (free) with C++ tools, or MinGW-w64
- **Linux**: Install build-essential: `sudo apt install build-essential`
- **macOS**: Install Xcode Command Line Tools: `xcode-select --install`

### "httplib.h not found"
- Download manually from: https://raw.githubusercontent.com/yhirose/cpp-httplib/master/httplib.h
- Place it in `backend/build/httplib.h`

### "pthread not found" (Linux)
- Install: `sudo apt install libpthread-stubs0-dev`

### Port 8080 already in use
- Change the port in `backend/src/server.cpp` (line with `svr.listen("0.0.0.0", 8080)`)

