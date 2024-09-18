#include <cassert>
#include <iostream>
#include <chrono>
#include <thread>

#include "../include/Display.hpp"

using namespace std;

void test_nonreturn(){
    Display display;
    display.clearScreen();
    string sss = "Testing";
    display.fast_print(sss);
    display.setCursor(1,1);
    display.clearLine(1);
}

void test_timer_setup(){
    Display display;
    display.tickTimerSetup("00:00:00");
}

void test_timer(){
    Display display;
    Timer timer(1,0,0);
    display.tickTimer(timer);
}

void test_stopwatch(){
    Display display;
    Stopwatch stopwatch;
    display.tickStopwatch(stopwatch);
}

void test_alarm(){
    Display display;
    Alarm alarm;
    display.tickAlarm(alarm);
}

int main() {
    try {
        
        test_nonreturn();
        test_timer_setup();
        test_timer();
        test_stopwatch();
        test_alarm();

        cout << "All tests passed successfully!\n";
    } catch (const exception& e) {
        cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}