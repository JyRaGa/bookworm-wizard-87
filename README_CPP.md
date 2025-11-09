# BookWise - C++ Console Application

This is a C++ console-based version of the BookWise book recommendation system, converted from the original TypeScript/React web application.

## Features

- **User Authentication**: Login and registration system
- **Book Browsing**: View all available books
- **Advanced Filtering**: Filter books by author, year, genre, and search prompts
- **Reading List**: Manage your personal reading list
- **File-based Storage**: Data persistence using text files

## Project Structure

```
bookworm-wizard-87 - Copy/
├── CMakeLists.txt          # CMake build configuration
├── include/                # Header files
│   ├── Book.h
│   ├── User.h
│   ├── ReadingList.h
│   ├── Storage.h
│   ├── AuthService.h
│   ├── BookService.h
│   └── UI.h
├── src/                    # Source files
│   ├── main.cpp
│   ├── Book.cpp
│   ├── User.cpp
│   ├── ReadingList.cpp
│   ├── Storage.cpp
│   ├── AuthService.cpp
│   ├── BookService.cpp
│   └── UI.cpp
└── data/                   # Data directory (created at runtime)
    ├── books.txt
    ├── users.txt
    └── reading_lists.txt
```

## Building the Project

### Prerequisites

- CMake 3.15 or higher
- C++17 compatible compiler (GCC, Clang, or MSVC)

### Build Instructions

#### Windows (using Visual Studio)

```powershell
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

#### Linux/macOS

```bash
mkdir build
cd build
cmake ..
make
```

### Running the Application

After building, run the executable:

**Windows:**
```powershell
.\build\Release\BookWise.exe
# or
.\build\Debug\BookWise.exe
```

**Linux/macOS:**
```bash
./build/BookWise
```

## Usage

1. **Start the application**: Run the compiled executable
2. **Register/Login**: Create a new account or login with existing credentials
3. **Browse Books**: View all available books in the library
4. **Filter Books**: Use advanced filters to find specific books
5. **Reading List**: Manage your personal reading list
6. **Logout**: Exit your session

## Data Storage

The application stores data in text files in the `data/` directory:

- `books.txt`: Book catalog
- `users.txt`: User accounts
- `reading_lists.txt`: User reading lists

These files are created automatically on first run with default book data.

## Default Books

The application comes with 5 default books:
- The Great Gatsby (F. Scott Fitzgerald)
- 1984 (George Orwell)
- To Kill a Mockingbird (Harper Lee)
- Pride and Prejudice (Jane Austen)
- The Catcher in the Rye (J.D. Salinger)

## Differences from Web Version

This C++ console version maintains the core functionality of the original web application but with some differences:

- **Console-based UI**: Text-based interface instead of web UI
- **File Storage**: Simple text file storage instead of database/API
- **No Images**: Book cover images are not displayed (text-only)
- **Simplified JSON**: Basic text parsing instead of full JSON library

## Future Enhancements

Potential improvements:
- Add a proper JSON library (e.g., nlohmann/json) for better data handling
- Implement password hashing for security
- Add book search with fuzzy matching
- Support for adding/removing books from reading list in UI
- Export reading list functionality
- Database integration (SQLite)

## License

Same as the original project.

