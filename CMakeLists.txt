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

# Add the combined test executable
add_executable(Tests
    tests/TimerTest.cpp
    tests/StopwatchTest.cpp
    tests/AlarmTest.cpp
    src/Timer.cpp
    src/Stopwatch.cpp
    src/Alarm.cpp
)

# Link the combined test executable with the necessary libraries or targets
# target_link_libraries(Tests <libraries>)

# Add the tests
add_test(NAME TimerTest COMMAND Tests --gtest_filter=TimerTest*)
add_test(NAME StopwatchTest COMMAND Tests --gtest_filter=StopwatchTest*)
add_test(NAME AlarmTest COMMAND Tests --gtest_filter=AlarmTest*)
