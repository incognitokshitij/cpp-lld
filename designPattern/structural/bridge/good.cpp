#include <iostream>
#include <string>
using namespace std;

// =========================================================
// Implementation Hierarchy: Engine interface (Low-Level Layer)
// =========================================================
class Engine {
public:
  virtual void start() = 0;
  virtual ~Engine() {}
};

// Concrete Implementors (LLL)
class PetrolEngine : public Engine {
public:
  void start() override {
    cout << "Petrol engine starting with ignition!" << endl;
  }
};

class DieselEngine : public Engine {
public:
  void start() override { cout << "Diesel engine roaring to life!" << endl; }
};

class ElectricEngine : public Engine {
public:
  void start() override {
    cout << "Electric engine powering up silently!" << endl;
  }
};

// =========================================================
// Abstraction Hierarchy: Car (High-Level Layer)
// =========================================================
class Car {
protected:
  Engine *engine; // <-- THE BRIDGE: HLL holds a reference to LLL
public:
  Car(Engine *e) { engine = e; }
  virtual void drive() = 0;
  virtual ~Car() {}
};

// Refined Abstraction: Sedan
class Sedan : public Car {
public:
  Sedan(Engine *e) : Car(e) {}
  void drive() override {
    engine->start(); // delegate to LLL via the bridge
    cout << "Driving a Sedan on the highway." << endl;
  }
};

// Refined Abstraction: SUV
class SUV : public Car {
public:
  SUV(Engine *e) : Car(e) {}
  void drive() override {
    engine->start(); // delegate to LLL via the bridge
    cout << "Driving an SUV off-road." << endl;
  }
};

// =========================================================
// Client code
// =========================================================
int main() {
  // 1. Build LLL implementations
  Engine *petrolEng = new PetrolEngine();
  Engine *dieselEng = new DieselEngine();
  Engine *electricEng = new ElectricEngine();

  // 2. Build HLL abstractions, injecting any LLL into any HLL
  Car *mySedan = new Sedan(petrolEng); // Sedan + Petrol
  Car *mySUV = new SUV(electricEng);   // SUV   + Electric
  Car *yourSUV = new SUV(dieselEng);   // SUV   + Diesel

  // 3. Use them — each call goes HLL.drive() -> LLL.start()
  mySedan->drive();
  mySUV->drive();
  yourSUV->drive();

  // 4. Cleanup (cars first, then engines, since cars don't own engines)
  delete mySedan;
  delete mySUV;
  delete yourSUV;
  delete petrolEng;
  delete dieselEng;
  delete electricEng;

  return 0;
}