#include "../include/Notification.hpp"
#include <shellapi.h>
#include <cstring>

using namespace std;

// Constructor definition
Notification::Notification(string title, string body) {
    _title = title;
    _body = body;
    ShowNotification(); // Automatically show notification when object is created
}

void Notification::ShowNotification() {
    // Initialize the NOTIFYICONDATA structure
    NOTIFYICONDATA nid;
    memset(&nid, 0, sizeof(NOTIFYICONDATA));
    nid.cbSize = sizeof(NOTIFYICONDATA);
    nid.hWnd = nullptr;  // No window handle needed
    nid.uID = 100;       // Unique ID for the notification
    nid.uFlags = NIF_INFO;  // Use NIF_INFO to show the balloon
    strcpy_s(nid.szInfoTitle, _title.c_str());  // Set the notification title
    strcpy_s(nid.szInfo, _body.c_str());        // Set the notification body

    // Set icon for the notification (optional, default system icon)
    nid.hIcon = LoadIcon(NULL, IDI_APPLICATION);

    // Display the notification
    Shell_NotifyIcon(NIM_ADD, &nid);

    // Wait for the balloon to display for 5 seconds (adjustable)
    Sleep(5000);

    // Remove the notification after display
    Shell_NotifyIcon(NIM_DELETE, &nid);
}
