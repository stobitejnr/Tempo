#include "Timer.h"

using namespace std;

Timer::Timer() {}

void Timer::start(int countdownSeconds) {
    endTime = chrono::steady_clock::now() + chrono::seconds(countdownSeconds);
}

int Timer::remainingSeconds() const {
    auto now = chrono::steady_clock::now();
    auto remaining = chrono::duration_cast<chrono::seconds>(endTime - now).count();
    return remaining > 0 ? remaining : 0;
}
