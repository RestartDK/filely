# Set the newest version CMAKE for the project to be built for
cmake_minimum_required(VERSION 3.29)

# Here we set the project name
project(file_converter)

# Set the newest version c++ for the project to be built for
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Make sure CMAKE makes a compile_commands file so that compiler recognises custom classes
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add executable target which will be main.cpp
add_executable(file_converter
    src/main.cpp
    src/converter.cpp
    src/cli.cpp
    src/formatters/jpegformat.cpp
    src/formatters/jpgformat.cpp
    src/formatters/pngformat.cpp
    src/formatters/csvformat.cpp
    src/formatters/jsonformat.cpp
)

# Specify where to look for header files (include directories)
target_include_directories(file_converter PUBLIC
    "${PROJECT_SOURCE_DIR}/include"
    "${PROJECT_SOURCE_DIR}/include/formatters"  
)

# Need to set output directory for binaries here
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
