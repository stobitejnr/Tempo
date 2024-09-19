#include "../include/Alarm.hpp"

using namespace std;

Alarm::Alarm(string time){
    // time is formatted "HH:MM:SS"
    _startTime = currentTime();
    _endTime = stringToTime(time);
    _running = true;
}

chrono::time_point<chrono::system_clock> Alarm::stringToTime(string s) {

    int hours, minutes, seconds;
    sscanf(s.c_str(), "%d:%d:%d", &hours, &minutes, &seconds);
    
    auto now = currentTime();
    time_t currentTime = chrono::system_clock::to_time_t(now);
    tm* localTime = localtime(&currentTime);

    localTime->tm_hour = hours;
    localTime->tm_min = minutes;
    localTime->tm_sec = seconds;
    
    auto futureTime = chrono::system_clock::from_time_t(mktime(localTime));
    return futureTime;

}

string Alarm::timeToString(chrono::time_point<chrono::system_clock> t) {

    time_t currentTime = chrono::system_clock::to_time_t(t);
    tm* localTime = localtime(&currentTime);

    stringstream ss;
    ss << setw(2) << setfill('0') << localTime->tm_hour << ":"
       << setw(2) << setfill('0') << localTime->tm_min << ":"
       << setw(2) << setfill('0') << localTime->tm_sec;

    return ss.str();

}


int Alarm::remainingMilliseconds() {
    auto now = currentTime();
    auto ms = chrono::duration_cast<chrono::milliseconds>(_endTime - now).count();
    return ms;
}

bool Alarm::isDone(){
    int remaining = remainingMilliseconds();
    if (remaining > 0) {
        return false;
    } 
    else {
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



