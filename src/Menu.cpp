#define OOF_IMPL
#include "../include/Menu.hpp"

using namespace std;

const double LOOPTIME = 0.01;



/* =========================================================
CONSTRUCTOR
========================================================= */

/**
 * @brief Constructs a Menu object and initializes its state.
 */
Menu::Menu(bool testing){ 
    srand(static_cast<unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count()));
    _display = Display();
    _run = true;
    _testing = testing;
}

/**
 * @brief Displays the start screen with logo art and credits.
 */
void Menu::start(){
    _display.clearScreen();

    string lBuffer = "                         ";
    _display.setFormat(Display::BOLD_CYAN);

    for (string line : _logoArt){
        cout << line << endl;
    }

    _display.clearFormat();
    _display.setFormat(Display::WHITE);

    cout << endl;

    for (string line : _credits){
        cout << lBuffer << line << endl;
    }

    _display.clearFormat();

    _display.setCursor(1,1);
    
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

    _display.setFormat(Display::BOLD_CYAN);

    for (string line : _menuArt){
        cout << "" << line << endl;
    }

    _display.clearFormat();
    _display.setFormat(Display::BOLD_WHITE);

    for (string line : _menuOptions){
        cout << "" << line << endl;
    }

    _display.clearFormat();

    if(_testing){
        timerSequence();
        stopwatchSequence();
        alarmSequence();
        return;
    }
    
    _display.setCursor(1,1);
    
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
        _display.clearScreen();
        return;
    }
    
    // Restart menu loop
    mainMenu();
}

/**
 * @brief Runs the timer sequence, allowing the user to set and interact with a timer.
 */
void Menu::timerSequence(){
    _display.clearScreen();

    bool run = true;

    Timer timer = createTimer(run);

    _display.clearScreen();

    while(run){
        // Display a message when the timer finishes
        if(timer.remainingMilliseconds() == 0) {
            _display.setSplash("TIMER FINISHED"); 
        }

        _display.tickTimer(timer);

        checkTimerInput(timer, run);

        wait(LOOPTIME);

        if(_testing){
            run = false;
        }
    }
}

/**
 * @brief Runs the stopwatch sequence, allowing the user to start, stop, and record splits.
 */
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

        wait(LOOPTIME);

        if(_testing){
            run = false;
        }
    }
}

/**
 * @brief Runs the alarm sequence, allowing the user to set and interact with an alarm.
 */
void Menu::alarmSequence(){
    _display.clearScreen();

    bool run = true;

    Alarm alarm = createAlarm(run);

    _display.clearScreen();

    while(run){
        // Display a message when the alarm finishes
        if(alarm.isDone()) {
            _display.setSplash("ALARM FINISHED"); 
        }

        _display.tickAlarm(alarm);

        checkAlarmInput(alarm, run);

        wait(LOOPTIME);

        if(_testing){
            run = false;
        }
    }
}

/**
 * @brief Creates a new Timer object based on user input.
 * @param run A reference to a boolean flag indicating whether to continue running the sequence.
 * @return A Timer object initialized with the user's input.
 */
Timer Menu::createTimer(bool& run){
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
        else if(_kbhit()){
            ch = _getch();
        }
        else{
            ch = 0;
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

        if(ch == 'q' || ch == 'Q'){
            run = false;
            return Timer(0,0,0);
        }

        h = stoi(input.substr(0, 2));
        m = stoi(input.substr(2, 2));
        s = stoi(input.substr(4, 2));

        to_print = (h < 10 ? "0" : "") + to_string(h) + ":" 
                 + (m < 10 ? "0" : "") + to_string(m) + ":" 
                 + (s < 10 ? "0" : "") + to_string(s);

        _display.tickTimerSetup(to_print);
        
        wait(LOOPTIME);

        if(_testing){
            break;
        }
    }
    _display.clearScreen();
    Timer timer(h,m,s);
    return timer;
}

/**
 * @brief Creates a new Alarm object based on user input.
 * @param run A reference to a boolean flag indicating whether to continue running the sequence.
 * @return An Alarm object initialized with the user's input.
 */
Alarm Menu::createAlarm(bool& run){
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
        else if(_kbhit()){
            ch = _getch();
        }
        else{
            ch = 0;
        }

        if (ch == 13) {
            break;
        } 
        else if (ch >= '0' && ch <= '9') {
            input = input.substr(1) + ch; 
        } 
        else if (ch == 8) { 
            input = '0' + input.substr(0, 3);
        }

        if(ch == 'q' || ch == 'Q'){
            run = false;
            return Alarm(0,0);
        }

        h = stoi(input.substr(0, 2));
        m = stoi(input.substr(2, 2));

        to_print = (h < 10 ? "0" : "") + to_string(h) + ":" 
                 + (m < 10 ? "0" : "") + to_string(m);

        _display.tickAlarmSetup(to_print);
        
        wait(LOOPTIME);

        if(_testing){
            break;
        }
    }
    _display.clearScreen();
    Alarm alarm(h,m);
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
                timer = createTimer(run);
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

/* =========================================================
HANDLE KEYBOARD INPUT FOR ALARM
========================================================= */

/**
 * @brief Checks and handles user input for the Alarm.
 * 
 * This function processes user input to control the Alarm. It updates the Alarm's state based on the key pressed.
 * 
 * @param alarm The Alarm object to control.
 * @param run A boolean reference that determines whether to continue the loop.
 */
void Menu::checkAlarmInput(Alarm& alarm, bool& run){
    if(_kbhit()){
        char ch = _getch();
        switch(ch){
            case 'A':
            case 'a':
                _display.clearScreen();
                _display.clearSplash();
                alarm = createAlarm(run);
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
                case 'Q':
                case 'q':
                    return 'q';
                default:
                    break;
            }
        }
        wait(LOOPTIME); // Slight delay before checking input again
    }
}
