#define _CRT_SECURE_NO_WARNINGS
#include "../include/Alarm.hpp"

/**
 * @class Alarm
 * @brief A class to manage alarms with time-based triggers.
 *
 * The Alarm class allows setting up an alarm for a future time, checking the progress of time, and determining when the alarm has finished.
 */

/**
 * @brief Constructor for the Alarm object.
 * 
 * Initializes the alarm with the specified hours and minutes. If the current time is past the set time, it schedules the alarm for the next day.
 * 
 * @param h Hour value for the new alarm (0-23).
 * @param m Minute value for the new alarm (0-59).
 */
Alarm::Alarm(int h, int m){
    _startTime = currentTime();
    _endTime = getTime(h, m);
    _remainingMilliseconds = 0;
    if(_startTime >= _endTime){
        _endTime = getTime(h+24, m);
    }
    _running = true;
}

/**
 * @brief Creates the nearest future time point with hours `h` and minutes `m`.
 * 
 * If the specified time has already passed today, this method sets the alarm for the same time on the next day.
 * 
 * @param h Hour value for the new alarm (0-23).
 * @param m Minute value for the new alarm (0-59).
 * 
 * @return Time point representing the future alarm time.
 */
chrono::time_point<chrono::system_clock> Alarm::getTime(int h, int m) {
    
    auto now = currentTime();

    time_t currentTime = chrono::system_clock::to_time_t(now);
    tm* localTime = localtime(&currentTime);

    localTime->tm_hour = h;
    localTime->tm_min = m;
    localTime->tm_sec = 0;
    
    auto futureTime = chrono::system_clock::from_time_t(mktime(localTime));
    return futureTime;
}

/**
 * @brief Converts a given time point to a string format (HH:MM).
 * 
 * @param t Time point to convert to string.
 * @return A string representing the time in HH:MM format.
 */
string Alarm::timeToString(chrono::time_point<chrono::system_clock> t) {

    time_t currentTime = chrono::system_clock::to_time_t(t);
    tm* localTime = localtime(&currentTime);

    stringstream ss;
    ss << setw(2) << setfill('0') << localTime->tm_hour << ":"
       << setw(2) << setfill('0') << localTime->tm_min;

    return ss.str();
}

/**
 * @brief Calculates the percentage of time that has elapsed from start to end.
 * 
 * This method calculates the percentage of time passed relative to the alarm's start and end times.
 * 
 * @return The percentage of time elapsed as a double.
 */
double Alarm::percentElapsed() {

    auto totalMilliseconds = chrono::duration_cast<chrono::milliseconds>(_endTime - _startTime).count();
    
    if (totalMilliseconds == 0) {
        return 100.0;
    }

    auto now = currentTime();
    auto elapsedMilliseconds = chrono::duration_cast<chrono::milliseconds>(now - _startTime).count();

    if (elapsedMilliseconds >= totalMilliseconds) {
        return 100.0;
    }

    double percentage = (static_cast<double>(elapsedMilliseconds) / totalMilliseconds) * 100.0;
    return percentage;
}

/**
 * @brief Calculates the remaining time in milliseconds until the alarm ends.
 * 
 * @return Remaining milliseconds until the alarm ends.
 */
int Alarm::remainingMilliseconds() {

    auto now = currentTime();
    auto ms = chrono::duration_cast<chrono::milliseconds>(_endTime - now).count();
    return ms;
}

/**
 * @brief Returns the alarm's start time.
 * 
 * @return Time point representing the start time of the alarm.
 */
chrono::time_point<chrono::system_clock> Alarm::getStartTime(){
    return _startTime;
}

/**
 * @brief Returns the alarm's end time.
 * 
 * @return Time point representing the end time of the alarm.
 */
chrono::time_point<chrono::system_clock> Alarm::getEndTime(){
    return _endTime;
}

/**
 * @brief Checks if the alarm has finished.
 * 
 * If the remaining milliseconds are less than or equal to 0, the alarm is considered done.
 * 
 * @return True if the alarm has completed, false otherwise.
 */
bool Alarm::isDone(){
    int remaining = remainingMilliseconds();
    if (remaining > 0) {
        return false;
    } else {
        _running = false;
        _remainingMilliseconds = 0;
        return true;
    }
}

/**
 * @brief Checks if the alarm is currently running.
 * 
 * @return True if the alarm is running, false otherwise.
 */
bool Alarm::isRunning() {
    return _running;
}

/**
 * @brief Returns the current system time.
 * 
 * @return A time point representing the current time.
 */
chrono::time_point<chrono::system_clock> Alarm::currentTime(){
    return chrono::system_clock::now();
}
