#include <iostream>
#include <chrono>
#include "Timer.hpp"
#include <conio.h>

using namespace std;

void wait(int seconds){
    auto start = chrono::steady_clock::now();
    while (chrono::steady_clock::now() - start < chrono::seconds(seconds));
}

int main() {
    int countdownSeconds;

    cout << "Enter countdown time in seconds: ";
    cin >> countdownSeconds;

    Timer timer = Timer(1, countdownSeconds, "Test", "");

    while (true) {
        int remaining = timer.remainingSeconds();
        cout << "\rTime remaining: " << remaining << " seconds" << flush;
        if (remaining == 0) break;

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
        
        // Wait for 1 second
        auto start = chrono::steady_clock::now();
        while (chrono::steady_clock::now() - start < chrono::seconds(1));
    }

    
    cout << "\nCountdown finished!" << endl;
    return 0;
}
