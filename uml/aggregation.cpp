#include <bits/stdc++.h>

using namespace std;

class Employee {
public:
  string name;
  int id;

  Employee(string name, int id) {
    this->name = name;
    this->id = id;
  }

  void work() { cout << this->name << " is working" << endl; }
};

class Department {
public:
  string name;
  vector<Employee *>
      employees; // has employees (holds pointers, doesn't own them)

  Department(string name) { this->name = name; }

  // Aggregation: Employee comes from OUTSIDE
  void addEmployee(Employee *employee) {
    employees.push_back(employee);
    cout << employee->name << " joined " << this->name << endl;
  }

  void removeEmployee(Employee *employee) {
    for (int i = 0; i < employees.size(); i++) {
      if (employees[i]->id == employee->id) {
        employees.erase(employees.begin() + i);
        break;
      }
    }
    cout << employee->name << " left " << name << endl;
  }

  void listEmployees() {
    cout << "\n" << name << " Department:" << endl;
    for (Employee *e : employees) {
      cout << "  - " << e->name << endl;
    }
  }
};

int main() {
  // Step 1: Employees exist INDEPENDENTLY
  Employee *alice = new Employee("Alice", 1);
  Employee *bob = new Employee("Bob", 2);
  Employee *charlie = new Employee("Charlie", 3);

  // Step 2: Department is created
  Department *engineering = new Department("Engineering");
  Department *marketing = new Department("Marketing");

  // Step 3: Employees are ADDED (not created inside)
  engineering->addEmployee(alice);
  engineering->addEmployee(bob);
  marketing->addEmployee(charlie);

  engineering->listEmployees();

  // Step 4: Department is "closed"
  engineering->employees.clear();
  cout << "\nEngineering department closed" << endl;

  // Step 5: Employees STILL EXIST
  cout << alice->name << endl; // Alice - still exists!
  alice->work();               // Alice is working
}
