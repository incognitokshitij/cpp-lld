#include <bits/stdc++.h>
using namespace std;

class SlidingWindowLog {
private:
  int windowSizeMs; // window duration
  int maxRequests;  // max requests in window
  deque<int> log;   // stores timestamps of each request

public:
  SlidingWindowLog(int windowSizeMs, int maxRequests) {
    this->windowSizeMs = windowSizeMs;
    this->maxRequests = maxRequests;
  }

  bool allowRequest(int currentTime) {

    // Step 1 - remove timestamps outside the window
    while (!log.empty() && currentTime - log.front() >= windowSizeMs) {
      cout << "🗑️  Removed old timestamp: " << log.front() << endl;
      log.pop_front();
    }

    // Step 2 - check count
    if (log.size() < maxRequests) {
      log.push_back(currentTime);
      cout << "✅ Allowed at t=" << currentTime << " | Log size: " << log.size()
           << "/" << maxRequests << endl;
      return true;
    } else {
      cout << "❌ Rejected at t=" << currentTime
           << " | Log size: " << log.size() << "/" << maxRequests << endl;
      return false;
    }
  }
};

int main() {
  SlidingWindowLog *sw =
      new SlidingWindowLog(1000, 3); // 1s window, max 3 requests

  vector<int> requestTimes = {0,    100, 200, // window fills up
                              300,  400,      // rejected! (still in window)
                              1100,           // t=0 falls out → allowed!
                              1200, // t=100 still in window → rejected
                              2000, // all old removed → fresh start
                              2100, 2200};

  for (int t : requestTimes) {
    sw->allowRequest(t);
  }

  delete sw;
  return 0;
}