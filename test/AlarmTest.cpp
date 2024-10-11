#include <cassert>
#include <iostream>
#include <chrono>
#include <thread>

#include "../include/Alarm.hpp"

using namespace std;

void test_alarm(){

    Alarm alarm(0,0);
    string start = alarm.timeToString(alarm.getEndTime());
    double percent = alarm.percentElapsed();
    int remaining = alarm.remainingMilliseconds();
    bool runing = alarm.isRunning();
    bool done = alarm.isDone();
    chrono::time_point<chrono::system_clock> t = alarm.getStartTime();
}


int main() {
    try {
        test_alarm();
        cout << "All tests passed successfully!\n";
    } catch (const exception& e) {
        cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}