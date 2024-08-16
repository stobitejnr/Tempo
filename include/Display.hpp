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

    void stageStopwatchDisplay(int hours, int minutes, int seconds, int hundredths);
    void stageStopwatchActions();

    void stageAlarmDisplay();
    void stageAlarmActions();

    void setSplash(string str);
    void stageSplash();

    void printStaged();

    static void clearScreen();
    static void resetCursor();


    template<typename char_type>
    static auto fast_print(const std::basic_string<char_type>& sss) -> void;


private:

    string _splash;
    string _buffer;
    
};

#endif // DISPLAY_HPP
