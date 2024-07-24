#ifndef TIMER_H // include guard to prevent multiple inclusions of this 
#define TIMER_H

#include<chrono>
#include<iostream>

using namespace std;

class Timer{

    private:

    int id;
    bool running;

    chrono::time_point<steady_clock> startTime;
    chrono::time_point<steady_clock> endTime;

    public:

    //Constructor
    Timer(int,int,int,int);

    void start();

    void stop();

    double elapsedMilliseconds() const;

    double remainingMilliseconds(double countdownTime) const;
    

    
    
};

#endif