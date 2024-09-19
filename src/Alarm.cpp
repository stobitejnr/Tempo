#include "../include/Alarm.hpp"

Alarm::Alarm(int h, int m){
    // time is formatted "HH:MM"
    _startTime = currentTime();
    _endTime = getTime(h, m);
    if(_startTime >= _endTime){
        _endTime = getTime(h+24, m);
    }
    _running = true;
}

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

double Alarm::percentElapsed() {
    // Total duration between the start and end time in milliseconds
    auto totalMilliseconds = chrono::duration_cast<chrono::milliseconds>(_endTime - _startTime).count();
    
    // If the total time is zero (which shouldn't happen unless start and end times are equal), return 100% immediately
    if (totalMilliseconds == 0) {
        return 100.0;
    }

    // Calculate the elapsed time since the alarm started
    auto now = currentTime();
    auto elapsedMilliseconds = chrono::duration_cast<chrono::milliseconds>(now - _startTime).count();

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
    auto ms = chrono::duration_cast<chrono::milliseconds>(_endTime - now).count();
    return ms;
}

chrono::time_point<chrono::system_clock> Alarm::getStartTime(){
    return _startTime;
}

chrono::time_point<chrono::system_clock> Alarm::getEndTime(){
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

chrono::time_point<chrono::system_clock> Alarm::currentTime(){
    return chrono::system_clock::now();
}