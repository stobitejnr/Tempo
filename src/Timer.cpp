#include "../include/Timer.hpp"
#include "../include/Display.hpp"

using namespace std;

/* =========================================================
CONSTRUCTOR
========================================================= */

/**
 * @brief Constructor to specify the timer duration directly in hours, minutes, and seconds.
 * 
 * Initializes and starts the timer with the specified duration.
 * 
 * @param hours The number of hours to set.
 * @param minutes The number of minutes to set.
 * @param seconds The number of seconds to set.
 */
Timer::Timer(int hours, int minutes, int seconds) {
    int milli = 3600000 * hours + 60000 * minutes + 1000 * seconds;
    if (milli >= 360000000) { milli = 359999999; }
    _countdownMilliseconds = milli;
    _remainingMilliseconds = milli;
    _startMilliseconds = milli;
    _incrementMilliseconds = 0;
    start(_countdownMilliseconds);
}

/* =========================================================
START THE TIMER
========================================================= */

/**
 * @brief Starts the timer by setting the end time based on the current time plus the countdown duration.
 * 
 * @param countdownMilliseconds The duration for the countdown in milliseconds.
 */
void Timer::start(int countdownMilliseconds) {
    _running = true;
    _endTime = chrono::steady_clock::now() + chrono::milliseconds(_countdownMilliseconds);
}

/* =========================================================
PAUSE THE TIMER
========================================================= */

/**
 * @brief Pauses the timer and calculates the remaining milliseconds.
 */
void Timer::pause() {
    if (_running) {
       _pauseTime = chrono::steady_clock::now();
       _remainingMilliseconds = chrono::duration_cast<chrono::milliseconds>(_endTime - _pauseTime).count();
       _running = false;
    }
}

/* =========================================================
RESUME THE TIMER
========================================================= */

/**
 * @brief Resumes the timer from where it was paused by recalculating the end time.
 */
void Timer::resume() {
    if (!_running) {
        _endTime = chrono::steady_clock::now() + chrono::milliseconds(_remainingMilliseconds);
        _running = true;
    }
}
/* =========================================================
RESET THE TIMER
========================================================= */

/**
 * @brief Resets the timer to its original duration and pauses it.
 */
void Timer::reset() {
    pause();
    _remainingMilliseconds = _startMilliseconds;
    _countdownMilliseconds = _startMilliseconds;
}

/* =========================================================
ADD TIME TO THE TIMER
========================================================= */

/**
 * @brief Adds a specified amount of time (in seconds) to the timer.
 * 
 * If the timer is running, it resumes after adding time.
 * 
 * @param seconds The number of seconds to add to the timer.
 */
void Timer::addTime(int seconds) {
    bool wasRunning = _running;
    pause();
    
    _remainingMilliseconds += 1000 * seconds;
    _countdownMilliseconds += 1000 * seconds;

    if(wasRunning){
        resume();
    }
}

/* =========================================================
GET REMAINING TIME IN MILLISECONDS
========================================================= */

/**
 * @brief Returns the remaining time in milliseconds.
 * 
 * If the timer has expired, it returns 0.
 * 
 * @return int The remaining time in milliseconds.
 */
int Timer::remainingMilliseconds() {
    if (_running) {
        auto now = chrono::steady_clock::now();
        auto remaining = chrono::duration_cast<chrono::milliseconds>(_endTime - now).count();
        if (remaining > 0) { 
            return remaining; 
        } else { 
            _running = false; 
            _remainingMilliseconds = 0; 
            return 0; 
        }
    } else {
        return _remainingMilliseconds;
    }
}

/* =========================================================
CHECK IF TIMER IS RUNNING
========================================================= */

/**
 * @brief Checks if the timer is currently running.
 * 
 * @return bool True if the timer is running, false otherwise.
 */
bool Timer::isRunning() {
    return _running;
}

/* =========================================================
GET PERCENTAGE OF TIME ELAPSED
========================================================= */

/**
 * @brief Returns the percentage of time that has elapsed since the timer started.
 * 
 * @return double The percentage of time elapsed.
 */
double Timer::percentElapsed() {
    int start = 0;
    if (_remainingMilliseconds > _startMilliseconds) {
        start = _remainingMilliseconds;
    } else {
        start = _startMilliseconds;
    }
    if (start == 0) { 
        return 100.0; 
    }

    int elapsedMilliseconds = start - remainingMilliseconds();
    double percentage = ((double)(elapsedMilliseconds) / start) * 100;
    return percentage;
}
