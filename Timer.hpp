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
    Timer(int hours, int minutes, int seconds, string name, string desc);

    //Destructor
    ~Timer();

    void start(int countdownSeconds);
    void pause();
    void resume();
    void reset();
    void addSeconds(int seconds);

    void createTimer();

    bool isRunning();
    int remainingMilliseconds() const;

private:
    int _startMilliseconds;
    int _countdownMilliseconds;
    int _remainingMilliseconds;


    string _name;
    string _desc;
    bool _running;
    
    chrono::time_point<chrono::steady_clock> _endTime;
    chrono::time_point<chrono::steady_clock> _pauseTime;
};

#endif // TIMER_HPP
