#include <bits/stdc++.h>

using namespace std;

class Room {
private:
  string name;

public:
  Room(string name) {
    this->name = name;
    cout << "Room created: " << name << endl;
  }

  ~Room() { cout << "Room destroyed: " << name << endl; }

  void display() { cout << "  Room: " << name << "\n"; }
};

class House {
private:
  vector<Room *> rooms;

  void createRooms(vector<string> names) {
    for (auto name : names) {
      rooms.push_back(new Room(name));
    }
  }

public:
  House(vector<string> names) {
    cout << "House built\n" << endl;
    createRooms(names);
  }

  ~House() {
    cout << "\nHouse demolished -- taking all rooms with it" << endl;
    for (auto room : rooms)
      delete room;
  }

  void display() {
    cout << "\nHouse contains:" << endl;
    for (auto &room : rooms) {
      room->display();
    }
  }
};

int main() {
  House *house = new House({"Living Room", "Kitchen", "Bedroom"});
  house->display();
  delete house;
  return 0;
}