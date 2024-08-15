#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include "Timer.hpp"
#include "Stopwatch.hpp"
#include "Alarm.hpp"

#include "../fonts/font1.hpp"

#include <cstring>
#include <iostream>
#include <vector>
#include <thread>

using namespace std;

class Display {
public:

    Display();

    void tickTimer(Timer& timer);
    void tickStopwatch(Stopwatch& stopwatch);
    void tickAlarm(Alarm& alarm);

    void stageTimerDisplay(int hours, int minutes, int seconds, int tenths);
    void stageTimerActions();

    void stageStopwatchDisplay(int hours, int minutes, int seconds, int tenths, int millis);
    void stageStopwatchActions();

    void stageAlarmDisplay();
    void stageAlarmActions();

    void setSplash(string str);
    void stageSplash();

    void printStaged();

    static void clearScreen();


private:

    string _splash;
    vector<string> _buffer;
    
};

#endif // DISPLAY_HPP
