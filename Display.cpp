#include "Display.hpp"
#include <vector>
#include <string>

using namespace std;

Display::Display(Timer& timer) : _timer(timer) {}

#define ASCII_HEIGHT 8

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

void Display::clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void Display::printTime(int hours, int minutes, int seconds){
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

void Display::tick(){
    int remaining = _timer.remainingSeconds();
    
    int hours = remaining / 3600;
    remaining %= 3600;
    int minutes = remaining / 60;
    int seconds = remaining % 60;
    
    printTime(hours, minutes, seconds);
}
