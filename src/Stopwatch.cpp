#include "../include/Stopwatch.hpp"

using namespace std;

Stopwatch::Stopwatch(){ 
}

int Stopwatch::currentMilliseconds() const { return 0;}

void Stopwatch::split() {
    int splitMilliseconds = chrono::duration_cast<chrono::milliseconds>(_pauseTime - _startTime).count();
}

void Stopwatch::start() {
    _running = true;
    _startTime = chrono::steady_clock::now();
}

void Stopwatch::pause(){
    if(_running){
       _pauseTime = chrono::steady_clock::now();
       _currMilliseconds = chrono::duration_cast<chrono::milliseconds>(_pauseTime - _startTime).count();
       _running = false;
    }
}

void Stopwatch::resume(){
    if(!_running){
        _startTime = chrono::steady_clock::now() + chrono::milliseconds(_currMilliseconds);
        _running = true;
    }
}

void Stopwatch::reset(){
    pause();
    _currMilliseconds = 0;
}

bool Stopwatch::isRunning(){
    return _running;
}