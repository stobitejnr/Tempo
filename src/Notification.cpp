#include "../include/Notification.hpp"

using namespace std;

void ShowTrayNotification(string info, string title, int duration) {
    NOTIFYICONDATAA nid = { };
    nid.cbSize = sizeof(NOTIFYICONDATAA);
    nid.hWnd = nullptr; // You need to set a valid window handle here if you have one
    nid.uFlags = NIF_INFO | NIF_MESSAGE | NIF_TIP | NIF_ICON;
    nid.uCallbackMessage = WM_USER + 1; // Custom message identifier for tray interaction
    nid.hIcon = LoadIcon(NULL, IDI_APPLICATION); // Default icon


    strcpy_s(nid.szTip, title.c_str()); // Tooltip text
    strcpy_s(nid.szInfo, info.c_str()); // Notification text
    strcpy_s(nid.szInfoTitle, "Tempo"); // Set the title to "tempo"

    // Remove any existing icon before adding a new one (to avoid conflicts)
    Shell_NotifyIconA(NIM_DELETE, &nid);

    // Add the icon to the system tray
    if (!Shell_NotifyIconA(NIM_ADD, &nid)) {
        MessageBoxA(NULL, "Failed to add the tray icon.", "Error", MB_OK | MB_ICONERROR);
    }
    
    // Update the icon to show notification (this can be optional)
    if (!Shell_NotifyIconA(NIM_MODIFY, &nid)) {
        MessageBoxA(NULL, "Failed to modify the tray icon.", "Error", MB_OK | MB_ICONERROR);
    }

// Keeping the application running to show the notification.
    Sleep(duration*1000); // 10 seconds delay
    
    NOTIFYICONDATAA nid = { };
    nid.cbSize = sizeof(NOTIFYICONDATAA);
    nid.hWnd = nullptr; 
    Shell_NotifyIconA(NIM_DELETE, &nid); // Clean up tray icon
    

}

Notification::Notification(string info, string title, int duration){
    ShowTrayNotification(info, title, duration);
}
