#include <bits/stdc++.h>

using namespace std;

enum OrderStatus { PLACED, CONFIRMED, SHIPPED, DELIVERED, CANCELLED };

int main() {

  cout << "PLACED: " << OrderStatus::PLACED << endl;       // 0
  cout << "CONFIRMED: " << OrderStatus::CONFIRMED << endl; // 1
  cout << "SHIPPED: " << OrderStatus::SHIPPED << endl;     // 2
  cout << "DELIVERED: " << OrderStatus::DELIVERED << endl; // 3
  cout << "CANCELLED: " << OrderStatus::CANCELLED << endl; // 4

  OrderStatus newOrderStatus = OrderStatus::SHIPPED;

  if (newOrderStatus == OrderStatus::SHIPPED) {
    cout << "Your package is on the way!" << endl;
  }
}