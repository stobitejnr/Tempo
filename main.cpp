#include <iostream>
#include <chrono>
#include <conio.h>
#include <vector>

#include "Timer.hpp"
#include "Display.hpp"

using namespace std;

void wait(int seconds){
    auto start = chrono::steady_clock::now();
    while (chrono::steady_clock::now() - start < chrono::seconds(seconds));
}

Timer createTimer(){
    int h = 0;
    int m = 0;
    int s = 0;
    int countdownSeconds = 0;

    Display::clearScreen();

    cout << "How long would you like to set a timer for?" << endl;

    while(true){
    cout << "Hours: "; cin >> h;
    if(h <= 99 && h>= 0) {break;}
    cout<<"Invalid number of hours."<<endl;}

    while(true){
    cout << "Minutes: "; cin >> m;
    if(m <= 59 && m>= 0) {break;}
    cout<<"Invalid number of minutes."<<endl;}

    while(true){
    cout << "Seconds: "; cin >> s;
    if(s <= 59 && s>= 0) {break;}
    cout<<"Invalid number of seconds."<<endl;}

    countdownSeconds = (3600*h) + (60*m) + (s);

    Timer timer = Timer(1, countdownSeconds, "Name", "Description");

    return timer;
}


// Main function
int main() {
    
    Timer timer = createTimer();
    Display display = Display(timer);

    //Main loop
    while (true) {
        display.tick();
        if (timer.remainingSeconds() == 0) break;
        if(_kbhit()){
            char ch = _getch();
            if(ch == 's'){
                cout << "\nTimer paused!" << endl;
                timer.pause();
            }

            if(ch == 'r'){
                cout << "\nTimer resumed!" << endl;
                timer.resume();
            }
        }
        
        wait(1);
    }

    
    cout << "\nCountdown finished!" << endl;
    return 0;
}
