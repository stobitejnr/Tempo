#ifndef MENU_HPP
#define MENU_HPP

#include "Timer.hpp"
#include "Stopwatch.hpp"
#include "Alarm.hpp"
#include "Display.hpp"

#include <iostream>
#include <conio.h>
#include <cstdlib>

using namespace std;

/**
 * @brief The Menu class manages the main menu and user input for the Timer, Stopwatch, and Alarm.
 */
class Menu
{
public:
    /**
     * @brief Constructs a Menu object.
     */
    Menu(bool testing);

    /**
     * @brief Waits for the user to press a valid key (1, 2, 3, or Q) for menu selection.
     *
     * This function repeatedly checks for user input until a valid menu option is pressed.
     * It then returns the corresponding character for the selected menu option.
     *
     * @return char The character corresponding to the user's menu selection.
     */
    char getMenuInput();

    /**
     * @brief Waits for a specific duration using busy-waiting.
     *
     * This function uses a high-resolution clock to wait for the specified amount of time (in seconds).
     * It continuously checks the elapsed time until the desired duration has passed.
     *
     * @param seconds The amount of time to wait, in seconds.
     */
    void wait(double seconds);

    /**
     * @brief Waits for any key press from the user.
     *
     * This function blocks until the user presses a key, using `_getch()` to capture the input.
     */
    void waitForInput();

    /**
     * @brief Checks and handles user input for the Timer.
     *
     * This function processes user input to control the Timer. It updates the Timer's state based on the key pressed.
     *
     * @param timer The Timer object to control.
     * @param run A boolean reference that determines whether to continue the loop.
     */
    void checkTimerInput(Timer &timer, bool &run);

    /**
     * @brief Checks and handles user input for the Stopwatch.
     *
     * This function processes user input to control the Stopwatch. It updates the Stopwatch's state based on the key pressed.
     *
     * @param stopwatch The Stopwatch object to control.
     * @param run A boolean reference that determines whether to continue the loop.
     */
    void checkStopwatchInput(Stopwatch &stopwatch, bool &run);


    void checkAlarmInput(Alarm& alarm, bool& run);

    /**
     * @brief Starts the main menu loop, allowing the user to choose between Timer, Stopwatch, and Alarm.
     *
     * The menu displays options to the user, processes the user's selection, and runs the appropriate sequence
     * for Timer, Stopwatch, or Alarm. It handles the input and output and returns to the menu after each operation
     * unless the user chooses to quit.
     */
    void mainMenu();

    void start();

    void timerSequence();

    void stopwatchSequence();

    void alarmSequence();

    Timer createTimer();

    Alarm createAlarm();

    void printTimerInput(int, int ,int);

private:
    Display _display;  ///< Instance of Display to manage the visual representation.
    bool _run;         ///< Boolean to control the main loop execution.
    bool _testing;
    vector<string> _logoArt = {                                                                                   
        "  +@@@@@@@@@@@+                                                               ",           
        " :@@@@@@@@@@@@+                                                               ",          
        " .:::@@@@@=:::  .-=======:   .====-.===-. .-===:   :====::===-.    :-=======: ",          
        "    =@@@@%    .#@@@@@@@@@@%  #@@@@@@@@@@@#@@@@@@=  %@@@@@@@@@@@. :%@@@@@@@@@@+",          
        "    %@@@@=    #@@@@- -@@@@% .@@@@@==@@@@@+-%@@@@= :@@@@%==@@@@@. %@@@@-:#@@@@+",           
        "   :@@@@@    .@@@@%==*@@@@= +@@@@+ -@@@@# .@@@@@  *@@@@= =@@@@# -@@@@#  %@@@@.",           
        "   *@@@@+    +@@@@@@@@@@@@  @@@@@. #@@@@- +@@@@* .@@@@@  %@@@@: #@@@@: -@@@@# ",            
        "  .@@@@@.    @@@@%  .++++: =@@@@# .@@@@@  %@@@@: +@@@@* :@@@@% :@@@@%  %@@@@: ",            
        "  +@@@@#    -@@@@@##@@@@@. %@@@@- *@@@@+ -@@@@#  @@@@@@%@@@@@- +@@@@@#%@@@@#  ",             
        "  @@@@@-     *%@@@@@@@%+. :@@@@% .@@@@@  %@@@@- =@@@@##@@@%*:  .#@@@@@@@@#    ",              
        "  ==============================================%@@@@*======================  ",             
        " ==============================================+@@@@@===================      ",                 
        "===============================================@@@@@*=============            "
    };

    vector<string> _credits = {
        "-------------------------------------",
        "             Tempo v1.0              ",
        "-------------------------------------",
        "    A lightweight timer, stopwatch,",
        "       and alarm terminal app.",
        "-------------------------------------",
        "            Developed by:",
        "          William Donnelly",
        "            Kevin Albert",
        "            Rowan Zeszut",
        "            Ben Sampson",
        "-------------------------------------"
        "",
        "    Press any key to continue..."
    };

    vector<string> _menuArt = {
    "    __  ___      _          __  ___                ",
    "   /  |/  /___ _(_)___     /  |/  /__  ____  __  __",
    "  / /|_/ / __ `/ / __ \\   / /|_/ / _ \\/ __ \\/ / / /",
    " / /  / / /_/ / / / / /  / /  / /  __/ / / / /_/ / ",
    "/_/  /_/\\__,_/_/_/ /_/  /_/  /_/\\___/_/ /_/\\____/  ",
    "=================================================="
    };

    vector<string> _stopMessages = {
        "EXACTLY ON THE DOT! YOU MUST BE A TIME WIZARD.",
        "THERE'S NO WAY YOU MEANT TO DO THAT...",
        "YOU'VE ACHIEVED STOPWATCH ZEN.",
        "IF YOU DID THAT ON PURPOSE, I'M IMPRESSED.",
    };

};

#endif // MENU_HPP
