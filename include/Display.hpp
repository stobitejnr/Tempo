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
    void stageTimerBar(double percentage);

    void stageStopwatchDisplay(int hours, int minutes, int seconds, int hundredths);
    void stageStopwatchControls();

    void stageAlarmDisplay();
    void stageAlarmControls();

    //Splash helpers
    void setSplash(string str);
    void clearSplash();
    
    //Printing logic
    void printSplash(int);
    void printAscii(int);
    void printControls(int);
    void printBar(int);

    //Terminal helpers
    void clearScreen();
    void setCursor(int, int);
    void clearLine(int);


    template<typename char_type>
    static auto fast_print(const std::basic_string<char_type>& sss) -> void;


private:

    string _asciiBuffer;
    string _barBuffer;
    string _controlBuffer;
    string _splash;

    string _oldAscii;
    string _oldControls;
    string _oldBar;
    string _oldSplash;

    int _asciiWidth;
    
};

#endif // DISPLAY_HPP
