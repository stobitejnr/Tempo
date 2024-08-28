#include <cassert>

#include <iostream>
#include <chrono>
#include <thread>
#include "include/Timer.hpp"

using namespace std;

void test_constructor(){
    Timer timer(0,30,0); // 30 minute
    assert(timer.remainingMilliseconds() == 1800000);
    assert(timer.isRunning());
}

/*
*   Sets a timer for 1 minute then checks if the pause and resume work 
*/
void test_pause_resume(){
    Timer timer(0,1,0); // One minute'
    this_thread::sleep_for(chrono::seconds(1));
    timer.pause();
    int timeRemaining = timer.remainingMilliseconds();
    assert(!timer.isRunning());
    this_thread::sleep_for(chrono::seconds(1));
    assert(timer.remainingMilliseconds() == timeRemaining);
    timer.resume();
    assert(timer.isRunning());
    assert(timer.remainingMilliseconds() < 59000);
}







int main(){
    try {
        test_constructor();
        test_pause_resume();
        cout <<"all tests passed";
        } catch (const std::exception& e) {
        std::cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}

