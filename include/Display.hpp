#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include "Timer.hpp"
#include <cstring>
#include <iostream>
#include <vector>
#include <thread>

using namespace std;

class Display {
public:
    Display(Timer& timer);
    Display();

    void tick();
    void stageTimer(int hours, int minutes, int seconds, int tenths);
    void stageActions();
    void setSplash(string str);
    void stageSplash();
    void printStaged();
    static void clearScreen();


private:
    Timer& _timer;
    string _splash;
    vector<string> _buffer;
};

#endif // DISPLAY_HPP
