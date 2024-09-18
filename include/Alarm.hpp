#ifndef ALARM_HPP
#define ALARM_HPP

#include <string>
#include <chrono>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <chrono>
#include <thread>

using namespace std;

class Alarm {
public:
    Alarm(string time);
    
    bool isDone() const;

    string getTimeString() const;

    static chrono::system_clock::time_point getCurrentTime();

    static chrono::system_clock::time_point parseTime(string time);

private:

    chrono::system_clock::time_point _time;

};

#endif