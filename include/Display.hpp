#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include "Timer.hpp"
#include "Stopwatch.hpp"
#include "Alarm.hpp"

#include "../fonts/font1.hpp"
#include "../fonts/font2.hpp"
#include "../fonts/font3.hpp"
#include "../fonts/font4.hpp"

#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

/**
 * @brief The Display class manages the visual representation and interaction
 *        logic for timers, stopwatches, and alarms.
 */
class Display
{
public:

    static const string SELECTED;

    static const string BOLD;

    static const string BLACK;
    static const string RED;
    static const string GREEN;
    static const string YELLOW;
    static const string BLUE;
    static const string MAGENTA;
    static const string CYAN;
    static const string WHITE;

    static const string BOLD_BLACK;
    static const string BOLD_RED;
    static const string BOLD_GREEN;
    static const string BOLD_YELLOW;
    static const string BOLD_BLUE;
    static const string BOLD_MAGENTA;
    static const string BOLD_CYAN;
    static const string BOLD_WHITE;


    /**
     * @brief Constructs a new Display object.
     */
    Display();

    void tickTimerSetup(string to_print);

    void tickAlarmSetup(string to_print, bool isAM);

    /**
     * @brief Updates the display based on the state of the provided Timer object.
     * @param timer Reference to the Timer object.
     */
    void tickTimer(Timer &timer);

    /**
     * @brief Updates the display based on the state of the provided Stopwatch object.
     * @param stopwatch Reference to the Stopwatch object.
     */
    void tickStopwatch(Stopwatch &stopwatch);

    /**
     * @brief Updates the display based on the state of the provided Alarm object.
     * @param alarm Reference to the Alarm object.
     */
    void tickAlarm(Alarm &alarm);

    /**
     * @brief Stages the timer display with provided time values.
     * @param hours Hours to display.
     * @param minutes Minutes to display.
     * @param seconds Seconds to display.
     * @param tenths Tenths of a second to display.
     */
    void stageTimerDisplay(int hours, int minutes, int seconds, int tenths);

    void stageAlarmDisplay(string time);

    /**
     * @brief Stages the controls for the timer.
     */
    void stageArt(vector<string> art);

    /**
     * @brief Stages the progress bar for the timer.
     * @param percentage The percentage of the timer's progress to display.
     */
    void stageTimerBar(double percentage);

    void stageAlarmBar(double percentage);

    /**
     * @brief Stages the stopwatch display with provided time values.
     * @param hours Hours to display.
     * @param minutes Minutes to display.
     * @param seconds Seconds to display.
     * @param hundredths Hundredths of a second to display.
     */
    void stageStopwatchDisplay(int hours, int minutes, int seconds, int hundredths);

    /**
     * @brief Stages the splits block to be displayed.
     */
    void stageStopwatchSplits(vector<int> splits);

    /**
     * @brief Stages the display for the alarm.
     */
    void stageAlarmDisplay();

    /**
     * @brief Sets the splash screen text.
     * @param str The string to display as the splash screen.
     */
    void setSplash(string str);

    /**
     * @brief Clears the splash screen.
     */
    void clearSplash();

    /**
     * @brief Prints the splash screen to the terminal.
     * @param splashIndex The index used for splash screen control.
     */
    void printSplash(int splashIndex, string formatting);

    /**
     * @brief Prints ASCII art to the terminal.
     * @param asciiIndex The index used for ASCII control.
     */
    void printAscii(int asciiIndex, string formatting);

    /**
     * @brief Prints controls to the terminal.
     * @param controlIndex The index used for control display.
     */
    void printArt(int controlIndex, string formatting);

    /**
     * @brief Prints the progress bar to the terminal.
     * @param barIndex The index used for bar control.
     */
    void printBar(int barIndex, string formatting);

    /**
     * @brief Prints the stopwatch splits to the terminal.
     */
    void printSplits(int splitsIndex, string formatting);

    /**
     * @brief Clears the terminal screen.
     */
    void clearScreen();

    /**
     * @brief Sets the terminal text color.
     * @param color The color to set the text to.
     */
    void setFormat(const string& code);

    /**
     * @brief Clears the terminal text color.
     */
    void clearFormat();

    /**
     * @brief Sets the cursor position in the terminal.
     * @param x The x-coordinate (column) to move the cursor to.
     * @param y The y-coordinate (row) to move the cursor to.
     */
    void setCursor(int x, int y);

    /**
     * @brief Clears a specific line in the terminal.
     * @param lineIndex The index of the line to clear.
     */
    void clearLine(int lineIndex);

    /**
     * @brief Sets the font style for the terminal.
     * @param num The font style to set.
     */
    void setFont(int num);


    /**
     * @brief Efficiently prints a string to the terminal.
     * @tparam char_type The character type of the string.
     * @param sss The string to print.
     */
    template <typename char_type>
    static auto fast_print(const basic_string<char_type> &sss) -> void;

private:
    string _asciiBuffer;   ///< Buffer for ASCII art.
    string _barBuffer;     ///< Buffer for progress bar.
    string _controlBuffer; ///< Buffer for controls.
    string _splitBuffer;   ///< Buffer for the splits block.
    string _splash;        ///< String for splash screen.

    string _oldAscii;    ///< Previous ASCII art for comparison.
    string _oldControls; ///< Previous controls for comparison.
    string _oldBar;      ///< Previous progress bar for comparison.
    string _oldSplash;   ///< Previous splash screen for comparison.
    string _oldSplits;   ///< Previous splits for comparison.

    vector<vector<vector<string>>> _fonts;   ///< List of font ascii
    vector<int> _fontHeights;   ///< List of font heights
    vector<vector<string>> _currFont;   ///< current font ascii

    int ASCII_HEIGHT;
    string PADDING;

    string _formatting;
    string _oldFormatting;

    int _asciiWidth; ///< Width of the ASCII art.

    vector<string> _timerSetupControls = {
        "  _     ___ _  _    ___ ___       _  _        _       __ ___      ",
        " |_ |\\ | | |_ |_)    |   |  |\\/| |_ |_)   |  |_ |\\ | /__  | |_| o ",
        " |_ | \\| | |_ | \\    |  _|_ |  | |_ | \\   |_ |_ | \\| \\_|  | | | o ",
    };

    vector<string> _alarmSetupControls = {
        " _     ___ _  _                  _         ___ ___       _   ",
        "|_ |\\ | | |_ |_)    /\\  |   /\\  |_) |\\/|    |   |  |\\/| |_ o ",
        "|_ | \\| | |_ | \\   /--\\ |_ /--\\ | \\ |  |    |  _|_ |  | |_ o ",
    };

    vector<string> _alarmSetupAM = {
        "           ",
        "  /\\  |\\/| ",
        " /--\\ |  | ",
        "           ",
    };


    vector<string> _alarmSetupPM = {
        "  _       ",
        " |_) |\\/| ",
        " |   |  | ",
        "          ",
    };

    vector<string> _alarmControls = {
        "",
        "A: New Alarm | Q: Main Menu",
        "",
    };

    vector<string> _timerControls = {
        "",
        "S: Start/Stop | R: Reset | A: New Timer | Q: Main Menu",
        "",
    };

    vector<string> _stopwatchControls = {
        "",
        "S: Start/Stop | R: Reset | A: Add Split | Q: Main Menu",
        "",
    };

};

#endif // DISPLAY_HPP
