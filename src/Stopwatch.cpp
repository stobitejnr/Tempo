#include "../include/Stopwatch.hpp"

using namespace std;

/* =========================================================
CONSTRUCTORS
========================================================= */

/**
 * @brief Default constructor initializes a Stopwatch with 0 milliseconds and not running.
 */
Stopwatch::Stopwatch() { 
    _running = false;
    _currMilliseconds = 0;
    _splits = {};
}

/**
 * @brief Constructor initializes a Stopwatch with a specified time (in hours, minutes, and seconds).
 * 
 * @param hours The number of hours to set.
 * @param minutes The number of minutes to set.
 * @param seconds The number of seconds to set.
 */
Stopwatch::Stopwatch(int hours, int minutes, int seconds) {
    int milli = 3600000 * hours + 60000 * minutes + 1000 * seconds;
    _running = false;
    _currMilliseconds = milli;
}

/* =========================================================
GET CURRENT ELAPSED TIME IN MILLISECONDS
========================================================= */

/**
 * @brief Returns the current elapsed time in milliseconds.
 * 
 * If the stopwatch is running, this includes the time since it was started; otherwise, it returns
 * the last recorded time.
 * 
 * @return int The current elapsed time in milliseconds.
 */
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

/**
 * @brief Records and prints the current split time in milliseconds.
 * 
 * A split time is a snapshot of the time elapsed, which can be useful for time intervals
 * without stopping the stopwatch.
 */
void Stopwatch::addSplit() {
    int splitMilliseconds = 0;
    if (_running) {
        splitMilliseconds = chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - _startTime).count();
        splitMilliseconds += _currMilliseconds;
        //cout << "Split time: " << _currMilliseconds + splitMilliseconds << " milliseconds" << endl;
    } 
    else {
        splitMilliseconds = _currMilliseconds;

        //cout << "Split time: " << _currMilliseconds << " milliseconds" << endl;
    }
    _splits.push_back(splitMilliseconds);
}

/**
 * @brief Clears the splits vector.
 */
void Stopwatch::clearSplits(){
    _splits = {};
}

/**
 * @brief Returns the splits vector.
 * @return vector<int> the vector containing split times in milliseconds.
 */
vector<int> Stopwatch::getSplits(){
    return _splits;
}

/* =========================================================
START THE STOPWATCH
========================================================= */

/**
 * @brief Starts the stopwatch.
 * 
 * If the stopwatch is already running, this function does nothing.
 */
void Stopwatch::start() {
    if (!_running) {
        _running = true;
        _startTime = chrono::steady_clock::now();
    }
}

/* =========================================================
PAUSE THE STOPWATCH
========================================================= */

/**
 * @brief Pauses the stopwatch.
 * 
 * Stops the time count until resumed. The current time is recorded.
 */
void Stopwatch::pause() {
    if (_running) {
       _pauseTime = chrono::steady_clock::now();
       _currMilliseconds += chrono::duration_cast<chrono::milliseconds>(_pauseTime - _startTime).count();
       _running = false;
    }
}

/* =========================================================
RESUME THE STOPWATCH
========================================================= */

/**
 * @brief Resumes the stopwatch from the last paused time.
 */
void Stopwatch::resume() {
    if (!_running) {
        _startTime = chrono::steady_clock::now();
        _running = true;
    }
}

/* =========================================================
RESET THE STOPWATCH
========================================================= */

/**
 * @brief Resets the stopwatch to 0 milliseconds and stops it.
 */
void Stopwatch::reset() {
    _running = false;
    clearSplits();
    _currMilliseconds = 0;
}

/* =========================================================
CHECK IF STOPWATCH IS RUNNING
========================================================= */

/**
 * @brief Checks if the stopwatch is currently running.
 * 
 * @return bool True if the stopwatch is running, false otherwise.
 */
bool Stopwatch::isRunning() {
    return _running;
}
