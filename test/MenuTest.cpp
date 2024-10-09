#include <cassert>
#include <ctime>
#include <iostream>
#include <sstream>
#include <fstream>
#include <chrono>
#include <thread>

#include "../include/Menu.hpp"

using namespace std;

class MockDisplay: public Display{
public:
    string lastFormat;
    string lastSplash;
    string lastSetup;
    time_t currentTime = time(nullptr);  // Get the current time

    void clearScreen() override{}
    void setFormat(const string& format) override {lastFormat = format;}
    void clearFormat() override { lastFormat.clear();}
    void setCursor(int x, int y) override{}
    void setFont(int font) override{}
    void setSplash(const string message) override {lastSplash = message;}
    void clearSplash() override {lastSplash.clear();}
    void tickTimer(Timer& timer) override {}
    void tickStopwatch(Stopwatch& stopwatch) override {}
    void tickAlarm(Alarm& alarm) override {}
    void tickTimerSetup(const string timer) override{currentTime;}
    void tickAlarmSetup(const string time) override {lastSetup = time;}
    
};

class MockTimer : public Timer {
public:
    bool isRunningCalled = false;
    bool pauseCalled = false;
    bool resumeCalled = false;
    bool resetCalled = false;

    MockTimer() : Timer(0, 0, 1) {}
    bool isRunning() override {return false;}
    void pause() override { pauseCalled = true; Timer::pause(); }
    void resume() override { resumeCalled = true; Timer::resume(); }
    void reset() override { resetCalled = true; Timer::reset(); }
};

class MockStopwatch : public Stopwatch{
public:
    bool isRunningCalled = false;
    bool pasueCalled = false;
    bool resumeCalled = false;
    bool resetCalled = false;
    bool addSplitCalled = false;

    bool isRunning() override{return false;}
    void pause() override{}
    void resume() override{}
    void reset() override{}
    void addSplit() override{}

};

class MockAlarm : public Alarm {
public:
    MockAlarm() : Alarm(0, 1) {}
};

// Helper function to redirect cout
class CoutRedirect {
    streambuf* old;
    stringstream ss;
public:
    CoutRedirect() : old(cout.rdbuf(ss.rdbuf())) {}
    ~CoutRedirect() { cout.rdbuf(old); }
    string str() const { return ss.str(); }
};

// void test_menu(){
//     Menu menu(true);
//     return;
// }

void testMenuConstructor(){
    Menu menu(true);
    assert(menu._run == true);
    assert(menu._testing == true);
    assert(menu._menuFormats.size() == 5);
    assert(menu._settingsFormats.size() == 4);
    assert(menu._notiSetting == true);
    assert(menu._fontSetting == 1);
}

void testLoadSettings() {
    ofstream tempFile("temp_settings.txt");
    tempFile << "2\nfalse\n";
    tempFile.close();

    Menu menu(true);
    menu.loadSettings();
    assert(menu._fontSetting = 2);
    assert(menu._notiSetting == false);

    remove("temp_settings.txt");
}

void testSaveSettings() {
    Menu menu(true);
    menu._fontSetting = 2;
    menu._notiSetting = false;
    menu.saveSettings();

    //reset settings then test to see if save worked
    menu._fontSetting = 1;
    menu._notiSetting = true;
    menu.loadSettings();

    assert(menu._fontSetting == 2);
    assert(menu._notiSetting == false);

    remove ("settings.txt");
}

void testPrintArt() {
    Menu menu(true);
    MockDisplay* mockDisplay = new MockDisplay(); // Create an instance of MockDisplay
    menu._display = *mockDisplay; // Assuming _display can be assigned this way

    vector<string> art = {"Test Art"};
    menu.printArt(art, Display::BOLD_CYAN);

    // Use mockDisplay instead of MockDisplay
    assert(mockDisplay->lastFormat == Display::BOLD_CYAN);

    delete mockDisplay; // Don't forget to delete the allocated memory to avoid memory leaks
}

void testCredits() {
    Menu menu(true);
    MockDisplay* mockDisplay = new MockDisplay();
    menu._display = *mockDisplay;

    CoutRedirect cr;
    menu.credits();

    string output = cr.str();
    assert(output.find("PRESS ANY KEY TO CONTINUE") != string::npos);
}

void testCreateTimer(){
    Menu menu(true);
    bool run = true;
    Timer timer = menu.createTimer(run);
    assert(timer.remainingMilliseconds() == 1000);

}

void testCreateAlarm() {
    Menu menu(true);
    bool run = true;
    Alarm alarm = menu.createAlarm(run);
    assert(alarm.remainingMilliseconds() == 60000);
}

void testWait(){
    Menu menu(true);
    auto start = chrono::high_resolution_clock::now();
    menu.wait(0.1);
    auto end(chrono::high_resolution_clock::now());
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    assert(duration.count() >= 100);

}

void testCheckTimerInput(){
    Menu menu(true);
    MockTimer mockTimer;
    bool run = true;

    menu.checkTimerInput(mockTimer, run);
    assert(mockTimer.isRunningCalled);
    assert(mockTimer.pauseCalled || mockTimer.resumeCalled);

    mockTimer = MockTimer();
    menu.checkTimerInput(mockTimer, run);
    assert(!run);
}

void testCheckStopwatchInput(){
    Menu menu(true);
    MockStopwatch mockStopwatch;
    bool run = true;

    menu.checkStopwatchInput(mockStopwatch, run);
    assert(mockStopwatch.isRunningCalled);
    assert(mockStopwatch.pasueCalled || mockStopwatch.resumeCalled);

    mockStopwatch = MockStopwatch();
    menu.checkStopwatchInput(mockStopwatch, run);
    assert(mockStopwatch.addSplitCalled);

    mockStopwatch = MockStopwatch();
    menu.checkStopwatchInput(mockStopwatch, run);
    assert(!run);
}

void testCheckAlarmInput(){
 Menu menu(true);
    MockAlarm mockAlarm;
    bool run = true;

    // Test create new alarm
    menu.checkAlarmInput(mockAlarm, run);
    assert(mockAlarm.remainingMilliseconds() == 60000);  // Assumes the test input sets alarm to 1 minute from now

    // Test quit
    mockAlarm = MockAlarm();
    menu.checkAlarmInput(mockAlarm, run);
    assert(!run);

}

void testGetMenuInput() {
    Menu menu(true);
    int selected = 0;
    char input = menu.getMenuInput(selected);
    assert(input == '1');

}

void testGetSettingsInput(){
    Menu menu(true);
    int selected = 0;
    char input = menu.getSettingsInput(selected);
    assert(input == '1');
}

void testMainMenu(){
    Menu menu(true);
    menu.mainMenu(0);
}



int main() {
    try {
    testMenuConstructor();
    testLoadSettings();
    testSaveSettings();
    testPrintArt();
    testCredits();
    testCreateTimer();
    testCreateAlarm();
    testWait();
    testCheckTimerInput();
    testCheckStopwatchInput();
    testCheckAlarmInput();
    testGetMenuInput();
    testGetSettingsInput();
    // testMainMenu();
    // testSettingsMenu();
    // testTimerSequence();
    // testStopwatchSequence();
    // testAlarmSequence();
        // test_menu();

        cout << "All tests passed successfully!\n";
    } catch (const exception& e) {
        cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    }
    return 0;


}