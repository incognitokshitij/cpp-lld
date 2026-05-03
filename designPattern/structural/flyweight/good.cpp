#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

// ============================================================
// 1. FLYWEIGHT — holds ONLY intrinsic (shareable) state
// ============================================================
class AsteroidFlyweight {
private:
  int length, width, weight;
  string color, texture, material;

public:
  AsteroidFlyweight(int l, int w, int wt, string col, string tex, string mat)
      : length(l), width(w), weight(wt), color(col), texture(tex),
        material(mat) {}

  // Extrinsic state is RECEIVED as parameters — not stored here
  void render(int posX, int posY, int velX, int velY) {
    cout << "Rendering " << color << ", " << texture << ", " << material
         << " asteroid at (" << posX << "," << posY << ") Size: " << length
         << "x" << width << " Velocity: (" << velX << ", " << velY << ")"
         << endl;
  }

  static size_t getMemoryUsage() {
    return sizeof(int) * 3 +    // length, width, weight
           sizeof(string) * 3 + // color, texture, material
           32 * 3;              // approx string char data
  }
};

// ============================================================
// 2. FLYWEIGHT FACTORY — creates & shares flyweights via a pool
// ============================================================
class AsteroidFactory {
private:
  static unordered_map<string, AsteroidFlyweight *> pool;

public:
  static AsteroidFlyweight *getAsteroid(int length, int width, int weight,
                                        string color, string texture,
                                        string material) {
    // Build a unique key from intrinsic values
    string key = to_string(length) + "_" + to_string(width) + "_" +
                 to_string(weight) + "_" + color + "_" + texture + "_" +
                 material;

    // If not in pool → create new and cache
    if (pool.find(key) == pool.end()) {
      pool[key] = new AsteroidFlyweight(length, width, weight, color, texture,
                                        material);
    }
    // Return SHARED instance
    return pool[key];
  }

  static int getFlyweightCount() { return pool.size(); }

  static size_t getTotalFlyweightMemory() {
    return pool.size() * AsteroidFlyweight::getMemoryUsage();
  }

  static void cleanup() {
    for (auto &pair : pool)
      delete pair.second;
    pool.clear();
  }
};
// Static member definition (required in C++)
unordered_map<string, AsteroidFlyweight *> AsteroidFactory::pool;

// ============================================================
// 3. CONTEXT — holds extrinsic state + reference to flyweight
// ============================================================
class AsteroidContext {
private:
  int posX, posY;
  int velocityX, velocityY;
  AsteroidFlyweight *flyweight; // pointer to SHARED flyweight

public:
  AsteroidContext(AsteroidFlyweight *fw, int x, int y, int vx, int vy)
      : flyweight(fw), posX(x), posY(y), velocityX(vx), velocityY(vy) {}

  // Client calls this — context passes its extrinsic state to flyweight
  void render() { flyweight->render(posX, posY, velocityX, velocityY); }

  static size_t getMemoryUsage() {
    return sizeof(int) * 4 + // posX, posY, velX, velY
           sizeof(void *);   // pointer to flyweight (~8 bytes on 64-bit)
  }
};

// ============================================================
// 4. CLIENT — the game
// ============================================================
class SpaceGameWithFlyweight {
private:
  vector<AsteroidContext *> asteroids;

public:
  void spawnAsteroids(int count) {
    cout << "\n=== Spawning " << count << " asteroids ===" << endl;

    vector<string> colors = {"Red", "Blue", "Gray"};
    vector<string> textures = {"Rocky", "Metallic", "Icy"};
    vector<string> materials = {"Iron", "Stone", "Ice"};
    int sizes[] = {25, 35, 45};

    for (int i = 0; i < count; i++) {
      int type = i % 3;

      // Get SHARED flyweight from factory (creates only if new combo)
      AsteroidFlyweight *fw = AsteroidFactory::getAsteroid(
          sizes[type], sizes[type], sizes[type] * 10, colors[type],
          textures[type], materials[type]);

      // Each context is small — just position/velocity + pointer
      asteroids.push_back(new AsteroidContext(fw,
                                              100 + i * 50, // posX
                                              200 + i * 30, // posY
                                              1, 2          // velocity
                                              ));
    }

    cout << "Created " << asteroids.size() << " asteroid contexts" << endl;
    cout << "Total UNIQUE flyweights: " << AsteroidFactory::getFlyweightCount()
         << endl;
  }

  void renderAll() {
    cout << "\n--- Rendering first 5 asteroids ---" << endl;
    for (int i = 0; i < min(5, (int)asteroids.size()); i++)
      asteroids[i]->render();
  }

  size_t calculateMemoryUsage() {
    size_t contextMem = asteroids.size() * AsteroidContext::getMemoryUsage();
    size_t flyweightMem = AsteroidFactory::getTotalFlyweightMemory();
    return contextMem + flyweightMem;
  }
};

int main() {
  const int ASTEROID_COUNT = 1000000;
  cout << "\n TESTING WITH FLYWEIGHT PATTERN" << endl;

  SpaceGameWithFlyweight *game = new SpaceGameWithFlyweight();
  game->spawnAsteroids(ASTEROID_COUNT);
  game->renderAll();

  size_t totalMemory = game->calculateMemoryUsage();
  cout << "\n=== MEMORY USAGE ===" << endl;
  cout << "Total asteroids: " << ASTEROID_COUNT << endl;
  cout << "Unique flyweights: " << AsteroidFactory::getFlyweightCount() << endl;
  cout << "Memory in MB: " << totalMemory / (1024.0 * 1024.0) << " MB" << endl;
  // Output: ~22 MB ✅

  AsteroidFactory::cleanup();
  return 0;
}