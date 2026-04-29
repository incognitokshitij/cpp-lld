

#include <bits/stdc++.h>

using namespace std;
class Document {
public:
  string font;
  string theme;
  string headerStyle;
  int margin;

  void loadTemplate() {
    cout << "Loading fonts from disk..." << endl;
    cout << "Loading theme from disk..." << endl;
    cout << "Loading styles from disk..." << endl;
    font = "Arial";
    theme = "Corporate Blue";
    headerStyle = "Bold 14px";
    margin = 20;
  }
};

int main() {
  // user 1 clicks new document
  Document *doc1 = new Document();
  doc1->loadTemplate(); // disk hit

  // user 2 clicks new document
  Document *doc2 = new Document();
  doc2->loadTemplate(); // disk hit again

  // user 3 clicks new document
  Document *doc3 = new Document();
  doc3->loadTemplate(); // disk hit again

  // 100 users = 100 disk hits!
}