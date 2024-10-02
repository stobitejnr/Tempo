#ifndef NOTIFICATION_HPP
#define NOTIFICATION_HPP

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <string>

using namespace std;

class Notification {
public:
    // Constructor
    Notification(string title, string body);

    // Show a tray notification
    void ShowNotification();

private:
    string _title;
    string _body;
};

#endif // NOTIFICATION_HPP
