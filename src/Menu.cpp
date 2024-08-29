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
Menu::Menu(){ 
    _display = Display();
    _run = true;
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
void Menu::start() {
    

    _display.clearScreen();

    cout << "1: Timer\n";
    cout << "2: Stopwatch\n";
    //cout << "3: Alarm\n";
    cout << "Q: Quit Program\n";

    char in = getMenuInput();

    // ENTER TIMER SEQUENCE
    if(in == '1'){
        _display.clearScreen();

        Timer timer;

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
        }

    }

    // ENTER STOPWATCH SEQUENCE
    else if(in == '2'){
        Stopwatch stopwatch;

        bool run = true;

        _display.tickStopwatch(stopwatch);

        cout << "\n Press any key to start your stopwatch." << endl;

        waitForInput();

        _display.clearScreen();

        stopwatch.start();
        
        while(run){
            _display.tickStopwatch(stopwatch);

            checkStopwatchInput(stopwatch, run);

            wait(0.01);
        }
    }

    // ENTER ALARM SEQUENCE
    else if(in == '3'){
        Alarm alarm;
    }

    // QUIT PROGRAM
    else if(in == 'q'){
        return;
    }
    
    // Restart menu loop
    start();
}

/* =========================================================
BUSY-WAIT FOR A SPECIFIED AMOUNT OF TIME (IN SECONDS)
========================================================= */

/**
 * @brief Waits for a specific duration using busy-waiting.
 * 
 * This function uses a high-resolution clock to wait for the specified amount of time (in seconds). 
 * It continuously checks the elapsed time until the desired duration has passed.
 * 
 * @param seconds The amount of time to wait, in seconds.
 */
void Menu::wait(double seconds) {
    auto start = chrono::high_resolution_clock::now();
    auto duration = chrono::duration<double>(seconds);
    while (chrono::high_resolution_clock::now() - start < duration) { }
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
                timer = Timer();
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
                    _display.setSplash("STOPWATCH PAUSED");
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
        wait(0.1); // Slight delay before checking input again
    }
}
