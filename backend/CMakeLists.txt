cmake_minimum_required(VERSION 3.15)
project(BookWiseBackend VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Download cpp-httplib (header-only HTTP library)
include(FetchContent)
FetchContent_Declare(
    httplib
    GIT_REPOSITORY https://github.com/yhirose/cpp-httplib.git
    GIT_TAG v0.14.3
)
FetchContent_MakeAvailable(httplib)

# Source files
set(SOURCES
    src/server.cpp
    src/Book.cpp
    src/User.cpp
    src/ReadingList.cpp
    src/Storage.cpp
    src/AuthService.cpp
    src/BookService.cpp
    src/JsonHelper.cpp
)

# Header files
set(HEADERS
    include/Book.h
    include/User.h
    include/ReadingList.h
    include/Storage.h
    include/AuthService.h
    include/BookService.h
    include/JsonHelper.h
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE 
    include
    ${httplib_SOURCE_DIR}
)

# Link libraries (for threading on some platforms)
if(UNIX)
    target_link_libraries(${PROJECT_NAME} pthread)
endif()

# Compiler-specific options
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic)
endif()

