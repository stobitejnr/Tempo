#include "Timer.hpp"

using namespace std;

//Default constructor
Timer::Timer(){
    _countdownSeconds = 0;
    start(_countdownSeconds);
}

//Constructor to specify members
Timer::Timer(int id, int countdownSeconds, string name, string desc){
    _countdownSeconds = countdownSeconds;
    _remainingSeconds = countdownSeconds;
    _id = id;
    _name = name;
    _desc = desc;
    start(_countdownSeconds);
}

Timer::~Timer(){
    
}

void Timer::start(int countdownSeconds) {
    _running = true;
    _endTime = chrono::steady_clock::now() + chrono::seconds(_countdownSeconds);
}

void Timer::pause(){
    if(_running){
       _pauseTime = chrono::steady_clock::now();
       _remainingSeconds = chrono::duration_cast<chrono::seconds>(_endTime - _pauseTime).count();
       _running = false;
    }
}

void Timer::resume(){
    if(!_running){
        _endTime = chrono::steady_clock::now() + chrono::seconds(_remainingSeconds);
        _running = true;
    }
}

int Timer::remainingSeconds() const {
    if(_running){
        auto now = chrono::steady_clock::now();
        auto remaining = chrono::duration_cast<chrono::seconds>(_endTime - now).count();
        return remaining > 0 ? remaining : 0;
    }
    else{
        return _remainingSeconds;
    }
}
