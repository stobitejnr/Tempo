#include <windows.h>
#include <shellapi.h>
#include <cstring>
#include <thread>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <sstream>

#include "../include/Notification.hpp"

using namespace std;

Notification::Notification(string title, string body) {
    showNotification(title.c_str(), body.c_str());
}

void Notification::showNotification(const char* title, const char* body) {

    HWND hWnd = CreateWindowA(
        "STATIC", 
        "HiddenWindow", 
        WS_OVERLAPPEDWINDOW,
        0, 0, 100, 100, 
        nullptr, nullptr, nullptr, nullptr);

    if (!hWnd) {
        MessageBoxA(NULL, "Failed to create hidden window.", "Error", MB_OK | MB_ICONERROR);
        return;
    }

    NOTIFYICONDATAA nid = { 0 };
    nid.cbSize = sizeof(NOTIFYICONDATAA);
    nid.hWnd = hWnd;  
    nid.uFlags = NIF_INFO | NIF_MESSAGE | NIF_TIP | NIF_ICON;
    nid.uCallbackMessage = WM_USER + 1; 
    nid.hIcon = LoadIcon(NULL, IDI_APPLICATION); 
    strcpy_s(nid.szTip, title); 
    strcpy_s(nid.szInfo, body); 
    strcpy_s(nid.szInfoTitle, "Tempo"); 

    Shell_NotifyIconA(NIM_DELETE, &nid);

    if (!Shell_NotifyIconA(NIM_ADD, &nid)) {
        MessageBoxA(NULL, "Failed to add the tray icon.", "Error", MB_OK | MB_ICONERROR);
        DestroyWindow(hWnd);
        return;  
    }

    if (!Shell_NotifyIconA(NIM_MODIFY, &nid)) {
        MessageBoxA(NULL, "Failed to modify the tray icon.", "Error", MB_OK | MB_ICONERROR);
        Shell_NotifyIconA(NIM_DELETE, &nid);
        DestroyWindow(hWnd);
        return;
    }

    Sleep(5000); 

    Shell_NotifyIconA(NIM_DELETE, &nid);
    DestroyWindow(hWnd);  
}
