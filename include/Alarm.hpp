#ifndef ALARM_HPP
#define ALARM_HPP

#include <thread>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <sstream>

using namespace std;

class Alarm {
public:

    Alarm(string time);

    chrono::time_point<chrono::system_clock> stringToTime(string s);
    string timeToString(chrono::time_point<chrono::system_clock> t);

    chrono::time_point<chrono::system_clock> getStartTime();
    chrono::time_point<chrono::system_clock> getEndTime();

    static chrono::time_point<chrono::system_clock> currentTime();

    void start();           
    bool isRunning();    
    bool isDone();   

    int remainingMilliseconds();


    double percentElapsed();

private:

    int _remainingMilliseconds;

    bool _running;

    chrono::time_point<chrono::system_clock> _startTime;
    chrono::time_point<chrono::system_clock> _endTime;  

};

#endif