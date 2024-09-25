# Set the newest version CMAKE for the project to be built for
cmake_minimum_required(VERSION 3.29)

# Here we set the project name
project(file_converter)

# Set the newest version c++ for the project to be built for
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add executable target which will be main.cpp
add_executable(file_converter
    src/main.cpp
    src/file.cpp
    src/filereader.cpp
    src/filewriter.cpp
    src/fileformat.cpp
    src/formatters/jpegformat.cpp
    src/formatters/jpgformat.cpp
    src/formatters/pngformat.cpp
    src/formatters/csvformat.cpp
    src/formatters/xslxformat.cpp
)

# Specify where to look for header files (include directories)
target_include_directories(FileConverter PUBLIC
    "${PROJECT_SOURCE_DIR}/include"
    "${PROJECT_SOURCE_DIR}/include/formatters"  
)

# Need to set output directory for binaries here

