#include <bits/stdc++.h>
using namespace std;

class Library {
public:
    void borrowBook() {
        cout << "Book borrowed from library" << endl;
    }
};

class Student {
private:
    Library* lib;  // Student knows Library

public:
    Student(Library* l) {
        lib = l;
    }

    void takeBook() {
        lib->borrowBook();
    }
};

int main() {
    Library* l = new Library();

    Student s(l);
    s.takeBook();

    return 0;
}