
#include <bits/stdc++.h>

using namespace std;

// ─────────────────────────────────────────
// 1. Target Interface (what YOUR system expects)
// ─────────────────────────────────────────
class PaymentProcessor {
public:
  virtual void processPayment(double amount, string currency) = 0;
  virtual bool isPaymentSuccessful() = 0;
  virtual string getTransactionId() = 0;
};

// ─────────────────────────────────────────
// 2. Your In-House Processor (already works perfectly)
// ─────────────────────────────────────────
class InHouseProcessor : public PaymentProcessor {
public:
  void processPayment(double amount, string currency) override {
    cout << "InHouse: Processing payment of " << amount << " " << currency
         << endl;
  }
  bool isPaymentSuccessful() override {
    cout << "InHouse: Payment successful!" << endl;
    return true;
  }
  string getTransactionId() override { return "INHOUSE-TXN-001"; }
};

// ─────────────────────────────────────────
// 3. Legacy Gateway (incompatible interface, cannot modify)
// ─────────────────────────────────────────
class LegacyGateway {
public:
  void executeTransaction(double amount, string currency) {
    cout << "Legacy: Executing transaction of " << amount << " " << currency
         << endl;
  }
  bool checkStatus(long transactionId) {
    cout << "Legacy: Checking status for ID " << transactionId << endl;
    return true;
  }
  long getReferenceNumber() { return 987654321L; }
};

// ─────────────────────────────────────────
// 4. Adapter (the middleman — translates your interface to legacy)
// ─────────────────────────────────────────
class LegacyGatewayAdapter : public PaymentProcessor {
private:
  LegacyGateway *legacy;
  long lastTransactionId;

public:
  LegacyGatewayAdapter(LegacyGateway *gw) {
    legacy = gw;
    lastTransactionId = 0;
  }

  // your system calls processPayment() → adapter calls executeTransaction()
  void processPayment(double amount, string currency) override {
    legacy->executeTransaction(amount, currency);
    lastTransactionId = legacy->getReferenceNumber();
  }

  // your system calls isPaymentSuccessful() → adapter calls checkStatus(id)
  bool isPaymentSuccessful() override {
    return legacy->checkStatus(lastTransactionId);
  }

  // your system expects String → adapter converts long to string
  string getTransactionId() override { return to_string(lastTransactionId); }
};

// ─────────────────────────────────────────
// 5. Checkout Service (never changes, doesn't care who processes payment)
// ─────────────────────────────────────────
class CheckoutService {
public:
  void processOrder(PaymentProcessor *processor, double amount,
                    string currency) {
    processor->processPayment(amount, currency);

    if (processor->isPaymentSuccessful()) {
      cout << "Order confirmed! Transaction ID: "
           << processor->getTransactionId() << endl;
    } else {
      cout << "Payment failed!" << endl;
    }
  }
};

// ─────────────────────────────────────────
// 6. Main
// ─────────────────────────────────────────
int main() {
  CheckoutService checkout;

  cout << "=== Paying with InHouse Processor ===" << endl;
  PaymentProcessor *inhouse = new InHouseProcessor();
  checkout.processOrder(inhouse, 999.99, "INR");

  cout << "\n=== Paying with Legacy Gateway ===" << endl;
  PaymentProcessor *legacy = new LegacyGatewayAdapter(new LegacyGateway());
  checkout.processOrder(legacy, 499.99, "INR");

  return 0;
}