#include <cassert>
#include <iostream>
#include <chrono>
#include <thread>

#include "../include/Alarm.hpp"

using namespace std;

void test_constructor(){
    //Alarm alarm(0,0);
}


int main() {
    try {
        test_constructor();
        cout << "All tests passed successfully!\n";
    } catch (const exception& e) {
        cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}