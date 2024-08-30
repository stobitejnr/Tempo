#include <cassert>
#include <iostream>
#include <chrono>
#include <thread>

#include "../include/Alarm.hpp"

using namespace std;


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
