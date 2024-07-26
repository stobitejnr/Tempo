#include <iostream>
#include <chrono>
#include "Timer.hpp"

using namespace std;

int main() {
    int countdownSeconds;

    cout << "Enter countdown time in seconds: ";
    cin >> countdownSeconds;

    Timer timer = Timer(1, countdownSeconds, "Test", "");

    while (true) {
        int remaining = timer.remainingSeconds();
        if (remaining == 1) cout << "\rTime remaining: " << remaining << " second" << flush;
        else cout << "\rTime remaining: " << remaining << " seconds" << flush;
        if (remaining == 0) break;
        
        // Wait for 1 second
        auto start = chrono::steady_clock::now();
        while (chrono::steady_clock::now() - start < chrono::seconds(1));
    }

    cout << "\nCountdown finished!" << endl;

    return 0;
}
