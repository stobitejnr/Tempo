cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(Tempo VERSION 0.1)

# Enable testing
enable_testing()

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories for header files
include_directories(${PROJECT_SOURCE_DIR}/include)

# Add the main executable
add_executable(Tempo
    src/main.cpp
    src/Menu.cpp
    src/Display.cpp
    src/Timer.cpp
    src/Stopwatch.cpp
    src/Alarm.cpp
    fonts/font1.cpp
)

# Add the test executables
add_executable(TimerTest
    tests/TimerTest.cpp
    src/Timer.cpp
)

add_executable(StopwatchTest
    tests/StopwatchTest.cpp
    src/Stopwatch.cpp
)

# Add the tests
add_test(NAME TimerTest COMMAND TimerTest)
add_test(NAME StopwatchTest COMMAND StopwatchTest)
