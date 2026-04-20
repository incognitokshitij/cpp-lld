#include <iostream>
using namespace std;

// Strategy Interface
class PricingStrategy {
public:
    virtual int calculate() = 0;
    virtual ~PricingStrategy() {} // good practice
};

class HourlyPricing : public PricingStrategy {
public:
    int calculate() override { return 50; }
};

class FlatPricing : public PricingStrategy {
public:
    int calculate() override { return 100; }
};

class WeekendPricing : public PricingStrategy {
public:
    int calculate() override { return 150; }
};

class PaymentService {
private:
    PricingStrategy* pricingStrategy;

public:
    PaymentService(PricingStrategy* strategy) {
        pricingStrategy = strategy;
    }

    int calculateFee() {
        return pricingStrategy->calculate();
    }
};

int main() {
    // 🔹 create objects using new
    PricingStrategy* hourly = new HourlyPricing();
    PricingStrategy* flat = new FlatPricing();
    PricingStrategy* weekend = new WeekendPricing();

    PaymentService service1(hourly);
    cout << "Hourly Fee: " << service1.calculateFee() << endl;

    PaymentService service2(flat);
    cout << "Flat Fee: " << service2.calculateFee() << endl;

    PaymentService service3(weekend);
    cout << "Weekend Fee: " << service3.calculateFee() << endl;

    // 🔹 free memory (important)
    delete hourly;
    delete flat;
    delete weekend;

    return 0;
}