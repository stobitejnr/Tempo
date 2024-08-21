#include "../include/Stopwatch.hpp"

using namespace std;

Stopwatch::Stopwatch(){ 
    _running = false;
    _currMilliseconds = 0;
}

Stopwatch::Stopwatch(int hours, int minutes, int seconds){
    int milli = 3600000 * hours + 60000 * minutes + 1000 * seconds;
    _running = false;
    _currMilliseconds = milli;
}

int Stopwatch::currentMilliseconds() { 
    if(_running){
        auto now = chrono::steady_clock::now();
        return _currMilliseconds + chrono::duration_cast<chrono::milliseconds>(now - _startTime).count();
    }
    else{
        return _currMilliseconds;
    }
}

void Stopwatch::split() {
    if (_running) {
        int splitMilliseconds = chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - _startTime).count();
        cout << "Split time: " << _currMilliseconds + splitMilliseconds << " milliseconds" << endl;
    } else {
        cout << "Split time: " << _currMilliseconds << " milliseconds" << endl;
    }
}

void Stopwatch::start() {
    if (!_running) {
        _running = true;
        _startTime = chrono::steady_clock::now();
    }
}

void Stopwatch::pause(){
    if(_running){
       _pauseTime = chrono::steady_clock::now();
       _currMilliseconds += chrono::duration_cast<chrono::milliseconds>(_pauseTime - _startTime).count();
       _running = false;
    }
}

void Stopwatch::resume(){
    if(!_running){
        _startTime = chrono::steady_clock::now();
        _running = true;
    }
}

void Stopwatch::reset(){
    _running = false;
    _currMilliseconds = 0;
}

bool Stopwatch::isRunning(){
    return _running;
}