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
    void stageTimerControls();

    void stageStopwatchDisplay(int hours, int minutes, int seconds, int hundredths);
    void stageStopwatchControls();

    void stageAlarmDisplay();
    void stageAlarmControls();

    void setSplash(string str);
    void printSplash();

    void printAscii();
    void printControls();


    void clearScreen();
    void setCursor(int, int);


    template<typename char_type>
    static auto fast_print(const std::basic_string<char_type>& sss) -> void;


private:

    string _asciiBuffer;
    string _controlBuffer;
    string _splash;

    string _oldAscii;
    string _oldControls;
    string _oldSplash;
    
};

#endif // DISPLAY_HPP
