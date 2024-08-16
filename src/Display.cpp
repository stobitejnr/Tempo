#include <windows.h>

#include "../include/Display.hpp"


using namespace std;

Display::Display() {
    _splash = "";
    _buffer = "";
}


#define ASCII_HEIGHT 8

/* =========================================================
TERMINAL CLEARING FOR SEAMLESS FRAMES
========================================================= */

void Display::clearScreen() {
    string clearscreen = "\033[2J\033[H";
    fast_print(clearscreen);
}

void Display::resetCursor() {
    string resetcursor = "\033[H";
    fast_print(resetcursor);
}

void Display::setSplash(string str){
    _splash = str;
}

void Display::stageSplash(){
    if(_splash != ""){
        _buffer+=("\n");
        _buffer+=((" << " + _splash + " >> \n"));
    }
}

/* =========================================================
STAGE TIMER IN ASCII
========================================================= */


void Display::stageTimerDisplay(int hours, int minutes, int seconds, int tenths){


    string padding = "  ";
    string to_print = "";

    //Only show hours if over 1 left
    if(hours != 0){
        to_print += to_string(hours) + ":";
    }

    //Check if minutes need leading 0
    if(int(minutes/10)!=0){
        to_print += to_string(minutes) + ":";
    }
    else{
        to_print += "0" + to_string(minutes) + ":";
    }

    //Check if seconds need leading zero
    if(int(seconds/10)!=0){
        to_print += to_string(seconds);
    }
    else{
        to_print += "0" + to_string(seconds);
    }

 /* =========================================================
JUST FOR TESTING TENTHS
========================================================= */
    //to_print += "." + to_string(tenths);
    

    for(int i = 0; i < ASCII_HEIGHT; i++){
        string line;
        for(char ch : to_print){
            if(ch == ':'){
                line += font1.at(10)[i];
                line += padding;
            }
            else if(ch == '.'){
                line += font1.at(11)[i];
                line += padding;
            }
            else{
                line += font1.at(ch-'0')[i];
                line += padding;
            }
        }
        _buffer+=((line+"\n"));
    }
}


void Display::stageTimerActions(){
    _buffer+=("\n");
    _buffer+=("===========================================\n");
    _buffer+=("Control your timer with the following keys: \n");
    _buffer+=("===========================================\n");
    _buffer+=("\n");
    _buffer+=("S : Start/Pause your timer.\n");
    _buffer+=("R : Reset your timer.\n");
    _buffer+=("I : Add 10 seconds to your timer.\n");
    _buffer+=("Q : End your timer immediately and return to menu.\n");
    _buffer+=("\n");

}

/* =========================================================
STAGE STOPWATCH IN ASCII
========================================================= */

void Display::stageStopwatchDisplay(int hours, int minutes, int seconds, int hundredths){


    string padding = "  ";
    string to_print = "";

    //Only show hours if over 1 left
    if(hours != 0){
        to_print += to_string(hours) + ":";
    }

    //Check if minutes need leading 0
    if(int(minutes/10)!=0){
        to_print += to_string(minutes) + ":";
    }
    else{
        to_print += "0" + to_string(minutes) + ":";
    }

    //Check if seconds need leading zero
    if(int(seconds/10)!=0){
        to_print += to_string(seconds);
    }
    else{
        to_print += "0" + to_string(seconds);
    }

    //Check if millis need leading zero
    to_print += ".";
    if(int(hundredths/10)!=0){
        to_print += to_string(hundredths);
    }
    else{
        to_print += "0" + to_string(hundredths);
    }

    

    for(int i = 0; i < ASCII_HEIGHT; i++){
        string line;
        for(char ch : to_print){
            if(ch == ':'){
                line += font1.at(10)[i];
                line += padding;
            }
            else if(ch == '.'){
                line += font1.at(11)[i];
                line += padding;
            }
            else{
                line += font1.at(ch-'0')[i];
                line += padding;
            }
        }
        _buffer+=((line+"\n"));
    }
}

void Display::stageStopwatchActions(){
    _buffer+=("\n");
    _buffer+=("===========================================\n");
    _buffer+=("Control your stopwatch with the following keys: \n");
    _buffer+=("===========================================\n");
    _buffer+=("\n");
    _buffer+=("S : Start/Stop your stopwatch.\n");
    _buffer+=("R : Reset your stopwatch.\n");
    _buffer+=("A : Create a split at the current time.\n");
    _buffer+=("Q : Stop your stopwatch immediately and return to menu.\n");
    _buffer+=("\n");

}

void Display::printStaged(){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    resetCursor();
    fast_print(_buffer);
    _buffer = "";
}

/* =========================================================
PARSING TIMER, CALLING PRINT FUNCTION
========================================================= */

void Display::tickTimer(Timer& timer){
    int remaining = timer.remainingMilliseconds();
    
    int hours = remaining / 3600000;
    remaining %= 3600000;
    int minutes = remaining / 60000;
    remaining %= 60000;
    int seconds = remaining / 1000;
    remaining %= 1000;
    int tenths = remaining / 100;

    stageTimerDisplay(hours, minutes, seconds, tenths);
    stageTimerActions();
    stageSplash();

    printStaged();

}

void Display::tickStopwatch(Stopwatch& stopwatch){
    int milliseconds = stopwatch.currentMilliseconds();
    
    int hours = milliseconds / 3600000;
    milliseconds %= 3600000;
    int minutes = milliseconds / 60000;
    milliseconds %= 60000;
    int seconds = milliseconds / 1000;
    milliseconds %= 1000;
    int hundredths = milliseconds / 10;

    stageStopwatchDisplay(hours, minutes, seconds, hundredths);
    stageStopwatchActions();
    stageSplash();

    printStaged();

}

template<typename char_type>
auto Display::fast_print(const std::basic_string<char_type>& sss) -> void
{
   HANDLE const output_handle = GetStdHandle(STD_OUTPUT_HANDLE);
   const auto char_count = static_cast<DWORD>(sss.length());
   if constexpr (std::is_same_v<char_type, char>)
      WriteConsoleA(output_handle, sss.c_str(), char_count, nullptr, nullptr);
   else
      WriteConsoleW(output_handle, sss.c_str(), char_count, nullptr, nullptr);
}