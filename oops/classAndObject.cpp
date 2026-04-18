#include <bits/stdc++.h>
using namespace std;

class Car {
public:
  string brand;
  string modal;
  int speed;

public:
  Car() {}
  Car(string brand, string modal, int speed) {
    this->brand = brand;
    this->modal = modal;
    this->speed = speed;
  }

  ~Car() { 
    cout << this->brand << " brand destroyed\n"; 
}

  void getInfo() {
    cout << "Brand : " << this->brand << ", modal : " << this->modal
         << ", speed : " << this->speed << endl;
  }
};

int main() {

  // WAY 1 - Dynamic allocation (heap memory)
  // Object lives until you manually call `delete`
  // Access members via arrow operator ->
  Car *marutiCar = new Car("Maruti", "2026", 100);
  marutiCar->getInfo();
  delete marutiCar; // must free manually, else memory leak

  // WAY 2 - Stack allocation, members set manually after creation
  // Empty constructor is called first, then fields assigned one by one
  // Access members via dot operator .
  Car nano;
  nano.brand = "tata";
  nano.modal = "2023";
  nano.speed = 50;
  nano.getInfo();

  // WAY 3 - Stack allocation with parameterized constructor (most common)
  // Cleaner than way 2, no manual field assignment needed
  Car honda("Honda", "2025", 120);
  honda.getInfo();

  // WAY 4 - Uniform initialization (modern C++11 style)
  // Same as way 3 but uses {} instead of ()
  Car bmw{"BMW", "2024", 200};
  bmw.getInfo();

  // WAY 5 - Smart pointer (modern C++, avoids manual delete)
  // Automatically freed when pointer goes out of scope
  unique_ptr<Car> tesla = make_unique<Car>("Tesla", "2026", 250);
  tesla->getInfo();
};