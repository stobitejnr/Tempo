#include <cassert>
#include <thread>

#include "../include/Stopwatch.hpp"

using namespace std;

void test_constructor() {
    Stopwatch stopwatch(0,0,0);
    assert(stopwatch.currentMilliseconds() == 0);
    assert(stopwatch.isRunning());
    cout << "Constructor test passed.\n";
}

void test_pause_resume() {
    Stopwatch stopwatch(0, 1, 0); // 1 minute
    std::this_thread::sleep_for(chrono::seconds(1));
    stopwatch.pause();
    int currentAfterPause = stopwatch.currentMilliseconds();
    assert(!stopwatch.isRunning());
    std::this_thread::sleep_for(chrono::seconds(1));
    assert(stopwatch.currentMilliseconds() == currentAfterPause);
    stopwatch.resume();
    assert(stopwatch.isRunning());
    assert(stopwatch.currentMilliseconds() > 59000);
    cout << "Pause and resume test passed.\n";
}

void test_reset() {
    Stopwatch stopwatch(0, 1, 0); // 1 minute
    std::this_thread::sleep_for(chrono::seconds(1));
    stopwatch.reset();
    assert(stopwatch.currentMilliseconds() == 0);
    assert(!stopwatch.isRunning());
    cout << "Reset test passed.\n";
}

void test_splits() {
    Stopwatch stopwatch(0, 0, 0);
    std::this_thread::sleep_for(chrono::seconds(1));
    stopwatch.addSplit();
    assert(stopwatch.getSplits().at(0) == 1000);
    stopwatch.clearSplits();
    assert(stopwatch.getSplits().empty());
    cout << "Split tests passed.\n";
}

int main() {
    try {
        test_constructor();
        test_pause_resume();
        test_reset();
        test_splits();
        cout << "All tests passed successfully!\n";
    } 
    catch (const exception& e) {
        cerr << "Test failed with exception: " << e.what() << endl;
        return 1;
    }
    return 0;
}
