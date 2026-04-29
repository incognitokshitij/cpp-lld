

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

class DeploymentFacade {
private:
  VersionControlSystem vcs;
  BuildSystem buildSystem;
  TestingFramework testingFramework;
  DeploymentTarget deploymentTarget;

public:
  bool deployApplication(string branch, string serverAddress) {
    cout << "\nFACADE: --- Initiating FULL DEPLOYMENT for branch: " << branch
         << " to " << serverAddress << " ---" << endl;
    bool success = true;

    try {
      vcs.pullLatestChanges(branch);

      if (!buildSystem.compileProject()) {
        cerr << "FACADE: DEPLOYMENT FAILED - Build compilation failed." << endl;
        return false;
      }

      string artifactPath = buildSystem.getArtifactPath();

      if (!testingFramework.runUnitTests()) {
        cerr << "FACADE: DEPLOYMENT FAILED - Unit tests failed." << endl;
        return false;
      }

      if (!testingFramework.runIntegrationTests()) {
        cerr << "FACADE: DEPLOYMENT FAILED - Integration tests failed." << endl;
        return false;
      }

      deploymentTarget.transferArtifact(artifactPath, serverAddress);
      deploymentTarget.activateNewVersion(serverAddress);

      cout << "FACADE: APPLICATION DEPLOYED SUCCESSFULLY to " << serverAddress
           << "!" << endl;
    } catch (exception &e) {
      cerr << "FACADE: DEPLOYMENT FAILED - An unexpected error occurred: "
           << e.what() << endl;
      success = false;
    }

    return success;
  }
};
class DeploymentAppFacade {
public:
  static void main() {
    DeploymentFacade deploymentFacade;

    // Deploy to production
    deploymentFacade.deployApplication("main", "prod.server.example.com");

    // Deploy a feature branch to staging
    cout << "\n--- Deploying feature branch to staging ---" << endl;
    deploymentFacade.deployApplication("feature/new-ui",
                                       "staging.server.example.com");
  }
};
int main() {
  DeploymentAppFacade::main();
  return 0;
}