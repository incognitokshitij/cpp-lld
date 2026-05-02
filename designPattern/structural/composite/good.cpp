

#include <bits/stdc++.h>

using namespace std;

class FileSystemItem {
public:
  virtual void ls(int indent = 0) = 0;           // list contents
  virtual void openAll(int indent = 0) = 0;      // expand full hierarchy
  virtual int getSize() = 0;                     // size of this item
  virtual FileSystemItem *cd(string target) = 0; // change directory
  virtual string getName() = 0;
  virtual bool isFolder() = 0;
  virtual ~FileSystemItem() {}
};

class File : public FileSystemItem {
  string name;
  int size;

public:
  File(string n, int s) : name(n), size(s) {}

  void ls(int indent = 0) override {
    cout << string(indent, ' ') << name << "\n";
  }
  void openAll(int indent = 0) override {
    cout << string(indent, ' ') << name << "\n"; // leaf → just print self
  }
  int getSize() override { return size; }
  FileSystemItem *cd(string) override {
    return nullptr;
  } // can't cd into a file
  string getName() override { return name; }
  bool isFolder() override { return false; }
};

class Folder : public FileSystemItem {
  string name;
  vector<FileSystemItem *> children; // ONE list — holds Files AND Folders
public:
  Folder(string n) : name(n) {}

  void add(FileSystemItem *item) { children.push_back(item); }

  void ls(int indent = 0) override {
    for (auto child : children) {
      string prefix = child->isFolder() ? "+ " : "  ";
      cout << string(indent, ' ') << prefix << child->getName() << "\n";
    }
  }

  void openAll(int indent = 0) override {
    cout << string(indent, ' ') << "[+] " << name << "\n";
    for (auto child : children)
      child->openAll(indent + 4); // recursive — works for both types!
  }

  int getSize() override {
    int total = 0;
    for (auto child : children)
      total += child->getSize(); // recurse until leaf
    return total;
  }

  FileSystemItem *cd(string target) override {
    for (auto child : children)
      if (child->isFolder() && child->getName() == target)
        return child; // found the sub-folder
    return nullptr;
  }

  string getName() override { return name; }
  bool isFolder() override { return true; }
};

int main() {
  Folder *root = new Folder("root");
  root->add(new File("file1.txt", 1));
  root->add(new File("file2.txt", 1));

  Folder *docs = new Folder("docs");
  docs->add(new File("resume.pdf", 2));
  docs->add(new File("notes.txt", 1));
  root->add(docs);

  root->openAll();         // expands entire hierarchy
  root->ls();              // shows immediate children only
  docs->ls();              // shows docs' contents
  cout << root->getSize(); // prints 5

  FileSystemItem *cwd = root->cd("docs");
  if (cwd)
    cwd->ls(); // we're now inside docs

  return 0;
}