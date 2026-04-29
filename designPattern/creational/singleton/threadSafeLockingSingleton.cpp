#include <bits/stdc++.h>

using namespace std;

class Singleton {
private:
  static Singleton *instance;
  static mutex mtx;

  Singleton() { cout << "Singleton Constructor Called!" << endl; }

public:
  static Singleton *getInstance() {
    cout << "Get Instance called" << endl;
    lock_guard<mutex> lock(mtx); // Lock for thread safety
    cout << "After lock" << endl;
    if (instance == nullptr) {
      instance = new Singleton();
    }
    return instance;
  }
};

// Initialize static members
Singleton *Singleton::instance = nullptr;
mutex Singleton::mtx;

int main() {
  Singleton *s1 = Singleton::getInstance();
  Singleton *s2 = Singleton::getInstance();

  cout << (s1 == s2) << endl;
}