#include <iostream>
using namespace std;

// ---------- Subsystem classes (unchanged) ----------

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

// ---------- Facade ----------

class BankFacade {
private:
  Account account;
  Security security;
  Funds funds;
  Notification notification;

public:
  void withdraw(string accNo, string pin, double amount) {
    cout << "Starting Withdrawal Process..." << endl;
    if (account.verifyAccount(accNo) && security.checkPin(pin) &&
        funds.hasSufficientFunds(amount)) {

      funds.debit(amount);
      notification.sendNotification("Withdrawal of $" + to_string(amount) +
                                    " successful.");
    } else {
      cout << "Withdrawal Failed!" << endl;
    }
  }
};

// ---------- Client ----------

int main() {
  BankFacade bank;
  bank.withdraw("ACC123", "4321", 100.0);
  return 0;
}