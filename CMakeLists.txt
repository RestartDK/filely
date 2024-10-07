# Set the newest version CMAKE for the project to be built for
cmake_minimum_required(VERSION 3.29)

# Set the project name
project(file_converter)

# Set the C++ standard to 14 for the project
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Ensure CMake creates compile_commands.json for development tools
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Find OpenCV package (it will search for OpenCV config file)
find_package(OpenCV REQUIRED)

# Add executable target which will be the main.cpp and all required sources
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
    ${OpenCV_INCLUDE_DIRS} # Include OpenCV headers
)

# Link the OpenCV libraries to the file_converter target
target_link_libraries(file_converter ${OpenCV_LIBS})

# Set output directory for binaries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
