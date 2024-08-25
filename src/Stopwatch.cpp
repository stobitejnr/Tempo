#include "../include/Stopwatch.hpp"

using namespace std;

/* =========================================================
CONSTRUCTORS
========================================================= */

// Default constructor initializes a Stopwatch with 0 milliseconds and not running
Stopwatch::Stopwatch(){ 
    _running = false;
    _currMilliseconds = 0;
}

// Constructor initializes a Stopwatch with a specified time (in hours, minutes, and seconds)
Stopwatch::Stopwatch(int hours, int minutes, int seconds){
    int milli = 3600000 * hours + 60000 * minutes + 1000 * seconds;
    _running = false;
    _currMilliseconds = milli;
}

/* =========================================================
GET CURRENT ELAPSED TIME IN MILLISECONDS
========================================================= */

// Returns the current elapsed time in milliseconds. If the stopwatch is running,
// it includes the time since it was started; otherwise, it returns the last recorded time.
int Stopwatch::currentMilliseconds() { 
    if(_running){
        auto now = chrono::steady_clock::now();
        return _currMilliseconds + chrono::duration_cast<chrono::milliseconds>(now - _startTime).count();
    }
    else{
        return _currMilliseconds;
    }
}

/* =========================================================
SPLIT TIME
========================================================= */

// Records and prints the current split time in milliseconds. A split time is a snapshot
// of the time elapsed, which can be useful for time intervals without stopping the stopwatch.
void Stopwatch::split() {
    if (_running) {
        int splitMilliseconds = chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - _startTime).count();
        cout << "Split time: " << _currMilliseconds + splitMilliseconds << " milliseconds" << endl;
    } else {
        cout << "Split time: " << _currMilliseconds << " milliseconds" << endl;
    }
}

/* =========================================================
START THE STOPWATCH
========================================================= */

// Starts the stopwatch. If already running, this function does nothing.
void Stopwatch::start() {
    if (!_running) {
        _running = true;
        _startTime = chrono::steady_clock::now();
    }
}

/* =========================================================
PAUSE THE STOPWATCH
========================================================= */

// Pauses the stopwatch, stopping the time count until resumed. The current time is recorded.
void Stopwatch::pause(){
    if(_running){
       _pauseTime = chrono::steady_clock::now();
       _currMilliseconds += chrono::duration_cast<chrono::milliseconds>(_pauseTime - _startTime).count();
       _running = false;
    }
}

/* =========================================================
RESUME THE STOPWATCH
========================================================= */

// Resumes the stopwatch from the last paused time.
void Stopwatch::resume(){
    if(!_running){
        _startTime = chrono::steady_clock::now();
        _running = true;
    }
}

/* =========================================================
RESET THE STOPWATCH
========================================================= */

// Resets the stopwatch to 0 milliseconds and stops it.
void Stopwatch::reset(){
    _running = false;
    _currMilliseconds = 0;
}

/* =========================================================
CHECK IF STOPWATCH IS RUNNING
========================================================= */

// Returns whether the stopwatch is currently running.
bool Stopwatch::isRunning(){
    return _running;
}
