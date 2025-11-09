# BookWise Architecture

This project now uses a **hybrid architecture** with a C++ backend and TypeScript/React frontend.

## Architecture Overview

```
┌─────────────────┐         HTTP/REST         ┌─────────────────┐
│                 │ ◄───────────────────────► │                 │
│  React Frontend │    JSON over HTTP         │  C++ Backend   │
│  (TypeScript)   │                           │  (HTTP Server) │
│                 │                           │                 │
└─────────────────┘                           └─────────────────┘
                                                       │
                                                       ▼
                                              ┌─────────────────┐
                                              │  File Storage   │
                                              │  (data/*.txt)    │
                                              └─────────────────┘
```

## Components

### Frontend (TypeScript/React)
- **Location**: `src/`
- **Framework**: React + TypeScript + Vite
- **UI Library**: shadcn-ui + Tailwind CSS
- **API Client**: `src/services/api.ts` - Makes HTTP requests to C++ backend

### Backend (C++)
- **Location**: `backend/`
- **HTTP Library**: cpp-httplib (header-only, downloaded via CMake)
- **Server**: `backend/src/server.cpp` - HTTP server on port 8080
- **Data Layer**: File-based storage in `data/` directory

## Communication Flow

1. **User Action** → Frontend component calls API service
2. **API Service** → Makes HTTP request to `http://localhost:8080/api`
3. **C++ Backend** → Processes request, reads/writes data files
4. **Response** → JSON sent back to frontend
5. **Frontend** → Updates UI with response data

## API Endpoints

All endpoints are under `/api`:

- `POST /api/auth/login` - User authentication
- `POST /api/auth/register` - User registration
- `GET /api/books` - Get all books
- `GET /api/books/filter` - Filter books (query params)
- `GET /api/books/:id` - Get book by ID
- `GET /api/reading-list/:userId` - Get user's reading list
- `POST /api/reading-list` - Add book to reading list
- `DELETE /api/reading-list/:bookId` - Remove book from reading list

## Data Storage

Data is persisted in text files:
- `data/books.txt` - Book catalog
- `data/users.txt` - User accounts  
- `data/reading_lists.txt` - User reading lists

Format: Pipe-delimited (`|`) for simplicity. Can be upgraded to database later.

## Running the Application

### 1. Start the C++ Backend

```bash
cd backend
mkdir build && cd build
cmake ..
cmake --build . --config Release  # or `make` on Linux
./BookWiseBackend  # or BookWiseBackend.exe on Windows
```

Backend runs on `http://localhost:8080`

### 2. Start the Frontend

```bash
npm install
npm run dev
```

Frontend runs on `http://localhost:5173` (or similar Vite port)

## Benefits of This Architecture

1. **Performance**: C++ backend provides fast data processing
2. **Modern UI**: React frontend for great user experience
3. **Separation of Concerns**: Clear separation between UI and business logic
4. **Scalability**: Backend can be upgraded to use database, caching, etc.
5. **Type Safety**: TypeScript on frontend, strong typing in C++

## Future Enhancements

- Replace file storage with SQLite/PostgreSQL
- Add JWT authentication
- Implement password hashing (bcrypt)
- Add request rate limiting
- Add comprehensive error handling
- Add request logging
- Use proper JSON library (nlohmann/json) instead of manual parsing

