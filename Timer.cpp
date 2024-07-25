#include "Timer.hpp"

using namespace std;

Timer::Timer(){
    _countdownSeconds = 10;
    start(_countdownSeconds);
}

Timer::Timer(int id, int countdownSeconds, string name, string desc){
    _countdownSeconds = countdownSeconds;
    _id = id;
    _name = name;
    _desc = desc;
    start(_countdownSeconds);
}

void Timer::start(int countdownSeconds) {
    _endTime = chrono::steady_clock::now() + chrono::seconds(countdownSeconds);
}

int Timer::remainingSeconds() const {
    auto now = chrono::steady_clock::now();
    auto remaining = chrono::duration_cast<chrono::seconds>(_endTime - now).count();
    return remaining > 0 ? remaining : 0;
}
