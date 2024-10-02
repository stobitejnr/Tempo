#ifndef NOTIFICATION_HPP
#define NOTIFICATION_HPP

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <shellapi.h>
#include <cstring>
#include <thread>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <sstream>

using namespace std;

class Notification {

public:

    Notification(string title, string body);

    void showNotification(const char* title, const char* body);
    
private:

};

#endif