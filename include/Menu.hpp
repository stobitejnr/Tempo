#ifndef MENU_HPP
#define MENU_HPP

#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <fstream>

#include "Timer.hpp"
#include "Stopwatch.hpp"
#include "Alarm.hpp"
#include "Display.hpp"
#include "Notification.hpp"


using namespace std;

/**
 * @brief The Menu class manages the main menu and user input for the Timer  Stopwatch  and Alarm.
 */
class Menu
{
public:
    /**
     * @brief Constructs a Menu object.
     */
    Menu(bool testing);

    /**
     * @brief Waits for the user to press a valid key (1  2  3  or Q) for menu selection.
     *
     * This function repeatedly checks for user input until a valid menu option is pressed.
     * It then returns the corresponding character for the selected menu option.
     *
     * @return char The character corresponding to the user's menu selection.
     */
    char getMenuInput(int& selected);

    /**
     * @brief Waits for the user to press a valid key (1  2  3  4  or Q) for settings selection.
     *
     * This function repeatedly checks for user input until a valid settings option is pressed.
     * It then returns the corresponding character for the selected settings option.
     *
     * @return char The character corresponding to the user's settings selection.
     */
    char getSettingsInput(int& selected);

    /**
     * @brief Waits for a specific duration using busy-waiting.
     *
     * This function uses a high-resolution clock to wait for the specified amount of time (in seconds).
     * It continuously checks the elapsed time until the desired duration has passed.
     *
     * @param seconds The amount of time to wait  in seconds.
     */
    void wait(double seconds);

    /**
     * @brief Waits for any key press from the user.
     *
     * This function blocks until the user presses a key  using `_getch()` to capture the input.
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

    /**
     * @brief Checks and handles user input for the Alarm.
     *
     * This function processes user input to control the Alarm. It updates the Alarm's state based on the key pressed.
     *
     * @param alarm The Alarm object to control.
     * @param run A boolean reference that determines whether to continue the loop.
     */
    void checkAlarmInput(Alarm& alarm, bool& run);

    /**
     * @brief Starts the main menu loop  allowing the user to choose between Timer  Stopwatch  and Alarm.
     *
     * The menu displays options to the user  processes the user's selection  and runs the appropriate sequence
     * for Timer  Stopwatch  or Alarm. It handles the input and output and returns to the menu after each operation
     * unless the user chooses to quit.
     */
    void mainMenu(int selected);

    /**
     * @brief Starts the settings menu loop  allowing the user to change the notification and font settings.
     *
     * The settings menu displays options to the user  processes the user's selection  and runs the appropriate sequence
     * for changing the notification and font settings. It handles the input and output and returns to the settings menu
     * after each operation unless the user chooses to quit.
     */
    void settingsMenu(int selected);

    /**
     * @brief Loads the notification and font settings from a file.
     */
    void loadSettings();

    /**
     * @brief Saves the notification and font settings to a file.
     */
    void saveSettings();

    /**
     * @brief Displays the credits for the Timer  Stopwatch  and Alarm.
     */
    void credits();

    /**
     * @brief Displays the help menu for the Timer  Stopwatch  and Alarm.
     */
    void timerSequence();

    /**
     * @brief Displays the help menu for the Timer  Stopwatch  and Alarm.
     */
    void stopwatchSequence();

    /**
     * @brief Displays the help menu for the Timer  Stopwatch  and Alarm.
     */
    void alarmSequence();

    /**
     * @brief Creates a Timer object with user input for the duration.
     *
     * This function prompts the user to enter the hours  minutes  and seconds for the Timer.
     * It then creates a Timer object with the specified duration and returns it.
     *
     * @param run A boolean reference that determines whether to continue the loop.
     * @return Timer The Timer object created with the user's input.
     */
    Timer createTimer(bool& run);

    /**
     * @brief Creates a Alarm object with user input for the duration.
     *
     * This function prompts the user to enter the hours  minutes  and seconds for the Alarm.
     * It then creates a Alarm object with the specified duration and returns it.
     *
     * @param run A boolean reference that determines whether to continue the loop.
     * @return The Alarm object created with the user's input.
     */
    Alarm createAlarm(bool& run);

    /**
     * @brief Prints the Timer's input duration to the console.
     *
     * This function prints the hours  minutes  and seconds of the Timer's input duration to the console.
     *
     * @param hours The hours of the Timer's input duration.
     * @param minutes The minutes of the Timer's input duration.
     * @param seconds The seconds of the Timer's input duration.
     */
    void printTimerInput(int,int,int);

    /**
     * @brief Prints the Alarm's input duration to the console.
     *
     * This function prints the hours  minutes  and seconds of the Alarm's input duration to the console.
     *
     * @param hours The hours of the Alarm's input duration.
     * @param minutes The minutes of the Alarm's input duration.
     * @param seconds The seconds of the Alarm's input duration.
     */
    void printArt(vector<string> art, string formatting);

private:
    Display _display;  ///< Instance of Display to manage the visual representation.
    bool _run;         ///< Boolean to control the main loop execution.
    bool _testing;

    vector<string> _menuFormats;
    vector<string> _settingsFormats;

    bool _notiSetting;
    int _fontSetting;


    vector<string> _logoArt = {
        "                                                                                                ", 
        "    &&&&&&&&&&&&&&&&                                                                            ", 
        "    &&&&&&&&&&&&&&&                                                                             ", 
        "        &&&&&&       &&&&&&&&&&&&&   &&&&&& &&&&&&& &&&&&&&&    &&&&&&&&&&&      &&&&&&&&&&&&& ", 
        "       &&&&&%     &&&&&&&&&&&&&&&   &&&&&&&&&&&&&&&&&&&&&&&   &&&&&&&&&&&&&&&  &&&&&&&&&&&&&&&  ", 
        "      &&&&&&      &&&&&&   &&&&&&  &&&&&&   &&&&&&   &&&&&&   &&&&&&  &&&&&&   &&&&&    &&&&&&  ",
        "     &&&&&&      &&&&&&&&&&&&&&&   &&&&&&  &&&&&&&  &&&&&&   &&&&&&   &&&&&&  &&&&&&    &&&&&&   ", 
        "    &&&&&&&      &&&&&&           &&&&&&   &&&&&&   &&&&&&  &&&&&&&  &&&&&&   &&&&&&   &&&&&&   ", 
        "    &&&&&&      &&&&&&&   &&&&   &&&&&&  &&&&&&#  &&&&&&   &&&&&&&&&&&&&&&  &&&&&&&&&&&&&&&    ",
        "   &&&&&&&     %&&&&&&&&&&&&&   &&&&&&   &&&&&&  #&&&&&&   &&&&&&&&&&&&       &&&&&&&&&&&&     ",
        "                                                          &&&&&&                                ",
        "  &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&         ",
        " &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&                  ",
        "                                                                                                "
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
        "-------------------------------------",
        "", 
        "    Press any key to continue...",
    };

    vector<string> _menuArt = {
        "             ___                 _            ", 
        " |\\/|   /\\    |   |\\ |    |\\/|  |_  |\\ |  | | ", 
        " |  |  /--\\  _|_  | \\|    |  |  |_  | \\|  |_| ", 
        "________________________________________________",
       "",
    };

    vector<string> _menuTimer = {
        "          ___  ___         _   _                         ", 
        " /|  o     |    |   |\\/|  |_  |_)                        ", 
        "  |  o     |   _|_  |  |  |_  | \\                        ",
        "                                                         ",
    };
    vector<string> _menuStopwatch = {
        " _         __  ___   _    _                 ___   _      ",
        "  )  o    (_    |   / \\  |_)  \\    /   /\\    |   /   |_| ", 
        " /_  o    __)   |   \\_/  |     \\/\\/   /--\\   |   \\_  | | ",
        "                                                         ",
    };
    vector<string> _menuAlarm = {
        " _                         _                             ", 
        " _)  o     /\\   |    /\\   |_)  |\\/|                      ", 
        " _)  o    /--\\  |_  /--\\  | \\  |  |                      ",
        "                                                         ", 
    };
    vector<string> _menuSettings = {
        " __       __  _ ___ ___ ___       __  __                 ", 
        "(_   o   (_  |_  |   |   |  |\\ | /__ (_                  ",  
        "__)  o   __) |_  |   |  _|_ | \\| \\_| __)                 ",
        "                                                         ",
    };
    vector<string> _menuQuit = {                                 
        " _         _        ___  ___                             ", 
        "/ \\  o    / \\  | |   |    |                              ", 
        "\\_X  o    \\_X  |_|  _|_   |                              ", 
        "                                                         ",
    };
    vector<string> _menuBlank = {                                 
        "                                                         ",
        "                                                         ",
        "                                                         ",
        "                                                         ",
        "                                                         ",
        "                                                         ",
        "                                                         ",
        "                                                         ",
        "                                                         ",
        "                                                         ",
        "                                                         ",
        "                                                         ",
        "                                                         ",
        "                                                         ",
        "                                                         ",
        "                                                         ",
        "                                                         ",
        "                                                         ",
        "                                                         ",
        "                                                         ",
        "                                                         ",
        "                                                         ",
        "                                                         ",
        "                                                         ",
        "                                                         ",
        "                                                         ",
        "                                                         ",
        "                                                         ",
        "                                                         ",
        "                                                         ",
        "                                                         ",
        "                                                         ",
    };

    vector<string> _settingsArt = {
        "   __  _ ___ ___ ___       __  __                                            ",                                     
        "  (_  |_  |   |   |  |\\ | /__ (_                                             ",                                     
        "  __) |_  |   |  _|_ | \\| \\_| __)                                            ",                                                                 
        "____________________________________                                         ",
        "                                                                             ",
    };

    vector<string> _settingsFont1 = {
        "                                                      $$\\                    ", 
        "                                                    $$$$ |                   ", 
        "          _  ___  __ ___ ___    _  _      ___       \\_$$ |                   ",
        " /|  o   | \\  |  /__  |   |    |_ / \\ |\\ | |    __    $$ |                   ",
        "  |  o   |_/ _|_ \\_| _|_  |    |  \\_/ | \\| |          $$ |                   ",
        "                                                      $$ |                   ",
        "                                                    $$$$$$\\                  ",
        "                                                    \\______|                 ",
        
    };
    vector<string> _settingsFont2 = {
        "          _  ___  __ ___ ___    _  _      ___        _                       ", 
        " /|  o   | \\  |  /__  |   |    |_ / \\ |\\ | |    __    )                      ", 
        "  |  o   |_/ _|_ \\_| _|_  |    |  \\_/ | \\| |         /_                      ",
        "                                                                             ",
    };
    vector<string> _settingsFont3 = {
        "                                                       .--.                  ", 
        "                                                     /     \\                 ", 
        "                                                    (___)`. |                ",
        "          _  ___  __ ___ ___    _  _      ___           .-' /                ",
        " /|  o   | \\  |  /__  |   |    |_ / \\ |\\ | |    __      '. \\                 ",
        "  |  o   |_/ _|_ \\_| _|_  |    |  \\_/ | \\| |         ___ \\ '                 ",
        "                                                    (   ) ; |                ",
        "                                                     \\ `-'  /                ",
        "                                                      ',__.'                 ",
    };
    vector<string> _settingsFont4 = {
        "                                                        d8888                ", 
        "                                                       d8P888                ", 
        "          _  ___  __ ___ ___    _  _      ___         d8P 888                ",
        " /|  o   | \\  |  /__  |   |    |_ / \\ |\\ | |    __   d8P  888                ",
        "  |  o   |_/ _|_ \\_| _|_  |    |  \\_/ | \\| |        d88   888                ",
        "                                                    8888888888               ",
        "                                                          888                ",
        "                                                          888                ", 
    };
    
    vector<string> _settingsNotiOn = {
        " _             _ ___ ___  _ ___  _     ___ ___  _        __         _        ",
        "  )  o   |\\ | / \\ |   |  |_  |  /   /\\  |   |  / \\ |\\ | (_    __   / \\ |\\ |  ", 
        " /_  o   | \\| \\_/ |  _|_ |  _|_ \\_ /--\\ |  _|_ \\_/ | \\| __)        \\_/ | \\|  ",
        "                                                                             ",
    };
    vector<string> _settingsNotiOff = {
        " _             _ ___ ___  _ ___  _     ___ ___  _        __         _   _  _ ",
        "  )  o   |\\ | / \\ |   |  |_  |  /   /\\  |   |  / \\ |\\ | (_    __   / \\ |_ |_ ", 
        " /_  o   | \\| \\_/ |  _|_ |  _|_ \\_ /--\\ |  _|_ \\_/ | \\| __)        \\_/ |  |  ",
        "                                                                             ",
    };
    vector<string> _settingsCredits = {
        " _        _  _   _  _  ___ ___ __                                            ", 
        " _)  o   /  |_) |_ | \\  |   | (_                                             ", 
        " _)  o   \\_ | \\ |_ |_/ _|_  | __)                                            ",
        "                                                                             ", 
    };
    vector<string> _settingsBack = {                                 
        " _        _        _                                                         ", 
        "/ \\  o   |_)  /\\  /  |/                                                      ", 
        "\\_X  o   |_) /--\\ \\_ |\\                                                      ", 
        "                                                                             ",

    };
    vector<string> _settingsBlank = {                                 
        "                                                                             ",
        "                                                                             ",
        "                                                                             ",
        "                                                                             ",
        "                                                                             ",
        "                                                                             ",
        "                                                                             ",
        "                                                                             ",
        "                                                                             ",
        "                                                                             ",
        "                                                                             ",
        "                                                                             ",
        "                                                                             ",
        "                                                                             ",
        "                                                                             ",
        "                                                                             ",
        "                                                                             ",
        "                                                                             ",
        "                                                                             ",
        "                                                                             ",
        "                                                                             ",
        "                                                                             ",
        "                                                                             ",
        "                                                                             ",
        "                                                                             ",
        "                                                                             ",
        "                                                                             ",
        "                                                                             ",
        "                                                                             ",
        "                                                                             ",
        "                                                                             ",
        "                                                                             ",
    };

    vector<string> _stopMessages = {
        "EXACTLY ON THE DOT! YOU MUST BE A TIME WIZARD.", 
        "THERE'S NO WAY YOU MEANT TO DO THAT...", 
        "YOU'VE ACHIEVED STOPWATCH ZEN.", 
        "IF YOU DID THAT ON PURPOSE, I'M IMPRESSED.", 
        "DAMN, NICE REFLEXES.", 
        "YOU'RE A MEAN GREEN STOPWATCH MACHINE.", 
        "MEAN GREEN STOPWATCH MACHINE", 
        "YOU HAVE TO BE A ROBOT, RIGHT?", 
        "EVEN QUICKSILVER COULDN'T HAVE DONE IT BETTER.",
        "YOU ARE A BUM, GO HOME LOSER!!!!"
    };

};

#endif // MENU_HPP
