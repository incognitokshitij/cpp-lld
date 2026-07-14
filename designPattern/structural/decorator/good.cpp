#include <iostream>
#include <string>
using namespace std;

// interface
class Pizza {
public:
  virtual string getDescription() = 0;
  virtual double getCost() = 0;
  virtual ~Pizza() {}
};

// base, implements Pizza directly, no wrapping
class PlainPizza : public Pizza {
public:
  string getDescription() override { return "Plain Pizza"; }
  double getCost() override { return 100.0; }
};

// decorator, implements Pizza directly, wraps a Pizza
class CheeseDecorator : public Pizza {
  Pizza *pizza;

public:
  CheeseDecorator(Pizza *p) : pizza(p) {}
  string getDescription() override {
    return pizza->getDescription() + " + Cheese";
  }
  double getCost() override { return pizza->getCost() + 20.0; }
  ~CheeseDecorator() { delete pizza; }
};

// decorator, implements Pizza directly, wraps a Pizza
class OliveDecorator : public Pizza {
  Pizza *pizza;

public:
  OliveDecorator(Pizza *p) : pizza(p) {}
  string getDescription() override {
    return pizza->getDescription() + " + Olives";
  }
  double getCost() override { return pizza->getCost() + 15.0; }
  ~OliveDecorator() { delete pizza; }
};

int main() {
  // user picks toppings at runtime, based on their input
  Pizza *myPizza = new OliveDecorator(new CheeseDecorator(new PlainPizza()));

  cout << myPizza->getDescription() << " -> Rs. " << myPizza->getCost() << endl;
  // Output: Plain Pizza + Cheese + Olives -> Rs. 135

  delete myPizza; // deletes the whole chain, since each decorator deletes what
                  // it wraps
  return 0;
}