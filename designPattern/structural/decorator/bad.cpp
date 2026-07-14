class Pizza {
public:
  virtual double getCost() = 0;
};

class PlainPizza : public Pizza {
public:
  double getCost() override { return 100.0; }
};

class PizzaWithCheese : public Pizza {
public:
  double getCost() override { return 100.0 + 20.0; }
};

class PizzaWithCheeseAndOlives : public Pizza {
public:
  double getCost() override { return 100.0 + 20.0 + 15.0; }
};

// what about PizzaWithOlives?
// PizzaWithCheeseAndOlivesAndJalapeno?
// 5 toppings = up to 32 classes just for combinations