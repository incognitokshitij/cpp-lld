#include <bits/stdc++.h>
using namespace std;

class Account; // forward declare, Transaction needs it

class Stock {
public:
  int id;
  string name;
  int price;
  int quantity;

  Stock(int id, string name, int price, int quantity)
      : id(id), name(name), price(price), quantity(quantity) {}

  string toString() {
    return to_string(id) + " | " + name + " | Price: " + to_string(price) +
           " | Qty: " + to_string(quantity);
  }
};

class Transaction {
public:
  int id;
  Account *account;
  Stock *stock;
  int shares;
  int amount;

  Transaction(Account *account, Stock *stock, int shares, int amount)
      : account(account), stock(stock), shares(shares), amount(amount) {
    id = rand() % 100000;
  }

  string toString() {
    return "Txn#" + to_string(id) + " " + stock->name + " " +
           to_string(shares) + " shares @ " + to_string(stock->price) + " = " +
           to_string(amount);
  }
};

class Account {
public:
  int id;
  int balance;
  unordered_map<Stock *, int> portfolio;
  vector<Transaction> transactions;

  Account(int id, int initialBalance) : id(id), balance(initialBalance) {}

  void viewPortfolio() {
    cout << "Portfolio of Account " << id << endl;
    for (auto &entry : portfolio) {
      cout << entry.first->name << " -> " << entry.second << " shares" << endl;
    }
  }

  void addStockInPortfolio(Stock *stock, int quantity) {
    if (portfolio.find(stock) == portfolio.end())
      portfolio[stock] = 0;
    portfolio[stock] += quantity;
  }

  void removeStockFromPortfolio(Stock *stock, int quantity) {
    if (portfolio.find(stock) != portfolio.end()) {
      int current = portfolio[stock];
      if (current <= quantity)
        portfolio.erase(stock);
      else
        portfolio[stock] = current - quantity;
    }
  }

  void addTransaction(Transaction transaction) {
    transactions.push_back(transaction);
  }

  void viewTransactions() {
    for (auto &txn : transactions) {
      cout << txn.toString() << endl;
    }
  }
};

class User {
public:
  int id;
  string name;
  Account *account;

  User(int id, string name) : id(id), name(name), account(nullptr) {}

  void createAccount(int initialBalance) {
    account = new Account(id, initialBalance);
  }

  Account *getAccount() { return account; }

  void viewPortfolio() { account->viewPortfolio(); }

  void viewTransactions() { account->viewTransactions(); }
};

// ==================== OBSERVER PATTERN ====================

class StockObserver {
public:
  virtual void update(Stock *stock) = 0;
  virtual ~StockObserver() {}
};

class UserNotifier : public StockObserver {
private:
  User *user;

public:
  UserNotifier(User *user) : user(user) {}

  void update(Stock *stock) override {
    cout << "Notifying " << user->name << ": Stock " << stock->name
         << " new price: " << stock->price << endl;
  }
};

// ==================== SINGLETON SERVICE ====================

class StockManager {
private:
  static StockManager *instance;
  vector<Stock *> stocks;
  vector<StockObserver *> observers;

  StockManager() {}

public:
  static StockManager *getInstance() {
    if (instance == nullptr)
      instance = new StockManager();
    return instance;
  }

  void addStock(Stock *stock) { stocks.push_back(stock); }

  void registerObserver(StockObserver *observer) {
    observers.push_back(observer);
  }

private:
  void notifyAllObservers(Stock *stock) {
    for (auto obs : observers) {
      obs->update(stock);
    }
  }

public:
  void updateStockPrice(int stockId, int newPrice) {
    for (auto stock : stocks) {
      if (stock->id == stockId) {
        stock->price = newPrice;
        notifyAllObservers(stock);
        break;
      }
    }
  }

  void buyStock(Account *account, int stockId, int shares) {
    for (auto stock : stocks) {
      if (stock->id == stockId) {
        int cost = shares * stock->price;
        if (account->balance < cost)
          throw runtime_error("Not enough balance!");
        if (stock->quantity < shares)
          throw runtime_error("Not enough stock available!");

        stock->quantity -= shares;
        account->addStockInPortfolio(stock, shares);
        account->balance -= cost;
        account->addTransaction(Transaction(account, stock, shares, cost));
        break;
      }
    }
  }

  void sellStock(Account *account, int stockId, int shares) {
    for (auto stock : stocks) {
      if (stock->id == stockId) {
        stock->quantity += shares;
        int revenue = shares * stock->price;
        account->removeStockFromPortfolio(stock, shares);
        account->balance += revenue;
        account->addTransaction(Transaction(account, stock, shares, revenue));
        break;
      }
    }
  }

  void viewStockList() {
    for (auto stock : stocks) {
      cout << stock->toString() << endl;
    }
  }
};

StockManager *StockManager::instance = nullptr;

// ==================== CLIENT CODE ====================

int main() {
  try {
    // Create stock manager (Singleton)
    StockManager *manager = StockManager::getInstance();

    // Add stocks
    Stock *s1 = new Stock(1, "AAPL", 150, 100);
    Stock *s2 = new Stock(2, "GOOG", 2800, 50);
    manager->addStock(s1);
    manager->addStock(s2);

    // Create user + account
    User u1(1, "Alice");
    u1.createAccount(10000);

    // Register for stock notifications
    manager->registerObserver(new UserNotifier(&u1));

    // Show stocks
    manager->viewStockList();

    // Buy stock
    manager->buyStock(u1.getAccount(), 1, 10);

    // Sell stock
    manager->sellStock(u1.getAccount(), 1, 5);

    // View portfolio
    u1.viewPortfolio();

    // View transactions
    u1.viewTransactions();

    // Update stock price -> triggers Observer notification
    manager->updateStockPrice(1, 160);

  } catch (exception &e) {
    cout << "Error: " << e.what() << endl;
  }

  return 0;
}