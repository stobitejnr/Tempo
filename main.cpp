#include <iostream>
#include <chrono>
#include <conio.h>
#include <vector>


#include "Timer.hpp"
#include "Display.hpp"

using namespace std;

void wait(double seconds) {
    auto start = chrono::high_resolution_clock::now();
    auto duration = chrono::duration<double>(seconds);
    while (chrono::high_resolution_clock::now() - start < duration) { }
}

void checkInput(Timer& timer, Display& display, bool& run){
    //Handle keypresses
    if(_kbhit()){
        char ch = _getch();
        if(ch == 's'){
            if(timer.isRunning()){
                timer.pause();
                display.setSplash("TIMER PAUSED");
                return;
            }
            else{
                display.setSplash("");
                timer.resume();
                return;
                
            }
            
        }
        if(ch == 'r'){
            timer.reset();
            display.setSplash("TIMER RESET, PRESS 'S' TO START");
            return;
        }
        if(ch == 'q'){
            run = false;
        }
    }
}

// Main function
int main() {

    bool run = true;

    Timer timer = Timer();
    Display display = Display(timer);

    //Main loop
    while (run) {

        if(timer.remainingMilliseconds() == 0) { display.setSplash("TIMER FINISHED"); }

        display.tick();

        checkInput(timer, display, run);

        wait(0.05);
    }

    display.setSplash("PROGRAM QUIT");
    display.tick();
    return 0;
}
