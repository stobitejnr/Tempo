#ifndef NOTIFICATION_HPP
#define NOTIFICATION_HPP

#include<string>

using namespace std;

class Notification {

public:

    Notification(string title, string body);

    void showNotification(const string& title, const string&  body);
    
private:

};

#endif