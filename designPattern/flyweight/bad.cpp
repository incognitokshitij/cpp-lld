#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Asteroid {
private:
  // Intrinsic (DUPLICATED across millions of objects — wasteful!)
  int length, width, weight;
  string color, texture, material;

  // Extrinsic (genuinely unique per asteroid)
  int posX, posY;
  int velocityX, velocityY;

public:
  Asteroid(int l, int w, int wt, string col, string tex, string mat, int pX,
           int pY, int vX, int vY) {
    length = l;
    width = w;
    weight = wt;
    color = col;
    texture = tex;
    material = mat;
    posX = pX;
    posY = pY;
    velocityX = vX;
    velocityY = vY;
  }

  void render() {
    cout << "Rendering " << color << ", " << texture << ", " << material
         << " asteroid at (" << posX << "," << posY << ") Size: " << length
         << "x" << width << " Velocity: (" << velocityX << ", " << velocityY
         << ")" << endl;
  }

  static size_t getMemoryUsage() {
    return sizeof(int) * 7 +    // length, width, weight, posX, posY, velX, velY
           sizeof(string) * 3 + // color, texture, material
           32 * 3;              // approx string char data
  }
};

class SpaceGame {
private:
  vector<Asteroid *> asteroids;

public:
  void spawnAsteroids(int count) {
    vector<string> colors = {"Red", "Blue", "Gray"};
    vector<string> textures = {"Rocky", "Metallic", "Icy"};
    vector<string> materials = {"Iron", "Stone", "Ice"};
    int sizes[] = {25, 35, 45};

    for (int i = 0; i < count; i++) {
      int type = i % 3;
      asteroids.push_back(new Asteroid(sizes[type], sizes[type],
                                       sizes[type] * 10, colors[type],
                                       textures[type], materials[type],
                                       100 + i * 50, // posX
                                       200 + i * 30, // posY
                                       1, 2          // velocity
                                       ));
    }
    cout << "Created " << asteroids.size() << " asteroid objects" << endl;
  }

  void renderAll() {
    for (int i = 0; i < min(5, (int)asteroids.size()); i++)
      asteroids[i]->render();
  }

  size_t calculateMemoryUsage() {
    return asteroids.size() * Asteroid::getMemoryUsage();
  }
};

int main() {
  const int ASTEROID_COUNT = 1000000;
  cout << "\n TESTING WITHOUT FLYWEIGHT PATTERN" << endl;

  SpaceGame *game = new SpaceGame();
  game->spawnAsteroids(ASTEROID_COUNT);
  game->renderAll();

  size_t totalMemory = game->calculateMemoryUsage();
  cout << "Memory in MB: " << totalMemory / (1024.0 * 1024.0) << " MB" << endl;
  // Output: ~187 MB 💥
  return 0;
}