cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project("Tempo")

# Enable testing
include(CTest)

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
    src/Notification.cpp
    src/Alarm.cpp
    fonts/font1.cpp
    fonts/font2.cpp
)

# Add the test executables
add_executable(TimerTest
    test/TimerTest.cpp
    src/Timer.cpp
)

add_executable(StopwatchTest
    test/StopwatchTest.cpp
    src/Stopwatch.cpp
)

add_executable(AlarmTest
    test/AlarmTest.cpp
    src/Alarm.cpp
)

add_executable(DisplayTest
    test/DisplayTest.cpp
    src/Display.cpp
    src/Menu.cpp
    src/Timer.cpp
    src/Stopwatch.cpp
    src/Notification.cpp
    src/Alarm.cpp
    fonts/font1.cpp
    fonts/font2.cpp
)

add_executable(MenuTest
    test/MenuTest.cpp
    src/Menu.cpp
    src/Display.cpp
    src/Timer.cpp
    src/Stopwatch.cpp
    src/Notification.cpp
    src/Alarm.cpp
    fonts/font1.cpp
    fonts/font2.cpp
)

# Add the tests
add_test(NAME TimerTest COMMAND TimerTest)
add_test(NAME StopwatchTest COMMAND StopwatchTest)
add_test(NAME AlarmTest COMMAND AlarmTest)
add_test(NAME DisplayTest COMMAND DisplayTest)
add_test(NAME MenuTest COMMAND MenuTest)
