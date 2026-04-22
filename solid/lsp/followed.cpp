#include <bits/stdc++.h>
using namespace std;

class DepositOnlyAccount {
public:
  virtual void deposit(double amount) = 0;
};

class WithdrawableAccount : public DepositOnlyAccount {
public:
  virtual void withdraw(double amount) = 0;
};

class SavingAccount : public WithdrawableAccount {
private:
  double balance;

public:
  SavingAccount() { this->balance = 0; }

  void deposit(double amount) {
    this->balance += amount;
    cout << "Deposited: " << amount
         << " in Savings Account. New Balance: " << this->balance << endl;
  }

  void withdraw(double amount) {
    if (this->balance >= amount) {
      this->balance -= amount;
      cout << "Withdrawn: " << amount
           << " from Savings Account. New Balance: " << this->balance << endl;
    } else {
      cout << "Insufficient funds in Savings Account!\n";
    }
  }
};

class CurrentAccount : public WithdrawableAccount {
private:
  double balance;

public:
  CurrentAccount() { balance = 0; }

  void deposit(double amount) {
    this->balance += amount;
    cout << "Deposited: " << amount
         << " in Current Account. New Balance: " << this->balance << endl;
  }

  void withdraw(double amount) {
    if (this->balance >= amount) {
      balance -= amount;
      cout << "Withdrawn: " << amount
           << " from Current Account. New Balance: " << this->balance << endl;
    } else {
      cout << "Insufficient funds in Current Account!\n";
    }
  }
};

class FixedTermAccount : public DepositOnlyAccount {
private:
  double balance;

public:
  FixedTermAccount() { this->balance = 0; }

  void deposit(double amount) {
    this->balance += amount;
    cout << "Deposited: " << amount
         << " in Fixed Term Account. New Balance: " << this->balance << endl;
  }
};

class BankClient {
private:
  vector<WithdrawableAccount *> withdrawableAccounts;
  vector<DepositOnlyAccount *> depositOnlyAccounts;

public:
  BankClient(vector<WithdrawableAccount *> withdrawableAccounts,
             vector<DepositOnlyAccount *> depositOnlyAccounts) {
    this->withdrawableAccounts = withdrawableAccounts;
    this->depositOnlyAccounts = depositOnlyAccounts;
  }

  void processTransactions() {
    for (WithdrawableAccount *acc : withdrawableAccounts) {
      acc->deposit(1000);
      acc->withdraw(500);
    }
    for (DepositOnlyAccount *acc : depositOnlyAccounts) {
      acc->deposit(5000);
    }
  }
};

int main() {
  vector<WithdrawableAccount *> withdrawableAccounts;
  withdrawableAccounts.push_back(new SavingAccount());
  withdrawableAccounts.push_back(new CurrentAccount());

  vector<DepositOnlyAccount *> depositOnlyAccounts;
  depositOnlyAccounts.push_back(new FixedTermAccount());

  BankClient *client =
      new BankClient(withdrawableAccounts, depositOnlyAccounts);
  client->processTransactions();

  return 0;
}
