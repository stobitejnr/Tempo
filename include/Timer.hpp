#ifndef TIMER_HPP
#define TIMER_HPP

#include <chrono>
#include <iostream>
#include <regex>

using namespace std;

class Timer {
public:
    //Constructors
    Timer();
    Timer(int hours, int minutes, int seconds);

    void start(int countdownMilliseconds);
    void pause();
    void resume();
    void reset();

    void addTime(int seconds);
    void addTime();
    void changeIncrementTime();

    bool isRunning();
    int remainingMilliseconds();
    double percentElapsed();

private:
    int _startMilliseconds;
    int _countdownMilliseconds;
    int _remainingMilliseconds;
    int _incrementMilliseconds;
    bool _running;
    
    chrono::time_point<chrono::steady_clock> _endTime;
    chrono::time_point<chrono::steady_clock> _pauseTime;
};

#endif // TIMER_HPP
