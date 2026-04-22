#include <bits/stdc++.h>

using namespace std;

class Knife {
private:
  string type;

public:
  Knife(string type) { this->type = type; }

  void chop(string item) {
    cout << "  " << type << " knife chopping " << item << endl;
  }
};

class Chef {
private:
  string name;

public:
  Chef(string name) { this->name = name; }

  // Dependency: Knife is passed in as a parameter.
  // Chef uses it only for the duration of this method -- no field, no ownership.
  void prepareMeal(Knife *knife, vector<string> items) {
    cout << name << " starts cooking" << endl;
    for (auto &item : items) {
      knife->chop(item);
    }
    cout << name << " is done -- knife goes back to the drawer\n" << endl;
  }
};

int main() {
  Chef *gordon = new Chef("Gordon");

  // Knife exists independently of the Chef
  Knife *chefKnife = new Knife("Chef's");
  Knife *paringKnife = new Knife("Paring");

  // Same chef, different knives at different times -- short-lived use
  gordon->prepareMeal(chefKnife, {"onions", "carrots"});
  gordon->prepareMeal(paringKnife, {"garlic"});

  // Chef holds no reference to either knife -- they can be reused or discarded
  delete chefKnife;
  delete paringKnife;
  delete gordon;
  return 0;
}
