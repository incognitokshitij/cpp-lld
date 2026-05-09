#include <bits/stdc++.h>
using namespace std;

class TokenBucket {
private:
  int bucketSize;
  int tokens;
  int refillAmount;
  int refillRateMs;
  int lastRefillTime;

public:
  TokenBucket(int bucketSize, int refillRateMs, int refillAmount) {
    this->bucketSize = bucketSize;
    this->tokens = bucketSize;
    this->refillAmount = refillAmount;
    this->refillRateMs = refillRateMs;
    this->lastRefillTime = 0;
  }

  bool allowRequest(int currentTime) {

    if (currentTime - this->lastRefillTime >= this->refillRateMs) {
      this->tokens = min(bucketSize, this->tokens + refillAmount);
      this->lastRefillTime = currentTime;
      cout << "Refilled! Tokens: " << this->tokens << endl;
    }

    if (this->tokens > 0) {
      this->tokens = this->tokens - 1;
      cout << "✅ Allowed at t=" << currentTime
           << " Tokens left: " << this->tokens << endl;
      return true;
    } else {
      cout << "❌ Rejected at t=" << currentTime << endl;
      return false;
    }
  }
};

int main() {
  TokenBucket *bucket =
      new TokenBucket(5, 1000, 2); // 5 tokens max, refill 2 every 1s

  vector<int> requestTimes = {
      0, 100, 200, 300, 400, 500, 600 // requests every 100ms → runs out fast!
  };

  for (int t : requestTimes) {
    bucket->allowRequest(t);
  }

  delete bucket;
  cout << endl;
  cout << endl;

  vector<int> burstTimes = {
      0,    100,  200,  300,  400, 500, // burst! empty the bucket
      1000, 1100, 1200,                 // after refill
      2000, 2100, 2200, 2300, 2400      // another burst
  };

  TokenBucket *bucket2 = new TokenBucket(5, 1000, 2);
  for (int t : burstTimes) {
    bucket2->allowRequest(t);
  }

  delete bucket2;
  return 0;
}