#include "../include/Notification.hpp"

using namespace std;

Notification::Notification(string title, string body) {
    showNotification(title.c_str(), body.c_str());
}

void Notification::showNotification(const char* title, const char* body) {

    NOTIFYICONDATAA nid = { 0 };
    nid.cbSize = sizeof(NOTIFYICONDATAA);
    nid.hWnd = nullptr; // Set a valid HWND if possible (or create one)
    nid.uFlags = NIF_INFO | NIF_MESSAGE | NIF_TIP | NIF_ICON;
    nid.uCallbackMessage = WM_USER + 1; // Custom message identifier for tray interaction
    nid.hIcon = LoadIcon(NULL, IDI_APPLICATION); // Default icon

    strcpy_s(nid.szTip, title);    // Tooltip text
    strcpy_s(nid.szInfo, body);    // Notification text
    strcpy_s(nid.szInfoTitle, "Tempo");  // Notification title

    // Remove any existing icon before adding a new one
    Shell_NotifyIconA(NIM_DELETE, &nid);

    // Add the icon to the system tray
    if (!Shell_NotifyIconA(NIM_ADD, &nid)) {
        MessageBoxA(NULL, "Failed to add the tray icon.", "Error", MB_OK | MB_ICONERROR);
        return;  // Exit the function if the tray icon fails to add
    }

    // Show the notification
    if (!Shell_NotifyIconA(NIM_MODIFY, &nid)) {
        MessageBoxA(NULL, "Failed to modify the tray icon.", "Error", MB_OK | MB_ICONERROR);
    }

    // Keeping the application running to show the notification.
    Sleep(5000);

    // Clean up: remove the tray icon
    Shell_NotifyIconA(NIM_DELETE, &nid); 
}
