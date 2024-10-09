#include "../include/Menu.hpp"

using namespace std;

const double LOOPTIME = 0.01;

const int NUM_FONTS = 4;

/* =========================================================
CONSTRUCTOR
========================================================= */

/**
 * @brief Constructs a Menu object and initializes its state.
 */
Menu::Menu(bool testing){ 
    srand(static_cast<unsigned int>(chrono::high_resolution_clock::now().time_since_epoch().count()));
    _display = Display();
    _run = true;
    _testing = testing;
    _menuFormats = { Display::BOLD_WHITE, Display::BOLD_WHITE, Display::BOLD_WHITE, Display::BOLD_WHITE, Display::BOLD_WHITE };
    _settingsFormats = { Display::BOLD_WHITE, Display::BOLD_WHITE, Display::BOLD_WHITE, Display::BOLD_WHITE};

    _notiSetting = true;
    _fontSetting = 1;

    loadSettings();

    _display.setFont(_fontSetting);

    _display.clearScreen();
    
    mainMenu(0);
}

void Menu::printArt(vector<string> art, string formatting){
    _display.setFormat(formatting);

    for (string line : art){
        cout << line << endl;
    }

    _display.clearFormat();
}

/**
 * @brief Displays the start screen with logo art and credits.
 */
void Menu::credits(){
    _display.clearScreen();

    string lBuffer = "                         ";

    printArt(_logoArt, Display::BOLD_CYAN);

    _display.setFormat(Display::WHITE);
    cout << endl;
    for (string line : _credits){
        cout << lBuffer << line << endl;
    }
    _display.clearFormat();

    _display.setCursor(1,1);
    
    waitForInput();

    _display.clearScreen();
}

void Menu::loadSettings() {
    ifstream settingsFile("settings.txt");
    
    if (settingsFile.is_open()) {
        settingsFile >> _fontSetting;
        settingsFile >> _notiSetting;
        settingsFile.close();
    } else {
        // Default settings if the file doesn't exist
        _fontSetting = 1;
        _notiSetting = true;
    }
}

void Menu::saveSettings() {
    ofstream settingsFile("settings.txt");
    
    if (settingsFile.is_open()) {
        settingsFile << _fontSetting << endl;
        settingsFile << _notiSetting << endl;
        settingsFile.close();
    }
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

void Menu::mainMenu(int selected) {

    for (int i = 0; i < _menuFormats.size(); ++i) {
        if (i == selected) {
            _menuFormats.at(i) = Display::SELECTED;
        } else {
            _menuFormats.at(i) = Display::BOLD_WHITE;
        }
    }

    _display.setCursor(1,1);

    printArt(_menuArt, Display::BOLD_CYAN);

    printArt(_menuTimer, _menuFormats.at(0));

    printArt(_menuStopwatch, _menuFormats.at(1));

    printArt(_menuAlarm, _menuFormats.at(2));

    printArt(_menuSettings, _menuFormats.at(3));

    printArt(_menuQuit, _menuFormats.at(4));

    _display.setCursor(1,1);

    if(_testing){
        timerSequence();
        stopwatchSequence();
        alarmSequence();
        return;
    }
    
    char in = getMenuInput(selected);
    // ENTER TIMER SEQUENCE
    if(in == '1'){
        timerSequence();
        _display.clearScreen();
    }

    // ENTER STOPWATCH SEQUENCE
    else if(in == '2'){
        stopwatchSequence();
        _display.clearScreen();
    }

    // ENTER ALARM SEQUENCE
    else if(in == '3'){
        alarmSequence();
        _display.clearScreen();
    }

    // ENTER SETTINGS SEQUENCE
    else if(in == 's' || in == '4'){
        _display.clearScreen();
        settingsMenu(0);
        _display.clearScreen();
    }

    // QUIT PROGRAM
    else if(in == 'q' || in == '5'){
        _display.clearScreen();
        return;
    }
    
    // Restart menu loop
    mainMenu(selected);
}

void Menu::settingsMenu(int selected) {

    for (int i = 0; i < _settingsFormats.size(); ++i) {
        if (i == selected) {
            _settingsFormats.at(i) = Display::SELECTED;
        } else {
            _settingsFormats.at(i) = Display::BOLD_WHITE;
        }
    }

    _display.setCursor(1,1);

    printArt(_settingsArt, Display::BOLD_CYAN);

    switch(_fontSetting){
        case 1:
            printArt(_settingsFont1, _settingsFormats.at(0));
            break;
        case 2:
            printArt(_settingsFont2, _settingsFormats.at(0));
            break;
        case 3:
            printArt(_settingsFont3, _settingsFormats.at(0));
            break;
        case 4:
            printArt(_settingsFont4, _settingsFormats.at(0));
            break;
    }

    if(_notiSetting){
        printArt(_settingsNotiOn, _settingsFormats.at(1));
    }
    else{
        printArt(_settingsNotiOff, _settingsFormats.at(1));
    }

    printArt(_settingsCredits, _settingsFormats.at(2));

    printArt(_settingsBack, _settingsFormats.at(3));

    _display.setCursor(1,1);

    if(_testing){
        return;
    }
    
    char in = getSettingsInput(selected);

    if(in == '1'){
        //Rotate fonts
        if(_fontSetting < NUM_FONTS){
            _fontSetting++;
        }
        else{
            _fontSetting = 1;
        }
        saveSettings();
    }
    else if(in == '2'){
        //Toggle notifications
        _notiSetting = !_notiSetting;
        saveSettings();
    }
    else if(in == '3'){
        credits();
    }
    else if(in == 'q' || in == '4'){
        saveSettings();
        _display.setFont(_fontSetting);
        return;
    }
    
    printArt(_settingsBlank, "");
    settingsMenu(selected);
}

/**
 * @brief Runs the timer sequence, allowing the user to set and interact with a timer.
 */
void Menu::timerSequence(){
    _display.clearScreen();

    bool run = true;
    bool notified = false;

    Timer timer = createTimer(run);

    _display.clearScreen();

    while(run){
        // Display a message when the timer finishes
        if(timer.remainingMilliseconds() == 0) {
            _display.setSplash("TIMER FINISHED"); 
            if(_notiSetting && !notified){
                Notification noti("Tempo", "Your timer is finished!");
                notified = true;
            }
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
    bool notified = false;

    Alarm alarm = createAlarm(run);

    _display.clearScreen();

    while(run){
        // Display a message when the alarm finishes
        if(alarm.isDone()) {
            _display.setSplash("ALARM FINISHED"); 
            if(_notiSetting && !notified){
                Notification noti("Tempo", "Your alarm is finished!");
                notified = true;
            }
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

    bool isAM = true;

    _display.tickAlarmSetup(to_print, isAM);
    
    int index = 3;
    
    
    while (true) {
        char ch; 

        if(_testing){
            ch = '1';
        }

        else if(_kbhit()){
            ch = _getch();

            if(ch == -32 || ch == 224 || ch == 0){
                ch = getch();
                switch(ch){
                    case 75:
                        isAM = 1;
                        break;
                    case 77:
                        isAM = 0;
                        break;   
                    default:
                        break; 
                }
            }
        }

        else{
            ch = 0;
        }

        if (ch == 13 && h) {
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

        if(h > 12) { 
            h = 12; 
        }

        if(h && m > 59) { 
            m = 59; 
        }

        to_print = (h < 10 ? "0" : "") + to_string(h) + ":" 
                 + (m < 10 ? "0" : "") + to_string(m);

        input = to_print.substr(0, 2) + to_print.substr(3, 2);

        _display.tickAlarmSetup(to_print, isAM);
        
        wait(LOOPTIME);

        if(_testing){
            break;
        }
    }
    _display.clearScreen();
    Alarm alarm(0,0);
    
    if(isAM){
        if(h == 12){
            alarm = Alarm(0,m);
        }
        else{
            alarm = Alarm(h,m);
        }
    }
    else{
        if(h == 12){
            alarm = Alarm(12,m);
        }
        else{
            alarm = Alarm(h+12,m);
        }
    }
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
char Menu::getMenuInput(int& selected){
    while(true){
        if(_kbhit()){
            char ch = _getch();

            if(ch == 13){
                return selected + '1';
            }

            if(ch == -32 || ch == 224 || ch == 0){
                ch = getch();
                switch(ch){
                    case 72:
                        selected = max(0,selected-1);
                        break;
                    case 80:
                        selected = min(4,selected+1);
                        break;   
                    default:
                        break; 
                }
                return '0';
            }

            else{
                switch(ch){
                    case '1':
                    case '2':
                    case '3':
                        selected = ch - '1';
                        return ch;
                    case 'S':
                    case 's':
                        selected = 3;
                        return 's';
                    case 'Q':
                    case 'q':
                        selected = 4;
                        return 'q';
                    default:
                        break;         
                }
            }

        }
        wait(LOOPTIME); // Slight delay before checking input again
    }
}


char Menu::getSettingsInput(int& selected){
    while(true){
        if(_kbhit()){
            char ch = _getch();

            if(ch == 13){
                return selected + '1';
            }

            if(ch == -32 || ch == 224 || ch == 0){
                ch = getch();
                switch(ch){
                    case 72:
                        selected = max(0,selected-1);
                        break;
                    case 80:
                        selected = min(3,selected+1);
                        break;   
                    default:
                        break; 
                }
                return '0';
            }
            else{
                switch(ch){
                    case '1':
                    case '2':
                    case '3':
                        selected = ch - '1';
                        return ch;
                    case 'Q':
                    case 'q':
                        selected = 3;
                        return 'q';
                    default:
                        break;         
                }
            }
        }
        wait(LOOPTIME); // Slight delay before checking input again
    }
}