#include <cassert>
#include <iostream>
#include <chrono>
#include <thread>

#include "../include/Timer.hpp"

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

/*
*   Tests that the reset reverts back to original time and is stopped
*/
void test_reset(){
    Timer timer(0,1,0);
    this_thread::sleep_for(chrono::seconds(1));
    timer.reset();
    assert(timer.remainingMilliseconds() == 60000);
    assert(!timer.isRunning());
}

/*
*   Tests adding time increases remaining time
*/
void test_add_time(){
    Timer timer(0,1,0);
    timer.addTime(30);
    assert(timer.remainingMilliseconds() == 90000);
}

/*
*   Test percent elapsed for the progress bar
*/
void test_percent_elapsed(){
    Timer timer(0,1,0);
    this_thread::sleep_for(chrono::seconds(30));
    double percent = timer.percentElapsed();
    assert(percent > 49.0 && percent < 51.0); // allows for a bit or margin of error
}

/*
*   Testing the timer stops when it finishes 
*/
void test_expiration() {
    Timer timer(0, 0, 2); // 2 seconds
    this_thread::sleep_for(chrono::seconds(3));
    assert(timer.remainingMilliseconds() == 0);
    assert(!timer.isRunning());
}

int main() {
    try {
        test_constructor();
        test_pause_resume();
        test_reset();
        test_add_time();
        test_percent_elapsed();
        test_expiration();
        std::cout << "All tests passed successfully!\n";
    } catch (const exception& e) {
        std::cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}