#include <cassert>
#include <iostream>
#include <chrono>
#include <thread>

#include "../include/Timer.hpp"

using namespace std;

void test_constructor() {
    Timer timer(0, 0, 1); // 1 second
    this_thread::sleep_for(chrono::milliseconds(10));
    int timeRemaining = timer.remainingMilliseconds();
    assert(timeRemaining < 1000);
    assert(timer.isRunning());
    //cout << "test_constructor passed!\n";
}

/*
*   Sets a timer for 1 second then checks if the pause and resume work 
*/
void test_pause_resume() {
    Timer timer(0, 0, 1);
    this_thread::sleep_for(chrono::milliseconds(10));
    timer.pause();
    int timeRemaining = timer.remainingMilliseconds();
    assert(!timer.isRunning());
    assert(timer.remainingMilliseconds() == timeRemaining);
    timer.resume();
    assert(timer.isRunning());
    this_thread::sleep_for(chrono::milliseconds(10));
    assert(timer.remainingMilliseconds() < 1000);
    //std::cout << "test_pause_resume passed!\n";
}

/*
*   Tests that the reset reverts back to original time and is stopped
*/
void test_reset() {
    Timer timer(0, 1, 0);
    this_thread::sleep_for(chrono::milliseconds(10));
    timer.reset();
    assert(timer.remainingMilliseconds() == 60000);
    assert(!timer.isRunning());
    //std::cout << "test_reset passed!\n";
}

/*
*   Tests adding time increases remaining time
*/
void test_add_time() {
    Timer timer(0, 0, 1);
    timer.addTime(1);
    int timeRemaining = timer.remainingMilliseconds();
    assert(timeRemaining > 1000 && timeRemaining <= 2000);
    //std::cout << "test_add_time passed!\n";
}

/*
*   Test percent elapsed for the progress bar
*/
void test_percent_elapsed() {
    Timer timer(0, 0, 1);
    this_thread::sleep_for(chrono::milliseconds(100));
    double percent = timer.percentElapsed();
    assert(percent <= 90); // allows for a bit or margin of error
    //std::cout << "test_percent_elapsed passed!\n";
}

/*
*   Testing the timer stops when it finishes 
*/
void test_expiration() {
    Timer timer(0, 0, 0); // 1 second
    assert(timer.remainingMilliseconds() == 0);
    assert(!timer.isRunning());
    //cout << "test_expiration passed!\n";
}

int main() {
    try {
        test_constructor();
        test_pause_resume();
        test_reset();
        test_add_time();
        test_percent_elapsed();
        test_expiration();

        cout << "All tests passed successfully!\n";
    } catch (const exception& e) {
        cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
