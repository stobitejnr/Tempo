#ifndef STOPWATCH_HPP
#define STOPWATCH_HPP

#include <chrono>
#include <iostream>

using namespace std;

/**
 * @brief The Stopwatch class provides a simple timer with start, pause, resume, and reset functionalities.
 */
class Stopwatch
{
public:
    /**
     * @brief Default constructor initializes a Stopwatch with 0 milliseconds and not running.
     */
    Stopwatch();

    /**
     * @brief Constructor initializes a Stopwatch with a specified time (in hours, minutes, and seconds).
     *
     * @param hours The number of hours to set.
     * @param minutes The number of minutes to set.
     * @param seconds The number of seconds to set.
     */
    Stopwatch(int hours, int minutes, int seconds);

    /**
     * @brief Starts the stopwatch.
     *
     * If the stopwatch is already running, this function does nothing.
     */
    void start();

    /**
     * @brief Records and prints the current split time in milliseconds.
     *
     * A split time is a snapshot of the time elapsed, which can be useful for time intervals
     * without stopping the stopwatch.
     */
    void split();

    /**
     * @brief Pauses the stopwatch.
     *
     * Stops the time count until resumed. The current time is recorded.
     */
    void pause();

    /**
     * @brief Resumes the stopwatch from the last paused time.
     */
    void resume();

    /**
     * @brief Resets the stopwatch to 0 milliseconds and stops it.
     */
    void reset();

    /**
     * @brief Checks if the stopwatch is currently running.
     *
     * @return bool True if the stopwatch is running, false otherwise.
     */
    bool isRunning();

    /**
     * @brief Returns the current elapsed time in milliseconds.
     *
     * If the stopwatch is running, this includes the time since it was started; otherwise, it returns
     * the last recorded time.
     *
     * @return int The current elapsed time in milliseconds.
     */
    int currentMilliseconds();

private:
    int _currMilliseconds;  ///< The current elapsed time in milliseconds.

    bool _running;  ///< Indicates whether the stopwatch is currently running.

    chrono::time_point<chrono::steady_clock> _startTime;  ///< The time point when the stopwatch was started.
    chrono::time_point<chrono::steady_clock> _pauseTime;  ///< The time point when the stopwatch was paused.
};

#endif // STOPWATCH_HPP
