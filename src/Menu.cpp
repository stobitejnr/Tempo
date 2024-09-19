#define OOF_IMPL
#include "../include/Menu.hpp"

using namespace std;

#define LOOPTIME 0.1

/* =========================================================
CONSTRUCTOR
========================================================= */

/**
 * @brief Constructs a Menu object and initializes its state.
 */
Menu::Menu(bool testing){ 
    _display = Display();
    _run = true;
    _testing = testing;
}

void Menu::start(){
    _display.clearScreen();

    string lBuffer = "                ";

    for (string line : _logoArt){
        cout << line << endl;
    }

    cout << endl;

    for (string line : _credits){
        cout << lBuffer << line << endl;
    }
    waitForInput();
}

/* =========================================================
MAIN MENU SEQUENCE
========================================================= */

/**
 * @brief Starts the main menu loop, allowing the user to choose between Timer, Stopwatch, and Alarm.
 * 
 * The menu displays options to the user, processes the user's selection, and runs the appropriate sequence
 * for Timer, Stopwatch, or Alarm. It handles the input and output and returns to the menu after each operation
 * unless the user chooses to quit.
 */
void Menu::mainMenu() {

    _display.clearScreen();

    for (string line : _menuArt){
        cout << "" << line << endl;
    }

    cout << "1: Timer\n";
    cout << "2: Stopwatch\n";
    cout << "3: Alarm **Beta Feature**\n";
    cout << "Q: Quit Program\n";

    if(_testing){
        timerSequence();
        stopwatchSequence();
        alarmSequence();
        return;
    }
    
    char in = getMenuInput();
    // ENTER TIMER SEQUENCE
    if(in == '1'){
        timerSequence();
    }

    // ENTER STOPWATCH SEQUENCE
    else if(in == '2'){
        stopwatchSequence();
    }

    // ENTER ALARM SEQUENCE
    else if(in == '3'){
        alarmSequence();
    }

    // QUIT PROGRAM
    else if(in == 'q'){
        return;
    }
    
    // Restart menu loop
    mainMenu();
}

void Menu::timerSequence(){
    _display.clearScreen();

    Timer timer = createTimer();

    bool run = true;

    _display.clearScreen();

    while(run){
        // Display a message when the timer finishes
        if(timer.remainingMilliseconds() == 0) {
            _display.setSplash("TIMER FINISHED"); 
        }

        _display.tickTimer(timer);

        checkTimerInput(timer, run);

        wait(0.01);

        if(_testing){
            run = false;
        }
    }
}

void Menu::stopwatchSequence(){

    _display.clearScreen();

    Stopwatch stopwatch;

    bool run = true;

    _display.setSplash("PRESS 'S' TO START");

    _display.tickStopwatch(stopwatch);

    //_display.clearScreen();
    
    while(run){
        _display.tickStopwatch(stopwatch);

        checkStopwatchInput(stopwatch, run);

        wait(0.01);

        if(_testing){
            run = false;
        }
    }
}

void Menu::alarmSequence(){
    _display.clearScreen();

    Alarm alarm = createAlarm();

    bool run = true;

    _display.clearScreen();

    while(run){
        // Display a message when the alarm finishes
        if(alarm.isDone()) {
            _display.setSplash("ALARM FINISHED"); 
        }

        _display.tickAlarm(alarm);

        checkAlarmInput(alarm, run);

        wait(0.01);

        if(_testing){
            run = false;
        }
    }
}

Timer Menu::createTimer(){
    int h = 0;
    int m = 0;
    int s = 0;
    int countdownSeconds = 0;

    string input = "000000";

    string to_print = "00:00:00";

    _display.tickTimerSetup(to_print);
    
    int index = 5;
    
    while (true) {
        char ch; 
        if(_testing){
            ch = '1';
        }
        else{
            ch = _getch();
        }

        if (ch == 13 && (h || m || s)) {
            break;
        } 
        else if (ch >= '0' && ch <= '9') {
            input = input.substr(1) + ch; 
        } 
        else if (ch == 8) { 
            input = '0' + input.substr(0, 5);
        }

        h = stoi(input.substr(0, 2));
        m = stoi(input.substr(2, 2));
        s = stoi(input.substr(4, 2));

        to_print = (h < 10 ? "0" : "") + to_string(h) + ":" 
                 + (m < 10 ? "0" : "") + to_string(m) + ":" 
                 + (s < 10 ? "0" : "") + to_string(s);

        _display.tickTimerSetup(to_print);
        
        wait(0.01);

        if(_testing){
            break;
        }
    }
    _display.clearScreen();
    Timer timer(h,m,s);
    return timer;
}

Alarm Menu::createAlarm(){
    int h = 0;
    int m = 0;

    string input = "0000";

    string to_print = "00:00";

    _display.tickAlarmSetup(to_print);
    
    int index = 3;
    
    while (true) {
        char ch; 
        if(_testing){
            ch = '1';
        }
        else{
            ch = _getch();
        }

        if (ch == 13 && (h || m)) {
            break;
        } 
        else if (ch >= '0' && ch <= '9') {
            input = input.substr(1) + ch; 
        } 
        else if (ch == 8) { 
            input = '0' + input.substr(0, 3);
        }

        h = stoi(input.substr(0, 2));
        m = stoi(input.substr(2, 2));

        // Ensure the hours are between 0 and 23, and minutes are between 0 and 59
        if (h > 23) {
            h = 23;  // Limit the hours to 23
            input = "23" + input.substr(2, 2);  // Update the input to reflect this
        }

        if (m > 59) {
            m = 59;  // Limit the minutes to 59
            input = input.substr(0, 2) + "59";  // Update the input to reflect this
        }

        to_print = (h < 10 ? "0" : "") + to_string(h) + ":" 
                 + (m < 10 ? "0" : "") + to_string(m);

        _display.tickTimerSetup(to_print);
        
        wait(0.01);

        if(_testing){
            break;
        }
    }
    _display.clearScreen();
    Alarm alarm(to_print);
    return alarm;
}

/**
 * @brief Waits for a specific duration using busy-waiting.
 * 
 * This function uses a high-resolution clock to wait for the specified amount of time (in seconds). 
 * It continuously checks the elapsed time until the desired duration has passed.
 * 
 * @param seconds The amount of time to wait, in seconds.
 */
void Menu::wait(double seconds) {
    int milli = 1000 * seconds;
    this_thread::sleep_for(chrono::milliseconds(milli));
}

/* =========================================================
WAIT FOR ANY USER INPUT
========================================================= */

/**
 * @brief Waits for any key press from the user.
 * 
 * This function blocks until the user presses a key, using `_getch()` to capture the input.
 */
void Menu::waitForInput() {
    if(_testing){
        return;
    }
    _getch();
}

/* =========================================================
HANDLE KEYBOARD INPUT FOR TIMER
========================================================= */

/**
 * @brief Checks and handles user input for the Timer.
 * 
 * This function processes user input to control the Timer. It updates the Timer's state based on the key pressed.
 * 
 * @param timer The Timer object to control.
 * @param run A boolean reference that determines whether to continue the loop.
 */
void Menu::checkTimerInput(Timer& timer, bool& run){
    if(_kbhit()){
        char ch = _getch();
        switch(ch){
            case 'S':
            case 's':
                if(timer.isRunning()){
                    timer.pause();
                    _display.setSplash("TIMER PAUSED");
                }
                else if(timer.remainingMilliseconds() > 0){
                    _display.clearSplash();
                    timer.resume();        
                }
                break;
            case 'R':
            case 'r':
                timer.reset();
                _display.clearScreen();
                _display.setSplash("TIMER RESET, PRESS 'S' TO START");
                break;
            case 'A':
            case 'a':
                _display.clearScreen();
                _display.clearSplash();
                timer = createTimer();
                break;
            case 'Q':
            case 'q':
                _display.clearSplash();
                run = false;
                return;
            default:
                break;
        }
    }
}

/* =========================================================
HANDLE KEYBOARD INPUT FOR STOPWATCH
========================================================= */

/**
 * @brief Checks and handles user input for the Stopwatch.
 * 
 * This function processes user input to control the Stopwatch. It updates the Stopwatch's state based on the key pressed.
 * 
 * @param stopwatch The Stopwatch object to control.
 * @param run A boolean reference that determines whether to continue the loop.
 */
void Menu::checkStopwatchInput(Stopwatch& stopwatch, bool& run){
    if(_kbhit()){
        char ch = _getch();
        switch(ch){
            case 'S':
            case 's':
                if(stopwatch.isRunning()){
                    stopwatch.pause();
                    if ((stopwatch.currentMilliseconds() / 10) % 100 == 0){
                        int i = rand() % _stopMessages.size();
                        _display.setSplash(_stopMessages[i]);
                    }
                    else{
                        _display.setSplash("STOPWATCH PAUSED");
                    }
                }
                else{
                    _display.clearSplash();
                    stopwatch.resume();        
                }
                break;
            case 'R':
            case 'r':
                stopwatch.reset();
                _display.clearScreen();
                _display.setSplash("STOPWATCH RESET, PRESS 'S' TO START");
                break;
            case 'A':
            case 'a':
                stopwatch.addSplit();
                _display.setSplash("SPLIT CREATED");
                break;
            case 'Q':
            case 'q':
            _display.clearSplash();
                run = false;
                return;
            default:
                if(!run){
                    return;
                }
                break;
        }
    }
}


void Menu::checkAlarmInput(Alarm& alarm, bool& run){
    if(_kbhit()){
        char ch = _getch();
        switch(ch){
            default:
                break;
        }
    }
}
/* =========================================================
GET USER INPUT FOR MENU SELECTION
========================================================= */

/**
 * @brief Waits for the user to press a valid key (1, 2, 3, or Q) for menu selection.
 * 
 * This function repeatedly checks for user input until a valid menu option is pressed. It then returns
 * the corresponding character for the selected menu option.
 * 
 * @return char The character corresponding to the user's menu selection.
 */
char Menu::getMenuInput(){
    while(true){
        if(_kbhit()){
            char ch = _getch();
            switch(ch){
                case '1':
                    return '1';
                case '2':
                    return '2';
                case '3':
                    return '3';
                case 'q':
                    return 'q';
                default:
                    break;
            }
        }
        wait(0.01); // Slight delay before checking input again
    }
}
