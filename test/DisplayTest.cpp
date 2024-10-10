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
    display.setSplash(sss);
    display.clearSplash();

}

void test_timer_setup(){
    Display display;
    display.tickTimerSetup("00:00:00");
}

void test_timer(){
    Display display;
    Timer timer(1,1,1);
    display.tickTimer(timer);
    timer.pause();
    display.tickTimer(timer);
}

void test_stopwatch(){
    Display display;
    Stopwatch stopwatch;
    stopwatch.addSplit();
    display.tickStopwatch(stopwatch);
}

void test_alarm(){
    Display display;
    Alarm alarm(12,12);
    display.tickAlarm(alarm);
}

void test_alarm_setup(){
    Display display;
    display.tickAlarmSetup("00:00", false);
    display.tickAlarmSetup("12:12", true);
}

int main() {
    try {
        
        test_nonreturn();
        test_timer_setup();
        test_timer();
        test_stopwatch();
        test_alarm();
        test_alarm_setup();

        cout << "All tests passed successfully!\n";
    } catch (const exception& e) {
        cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}