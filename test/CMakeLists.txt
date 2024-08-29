# Add the test executables
add_executable(TimerTest
    tests/TimerTest.cpp
    src/Timer.cpp
)

add_executable(StopwatchTest
    tests/StopwatchTest.cpp
    src/Stopwatch.cpp
)

add_executable(AlarmTest
    tests/AlarmTest.cpp
    src/Alarm.cpp
)

# Add the tests
add_test(NAME TimerTest COMMAND TimerTest)
add_test(NAME StopwatchTest COMMAND StopwatchTest)
add_test(NAME AlarmTest COMMAND AlarmTest)