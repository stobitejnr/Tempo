#include <windows.h>

#include "Display.hpp"

using namespace std;

Display::Display(Timer& timer) : _timer(timer) {}

#define ASCII_HEIGHT 8

/* =========================================================
DEFINITION OF ALL ASCII CHARACTER ART
========================================================= */

vector<string> _0 = {
" $$$$$$\\  ",
"$$$ __$$\\ ",
"$$$$\\ $$ |",
"$$\\$$\\$$ |",
"$$ \\$$$$ |",
"$$ |\\$$$ |",
"\\$$$$$$  /",
" \\______/ "};
          
vector<string> _1 = {
"  $$\\   ",
"$$$$ |  ",
"\\_$$ |  ",
"  $$ |  ",
"  $$ |  ",
"  $$ |  ",
"$$$$$$\\ ",
"\\______|"};

vector<string> _2 = {
" $$$$$$\\  ",
"$$  __$$\\ ",
"\\__/  $$ |",
" $$$$$$  |",
"$$  ____/ ",
"$$ |      ",
"$$$$$$$$\\ ",
"\\________|"};

vector<string> _3 = {
" $$$$$$\\  ",
"$$ ___$$\\ ",
"\\_/   $$ |",
"  $$$$$ / ",
"  \\___$$\\ ",
"$$\\   $$ |",
"\\$$$$$$  |",
" \\______/ "};

vector<string> _4 = {
"$$\\   $$\\ ",
"$$ |  $$ |",
"$$ |  $$ |",
"$$$$$$$$ |",
"\\_____$$ |",
"      $$ |",
"      $$ |",
"      \\__|"};  

vector<string> _5 = {
"$$$$$$$\\  ",
"$$  ____| ",
"$$ |      ",
"$$$$$$$\\  ",
"\\_____$$\\ ",
"$$\\   $$ |",
"\\$$$$$$  |",
" \\______/ "};
          
vector<string> _6 = {
" $$$$$$\\  ",
"$$  __$$\\ ",
"$$ /  \\__|",
"$$$$$$$\\  ",
"$$  __$$\\ ",
"$$ /  $$ |",
" $$$$$$  |",
" \\______/ "};
    
vector<string> _7 = {
"$$$$$$$$\\ ",
"\\____$$  |",
"    $$  / ",
"   $$  /  ",
"  $$  /   ",
" $$  /    ",
"$$  /     ",
"\\__/      "};

vector<string> _8 = {
" $$$$$$\\  ",
"$$  __$$\\ ",
"$$ /  $$ |",
" $$$$$$  |",
"$$  __$$< ",
"$$ /  $$ |",
"\\$$$$$$  |",
" \\______/ "};
    
vector<string> _9 = {
" $$$$$$\\  ",
"$$  __$$\\ ",
"$$ /  $$ |",
"\\$$$$$$$ |",
" \\____$$ |",
"$$\\   $$ |",
"\\$$$$$$  |",
" \\______/ "};

vector<string> _colon = {
"    ",
"    ",
"$$\\ " ,
"\\__|",
"    ",
"$$\\ ",
"\\__|",
"    "};
    
vector<string> _period = {
"    ",
"    ",
"    " ,
"    ",
"    ",
"    ",
"$$\\ ",
"\\__|"};

vector<vector<string>> font1 = {_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _colon};

/* =========================================================
=TRERMINAL CLEARING FOR SEAMLESS FRAMES
========================================================= */

void Display::clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

/* =========================================================
PRINTING OF TIMER IN ASCII
========================================================= */

void Display::stageTimer(int hours, int minutes, int seconds, int tenths){

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
                line += _colon[i];
                line += padding;
            }
            else if(ch == '.'){
                line += _period[i];
                line += padding;
            }
            else{
                line += font1.at(ch-'0')[i];
                line += padding;
            }
        }
        _buffer.push_back((line+"\n"));
    }
}


void Display::stageActions(){
    _buffer.push_back("\n");
    _buffer.push_back("===========================================\n");
    _buffer.push_back("Control your timer with the following keys: \n");
    _buffer.push_back("===========================================\n");
    _buffer.push_back("\n");
    _buffer.push_back("S : Start/Pause your timer.\n");
    _buffer.push_back("R : Reset your timer.\n");
    _buffer.push_back("Q : End your timer immediately and quit.\n");
    _buffer.push_back("I : Add 10 seconds to your timer.\n");
    _buffer.push_back("\n");
}

void Display::setSplash(string str){
    _splash = str;
}

void Display::stageSplash(){
    if(_splash != ""){
        _buffer.push_back("\n");
        _buffer.push_back((" << " + _splash + " >> \n"));
    }
}

void Display::printStaged(){
    // HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    
    for(string line : _buffer){
        // DWORD written;
        // Write the text to the console
        // WriteConsoleA(
        //     hConsole,           // Handle to the console
        //     line,               // Buffer to write from
        //     strlen(line),       // Number of characters to write
        //     &written,           // Number of characters written
        //     NULL                // Reserved, must be NULL
        // );
        cout << line;
    }
    _buffer.clear();
}

/* =========================================================
PARSING TIMER, CALLING PRINT FUNCTION
========================================================= */

void Display::tick(){
    int remaining = _timer.remainingMilliseconds();
    
    int hours = remaining / 3600000;
    remaining %= 3600000;
    int minutes = remaining / 60000;
    remaining %= 60000;
    int seconds = remaining / 1000;
    remaining %= 1000;
    int tenths = remaining / 100;
    
    stageTimer(hours, minutes, seconds, tenths);
    stageActions();
    stageSplash();

    clearScreen();
    printStaged();
}
