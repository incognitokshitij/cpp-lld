#include <bits/stdc++.h>
using namespace std;

class MySQLDatabase { // Low-level module
public:
  void saveToSQL(string data) {
    cout << "Executing SQL Query: INSERT INTO users VALUES('" << data << "');"
         << endl;
  }
};

class MongoDBDatabase { // Low-level module
public:
  void saveToMongo(string data) {
    cout << "Executing MongoDB Function: db.users.insert({name: '" << data
         << "'})" << endl;
  }
};

class UserService { // High-level module (Tightly coupled)
private:
  MySQLDatabase *sqlDb;
  MongoDBDatabase *mongoDb;

public:
  UserService() {
    sqlDb = new MySQLDatabase();     // ❌ hardcoded
    mongoDb = new MongoDBDatabase(); // ❌ hardcoded
  }

  void storeUserToSQL(string user) { sqlDb->saveToSQL(user); }

  void storeUserToMongo(string user) { mongoDb->saveToMongo(user); }

  ~UserService() {
    delete sqlDb;
    delete mongoDb;
  }
};

int main() {
  UserService *service = new UserService();
  service->storeUserToSQL("Aditya");
  service->storeUserToMongo("Rohit");

  delete service;
  return 0;
}