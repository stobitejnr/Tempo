#include <windows.h>
#include "../include/Display.hpp"

using namespace std;

const string Display::SELECTED = "\033[1;30;46m";

const string Display::BOLD = "\033[1m";

const string Display::BLACK = "\033[30m";
const string Display::RED = "\033[31m";
const string Display::GREEN = "\033[32m";
const string Display::YELLOW = "\033[33m";
const string Display::BLUE = "\033[34m";
const string Display::MAGENTA = "\033[35m";
const string Display::CYAN = "\033[36m";
const string Display::WHITE = "\033[37m";

const string Display::BOLD_BLACK = "\033[1;30m";
const string Display::BOLD_RED = "\033[1;31m";
const string Display::BOLD_GREEN = "\033[1;32m";
const string Display::BOLD_YELLOW = "\033[1;33m";
const string Display::BOLD_BLUE = "\033[1;34m";
const string Display::BOLD_MAGENTA = "\033[1;35m";
const string Display::BOLD_CYAN = "\033[1;36m";
const string Display::BOLD_WHITE = "\033[1;37m";

/* =========================================================
CONSTRUCTOR
========================================================= */

/**
 * @class Display
 * @brief Handles the terminal display for a timer and stopwatch, including ASCII art and controls.
 */
Display::Display()
{
    _splash = "";
    _asciiBuffer = "";
    _barBuffer = "";
    _controlBuffer = "";
    _splitBuffer = "";

    _oldAscii = "";
    _oldControls = "";
    _oldSplash = "";
    _oldSplits = "";

    _fonts = {f1_ascii, f2_ascii};
    _fontHeights = {f1_height, f2_height};

    setFont(1);

    _asciiWidth = 0;
}

/* =========================================================
TERMINAL INTERACTION HELPERS
========================================================= */

/**
 * @brief Clears the terminal screen and resets the old buffers.
 */
void Display::clearScreen()
{
    string clearscreen = "\033[2J\033[H";

    _oldAscii = "";
    _oldControls = "";
    _oldSplash = "";
    _oldBar = "";

    fast_print(clearscreen);
}

void Display::setFont(int num)
{
    _currFont = _fonts.at(num-1);

    ASCII_HEIGHT = _fontHeights.at(num-1);
    
    if(ASCII_HEIGHT >= 8){
        PADDING = "";
        for(int i=0; i< ASCII_HEIGHT/4; i++){
            PADDING += " ";
        }
    }
    else{
        PADDING = "";
    }
}

/**
 * @brief Sets the cursor position in the terminal.
 * @param row The row position.
 * @param col The column position.
 */
void Display::setCursor(int row, int col)
{
    string setcursor = "\033[" + to_string(row) + ";" + to_string(col) + "H";
    fast_print(setcursor);
}

/**
 * @brief Clears a specific line in the terminal.
 * @param row The row number to clear.
 */
void Display::clearLine(int row)
{
    string clearline = "\033[K";
    setCursor(row, 1);
    fast_print(clearline);
}

/**
 * @brief Prints a string to the console efficiently using the Windows API.
 * @tparam char_type The character type (either char or wchar_t).
 * @param sss The string to print.
 */
template <typename char_type>
auto Display::fast_print(const std::basic_string<char_type> &sss) -> void
{
    HANDLE const output_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    const auto char_count = static_cast<DWORD>(sss.length());
    if constexpr (std::is_same_v<char_type, char>)
        WriteConsoleA(output_handle, sss.c_str(), char_count, nullptr, nullptr);
    else
        WriteConsoleW(output_handle, sss.c_str(), char_count, nullptr, nullptr);
}


void Display::setFormat(const std::string& code) {
    _oldFormatting = _formatting;
    _formatting = code;
    cout << code;
}

void Display::clearFormat(){
    _oldFormatting = _formatting;
    _formatting = "\033[0m";

    cout << "\033[0m";
}

/* =========================================================
SPLASH TEXT HELPERS
========================================================= */

/**
 * @brief Sets the splash text to be displayed at the top or bottom of the screen.
 * @param str The splash text to display.
 */
void Display::setSplash(string str)
{
    _splash = "<< " + str + " >>";
}

/**
 * @brief Clears the splash text from the screen.
 */
void Display::clearSplash()
{
    _splash = "";
}

/* =========================================================
STAGE TIMER IN ASCII
========================================================= */

/**
 * @brief Converts the timer values into an ASCII representation and stages it for display.
 * @param hours The number of hours.
 * @param minutes The number of minutes.
 * @param seconds The number of seconds.
 * @param tenths The number of tenths of a second.
 */
void Display::stageTimerDisplay(int hours, int minutes, int seconds, int tenths)
{
    string to_print = "";

    // Only display hours if there is at least 1 hour left
    if (hours != 0)
    {
        to_print += to_string(hours) + ":";
    }

    // Add leading zero to minutes if needed
    if (int(minutes / 10) != 0)
    {
        to_print += to_string(minutes) + ":";
    }
    else
    {
        to_print += "0" + to_string(minutes) + ":";
    }

    // Add leading zero to seconds if needed
    if (int(seconds / 10) != 0)
    {
        to_print += to_string(seconds);
    }
    else
    {
        to_print += "0" + to_string(seconds);
    }  

    // Build the ASCII art for the timer display
    for (int i = 0; i < ASCII_HEIGHT; i++)
    {
        string line;
        for (char ch : to_print)
        {
            if (ch == ':')
            {
                line += _currFont.at(10)[i]; // Colon character
                line += PADDING;
            }
            else if (ch == '.')
            {
                line += _currFont.at(11)[i]; // Period character
                line += PADDING;
            }
            else
            {
                line += _currFont.at(ch - '0')[i]; // Numeric character
                line += PADDING;
            }
        }
        _asciiWidth = line.length(); // Update ASCII width
        _asciiBuffer += (line + "\n");
    }
}

/**
 * @brief Converts the alarm time into an ASCII representation and stages it for display.
 * @param time The alarm time string in "HH:MM" format.
 */
void Display::stageAlarmDisplay(string time){

    string to_print = "";

    int hours = stoi(time.substr(0,2));
    int minutes = stoi(time.substr(3,2));

    // Determine AM/PM and convert 24-hour format to 12-hour format
    string period = (hours >= 12) ? "pm" : "am";
    hours = hours % 12; // Convert 24-hour to 12-hour format
    if (hours == 0) { hours = 12; } // Handle the case where hour is 0 (midnight or noon)

    to_print += to_string(hours) + ":";

    // Add leading zero to minutes if needed
    if (int(minutes / 10) != 0)
    {
        to_print += to_string(minutes);
    }
    else
    {
        to_print += "0" + to_string(minutes);
    }

    // Add " am" or " pm"
    to_print += period;


    // Build the ASCII art for the alarm display
    for (int i = 0; i < ASCII_HEIGHT; i++)
    {
        string line;
        for (char ch : to_print)
        {
            if (ch == ':')
            {
                line += _currFont.at(10)[i];
                line += PADDING;
            }
            else if (ch == 'a')
            {
                line += _currFont.at(12)[i];
                line += PADDING;
            }
            else if (ch == 'p')
            {
                line += _currFont.at(13)[i];
                line += PADDING;
            }
            else if (ch == 'm')
            {
                line += _currFont.at(14)[i];
                line += PADDING;
            }
            else
            {
                line += _currFont.at(ch - '0')[i];
                line += PADDING;
            }
        }
        _asciiWidth = line.length();
        _asciiBuffer += (line + "\n");
    }
}

/**
 * @brief Creates a visual progress bar for the timer based on the percentage completed.
 * @param percentage The percentage of completion.
 */
void Display::stageTimerBar(double percentage)
{
    int width = _asciiWidth - 2;
    int filled = (int)((percentage / 100) * width);

    string border = "";

    // Build the top and bottom borders of the bar
    border += "+";
    for (int i = 0; i < width; ++i)
    {
        border += "-";
    }
    border += "+\n";

    _barBuffer += border;

    _barBuffer += "|";

    // Fill the bar with '#' characters based on the percentage completed
    for (int i = 0; i < width; ++i)
    {
        if (i < filled)
        {
            _barBuffer += "#";
        }
        else
        {
            _barBuffer += " ";
        }
    }

    _barBuffer += "|\n";
    _barBuffer += border;
}

/**
 * @brief Creates a visual progress bar for the alarm based on the percentage completed.
 * @param percentage The percentage of completion.
 */
void Display::stageAlarmBar(double percentage)
{
    int width = _asciiWidth - 2;
    int filled = (int)((percentage / 100) * width);

    string border = "";

    // Build the top and bottom borders of the bar
    border += "+";
    for (int i = 0; i < width; ++i)
    {
        border += "-";
    }
    border += "+\n";

    _barBuffer += border;

    _barBuffer += "|";

    // Fill the bar with '#' characters based on the percentage completed
    for (int i = 0; i < width; ++i)
    {
        if (i < filled)
        {
            _barBuffer += "#";
        }
        else
        {
            _barBuffer += " ";
        }
    }

    _barBuffer += "|\n";
    _barBuffer += border;
    
}

/**
 * @brief Stages vector<string> ascii art to be displayed in the terminal.
 */
void Display::stageArt(vector<string> art)
{
    for(int i=0; i<art.size(); ++i){
        _controlBuffer += (art.at(i) + "\n");
    }
}

/* =========================================================
STAGE STOPWATCH IN ASCII
========================================================= */

/**
 * @brief Converts the stopwatch values into an ASCII representation and stages it for display.
 * @param hours The number of hours.
 * @param minutes The number of minutes.
 * @param seconds The number of seconds.
 * @param hundredths The number of hundredths of a second.
 */
void Display::stageStopwatchDisplay(int hours, int minutes, int seconds, int hundredths)
{
    string to_print = "";

    // Only show hours if there are more than 0
    if (hours != 0)
    {
        to_print += to_string(hours) + ":";
    }

    // Show minutes with a leading zero if needed
    if (hours)
    {
        if (int(minutes / 10) != 0)
        {
            to_print += to_string(minutes) + ":";
        }
        else
        {
            to_print += "0" + to_string(minutes) + ":";
        }
    }
    else if (minutes)
    {
        to_print += to_string(minutes) + ":";
    }

    // Show seconds with a leading zero if needed
    if (hours || minutes)
    {
        if (int(seconds / 10) != 0)
        {
            to_print += to_string(seconds);
        }
        else
        {
            to_print += "0" + to_string(seconds);
        }
    }
    else
    {
        to_print += to_string(seconds);
    }

    // Show hundredths of a second if there are no hours
    if (hours == 0)
    {
        to_print += ".";
        if (int(hundredths / 10) != 0)
        {
            to_print += to_string(hundredths);
        }
        else
        {
            to_print += "0" + to_string(hundredths);
        }
    }

    // Build the ASCII art for the stopwatch display
    for (int i = 0; i < ASCII_HEIGHT; i++)
    {
        string line;
        for (char ch : to_print)
        {
            if (ch == ':')
            {
                line += _currFont.at(10)[i]; // Colon character
                line += PADDING;
            }
            else if (ch == '.')
            {
                line += _currFont.at(11)[i]; // Period character
                line += PADDING;
            }
            else
            {
                line += _currFont.at(ch - '0')[i]; // Numeric character
                line += PADDING;
            }
        }
        _asciiBuffer += (line + "\n");
    }
}

/**
 * @brief Stages the splits block to be displayed.
 */
void Display::stageStopwatchSplits(vector<int> splits){
    if (!splits.empty()) {
        _splitBuffer += "  SPLITS:\n\n";
        int startIdx = (splits.size() > 10) ? splits.size() - 10 : 0;
        for (int i = startIdx; i < splits.size(); ++i) {

            int milliseconds = splits.at(i);
            int hours = milliseconds / 3600000;
            milliseconds %= 3600000;
            int minutes = milliseconds / 60000;
            milliseconds %= 60000;
            int seconds = milliseconds / 1000;
            milliseconds %= 1000;
            int hundredths = milliseconds / 10;
            string to_print = "";

            // Only show hours if there are more than 0
            if (hours != 0) {
                to_print += to_string(hours) + ":";
            }

            // Show minutes with a leading zero if needed
            if (hours) {
                if (int(minutes / 10) != 0) {
                    to_print += to_string(minutes) + ":";
                } else {
                    to_print += "0" + to_string(minutes) + ":";
                }
            } else if (minutes) {
                to_print += to_string(minutes) + ":";
            }

            // Show seconds with a leading zero if needed
            if (hours || minutes) {
                if (int(seconds / 10) != 0) {
                    to_print += to_string(seconds);
                } else {
                    to_print += "0" + to_string(seconds);
                }
            } else {
                to_print += to_string(seconds);
            }

            // Show hundredths of a second if there are no hours
            if (hours == 0) {
                to_print += ".";
                if (int(hundredths / 10) != 0) {
                    to_print += to_string(hundredths);
                } else {
                    to_print += "0" + to_string(hundredths);
                }
            }
            string fullprint = "Split " + to_string(i + 1) + ": " + to_print + "\n";
            _splitBuffer += fullprint;
        }
    } else {
        _splitBuffer = "";
    }
}

/* =========================================================
PRINTING TO TERMINAL
========================================================= */

/**
 * @brief Prints the ASCII art representation of the timer or stopwatch to the terminal.
 * @param row The row position to print.
 */
void Display::printAscii(int row, string formatting)
{
    setFormat(formatting);

    if (_asciiBuffer != _oldAscii || _formatting != _oldFormatting)
    {
        setCursor(row, 1);
        fast_print(_asciiBuffer);
        _oldAscii = _asciiBuffer;
    }
    _asciiBuffer = "";

    clearFormat();
}

/**
 * @brief Prints the controls for the timer or stopwatch to the terminal.
 * @param row The row position to print.
 */
void Display::printArt(int row, string formatting)
{
    setFormat(formatting);

    if (_controlBuffer != _oldControls || _formatting != _oldFormatting)
    {
        setCursor(row, 1);
        fast_print(_controlBuffer);
        _oldControls = _controlBuffer;
    }
    _controlBuffer = "";

    clearFormat();
}

/**
 * @brief Prints the progress bar for the timer to the terminal.
 * @param row The row position to print.
 */
void Display::printBar(int row, string formatting)
{
    setFormat(formatting);

    if (_barBuffer != _oldBar || _formatting != _oldFormatting)
    {
        setCursor(row, 1);
        fast_print(_barBuffer);
        _oldBar = _barBuffer;
    }
    _barBuffer = "";

    clearFormat();
}

/**
 * @brief Prints the splash text to the terminal.
 * @param row The row position to print.
 */
void Display::printSplash(int row, string formatting)
{
    setFormat(formatting);

    if (_splash != _oldSplash || _formatting != _oldFormatting)
    {
        clearLine(row);
        setCursor(row, 1);
        fast_print(_splash);
        _oldSplash = _splash;
    }

    clearFormat();
}

/**
 * @brief Prints the stopwatch splits to the terminal.
 * @param row The row position to print.
 */
void Display::printSplits(int row, string formatting)
{
    setFormat(formatting);
    if (_splitBuffer != _oldSplits || _formatting != _oldFormatting)
    {
        setCursor(row, 1);
        fast_print(_splitBuffer);
        _oldSplits = _splitBuffer;
    }
    _splitBuffer = "";
    
    clearFormat();
}

/**
 * @brief Updates the timer setup display, showing the current input with a blinking cursor.
 * @param to_print The current timer setup input string.
 */
void Display::tickTimerSetup(string to_print)
{
    auto now = std::chrono::steady_clock::now();
    auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();

    bool showBar = ((millis / 500) % 2 == 0);

    _asciiBuffer.clear(); // Clear buffer before filling it with new content

    for (int i = 0; i < ASCII_HEIGHT; ++i)
    {
        string line;
        for (char ch : to_print)
        {
            if (ch == ':')
            {
                line += _currFont.at(10)[i]; // Colon character
            }
            else
            {
                line += _currFont.at(ch - '0')[i]; // Numeric character
            }
            line += PADDING;
        }
        line += showBar ? " |" : "   "; // Append progress bar indicator
        _asciiWidth = line.length();
        _asciiBuffer += (line + "\n");
    }
    stageArt(_timerSetupControls);

    printArt(1, BOLD_CYAN);
    printAscii(5, BOLD_WHITE);
    

    setCursor(1,1);

}

/**
 * @brief Updates the alarm setup display, showing the current input with a blinking cursor.
 * @param to_print The current alarm setup input string.
 */
void Display::tickAlarmSetup(string to_print)
{
    auto now = std::chrono::steady_clock::now();
    auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();

    bool showBar = ((millis / 500) % 2 == 0);

    for (int i = 0; i < ASCII_HEIGHT; i++)
    {
        string line;
        for (char ch : to_print)
        {
            if (ch == ':')
            {
                line += _currFont.at(10)[i]; // Colon character
                line += PADDING;
            }
            else
            {
                line += _currFont.at(ch - '0')[i]; // Numeric character
                line += PADDING;
            }
        }

        if(showBar){
            line += " |";
        }

        else{
            line += "   ";
        }

        _asciiWidth = line.length(); // Update ASCII width
        _asciiBuffer += (line + "\n");

    }

    stageArt(_alarmSetupControls);

    printArt(1, BOLD_CYAN);

    printAscii(5,BOLD_WHITE);
    

    setCursor(1,1);

}

/**
 * @brief Updates the timer display on each tick, converting time into ASCII and updating the terminal.
 * @param timer The Timer object to get the remaining time from.
 */
void Display::tickTimer(Timer &timer)
{
    int remaining = timer.remainingMilliseconds();
    int hours = remaining / 3600000;
    remaining %= 3600000;
    int minutes = remaining / 60000;
    remaining %= 60000;
    int seconds = remaining / 1000;
    remaining %= 1000;
    int tenths = remaining / 100;

    stageTimerDisplay(hours, minutes, seconds, tenths);
    stageTimerBar(timer.percentElapsed());
    stageArt(_timerControls);

    string temp;
    if(!timer.isRunning()){
        temp = BOLD_RED;
    }
    else{
        temp = BOLD_WHITE;
    }

    printAscii(1, temp);
    printBar(ASCII_HEIGHT+2, temp);
    printArt(ASCII_HEIGHT+5, BOLD_CYAN);
    printSplash(ASCII_HEIGHT+8, WHITE);

    setCursor(1,1);
}

/**
 * @brief Updates the stopwatch display on each tick, converting time into ASCII and updating the terminal.
 * @param stopwatch The Stopwatch object to get the current time from.
 */
void Display::tickStopwatch(Stopwatch &stopwatch){

    int milliseconds = stopwatch.currentMilliseconds();

    int hours = milliseconds / 3600000;
    milliseconds %= 3600000;
    int minutes = milliseconds / 60000;
    milliseconds %= 60000;
    int seconds = milliseconds / 1000;
    milliseconds %= 1000;
    int hundredths = milliseconds / 10;

    stageStopwatchDisplay(hours, minutes, seconds, hundredths);
    stageArt(_stopwatchControls);
    stageStopwatchSplits(stopwatch.getSplits());

    string temp;
    if(!stopwatch.isRunning()){
        if ((stopwatch.currentMilliseconds() / 10) % 100 == 0 && stopwatch.currentMilliseconds() != 0){
            temp = BOLD_GREEN;
        }   
        else{
            temp = BOLD_RED;
        }
    }
    else{
        temp = BOLD_WHITE;
    }
    printAscii(1, temp);

    printArt(ASCII_HEIGHT+2, BOLD_CYAN);
    printSplash(ASCII_HEIGHT+5, WHITE);
    printSplits(ASCII_HEIGHT+7, WHITE);

    clearFormat();
    setCursor(1,1);

}

/**
 * @brief Updates the alarm display on each tick, showing the alarm time and progress bar.
 * @param alarm The Alarm object to get the alarm time and progress from.
 */
void Display::tickAlarm(Alarm &alarm){

    string time = alarm.timeToString(alarm.getEndTime()).substr(0,5);

    stageAlarmDisplay(time);
    stageAlarmBar(alarm.percentElapsed());
    stageArt(_alarmControls);

    string temp;
    if(alarm.isDone()){
        temp = BOLD_RED;
    }
    else{
        temp = BOLD_WHITE;
    }
    printAscii(1, temp);
    printBar(ASCII_HEIGHT+2, temp);

    printArt(ASCII_HEIGHT+5, BOLD_CYAN);
    printSplash(ASCII_HEIGHT+8, WHITE);
    
    clearFormat();
    setCursor(1,1);

    return;

}

