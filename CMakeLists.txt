cmake_minimum_required(VERSION 3.27.7)

project(PhotoToAsciiProject)

add_executable(${PROJECT_NAME} main.cpp)

# debug
set(CMAKE_BUILD_TYPE Debug)

# Specify paths to zlib and libpng
set(ZLIB_INCLUDE_DIR "C:/Program Files (x86)/zlib/include")
set(ZLIB_LIBRARY "C:/Program Files (x86)/zlib/lib")

set(PNG_INCLUDE_DIR "C:/Program Files (x86)/libpng/include")
set(PNG_LIBRARY "C:/Program Files (x86)/libpng/lib")

set(JPG_INCLUDE_DIR "C:/libjpeg-turbo-gcc64/include")
set(JPG_LIBRARY "C:/libjpeg-turbo-gcc64/lib")

# Include libpng if needed
include_directories(${PNG_INCLUDE_DIR})
target_link_directories(${PROJECT_NAME} PRIVATE ${PNG_LIBRARY})

# Include zlib
include_directories(${ZLIB_INCLUDE_DIR})
target_link_directories(${PROJECT_NAME} PRIVATE ${ZLIB_LIBRARY})

# Include libJPEG
include_directories(${JPG_INCLUDE_DIR})
target_link_directories(${PROJECT_NAME} PRIVATE ${JPG_LIBRARY})

# Link libpng if needed
target_link_libraries(${PROJECT_NAME} PRIVATE libpng16.a)

# Link zlib
target_link_libraries(${PROJECT_NAME} PRIVATE libzlibstatic.a)

# Link libjpg
target_link_libraries(${PROJECT_NAME} PRIVATE libjpeg.a)