#include <cassert>
#include <iostream>
#include <chrono>
#include <thread>

#include "../include/Notification.hpp"

using namespace std;

void test_notify(){

    Notification noti("test", "test");
}


int main() {
    try {
        test_notify();
        cout << "All tests passed successfully!\n";
    } catch (const exception& e) {
        cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}