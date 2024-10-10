#include <windows.h>
#include <shellapi.h>
#include <cstring>
#include <thread>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <sstream>
#include <cstdlib>

#include "../include/Notification.hpp"
#include "Notification.hpp"

using namespace std;

Notification::Notification(string title, string body) {
    showNotification();
}

void Notification::showNotification() {
    const char* powershellCommand = "powershell.exe -ExecutionPolicy Bypass -File \"J:\\COSC345\\Tempo\\src\\notification.ps1";
    
    int result = system(powershellCommand);

}
