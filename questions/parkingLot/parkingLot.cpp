#include <iostream>
#include <mutex>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

// ---------- Enums ----------
enum class VehicleType { BIKE, CAR, TRUCK };
enum class SpotSize { SMALL, MEDIUM, LARGE };

// ---------- Vehicle Hierarchy ----------
class Vehicle {
protected:
  string licensePlate;
  VehicleType type;

public:
  Vehicle(string plate, VehicleType t) {
    licensePlate = plate;
    type = t;
  }
  VehicleType getType() { return type; }
  string getPlate() { return licensePlate; }
};

class Bike : public Vehicle {
public:
  Bike(string plate) : Vehicle(plate, VehicleType::BIKE) {}
};

class Car : public Vehicle {
public:
  Car(string plate) : Vehicle(plate, VehicleType::CAR) {}
};

class Truck : public Vehicle {
public:
  Truck(string plate) : Vehicle(plate, VehicleType::TRUCK) {}
};

// ---------- Factory Pattern: creates vehicles ----------
class VehicleFactory {
public:
  static Vehicle *createVehicle(VehicleType type, string plate) {
    if (type == VehicleType::BIKE)
      return new Bike(plate);
    if (type == VehicleType::CAR)
      return new Car(plate);
    if (type == VehicleType::TRUCK)
      return new Truck(plate);
    return nullptr;
  }
};

// ---------- Parking Spot ----------
class ParkingSpot {
  int spotId;
  SpotSize size;
  bool occupied;
  Vehicle *parkedVehicle;

public:
  ParkingSpot(int id, SpotSize s) {
    spotId = id;
    size = s;
    occupied = false;
    parkedVehicle = nullptr;
  }

  bool isFree() { return !occupied; }
  SpotSize getSize() { return size; }
  int getId() { return spotId; }

  bool canFitVehicle(VehicleType vt) {
    if (vt == VehicleType::BIKE)
      return true;
    if (vt == VehicleType::CAR)
      return size == SpotSize::MEDIUM || size == SpotSize::LARGE;
    if (vt == VehicleType::TRUCK)
      return size == SpotSize::LARGE;
    return false;
  }

  void parkVehicle(Vehicle *v) {
    parkedVehicle = v;
    occupied = true;
  }

  void removeVehicle() {
    parkedVehicle = nullptr;
    occupied = false;
  }

  Vehicle *getVehicle() { return parkedVehicle; }
};

// ---------- Strategy Pattern: pricing ----------
class PricingStrategy {
public:
  virtual double calculateFare(SpotSize size, int hours) = 0;
};

class HourlyPricingStrategy : public PricingStrategy {
public:
  double calculateFare(SpotSize size, int hours) override {
    int rate = (size == SpotSize::SMALL)    ? 10
               : (size == SpotSize::MEDIUM) ? 20
                                            : 30;
    return rate * hours;
  }
};

// ---------- Ticket ----------
class Ticket {
  static int ticketCounter;

public:
  int ticketId;
  Vehicle *vehicle;
  ParkingSpot *spot;
  int entryHour; // just a number like 10 (10 AM), easy to write, no time_t
                 // needed

  Ticket(Vehicle *v, ParkingSpot *s, int hour) {
    vehicle = v;
    spot = s;
    entryHour = hour;
    ticketId = ++ticketCounter;
  }
};
int Ticket::ticketCounter = 0;

// ---------- Floor ----------
class ParkingFloor {
  int floorNumber;
  vector<ParkingSpot *> spots;
  mutex floorMutex; // ensures two gates can't grab the same spot at once

public:
  ParkingFloor(int num) { floorNumber = num; }

  void addSpot(ParkingSpot *spot) { spots.push_back(spot); }

  // find + assign together under one lock, so the check and the claim are
  // atomic
  ParkingSpot *findAndAssignSpot(VehicleType vt, Vehicle *v) {
    lock_guard<mutex> lock(floorMutex);
    for (auto spot : spots) {
      if (spot->isFree() && spot->canFitVehicle(vt)) {
        spot->parkVehicle(v);
        return spot;
      }
    }
    return nullptr;
  }
};

// ---------- Singleton Pattern: ParkingLot ----------
class ParkingLot {
  static ParkingLot *instance;
  vector<ParkingFloor *> floors;
  PricingStrategy *pricingStrategy;
  unordered_map<int, Ticket *> activeTickets;

  ParkingLot() { pricingStrategy = new HourlyPricingStrategy(); }

public:
  ParkingLot(const ParkingLot &) = delete;
  void operator=(const ParkingLot &) = delete;

  static ParkingLot *getInstance() {
    if (instance == nullptr)
      instance = new ParkingLot();
    return instance;
  }

  void addFloor(ParkingFloor *floor) { floors.push_back(floor); }

  Ticket *parkVehicle(Vehicle *v, int entryHour) {
    for (auto floor : floors) {
      ParkingSpot *spot = floor->findAndAssignSpot(v->getType(), v);
      if (spot != nullptr) {
        Ticket *t = new Ticket(v, spot, entryHour);
        activeTickets[t->ticketId] = t;
        cout << "Parked " << v->getPlate() << " at spot " << spot->getId()
             << " | Ticket ID: " << t->ticketId << endl;
        return t;
      }
    }
    cout << "No spot available for " << v->getPlate() << endl;
    return nullptr;
  }

  double unparkVehicle(int ticketId, int exitHour) {
    if (activeTickets.find(ticketId) == activeTickets.end()) {
      cout << "Invalid ticket" << endl;
      return -1;
    }
    Ticket *t = activeTickets[ticketId];
    int hoursParked = max(1, exitHour - t->entryHour);
    double fare =
        pricingStrategy->calculateFare(t->spot->getSize(), hoursParked);

    t->spot->removeVehicle();
    activeTickets.erase(ticketId);

    cout << "Vehicle " << t->vehicle->getPlate() << " exited. Fare: Rs " << fare
         << endl;
    return fare;
  }
};
ParkingLot *ParkingLot::instance = nullptr;

// ---------- Driver code ----------
int main() {
  ParkingLot *lot = ParkingLot::getInstance();

  ParkingFloor *floor1 = new ParkingFloor(1);
  floor1->addSpot(new ParkingSpot(1, SpotSize::SMALL));
  floor1->addSpot(new ParkingSpot(2, SpotSize::MEDIUM));
  floor1->addSpot(new ParkingSpot(3, SpotSize::LARGE));
  lot->addFloor(floor1);

  Vehicle *car1 = VehicleFactory::createVehicle(VehicleType::CAR, "KA-01-1234");
  Ticket *t1 = lot->parkVehicle(car1, 10); // entered at hour 10

  Vehicle *bike1 =
      VehicleFactory::createVehicle(VehicleType::BIKE, "KA-01-9999");
  lot->parkVehicle(bike1, 10);

  if (t1 != nullptr) {
    lot->unparkVehicle(t1->ticketId, 13); // exited at hour 13
  }

  return 0;
}