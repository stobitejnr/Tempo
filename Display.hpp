#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include "Timer.hpp"
#include <iostream>

using namespace std;

class Display {
public:
    Display(Timer& timer);

    void tick();
    void printTime(int hours, int minutes, int seconds);
    void clearScreen();

private:
    Timer& _timer;
};

#endif // DISPLAY_HPP
