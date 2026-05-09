#include <bits/stdc++.h>
using namespace std;

class SlidingWindowCounter {
private:
    int windowSizeMs;    // 60s window
    int maxRequests;     // max allowed
    int prevCount;       // previous window count
    int currCount;       // current window count
    int windowStartTime; // when current window started

public:
    SlidingWindowCounter(int windowSizeMs, int maxRequests) {
        this->windowSizeMs = windowSizeMs;
        this->maxRequests = maxRequests;
        this->prevCount = 0;
        this->currCount = 0;
        this->windowStartTime = 0;
    }

    bool allowRequest(int currentTime) {

        // Step 1 - check if current window expired
        if (currentTime - windowStartTime >= windowSizeMs) {
            prevCount = currCount;  // current becomes previous
            currCount = 0;          // reset current
            windowStartTime = currentTime;
            cout << "🔄 New window! prevCount=" << prevCount << endl;
        }

        // Step 2 - calculate weight
        int timeElapsed = currentTime - windowStartTime;
        double weight = (double)(windowSizeMs - timeElapsed) / windowSizeMs;

        // Step 3 - estimate
        double estimatedCount = (prevCount * weight) + currCount;

        cout << "⚖️  timeElapsed=" << timeElapsed
             << " weight=" << weight
             << " estimated=" << estimatedCount << endl;

        // Step 4 - allow or reject
        if (estimatedCount < maxRequests) {
            currCount++;
            cout << "✅ Allowed at t=" << currentTime
                 << " | currCount=" << currCount << endl;
            return true;
        } else {
            cout << "❌ Rejected at t=" << currentTime << endl;
            return false;
        }
    }
};

int main() {
    SlidingWindowCounter *sw = new SlidingWindowCounter(1000, 5); // 1s window, max 5

    vector<int> requestTimes = {
        0, 100, 200, 300, 400,   // fill up window 1
        500, 600,                 // rejected!
        1000,                     // new window starts
        1200, 1400,               // weight kicks in here
        2000                      // fresh window
    };

    for (int t : requestTimes) {
        sw->allowRequest(t);
        cout << endl;
    }

    delete sw;
    return 0;
}