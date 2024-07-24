#include <iostream>
#include <thread>
#include <chrono>
#include "timer.h"

void waitForUser() {
    std::cout << "Press Enter to stop the timer..." << std::endl;
    std::cin.get();
}

int main() {
    Timer timer;

    std::cout << "Starting timer..." << std::endl;
    timer.start();

    waitForUser();

    timer.stop();
    std::cout << "Elapsed time: " << timer.elapsedMilliseconds() << " milliseconds." << std::endl;

    return 0;
}
