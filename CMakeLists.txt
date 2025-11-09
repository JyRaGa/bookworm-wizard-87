cmake_minimum_required(VERSION 3.15)
project(BookWise VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source files
set(SOURCES
    src/main.cpp
    src/Book.cpp
    src/User.cpp
    src/ReadingList.cpp
    src/Storage.cpp
    src/AuthService.cpp
    src/BookService.cpp
    src/UI.cpp
)

# Header files
set(HEADERS
    include/Book.h
    include/User.h
    include/ReadingList.h
    include/Storage.h
    include/AuthService.h
    include/BookService.h
    include/UI.h
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE include)

# Compiler-specific options
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic)
endif()

