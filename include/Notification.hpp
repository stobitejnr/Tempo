#ifndef NOTIFICATION_HPP
#define NOTIFICATION_HPP

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
void ShowTrayNotification(string info, string title, int duration);
Notification(string info, string title, int duration);
private:

};

#endif