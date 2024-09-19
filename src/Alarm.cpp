#define _CRT_SECURE_NO_WARNINGS
#include "../include/Alarm.hpp"

/**
 * @brief Constructor for alarm object.
 * 
 * @param h Hour value for new alarm.
 * @param m Minute value for new alarm.
 */
Alarm::Alarm(int h, int m){
    _startTime = currentTime();
    _endTime = getTime(h, m);
    if(_startTime >= _endTime){
        _endTime = getTime(h+24, m);
    }
    _running = true;

}

/**
 * @brief Creates nearest future time point with hours h and minutes m
 * 
 * @param h Hour value for new alarm.
 * @param m Minute value for new alarm.
 * 
 * @return Time point for alarm.
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

string Alarm::timeToString(chrono::time_point<chrono::system_clock> t) {

    time_t currentTime = chrono::system_clock::to_time_t(t);
    tm* localTime = localtime(&currentTime);

    stringstream ss;
    ss << setw(2) << setfill('0') << localTime->tm_hour << ":"
       << setw(2) << setfill('0') << localTime->tm_min;

    return ss.str();
}

/**
 * @brief Calculates the percentage of time elapsed from start to end.
 * 
 * @return double The percentage of time elapsed.
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
 * @return int The remaining milliseconds.
 */
int Alarm::remainingMilliseconds() {

    auto now = currentTime();
    auto ms = chrono::duration_cast<chrono::milliseconds>(_endTime - now).count();
    return ms;

}

chrono::time_point<chrono::system_clock> Alarm::getStartTime(){

    return _startTime;

}

chrono::time_point<chrono::system_clock> Alarm::getEndTime(){

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

chrono::time_point<chrono::system_clock> Alarm::currentTime(){

    return chrono::system_clock::now();

}
