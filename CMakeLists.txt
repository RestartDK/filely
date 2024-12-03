# Set the newest version CMAKE for the project to be built for
cmake_minimum_required(VERSION 3.14)

# Set the project name
project(file_converter)

# Set the C++ standard to 17 for the project
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Ensure CMake creates compile_commands.json for development tools
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Find OpenCV package
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# Find Google Test
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Include directories for your headers
include_directories(include)
include_directories(include/formatters)
include_directories(src)

# Conditionally include third party libraries depending on path
if(APPLE)
    # macOS
    include_directories(/opt/homebrew/include)
elseif(UNIX)
    # Linux
    include_directories(/usr/local/include)
endif()

# Source files for the converter library
set(CONVERTER_SOURCES
        src/converter.cpp
        src/cli.cpp
        src/utils.cpp
        src/formatters/jpegformat.cpp
        src/formatters/jpgformat.cpp
        src/formatters/pngformat.cpp
        src/formatters/csvformat.cpp
        src/formatters/jsonformat.cpp
        src/formatters/bmpformat.cpp
        src/formatters/textformat.cpp
)

# Create a static library for the converter code
add_library(converter_lib STATIC ${CONVERTER_SOURCES})

# Link OpenCV libraries to converter_lib
target_link_libraries(converter_lib ${OpenCV_LIBS})

if(WIN32)
    add_definitions(-DPLATFORM_WINDOWS)
endif()

# Add executable target for the main application
add_executable(file_converter src/main.cpp)
target_link_libraries(file_converter converter_lib)

# Add executable target for the api application
add_executable(api_service api/api_main.cpp api/api_handler.cpp)
target_link_libraries(api_service converter_lib)

# Add test executable
add_executable(runTests test/test_cli.cpp)
target_link_libraries(runTests converter_lib ${GTEST_LIBRARIES} pthread)

# Set output directory for binaries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
