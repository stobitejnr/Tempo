#ifndef TIMER_HPP
#define TIMER_HPP

#include <chrono>
#include <iostream>

using namespace std;

class Timer {
public:
    //Constructors
    Timer();
    Timer(int id, int, string name, string desc);

    //Destructor
    ~Timer();

    void start(int countdownSeconds);
    void pause();
    void resume();

    int remainingSeconds() const;

private:
    int _id;
    int _countdownSeconds;
    int _remainingSeconds;
    string _name;
    string _desc;
    bool _running;
    
    chrono::time_point<chrono::steady_clock> _endTime;
    chrono::time_point<chrono::steady_clock> _pauseTime;
};

#endif // TIMER_HPP
