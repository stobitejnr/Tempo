#include <windows.h>
#include <iostream>
#include <string>
#include <cstdlib>

#include "../include/Notification.hpp"
#include "Notification.hpp"

using namespace std;

Notification::Notification(string title, string body) {
    showNotification(title, body);
}

void Notification::showNotification(const string& title, const string& body) {
    // Prepare the PowerShell command with parameters
    string powershellCommand = "powershell.exe -ExecutionPolicy Bypass -File \"J:\\COSC345\\Tempo\\src\\notification.ps1\" -title \"" + title + "\" -message \"" + body + "\"";

    // Set up the structures
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // This hides the PowerShell window
    si.dwFlags = STARTF_USESHOWWINDOW;
    si.wShowWindow = SW_HIDE;

    // Create the process
    if (!CreateProcess(NULL, 
        const_cast<char*>(powershellCommand.c_str()),  // Command line
        NULL,           // Process handle not inheritable
        NULL,           // Thread handle not inheritable
        FALSE,          // No handle inheritance
        0,              // No creation flags
        NULL,           // Use parent's environment block
        NULL,           // Use parent's starting directory
        &si,            // Pointer to STARTUPINFO (to hide window)
        &pi)            // Pointer to PROCESS_INFORMATION
    ) {
        std::cerr << "CreateProcess failed: " << GetLastError() << std::endl;
        return;
    }

    // Close process and thread handles immediately (since the process runs in background)
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return;
}