#ifndef TIMER_HPP
#define TIMER_HPP

#include <chrono>
#include <iostream>
#include <regex>

using namespace std;

/**
 * @brief The Timer class provides a countdown timer with start, pause, resume, reset, and time adjustment functionalities.
 */
class Timer
{
public:
    /**
     * @brief Default constructor prompts the user to set a timer with a specific duration.
     *
     * The user can specify the duration in hours, minutes, and seconds. The timer is initialized
     * and started based on the user input.
     */
    Timer();

    /**
     * @brief Constructor to specify the timer duration directly in hours, minutes, and seconds.
     *
     * Initializes and starts the timer with the specified duration.
     *
     * @param hours The number of hours to set.
     * @param minutes The number of minutes to set.
     * @param seconds The number of seconds to set.
     */
    Timer(int hours, int minutes, int seconds);

    /**
     * @brief Starts the timer by setting the end time based on the current time plus the countdown duration.
     *
     * @param countdownMilliseconds The duration for the countdown in milliseconds.
     */
    void start(int countdownMilliseconds);

    /**
     * @brief Pauses the timer and calculates the remaining milliseconds.
     */
    void pause();

    /**
     * @brief Resumes the timer from where it was paused by recalculating the end time.
     */
    void resume();

    /**
     * @brief Resets the timer to its original duration and pauses it.
     */
    void reset();

    void addTime();
    /**
     * @brief Adds a specified amount of time (in seconds) to the timer.
     *
     * If the timer is running, it resumes after adding time.
     *
     * @param seconds The number of seconds to add to the timer.
     */
    void addTime(int seconds);

    /**
     * @brief Allows the user to change the increment time used for adding time to the timer.
     *
     * The increment time can be specified in hours, minutes, or seconds.
     */
    void changeIncrementTime();

    /**
     * @brief Checks if the timer is currently running.
     *
     * @return bool True if the timer is running, false otherwise.
     */
    bool isRunning();

    /**
     * @brief Returns the remaining time in milliseconds.
     *
     * If the timer has expired, it returns 0.
     *
     * @return int The remaining time in milliseconds.
     */
    int remainingMilliseconds();

    /**
     * @brief Returns the percentage of time that has elapsed since the timer started.
     *
     * @return double The percentage of time elapsed.
     */
    double percentElapsed();

private:
    int _startMilliseconds;      ///< The initial duration of the timer in milliseconds.
    int _countdownMilliseconds;  ///< The duration of the countdown in milliseconds.
    int _remainingMilliseconds;  ///< The remaining time in milliseconds.
    int _incrementMilliseconds;  ///< The increment time in milliseconds for adding time.

    bool _running;  ///< Indicates whether the timer is currently running.

    chrono::time_point<chrono::steady_clock> _endTime;  ///< The time point when the timer will end.
    chrono::time_point<chrono::steady_clock> _pauseTime; ///< The time point when the timer was paused.
};

#endif // TIMER_HPP
