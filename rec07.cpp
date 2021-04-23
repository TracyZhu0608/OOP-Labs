//
//  main.cpp
//  Rec 7
//
/*
  Recitation 06
  CS2124
 
  Focus: Dynamic arrays and copy control
 */

#include <string>
#include <iostream>
using namespace std;

class Position {
    friend ostream& operator<<(ostream& os, const Position& rhs) {
        os << '[' << rhs.title << ',' << rhs.salary << ']';
        return os;
    }
public:
    Position(const string& aTitle, double aSalary)
        : title(aTitle), salary(aSalary) {}
    const string& getTitle() const { return title; }
    double getSalary() const { return salary; }
    void changeSalaryTo(double d) { salary = d; }
private:
    string title;
    double salary;
}; // class Position

class Entry {
    friend ostream& operator<<(ostream& os, const Entry& rhs) {
        os << rhs.name << ' ' << rhs.room
            << ' ' << rhs.phone << ", " << *rhs.pos;
        return os;
    }
public:
    Entry(const string& name, unsigned room, unsigned phone, Position& position)
        : name(name), room(room), phone(phone), pos(&position) {
    }
    const string& getName() const { return name; }
    unsigned getPhone() const { return phone; }
private:
    string name;
    unsigned room;
    unsigned phone;
    Position* pos;
}; // class Entry

class Directory {
    // Overload output operator
    friend ostream& operator<<(ostream& os, const Directory& directory) {
        for (size_t index = 0; index < directory.size; index++) {
            os << *directory.entries[index] << endl;
        }
        return os;
    }
public:
    // Of course the first function you need to write for this (or
    // any) class is...
    // ???
    // ...
    Directory() {
        size = 0;
        capacity = 1;
        entries = new Entry* [capacity];
    }

    Directory(const Directory& rhsDir) {
        cout << "Copy Constructor Running\n";
        size = rhsDir.size;
        capacity = rhsDir.capacity;
        entries = new Entry * [capacity];
        for (size_t index = 0; index < size; index++) {
            entries[index] = new Entry(*rhsDir.entries[index]);
        }
    }

    Directory& operator=(const Directory& rhsDir) {
        cout << "Assignment Constructor Running\n";
        if (this != &rhsDir) {
            for (size_t index = 0; index < size; index++) {
                delete entries[index];
                entries[index] = nullptr;
            }
            delete[] entries;
            size = rhsDir.size;
            capacity = rhsDir.capacity;
            entries = new Entry * [capacity];
            for (size_t index = 0; index < size; index++) {
                entries[index] = new Entry(*rhsDir.entries[index]);
            }
        }
        return *this;
    }

    ~Directory() {
        cout << "Deconstructor Running...\n";
        for (size_t index = 0; index < size; index++) {
            delete(entries[index]);
            entries[index] = nullptr;
        }
        delete[] entries;
    }

    unsigned operator[](const string& name) const {
        cout << "[] Operator Running...\n";
        for (size_t index = 0; index < size; index++) {
            if (entries[index]->getName() == name) {
                return entries[index]->getPhone();
            }
        }
        return 0;
    }


    // We'll get you started with the add method, but obviously you
    // have a lot of work to do here.
    void add(const string& name, unsigned room, unsigned ph, Position& pos) {
        if (size == capacity) {
            // something is missing!!!  Add it!
            Entry** oldEntries = entries;
            entries = new Entry * [2 * capacity];
            for (size_t index = 0; index < capacity; index++) {
                entries[index] = oldEntries[index];
            }
            delete[] oldEntries;
            capacity *= 2;
        } // if
        entries[size] = new Entry(name, room, ph, pos);
        ++size;
    } // add

private:
    Entry** entries;
    size_t size;
    size_t capacity;
}; // class Directory

void doNothing(Directory dir) { cout << dir << endl; }

int main() {

    // Note that the Postion objects are NOT on the heap.
    Position boss("Boss", 3141.59);
    Position pointyHair("Pointy Hair", 271.83);
    Position techie("Techie", 14142.13);
    Position peon("Peonissimo", 34.79);

    // Create a Directory
    Directory d;
    d.add("Marilyn", 123, 4567, boss);
    cout << d << endl;

    Directory d2 = d;    // What function is being used??
    d2.add("Gallagher", 111, 2222, techie);
    d2.add("Carmack", 314, 1592, techie);
    cout << d << endl;

    cout << "Calling doNothing\n";
    doNothing(d2);
    cout << "Back from doNothing\n";

    Directory d3;
    d3 = d2;

    // Should display 1592
    cout << d2["Carmack"] << endl;

} // main
