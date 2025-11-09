# BookWise C++ Backend Server

This is the C++ HTTP backend server for the BookWise application. It provides REST API endpoints that the TypeScript/React frontend communicates with.

## Features

- RESTful API endpoints for authentication, books, and reading lists
- File-based data persistence
- CORS support for frontend communication
- JSON request/response handling

## Prerequisites

- C++17 compatible compiler (GCC, Clang, or MSVC)
- Internet connection (for downloading cpp-httplib header during build)
- **Optional**: CMake 3.15+ (only if using CMake build method)

## Building

### Quick Start (No CMake Required) ⚡

**Windows:**
```batch
cd backend
build_simple.bat
```

**Linux/macOS:**
```bash
cd backend
chmod +x build_simple.sh
./build_simple.sh
```

### Using CMake (Alternative)

If you have CMake installed:

**Windows:**
```powershell
cd backend
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

**Linux/macOS:**
```bash
cd backend
mkdir build
cd build
cmake ..
make
```

> **Note**: If you don't have CMake, use the simple build scripts above. See `BUILD_INSTRUCTIONS.md` for more options.

## Running

After building, run the server:

**Windows (Easiest):**
```batch
run_server.bat
```

**Windows (Manual):**
```powershell
cd build
.\BookWiseBackend.exe
```

**Or from backend directory:**
```powershell
.\build\BookWiseBackend.exe
```

**Linux/macOS:**
```bash
cd build
./BookWiseBackend
```

The server will start on `http://localhost:8080` and display a message when ready.

## API Endpoints

### Authentication

- `POST /api/auth/login` - User login
  - Body: `{ "email": "user@example.com", "password": "password" }`
  - Returns: `{ "id": "user_1234", "email": "user@example.com", "name": "User Name" }`

- `POST /api/auth/register` - User registration
  - Body: `{ "email": "user@example.com", "password": "password", "name": "User Name" }`
  - Returns: `{ "id": "user_1234", "email": "user@example.com", "name": "User Name" }`

### Books

- `GET /api/books` - Get all books
  - Returns: Array of book objects

- `GET /api/books/filter?author=Orwell&year=1940&genre=Fiction&prompt=dystopian` - Filter books
  - Query parameters: `author`, `year`, `genre`, `prompt`
  - Returns: Array of filtered book objects

- `GET /api/books/:id` - Get book by ID
  - Returns: Single book object

### Reading List

- `GET /api/reading-list/:userId` - Get user's reading list
  - Returns: Array of books with status

- `POST /api/reading-list` - Add book to reading list
  - Body: `{ "userId": "user_1234", "bookId": "1", "status": "want-to-read" }`
  - Status values: `"want-to-read"`, `"reading"`, `"completed"`

- `DELETE /api/reading-list/:bookId?userId=user_1234` - Remove book from reading list

## Data Storage

Data is stored in text files in the `data/` directory (created automatically):

- `data/books.txt` - Book catalog
- `data/users.txt` - User accounts
- `data/reading_lists.txt` - User reading lists

## Frontend Integration

The frontend is configured to connect to `http://localhost:8080/api`. Make sure the backend server is running before starting the frontend development server.

To start the frontend:
```bash
npm run dev
```

## Architecture

- **cpp-httplib**: Header-only HTTP library for the server
- **File-based storage**: Simple text file persistence (can be upgraded to database)
- **JSON handling**: Custom JSON serialization/parsing (can be upgraded to nlohmann/json)

## Future Enhancements

- Add proper JSON library (nlohmann/json)
- Implement password hashing (bcrypt)
- Add session management/JWT tokens
- Database integration (SQLite/PostgreSQL)
- Rate limiting and security improvements
- Request logging

