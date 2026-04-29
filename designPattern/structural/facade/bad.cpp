

#include <bits/stdc++.h>

using namespace std;

class VersionControlSystem {
public:
  void pullLatestChanges(string branch) {
    cout << "VCS: Pulling latest changes from '" << branch << "'..." << endl;
    simulateDelay();
    cout << "VCS: Pull complete." << endl;
  }

private:
  void simulateDelay() { this_thread::sleep_for(chrono::milliseconds(1000)); }
};

class BuildSystem {
public:
  bool compileProject() {
    cout << "BuildSystem: Compiling project..." << endl;
    simulateDelay(2000);
    cout << "BuildSystem: Build successful." << endl;
    return true;
  }

  string getArtifactPath() {
    string path = "target/myapplication-1.0.jar";
    cout << "BuildSystem: Artifact located at " << path << endl;
    return path;
  }

private:
  void simulateDelay(int ms) {
    this_thread::sleep_for(chrono::milliseconds(ms));
  }
};
class TestingFramework {
public:
  bool runUnitTests() {
    cout << "Testing: Running unit tests..." << endl;
    simulateDelay(1500);
    cout << "Testing: Unit tests passed." << endl;
    return true;
  }

  bool runIntegrationTests() {
    cout << "Testing: Running integration tests..." << endl;
    simulateDelay(3000);
    cout << "Testing: Integration tests passed." << endl;
    return true;
  }

private:
  void simulateDelay(int ms) {
    this_thread::sleep_for(chrono::milliseconds(ms));
  }
};
class DeploymentTarget {
public:
  void transferArtifact(string artifactPath, string server) {
    cout << "Deployment: Transferring " << artifactPath << " to " << server
         << "..." << endl;
    simulateDelay(1000);
    cout << "Deployment: Transfer complete." << endl;
  }

  void activateNewVersion(string server) {
    cout << "Deployment: Activating new version on " << server << "..." << endl;
    simulateDelay(500);
    cout << "Deployment: Now live on " << server << "!" << endl;
  }

private:
  void simulateDelay(int ms) {
    this_thread::sleep_for(chrono::milliseconds(ms));
  }
};
class DeploymentClient {
public:
  static int Main() {
    string branch = "main";
    string prodServer = "prod.server.example.com";

    // Client must create and manage all subsystems
    VersionControlSystem vcs;
    BuildSystem buildSystem;
    TestingFramework testFramework;
    DeploymentTarget deployTarget;

    cout << "\n[Client] Starting deployment for branch: " << branch << "\n";

    // Step 1: Pull latest code
    vcs.pullLatestChanges(branch);

    // Step 2: Build the project
    if (!buildSystem.compileProject()) {
      cerr << "[Client] Build failed. Deployment aborted.\n";
      return 0;
    }
    string artifact = buildSystem.getArtifactPath();

    // Step 3: Run tests
    if (!testFramework.runUnitTests()) {
      cerr << "[Client] Unit tests failed. Deployment aborted.\n";
      return 0;
    }
    if (!testFramework.runIntegrationTests()) {
      cerr << "[Client] Integration tests failed. Deployment aborted.\n";
      return 0;
    }

    // Step 4: Deploy to production
    deployTarget.transferArtifact(artifact, prodServer);
    deployTarget.activateNewVersion(prodServer);

    cout << "[Client] Deployment successful!\n";
    return 0;
  }
};
int main() {
  DeploymentClient::Main();
  return 0;
}