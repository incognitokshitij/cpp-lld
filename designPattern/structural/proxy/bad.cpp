

#include <bits/stdc++.h>

using namespace std;

class Image {
public:
  virtual void display() = 0;
  virtual string getFileName() = 0;
  virtual ~Image() {}
};

class HighResolutionImage : public Image {
private:
  string fileName;
  char *imageData;

  void loadImageFromDisk() {
    cout << "Loading image: " << fileName
         << " from disk (Expensive Operation)..." << endl;
    this_thread::sleep_for(chrono::milliseconds(200));
    imageData = new char[10 * 1024 * 1024];
    cout << "Image " << fileName << " loaded successfully." << endl;
  }

public:
  HighResolutionImage(string fileName)
      : fileName(fileName), imageData(nullptr) {
    loadImageFromDisk();
  }

  ~HighResolutionImage() { delete[] imageData; }

  void display() override { cout << "Displaying image: " << fileName << endl; }

  string getFileName() override { return fileName; }
};

int main() {
  cout << "Application Started. Initializing images for gallery..." << endl;

  Image *image1 = new HighResolutionImage("photo1.jpg");
  Image *image2 = new HighResolutionImage("photo2.png");
  Image *image3 = new HighResolutionImage("photo3.gif");

  cout << "\nGallery initialized. User might view an image now." << endl;

  cout << "User requests to display " << image1->getFileName() << endl;
  image1->display();

  cout << "\nUser requests to display " << image3->getFileName() << endl;
  image3->display();

  cout << "\nApplication finished." << endl;

  delete image1;
  delete image2;
  delete image3;
  return 0;
}