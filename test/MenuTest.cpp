#include <cassert>
#include <iostream>
#include <chrono>
#include <thread>

#include "../include/Menu.hpp"

using namespace std;

void test_menu(){
    Menu menu(true);
    menu.start();
    cout << "start passed." << endl;
    menu.mainMenu();
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