
#include <bits/stdc++.h>

using namespace std;

class EmailNotification {
public:
  void send(string message) {
    cout << "Sending an Email notification..." << message << endl;
  }
};
class SMSNotification {
public:
  void send(string message) {
    cout << "Sending an Email notification..." << message << endl;
  }
};
class PushNotification {
public:
  void send(string message) {
    cout << "Sending an Email notification..." << message << endl;
  }
};
class SlackNotification {
public:
  void send(string message) {
    cout << "Sending an Email notification..." << message << endl;
  }
};

class NotificationService {
public:
  void sendNotification(const string &type, const string &message) {
    if (type == "EMAIL") {
      EmailNotification email;
      email.send(message);
    } else if (type == "SMS") {
      SMSNotification sms;
      sms.send(message);
    } else if (type == "Push") {
      PushNotification push;
      push.send(message);
    } else if (type == "Slack") {
      SlackNotification slack;
      slack.send(message);
    }
  }
};
int main() {

  NotificationService *nofiy = new NotificationService();

  nofiy->sendNotification("EMAIL", "Hi ");

  return 0;
}