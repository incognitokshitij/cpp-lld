

#include <bits/stdc++.h>

using namespace std;

class Account {
public:
  bool verifyAccount(string accountNumber) {
    cout << "Account verified: " << accountNumber << endl;
    return true;
  }
};

class Security {
public:
  bool checkPin(string pin) {
    cout << "PIN verified" << endl;
    return true;
  }
};

class Funds {
public:
  bool hasSufficientFunds(double amount) {
    cout << "Sufficient funds available" << endl;
    return true;
  }
  void debit(double amount) { cout << "Debited: $" << amount << endl; }
};

class Notification {
public:
  void sendNotification(string message) {
    cout << "Notification sent: " << message << endl;
  }
};

// ---- Client without a Facade ----
int main() {
  Account account;
  Security security;
  Funds funds;
  Notification notification;

  double amount = 100.0;

  cout << "Starting Withdrawal Process..." << endl;
  if (account.verifyAccount("ACC123") && security.checkPin("4321") &&
      funds.hasSufficientFunds(amount)) {

    funds.debit(amount);
    notification.sendNotification("Withdrawal of $" + to_string(amount) +
                                  " successful.");
  } else {
    cout << "Withdrawal Failed!" << endl;
  }
  return 0;
}