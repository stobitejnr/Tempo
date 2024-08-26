#define OOF_IMPL

#include "../include/Menu.hpp"

using namespace std;

#define LOOPTIME 0.1

Menu::Menu(){ 
    _display = Display();
    _run = true;
}

void Menu::start(){

    _display.clearScreen();

    cout << "1: Timer\n2: Stopwatch\n3: Alarm\nQ: Quit Program" << endl;

    char in = getMenuInput();

    //ENTER TIMER SEQUENCE
    if(in == '1'){
        _display.clearScreen();

        Timer timer;

        bool run = true;

        _display.clearScreen();

        while(run){
            if(timer.remainingMilliseconds() == 0) {
                _display.setSplash("TIMER FINISHED"); 
            }

            _display.tickTimer(timer);

            checkTimerInput(timer, run);

            wait(0.01);
        }

    }

    //ENTER STOPWATCH SEQUENCE
    else if(in == '2'){
        //Stopwatch stopwatch = Stopwatch(0,59,55);
        Stopwatch stopwatch;

        bool run = true;

        _display.tickStopwatch(stopwatch);

        cout << "\n Press any key to start your stopwatch." << endl;

        waitForInput();

        _display.clearScreen();

        stopwatch.start();
        
        while(run){

            _display.tickStopwatch(stopwatch);

            checkStopwatchInput(stopwatch, run);

            wait(0.01);
        }
    }

    //ENTER ALARM SEQUENCE
    else if(in == '3'){
        Alarm alarm;
    }

    //QUIT
    else if(in == 'q'){
        return;
    }
    start();
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
WAIT FOR ANY USER INPUT
========================================================= */
void Menu::waitForInput() {
    _getch();
}

/* =========================================================
HANDLE KEYBOARD INPUT FOR TIMER
========================================================= */
void Menu::checkTimerInput(Timer& timer, bool& run){
    if(_kbhit()){
        char ch = _getch();
        switch(ch){
            case 'S':
            case 's':
                if(timer.isRunning()){
                    timer.pause();
                    _display.setSplash("TIMER PAUSED");
                }
                else if(timer.remainingMilliseconds() > 0){
                    _display.clearSplash();
                    timer.resume();        
                }
                break;
            case 'R':
            case 'r':
                timer.reset();
                _display.clearScreen();
                _display.setSplash("TIMER RESET, PRESS 'S' TO START");
                break;
            case 'A':
            case 'a':
                timer.addTime();
                _display.setSplash("X ADDED TO TIMER");
                break;
            case 'C':
            case 'c':
                timer.changeIncrementTime();
                _display.setSplash("TIME INCREMENT CHANGED");
                break;
            case 'Q':
            case 'q':
                _display.clearSplash();
                run = false;
                return;
            default:
                break;
        }
    }
}

void Menu::checkStopwatchInput(Stopwatch& stopwatch, bool& run){
    if(_kbhit()){
        char ch = _getch();
        switch(ch){
            case 'S':
            case 's':
                if(stopwatch.isRunning()){
                    stopwatch.pause();
                    _display.setSplash("STOPWATCH PAUSED");
                }
                else{
                    _display.clearSplash();
                    stopwatch.resume();        
                }
                break;
            case 'R':
            case 'r':
                stopwatch.reset();
                _display.clearScreen();
                _display.setSplash("STOPWATCH RESET, PRESS 'S' TO START");
                break;
            case 'A':
            case 'a':
                stopwatch.split();
                _display.setSplash("SPLIT CREATED");
                break;
            case 'Q':
            case 'q':
            _display.clearSplash();
                run = false;
                return;
            default:
                if(!run){
                    return;
                }
                break;
        }
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
                    return 'q';
                default:
                    break;
            }
        }
        wait(0.1);
    }
}