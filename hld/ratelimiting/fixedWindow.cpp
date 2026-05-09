#include <bits/stdc++.h>
using namespace std;

class FixedWindow {
private:
  int windowSizeMs;    // window duration
  int maxRequests;     // max requests per window
  int requestCount;    // current count in this window
  int windowStartTime; // when did current window start

public:
  FixedWindow(int windowSizeMs, int maxRequests) {
    this->windowSizeMs = windowSizeMs;
    this->maxRequests = maxRequests;
    this->requestCount = 0;
    this->windowStartTime = 0;
  }

  bool allowRequest(int currentTime) {

    // Check if current window expired → reset
    if (currentTime - windowStartTime >= windowSizeMs) {
      windowStartTime = currentTime;
      requestCount = 0;
      cout << "🔄 New window started at t=" << currentTime << endl;
    }

    // Allow or reject
    if (requestCount < maxRequests) {
      requestCount++;
      cout << "✅ Allowed at t=" << currentTime << " | Count: " << requestCount
           << "/" << maxRequests << endl;
      return true;
    } else {
      cout << "❌ Rejected at t=" << currentTime << " | Count: " << requestCount
           << "/" << maxRequests << endl;
      return false;
    }
  }
};

int main() {
  FixedWindow *fw = new FixedWindow(1000, 3); // window 1s, max 3 requests

  vector<int> requestTimes = {
      0,    100,  200,  // window 1 → all allowed (hits limit)
      300,  400,        // window 1 → rejected!
      1000, 1100, 1200, // window 2 → all allowed (reset!)
      1300,             // window 2 → rejected!
      2000, 2100        // window 3 → allowed again
  };

  for (int t : requestTimes) {
    fw->allowRequest(t);
  }

  delete fw;
  return 0;
}