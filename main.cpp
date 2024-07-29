#include <iostream>
#include <chrono>
#include <conio.h>
#include <vector>
#include <regex>

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

    while(true){
        cout << "How long would you like to set a timer for?" << endl;
        string input = "";
        getline(cin,input);

    
        //Regular expressions :D
        regex hours_regex(R"((\d+)\s*hours?)");
        regex minutes_regex(R"((\d+)\s*minutes?)");
        regex seconds_regex(R"((\d+)\s*seconds?)");

        smatch match;

        //Find hours
        if (regex_search(input, match, hours_regex)) {
        h = stoi(match[1].str());
        }

        // Find minutes
        if (regex_search(input, match, minutes_regex)) {
            m = stoi(match[1].str());
        }

        // Find seconds
        if (regex_search(input, match, seconds_regex)) {
            s = stoi(match[1].str());
        }
        
        countdownSeconds = (3600*h) + (60*m) + (s);
        if (countdownSeconds <= 360000){break;}
        else{
            cout << "Cannot set a timer for more than 100 hours." << endl;
        }
    }

    Timer timer = Timer(1, countdownSeconds, "Name", "Description");

    return timer;
}


// Main function
int main() {

    vector<Timer> timers;
    vector<Display> displays;
    
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

    
    cout << "\nTimer finished!" << endl;
    return 0;
}
