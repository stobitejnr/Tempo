#include <windows.h>
#include <shellapi.h>

/* =========================================================
CONSTANTS
========================================================= */

#define WM_TRAYICON (WM_USER + 1)

/* =========================================================
WINDOW PROCEDURE
========================================================= */

/**
 * @brief Window procedure for handling messages.
 * 
 * This function processes messages sent to the window, including custom tray icon messages and window destruction.
 * 
 * @param hwnd Handle to the window.
 * @param message The message identifier.
 * @param wParam Additional message information.
 * @param lParam Additional message information.
 * @return LRESULT The result of the message processing.
 */
LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
        case WM_TRAYICON:
            if (lParam == WM_LBUTTONUP) {
                MessageBox(NULL, "You clicked the notification icon!", "Notification", MB_OK);
            }
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, message, wParam, lParam);
    }
    return 0;
}

/* =========================================================
SHOW NOTIFICATION
========================================================= */

/**
 * @brief Shows a notification in the system tray.
 * 
 * This function adds a notification icon to the system tray and displays a notification message.
 * 
 * @param hInstance Handle to the application instance.
 * @param hwnd Handle to the window.
 */
void ShowNotification(HINSTANCE hInstance, HWND hwnd) {
    NOTIFYICONDATA nid = { 0 };
    nid.cbSize = sizeof(nid);
    nid.hWnd = hwnd;
    nid.uID = 1001;
    nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP | NIF_INFO;
    nid.uCallbackMessage = WM_TRAYICON; // Custom message for icon interactions
    nid.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    strcpy_s(nid.szTip, "My Notification App");
    strcpy_s(nid.szInfo, "Hello! This is your notification.");
    strcpy_s(nid.szInfoTitle, "Notification Title");
    nid.dwInfoFlags = NIIF_INFO;

    Shell_NotifyIcon(NIM_ADD, &nid);
}

/* =========================================================
WINMAIN
========================================================= */

/**
 * @brief Entry point for the Windows application.
 * 
 * This function initializes the application, creates a window, and enters the message loop.
 * 
 * @param hInstance Handle to the application instance.
 * @param hPrevInstance Handle to the previous instance (always NULL for Win32).
 * @param lpCmdLine Command line arguments.
 * @param nCmdShow How the window should be shown.
 * @return int The exit code of the application.
 */
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    const char CLASS_NAME[] = "NotificationApp";

    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = WindowProcedure;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(0, CLASS_NAME, "Notification Window", 0, 0, 0, 0, 0, NULL, NULL, hInstance, NULL);

    if (hwnd == NULL) {
        return 0;
    }

    ShowNotification(hInstance, hwnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
