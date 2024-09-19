#define _CRT_SECURE_NO_WARNINGS
#include "../include/Alarm.hpp"

Alarm::Alarm(std::string time){
    // time is formatted "HH:MM:SS"
    _startTime = currentTime();
    _endTime = stringToTime(time);
    _running = true;
}

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

std::string Alarm::timeToString(std::chrono::time_point<std::chrono::system_clock> t) {

    std::time_t currentTime = std::chrono::system_clock::to_time_t(t);
    std::tm* localTime = std::localtime(&currentTime);

    std::stringstream ss;
    ss << std::setw(2) << std::setfill('0') << localTime->tm_hour << ":"
       << std::setw(2) << std::setfill('0') << localTime->tm_min << ":"
       << std::setw(2) << std::setfill('0') << localTime->tm_sec;

    return ss.str();
}

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

int Alarm::remainingMilliseconds() {
    auto now = currentTime();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(_endTime - now).count();
    return ms;
}

std::chrono::time_point<std::chrono::system_clock> Alarm::getStartTime(){
    return _startTime;
}

std::chrono::time_point<std::chrono::system_clock> Alarm::getEndTime(){
    return _endTime;
}

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

bool Alarm::isRunning() {
    return _running;
}

std::chrono::time_point<std::chrono::system_clock> Alarm::currentTime(){
    return std::chrono::system_clock::now();
}