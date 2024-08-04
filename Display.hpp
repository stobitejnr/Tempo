#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include "Timer.hpp"
#include <iostream>
#include <vector>

using namespace std;

class Display {
public:
    Display(Timer& timer);

    void tick();
    void printTimer(int hours, int minutes, int seconds, int tenths);
    void printActions();
    void setSplash(string str);
    void printSplash();
    static void clearScreen();

private:
    Timer& _timer;
    string _splash;
};

#endif // DISPLAY_HPP
