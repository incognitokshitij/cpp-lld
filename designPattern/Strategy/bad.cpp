#include <bits/stdc++.h>

using namespace std;

class PaymentProcessor {
public:
  void pay(std::string type, double amount) {
    if (type == "credit_card") {
      // validate card, call bank API, log txn
    } else if (type == "paypal") {
      // OAuth, call PayPal API
    } else if (type == "upi") {
      // generate UPI intent, call NPCI
    } else if (type == "stripe") {
      // ...
    }
    // grows forever
  }
};
int main() { return 0; }