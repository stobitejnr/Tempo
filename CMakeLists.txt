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

# Add the test executable
add_executable(timer_test
    tests/timer_test.cpp
    src/Timer.cpp  # Include the Timer implementation
)

# Add the test
add_test(NAME TimerTest COMMAND timer_test)

# Optional: Add a custom target to run all tests
add_custom_target(run_tests
    COMMAND ${CMAKE_CTEST_COMMAND}
    DEPENDS timer_test
)