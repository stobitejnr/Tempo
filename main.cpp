

#include "Timer.hpp"
#include "Display.hpp"


#include <iostream>
#include <chrono>
#include <conio.h>
#include <vector>

#define LOOPTIME 1

using namespace std;

/* =========================================================
BUSY-WAIT FOR A SPECIFIED AMOUNT OF TIME (IN SECONDS)
========================================================= */
void wait(double seconds) {
    auto start = chrono::high_resolution_clock::now();
    auto duration = chrono::duration<double>(seconds);
    while (chrono::high_resolution_clock::now() - start < duration) { }
}

/* =========================================================
HANDLE KEYBOARD INPUT
========================================================= */
void checkInput(Timer& timer, Display& display, bool& run){
    if(_kbhit()){
        char ch = _getch();
        switch(ch){
            case 's':
                if(timer.isRunning()){
                    timer.pause();
                    display.setSplash("TIMER PAUSED");
                }
                else{
                    display.setSplash("");
                    timer.resume();        
                }
                break;
            case 'r':
                timer.reset();
                display.setSplash("TIMER RESET, PRESS 'S' TO START");
                break;
            case 'q':
                run = false;
                break;
            case 'i':
                timer.increment();
                display.setSplash("TIMER INCREMENTED");
                break;
            default:
                break;
        }
    }
}

/* =========================================================
MAIN FUNCTION
========================================================= */
int main() {

    bool run = true;

    Timer timer = Timer();
    Display display = Display(timer);

    //Main loop
    while (run) {

        if(timer.remainingMilliseconds() == 0) { display.setSplash("TIMER FINISHED"); }
 
        display.tick();

        checkInput(timer, display, run);

        wait(LOOPTIME);
    }

    display.setSplash("PROGRAM QUIT");
    display.tick();

    return 0;
}
