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

    void start(int countdownSeconds);
    int remainingSeconds() const;

private:
    int _id;
    int _countdownSeconds;
    string _name;
    string _desc;
    
    chrono::time_point<chrono::steady_clock> _endTime;
};

#endif // TIMER_HPP
