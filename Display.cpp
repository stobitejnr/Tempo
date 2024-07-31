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
    
vector<vector<string>> ascii = {_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _colon};

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

void Display::printTimer(int hours, int minutes, int seconds){
    clearScreen();

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

    for(int i = 0; i < ASCII_HEIGHT; i++){
        for(char ch : to_print){
            if(ch == ':'){
                cout << _colon[i];
                cout << padding;
            }
            else{
                cout << ascii.at(ch-'0')[i];
                cout << padding;
            }
        }
        cout << endl;
    }
}


void Display::printActions(){
    cout << endl;
    cout << "===========================================" << endl;
    cout << "Control your timer with the following keys: " << endl;
    cout << "===========================================" << endl;
    cout << endl;
    cout << "S : Start/Pause your timer." << endl;
    cout << "R : Reset your timer." << endl;
    cout << "Q : End your timer immediately and quit." << endl;
    cout << endl;
}

void Display::setSplash(string str){
    _splash = str;
}

void Display::printSplash(){
    if(_splash != ""){
        cout << endl;
        cout << " >> " << _splash << " << " << endl;
    }
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
    int seconds = (remaining / 1000);
    
    printTimer(hours, minutes, seconds);
    printActions();
    printSplash();
}
