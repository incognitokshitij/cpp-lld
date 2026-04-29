
#include <bits/stdc++.h>

using namespace std;
class Notification {
public:
  virtual void send(const std::string &message) = 0;
  virtual ~Notification() {}
};

class EmailNotification : public Notification {
public:
  void send(const std::string &msg) override {
    std::cout << "Email: " << msg << std::endl;
  }
};

class SMSNotification : public Notification {
public:
  void send(const std::string &msg) override {
    std::cout << "SMS: " << msg << std::endl;
  }
};

class PushNotification : public Notification {
public:
  void send(const std::string &msg) override {
    std::cout << "Push: " << msg << std::endl;
  }
};

class SlackNotification : public Notification {
public:
  void send(const std::string &msg) override {
    std::cout << "Slack: " << msg << std::endl;
  }
};
class NotificationCreator {
public:
  // subclasses decide what object to create
  virtual Notification *createNotification() = 0;

  // shared logic — base class defines the flow
  void send(const std::string &message) {
    Notification *n = createNotification();
    n->send(message);
    delete n;
  }

  virtual ~NotificationCreator() {}
};
class EmailNotificationCreator : public NotificationCreator {
public:
  Notification *createNotification() override {
    return new EmailNotification();
  }
};

class SMSNotificationCreator : public NotificationCreator {
public:
  Notification *createNotification() override { return new SMSNotification(); }
};

class PushNotificationCreator : public NotificationCreator {
public:
  Notification *createNotification() override { return new PushNotification(); }
};

class SlackNotificationCreator : public NotificationCreator {
public:
  Notification *createNotification() override {
    return new SlackNotification();
  }
};
int main() {
  NotificationCreator *creator;

  creator = new EmailNotificationCreator();
  creator->send("Welcome to the platform!");
  delete creator;

  creator = new SMSNotificationCreator();
  creator->send("Your OTP is 123456");
  delete creator;

  creator = new PushNotificationCreator();
  creator->send("You have a new follower!");
  delete creator;

  creator = new SlackNotificationCreator();
  creator->send("Standup in 10 minutes!");
  delete creator;

  return 0;
}