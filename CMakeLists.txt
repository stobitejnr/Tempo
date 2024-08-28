 cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(Tempo VERSION 0.1)

enable_testing()

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories for header files
include_directories(${PROJECT_SOURCE_DIR}/include)

# Add the executable
add_executable(Tempo

    #cpps
    src/main.cpp
    src/Menu.cpp
    src/Display.cpp
    src/Timer.cpp
    src/Stopwatch.cpp
    src/Alarm.cpp

    #fonts
    fonts/font1.cpp

)
