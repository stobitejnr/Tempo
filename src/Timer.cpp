#include "../include/Timer.hpp"
#include "../include/Display.hpp"

using namespace std;

/* =========================================================
CONSTRUCTORS
========================================================= */

/**
 * @brief Default constructor prompts the user to set a timer with a specific duration.
 * 
 * The user can specify the duration in hours, minutes, and seconds. The timer is initialized
 * and started based on the user input.
 */
Timer::Timer() {
    int h = 0;
    int m = 0;
    int s = 0;
    int countdownSeconds = 0;
    int _incrementMilliseconds = 1000;

    while (true) {
        cout << "How long would you like to set a timer for?" << endl;
        string input = "";
        getline(cin, input);

        // Regular expressions to match hours, minutes, and seconds
        regex hours_regex(R"((\d+)\s*hour?)");
        regex minutes_regex(R"((\d+)\s*minute?)");
        regex seconds_regex(R"((\d+)\s*second?)");

        smatch match;

        // Extract hours
        if (regex_search(input, match, hours_regex)) {
            h = stoi(match[1].str());
        }

        // Extract minutes
        if (regex_search(input, match, minutes_regex)) {
            m = stoi(match[1].str());
        }

        // Extract seconds
        if (regex_search(input, match, seconds_regex)) {
            s = stoi(match[1].str());
        }

        countdownSeconds = (3600 * h) + (60 * m) + (s);
        if (countdownSeconds == 0) { 
            continue; 
        }
        if (countdownSeconds <= 360000) { 
            break; 
        } else {
            cout << "Cannot set a timer for more than 100 hours." << endl;
        }
    }

    _startMilliseconds = countdownSeconds * 1000;
    _remainingMilliseconds = _startMilliseconds;
    _countdownMilliseconds = _startMilliseconds;
    start(_countdownMilliseconds);
}

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
    _countdownMilliseconds = milli;
    _remainingMilliseconds = milli;
    _startMilliseconds = milli;
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
    
    _remainingMilliseconds += _incrementMilliseconds * seconds;
    _countdownMilliseconds += _incrementMilliseconds * seconds;

    if (wasRunning) {
        resume();
    }
}

/* =========================================================
CHANGE INCREMENT TIME
========================================================= */

/**
 * @brief Allows the user to change the increment time used for adding time to the timer.
 * 
 * The increment time can be specified in hours, minutes, or seconds.
 */
void Timer::changeIncrementTime() {
    // Pause the timer to safely change the increment time
    bool wasRunning = _running;
    pause();

    cout << "Enter the increment time (e.g., '5 seconds', '2 minutes', '1 hour'): ";
    string input;
    getline(cin, input);
    
    // Regular expressions to match hours, minutes, and seconds
    regex hours_regex(R"((\d+)\s*hour?)");
    regex minutes_regex(R"((\d+)\s*minute?)");
    regex seconds_regex(R"((\d+)\s*second?)");

    smatch match;
    int newIncrementMilliseconds = 0;
    string unit;

    try {
        // Convert input to milliseconds based on what unit is specified
        if (regex_search(input, match, hours_regex)) {
            newIncrementMilliseconds = stoi(match[1].str()) * 360000;
            unit = "hour(s)";
        } else if (regex_search(input, match, minutes_regex)) {
            newIncrementMilliseconds = stoi(match[1].str()) * 6000;
            unit = "minute(s)";
        } else if (regex_search(input, match, seconds_regex)) {
            newIncrementMilliseconds = stoi(match[1].str()) * 100;
            unit = "second(s)";
        } else {
            cout << "Invalid input format. Increment time must be specified in hours, minutes, or seconds." << endl;
            return;
        }

        if (newIncrementMilliseconds <= 0) {
            cout << "Increment time must be a positive value. Keeping the previous value of " << _incrementMilliseconds << " milliseconds." << endl;
        } else {
            _incrementMilliseconds = newIncrementMilliseconds;
            cout << "Increment time set to " << match[1].str() << " " << unit << "." << endl;
        }
    } catch (invalid_argument& e) {
        cout << "Invalid input. Please enter a valid numeric value. Keeping the previous value of " << _incrementMilliseconds << " milliseconds." << endl;
    } catch (out_of_range& e) {
        cout << "The value is too large. Keeping the previous value of " << _incrementMilliseconds << " milliseconds." << endl;
    }

    std::this_thread::sleep_for(std::chrono::seconds(1)); 
    cout << "\r\033[K"; // Clear the line after waiting for input

    if (wasRunning) {
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
