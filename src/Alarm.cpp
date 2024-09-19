#define _CRT_SECURE_NO_WARNINGS
#include "../include/Alarm.hpp"

/* =========================================================
CONSTRUCTOR
========================================================= */

/**
 * @brief Constructs an Alarm object with a specified end time.
 * 
 * @param time The end time for the alarm in "HH:MM:SS" format.
 */
Alarm::Alarm(std::string time){
    // time is formatted "HH:MM:SS"
    _startTime = currentTime();
    _endTime = stringToTime(time);
    _running = true;
}

/* =========================================================
METHODS
========================================================= */

/**
 * @brief Converts a string representation of time to a time_point.
 * 
 * @param s The time string in "HH:MM:SS" format.
 * @return std::chrono::time_point<std::chrono::system_clock> The corresponding time_point.
 */
std::chrono::time_point<std::chrono::system_clock> Alarm::stringToTime(std::string s) {
    int hours, minutes, seconds;
    sscanf(s.c_str(), "%d:%d:%d", &hours, &minutes, &seconds);
    
    auto now = currentTime();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
    std::tm* localTime = std::localtime(&currentTime);

    localTime->tm_hour = hours;
    localTime->tm_min = minutes;
    localTime->tm_sec = seconds;
    
    auto futureTime = std::chrono::system_clock::from_time_t(std::mktime(localTime));
    return futureTime;
}

/**
 * @brief Converts a time_point to a string representation.
 * 
 * @param t The time_point to convert.
 * @return std::string The string representation of the time in "HH:MM:SS" format.
 */
std::string Alarm::timeToString(std::chrono::time_point<std::chrono::system_clock> t) {
    std::time_t currentTime = std::chrono::system_clock::to_time_t(t);
    std::tm* localTime = std::localtime(&currentTime);

    std::stringstream ss;
    ss << std::setw(2) << std::setfill('0') << localTime->tm_hour << ":"
       << std::setw(2) << std::setfill('0') << localTime->tm_min << ":"
       << std::setw(2) << std::setfill('0') << localTime->tm_sec;

    return ss.str();
}

/**
 * @brief Calculates the percentage of time elapsed from start to end.
 * 
 * @return double The percentage of time elapsed.
 */
double Alarm::percentElapsed() {
    // Total duration between the start and end time in milliseconds
    auto totalMilliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(_endTime - _startTime).count();
    
    // If the total time is zero (which shouldn't happen unless start and end times are equal), return 100% immediately
    if (totalMilliseconds == 0) {
        return 100.0;
    }

    // Calculate the elapsed time since the alarm started
    auto now = currentTime();
    auto elapsedMilliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(now - _startTime).count();

    // Ensure we don't return more than 100% if the current time is after the alarm end time
    if (elapsedMilliseconds >= totalMilliseconds) {
        return 100.0;
    }

    // Calculate the percentage of time elapsed
    double percentage = (static_cast<double>(elapsedMilliseconds) / totalMilliseconds) * 100.0;
    return percentage;
}

/**
 * @brief Calculates the remaining time in milliseconds until the alarm ends.
 * 
 * @return int The remaining milliseconds.
 */
int Alarm::remainingMilliseconds() {
    auto now = currentTime();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(_endTime - now).count();
    return ms;
}

/**
 * @brief Gets the start time of the alarm.
 * 
 * @return std::chrono::time_point<std::chrono::system_clock> The start time.
 */
std::chrono::time_point<std::chrono::system_clock> Alarm::getStartTime(){
    return _startTime;
}

/**
 * @brief Gets the end time of the alarm.
 * 
 * @return std::chrono::time_point<std::chrono::system_clock> The end time.
 */
std::chrono::time_point<std::chrono::system_clock> Alarm::getEndTime(){
    return _endTime;
}

/**
 * @brief Checks if the alarm has completed.
 * 
 * @return bool True if the alarm has completed, false otherwise.
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
 * @return bool True if the alarm is running, false otherwise.
 */
bool Alarm::isRunning() {
    return _running;
}

/**
 * @brief Gets the current time.
 * 
 * @return std::chrono::time_point<std::chrono::system_clock> The current time.
 */
std::chrono::time_point<std::chrono::system_clock> Alarm::currentTime(){
    return std::chrono::system_clock::now();
}
