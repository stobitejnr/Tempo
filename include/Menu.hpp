#ifndef MENU_HPP
#define MENU_HPP

#include "Timer.hpp"
#include "Stopwatch.hpp"
#include "Alarm.hpp"
#include "Display.hpp"

#include <iostream>
#include <conio.h>

using namespace std;

class Menu {
public:
    Menu();
    void printMenu();
    char getMenuInput();
    void wait(double seconds);

    void checkTimerInput(Timer& timer);

    void start();

private:

Display _display = Display();
bool _run;

};

#endif // MENU_HPP
