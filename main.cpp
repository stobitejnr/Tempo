#include <iostream>
#include <chrono>
#include "Timer.h"

using namespace std;

int main() {
    Timer timer;
    int countdownSeconds;

    std::cout << "Enter countdown time in seconds: ";
    std::cin >> countdownSeconds;

    timer.start(countdownSeconds);

    while (true) {
        int remaining = timer.remainingSeconds();
        std::cout << "\rTime remaining: " << remaining << " seconds" << std::flush;
        if (remaining == 0) break;
        
        // Busy-wait for 1 second
        auto start = std::chrono::steady_clock::now();
        while (std::chrono::steady_clock::now() - start < std::chrono::seconds(1));
    }

    std::cout << "\nCountdown finished!" << std::endl;

    return 0;
}
