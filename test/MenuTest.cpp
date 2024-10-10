#include <cassert>
#include <iostream>
#include <chrono>
#include <thread>

#include "../include/Menu.hpp"

using namespace std;

void test_menu(){
    Menu menu(true);
    menu.saveSettings();
    menu.loadSettings();
    menu.settingsMenu(1);
    menu.settingsMenu(2);
    menu.settingsMenu(3);
    int select = 0;
    char ch = menu.getSettingsInput(select);
    char ch = menu.getSettingsInput(select);
    return;
}


int main() {
    try {
        test_menu();

        cout << "All tests passed successfully!\n";
    } catch (const exception& e) {
        cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}