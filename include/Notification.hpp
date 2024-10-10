#ifndef NOTIFICATION_HPP
#define NOTIFICATION_HPP

#include <string>

using namespace std;

/**
 * @class Notification
 * @brief A class to manage system notifications using PowerShell scripts.
 */
class Notification {

public:

    /**
     * @brief Constructs a Notification object and displays the notification.
     * 
     * @param title The title of the notification.
     * @param body The body message of the notification.
     */
    Notification(string title, string body);

    /**
     * @brief Displays a notification with the given title and body.
     * 
     * @param title The title of the notification.
     * @param body The body message of the notification.
     */
    void showNotification(const string& title, const string& body);

    /**
     * @brief Setups up the environment or configurations needed for notifications.
     * 
     * This static method can be used to initialize any resources required for notifications
     * before creating individual notification instances.
     */
    static void setupNotifications();

private:
    // No private members currently
};

#endif