#ifndef STOPWATCH_HPP
#define STOPWATCH_HPP

#include <chrono>
#include <iostream>

using namespace std;

class Stopwatch {
public:
    Stopwatch();

    void start();

    void split();
    void pause();
    void resume();
    void reset();

    bool isRunning();
    int currentMilliseconds();

private:

    int _currMilliseconds;

    bool _running;
    
    chrono::time_point<chrono::steady_clock> _startTime;
    chrono::time_point<chrono::steady_clock> _pauseTime;

};

#endif // STOPWATCH_HPP