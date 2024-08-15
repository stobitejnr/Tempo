#include "../include/Menu.hpp"

using namespace std;

#define LOOPTIME 0.1

Menu::Menu(){ 
    _run = true;
}

void Menu::start(){

    Display::clearScreen();

    cout << "1: Timer\n2: Stopwatch\n3: Alarm\nQ: Quit Program" << endl;

    char in = getMenuInput();

    if(in == '1'){

        bool run = true;

        Timer timer;
        while(run){
            if(timer.remainingMilliseconds() == 0) { _display.setSplash("TIMER FINISHED"); }

            _display.tickTimer(timer);

            checkTimerInput(timer);

            wait(0.1);
        }
    }
    else if(in == '2'){
        Stopwatch stopwatch;
    }
    else if(in == '3'){
        Alarm alarm;
    }
    else if(in == 'q'){
        return;
    }
}

/* =========================================================
BUSY-WAIT FOR A SPECIFIED AMOUNT OF TIME (IN SECONDS)
========================================================= */
void Menu::wait(double seconds) {
    auto start = chrono::high_resolution_clock::now();
    auto duration = chrono::duration<double>(seconds);
    while (chrono::high_resolution_clock::now() - start < duration) { }
}

/* =========================================================
HANDLE KEYBOARD INPUT FOR TIMER
========================================================= */
void Menu::checkTimerInput(Timer& timer){
    if(_kbhit()){
        char ch = _getch();
        switch(ch){
            case 's':
                if(timer.isRunning()){
                    timer.pause();
                    _display.setSplash("TIMER PAUSED");
                }
                else{
                    _display.setSplash("");
                    timer.resume();        
                }
                break;
            case 'r':
                timer.reset();
                _display.setSplash("TIMER RESET, PRESS 'S' TO START");
                break;
            case 'i':
                timer.addSeconds(10);
                _display.setSplash("10 SECONDS ADDED TO TIMER");
                break;
            case 'q':
                start();
                break;

            default:
                break;
        }
        _display.tickTimer(timer);
    }
}

char Menu::getMenuInput(){
    while(true){
        if(_kbhit()){
            char ch = _getch();
            switch(ch){
                case '1':
                    return '1';
                case '2':
                    return '2';
                case '3':
                    return '3';
                case 'q':
                case 'Q':
                    return 'q';
                default:
                    break;
            }
        }
    }
}