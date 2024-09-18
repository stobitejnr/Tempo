#include "../include/Alarm.hpp"

using namespace std;

Alarm::Alarm(string time) {
    _time = parseTime(time);
}

chrono::system_clock::time_point Alarm::parseTime(string time){
    
}