#ifndef TIMER_H
#define TIMER_H

#include <chrono>

using namespace std;

class Timer {
public:
    Timer();
    void start(int countdownSeconds);
    int remainingSeconds() const;

private:
    chrono::time_point<chrono::steady_clock> endTime;
};

#endif // TIMER_H
