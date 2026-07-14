#include <bits/stdc++.h>
using namespace std;

// 1. Strategy interface
class PaymentStrategy {
public:
  virtual ~PaymentStrategy() {}
  virtual void pay(double amount) = 0;
};

// 2. Concrete strategies
class CreditCardPayment : public PaymentStrategy {
  string cardNumber;

public:
  CreditCardPayment(const string &card) : cardNumber(card) {}
  void pay(double amount) override {
    cout << "Paid $" << amount << " via Credit Card: " << cardNumber << "\n";
  }
};

class PayPalPayment : public PaymentStrategy {
  string email;

public:
  PayPalPayment(const string &mail) : email(mail) {}
  void pay(double amount) override {
    cout << "Paid $" << amount << " via PayPal: " << email << "\n";
  }
};

class UPIPayment : public PaymentStrategy {
  string upiId;

public:
  UPIPayment(const string &id) : upiId(id) {}
  void pay(double amount) override {
    cout << "Paid Rs." << amount << " via UPI: " << upiId << "\n";
  }
};

// 3. Context — holds a raw pointer to a strategy (does NOT own it)
class PaymentProcessor {
  PaymentStrategy *strategy;

public:
  void setStrategy(PaymentStrategy *s) { strategy = s; }

  void processPayment(double amount) {
    if (!strategy) {
      cout << "No payment strategy set!\n";
      return;
    }
    strategy->pay(amount); // use the strategy
  }
};

// 4. Client
int main() {
  // Caller owns the strategy objects (stack-allocated here)
  CreditCardPayment *cc = new CreditCardPayment("1234-5678-9012-3456");
  PayPalPayment *pp = new PayPalPayment("sagar@example.com");
  UPIPayment *upi = new UPIPayment("sagar@upi");

  PaymentProcessor *processor = new PaymentProcessor();

  processor->setStrategy(cc);
  processor->processPayment(100.50);

  processor->setStrategy(pp);
  processor->processPayment(50.25);

  processor->setStrategy(upi);
  processor->processPayment(25.00);
  delete cc;
  delete pp;
  delete upi;
  delete processor;

  return 0;
}