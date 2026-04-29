

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

  Document *clone() {
    return new Document(*this); // instant, no disk loading
  }
};

int main() {
  // load once at startup
  Document *templateDoc = new Document();
  templateDoc->loadTemplate();
  cout << "--- Template ready ---" << endl;

  // every new document is instant
  Document *doc1 = templateDoc->clone();
  Document *doc2 = templateDoc->clone();
  Document *doc3 = templateDoc->clone();

  // user customizes only what they need
  doc1->font = "Times New Roman";
  doc2->theme = "Dark Mode";
}