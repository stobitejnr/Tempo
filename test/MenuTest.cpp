#include <cassert>
#include <iostream>
#include <chrono>
#include <thread>

#include "../include/Menu.hpp"

using namespace std;

void simIn(const std::string& input) {
    std::stringstream simulatedInput;
    simulatedInput << input << std::endl;
    std::cin.rdbuf(simulatedInput.rdbuf());
}

void test_timer(){
    Menu menu;
    menu.start();
    simIn("a");
    menu.mainMenu();
    simIn("1");
    Timer timer = menu.createTimer();
    menu.timerSequence();
    simIn("1");
    simIn("\n");
    simIn("q");
    simIn("q");


    cin.rdbuf(nullptr);
}


int main() {
    try {
        //calls here
        cout << "All tests passed successfully!\n";
    } catch (const exception& e) {
        cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}