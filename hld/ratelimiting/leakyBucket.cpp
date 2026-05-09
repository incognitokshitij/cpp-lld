#include <bits/stdc++.h>
using namespace std;

class LeakyBucket {
private:
  int bucketSize;    // max queue size
  int leakRateMs;    // process one request every X ms
  int lastLeakTime;  // when did we last process
  queue<int> bucket; // queue of requests

public:
  LeakyBucket(int bucketSize, int leakRateMs) {
    this->bucketSize = bucketSize;
    this->leakRateMs = leakRateMs;
    this->lastLeakTime = 0;
  }

  void processRequest(int currentTime) {

    // Leak (process) one request if enough time has passed
    if (!bucket.empty() && currentTime - lastLeakTime >= leakRateMs) {
      int req = bucket.front();
      bucket.pop();
      lastLeakTime = currentTime;
      cout << "💧 Processed request that came at t=" << req
           << " | Queue size: " << bucket.size() << endl;
    }

    // Try to add new request to queue
    if (bucket.size() < bucketSize) {
      bucket.push(currentTime);
      cout << "✅ Queued at t=" << currentTime
           << " | Queue size: " << bucket.size() << endl;
    } else {
      cout << "❌ Rejected at t=" << currentTime << " | Queue full!" << endl;
    }
  }
};

int main() {
  LeakyBucket *bucket =
      new LeakyBucket(5, 1000); // queue size 5, process 1 every 1s

  // Burst of requests coming fast
  vector<int> requestTimes = {
      0,    100,  200, 300, 400, 500, // fast burst → queue fills up
      600,  700,                      // queue full → rejections
      1000, 2000, 3000                // slow requests after leak
  };

  for (int t : requestTimes) {
    bucket->processRequest(t);
  }

  delete bucket;
  return 0;
}