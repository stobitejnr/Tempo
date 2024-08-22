#include "../include/Timer.hpp"
#include "../include/Display.hpp"

using namespace std;

//Default constructor to take user input
Timer::Timer(){
    int h = 0;
    int m = 0;
    int s = 0;
    int countdownSeconds = 0;

    while(true){
        
        cout << "How long would you like to set a timer for?" << endl;
        string input = "";
        getline(cin,input);

    
        //Regular expressions :D
        regex hours_regex(R"((\d+)\s*hour?)");
        regex minutes_regex(R"((\d+)\s*minute?)");
        regex seconds_regex(R"((\d+)\s*second?)");

        smatch match;

        //Find hours
        if (regex_search(input, match, hours_regex)) {
            h = stoi(match[1].str());
        }

        // Find minutes
        if (regex_search(input, match, minutes_regex)) {
            m = stoi(match[1].str());
        }

        // Find seconds
        if (regex_search(input, match, seconds_regex)) {
            s = stoi(match[1].str());
        }
        
        countdownSeconds = (3600*h) + (60*m) + (s);
        if(countdownSeconds == 0){ continue; }
        if (countdownSeconds <= 360000){break;}
        else{
            cout << "Cannot set a timer for more than 100 hours." << endl;
        }
    }

    _startMilliseconds = countdownSeconds * 1000;
    _remainingMilliseconds = _startMilliseconds;
    _countdownMilliseconds = _startMilliseconds;
    start(_countdownMilliseconds);
}

//Constructor to specify members directly
Timer::Timer(int hours, int minutes, int seconds){
    int milli = 3600000 * hours + 60000 * minutes + 1000 * seconds;
    _countdownMilliseconds = milli;
    _remainingMilliseconds = milli;
    _startMilliseconds = milli;
    start(_countdownMilliseconds);
}


void Timer::start(int countdownMilliseconds) {
    _running = true;
    _endTime = chrono::steady_clock::now() + chrono::milliseconds(_countdownMilliseconds);
}

void Timer::pause(){
    if(_running){
       _pauseTime = chrono::steady_clock::now();
       _remainingMilliseconds = chrono::duration_cast<chrono::milliseconds>(_endTime - _pauseTime).count();
       _running = false;
    }
}

void Timer::resume(){
    if(!_running){
        _endTime = chrono::steady_clock::now() + chrono::milliseconds(_remainingMilliseconds);
        _running = true;
    }
}

void Timer::reset(){
    pause();
    _remainingMilliseconds = _startMilliseconds;
    _countdownMilliseconds = _startMilliseconds;
}

void Timer::addSeconds(int seconds){
    bool wasRunning = _running;
    pause();
    
    _remainingMilliseconds += 1000 * seconds;
    _countdownMilliseconds += 1000 * seconds;

    if(wasRunning){
        resume();
    }
}

int Timer::remainingMilliseconds() {
    if(_running){
        auto now = chrono::steady_clock::now();
        auto remaining = chrono::duration_cast<chrono::milliseconds>(_endTime - now).count();
        if(remaining > 0){ return remaining; } 
        else{ 
            _running = false; 
            _remainingMilliseconds = 0; 
            return 0; 
        }
    }   
    else{
        return _remainingMilliseconds;
    }
}

bool Timer::isRunning(){
    return _running;
}

double Timer::percentElapsed() {
    int start = 0;
    if(_remainingMilliseconds > _startMilliseconds){
        start = _remainingMilliseconds;
    }
    else{
        start = _startMilliseconds;
    }
    if (start == 0) { return 100.0; }

    int elapsedMilliseconds = start - remainingMilliseconds();
    double percentage = ((double)(elapsedMilliseconds) / start) * 100;
    return percentage;
}
