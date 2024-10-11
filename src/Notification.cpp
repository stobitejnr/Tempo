/**
 * @file Notification.cpp
 * @brief Implementation of the Notification class to display system notifications.
 */

#include <windows.h>
#include <iostream>
#include <string>
#include <cstdlib>

#include "../include/Notification.hpp"
#include "Notification.hpp"

using namespace std;

/**
 * @class Notification
 * @brief A class to handle system notifications using PowerShell scripts.
 */

/**
 * @brief Constructor that creates a Notification object and shows the notification.
 * 
 * @param title The title of the notification.
 * @param body The body message of the notification.
 */
Notification::Notification(string title, string body) {
    showNotification(title, body);
}

/**
 * @brief Displays a notification using PowerShell with the given title and body.
 * 
 * This method constructs the path to the PowerShell script and an image file,
 * then creates a hidden process to execute the PowerShell command that shows
 * the notification.
 * 
 * @param title The title of the notification.
 * @param body The body message of the notification.
 */
void Notification::showNotification(const string& title, const string& body) {
    // Get the path to the executable's directory
    char executablePath[MAX_PATH];
    GetModuleFileName(NULL, executablePath, MAX_PATH);

    // Extract the directory from the executable's path
    string path(executablePath);
    size_t lastSlash = path.find_last_of("\\/");
    string directory = path.substr(0, lastSlash);

    // Construct the relative path to the PowerShell script and resolve it to an absolute path
    char fullScriptPath[MAX_PATH];
    if (_fullpath(fullScriptPath, (directory + "\\..\\script\\notification.ps1").c_str(), MAX_PATH)) {
        string scriptPath(fullScriptPath);
        
        // Similarly, resolve the image path to an absolute path
        char fullImagePath[MAX_PATH];
        if (_fullpath(fullImagePath, (directory + "\\..\\logo.png").c_str(), MAX_PATH)) {
            string imagePath(fullImagePath);

            // Prepare the PowerShell command with parameters
            string powershellCommand = "powershell.exe -ExecutionPolicy Bypass -File \"" + scriptPath + 
                                       "\" -title \"" + title + 
                                       "\" -message \"" + body +
                                       "\" -imagePath \"" + imagePath + "\"";

            // Set up the structures for creating the hidden process
            STARTUPINFO si;
            PROCESS_INFORMATION pi;

            ZeroMemory(&si, sizeof(si));
            si.cb = sizeof(si);
            ZeroMemory(&pi, sizeof(pi));

            // This hides the PowerShell window
            si.dwFlags = STARTF_USESHOWWINDOW;
            si.wShowWindow = SW_HIDE;

            // Create the process to run the PowerShell command
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
        } else {
            cerr << "Failed to resolve absolute path for logo.png" << endl;
        }
    } else {
        cerr << "Failed to resolve absolute path for notification.ps1" << endl;
    }

    return;
}
