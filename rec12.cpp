//
//  main.cpp
//  rec 12
//
//  Created by Tracy Zhu on 20/11/20.
//

#include <cstdlib>
#include <iostream>
using namespace std;

class List {
    struct Node {
        Node(int data = 0, Node* prev = nullptr, Node* next = nullptr)
            : data(data), prev(prev), next(next)
        {}
        int data;
        Node* prev;
        Node* next;
    };

    friend ostream& operator<<(ostream& os, const List& list) {
        Node* ptr = list.header->next;
        while (ptr != list.trailer) {
            os << ptr->data << ' ';
            ptr = ptr->next;
        }
        return os;
    }
public:
    
    class Iterator {
        friend List;
    public:
        Iterator(Node* node) : ptr(node) {}

        Iterator& operator++() {
            if(ptr) ptr = ptr->next;
            return *this;
        }
        Iterator& operator--() {
            if (ptr && ptr->prev) ptr = ptr->prev;
            return *this;
        }

        friend bool operator==(const Iterator& lhs, const Iterator& rhs) {
                return lhs.ptr == rhs.ptr;
        }
        friend bool operator!=(const Iterator& lhs, const Iterator& rhs) {
            return !(lhs == rhs);
        }

        int operator*() const { return ptr->data; }
        int& operator*() { return ptr->data; }
    
    private:
        Node* ptr;
    };
    
    
    
    
    
    /* ==================================== */

    List() : theSize(0), header(new Node()),trailer( new Node()){
        header->next = trailer;
        trailer->prev = header;
    }

    int& operator[](size_t index) const {
        Node* ptr = header->next;
        while (index) {
            ptr = ptr->next;
            --index;
        }
        return ptr->data;
    }
    
    int& operator[](size_t index) {
        Node* ptr = header->next;
        while (index) {
            ptr = ptr->next;
            --index;
        }
        return ptr->data;
    }

    void push_back(int data) {
        Node* newNode = new Node(data, trailer->prev, trailer);
        newNode->prev->next = newNode;
        trailer->prev = newNode;
        ++theSize;
    }

    void pop_back() {
        Node* toDelete = trailer->prev;
        trailer->prev = toDelete->prev;
        toDelete->prev->next = trailer;
        delete toDelete;
        --theSize;
    }

    void push_front(int data) {
        Node* newNode = new Node(data, header, header->next);
        header->next->prev = newNode;
        header->next = newNode;
        ++theSize;
    }

    void pop_front() {
        Node* toDelete = header->next;
        header->next = toDelete->next;
        toDelete->next->prev = header;
        delete(toDelete);
        --theSize;
    }

    Iterator insert(Iterator iter, int data) {
        Node* newNode = new Node(data, iter.ptr->prev, iter.ptr);
        newNode->prev->next = newNode;
        iter.ptr->prev = newNode;
        ++theSize;
        return Iterator(newNode);
    }

    Iterator erase(Iterator iter) {
        Node* toDelete = iter.ptr;
        toDelete->prev->next = toDelete->next;
        toDelete->next->prev = toDelete->prev;
        Iterator returnIter = Iterator(toDelete->next);
        delete toDelete;
        --theSize;
        return returnIter;
    }

    void clear() {
        while (theSize) {
            pop_back();
        }
    }

    Iterator begin() { return Iterator(header->next); }
    Iterator end() { return Iterator(trailer); }

    int front() const { return header->next->data; }
    int& front() { return header->next->data; }
    int back() const { return trailer->prev->data; }
    int& back() { return trailer->prev->data; }

    size_t size() const { return theSize; }
private:
    size_t theSize;
    Node* header;
    Node* trailer;
};

// Task 1
void printListInfo(const List& myList) {
    cout << "size: " << myList.size()
        << ", front: " << myList.front()
        << ", back(): " << myList.back()
        << ", list: " << myList << endl;
}

// The following should not compile. Check that it does not.
// void changeFrontAndBackConst(const List& theList){
//     theList.front() = 17;
//     theList.back() = 42;
// }

void changeFrontAndBack(List& theList) {
    theList.front() = 17;
    theList.back() = 42;
}

// Task 4
void printListSlow(const List& myList) {
    for (size_t i = 0; i < myList.size(); ++i) {
        cout << myList[i] << ' ';
    }
    cout << endl;
}

// // Task 8
// void doNothing(List aList) {
//     cout << "In doNothing\n";
//     printListInfo(aList);
//     cout << endl;
//     cout << "Leaving doNothing\n";
// }

int main() {

    // Task 1
    cout << "\n------Task One------\n";
    List myList;
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        cout << "myList.push_back(" << i * i << ");\n";
        myList.push_back(i * i);
        printListInfo(myList);
    }
    cout << "===================\n";

    cout << "Modify the first and last items, and display the results\n";
    changeFrontAndBack(myList);
    printListInfo(myList);
    cout << "===================\n";

    cout << "Remove the items with pop_back\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.pop_back();
    }
    cout << "===================\n";

    // Task 2
    cout << "\n------Task Two------\n";
    cout << "Fill empty list with push_front: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        cout << "myList2.push_front(" << i * i << ");\n";
        myList.push_front(i * i);
        printListInfo(myList);
    }
    cout << "===================\n";
    cout << "Remove the items with pop_front\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.pop_front();
    }
    cout << "===================\n";

    // Task 3
    cout << "\n------Task Three------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        myList.push_back(i * i);
    }
    printListInfo(myList);
    cout << "Now clear\n";
    myList.clear();
    cout << "Size: " << myList.size() << ", list: " << myList << endl;
    cout << "===================\n";

    // Task 4
    cout << "\n------Task Four------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i)  myList.push_back(i * i);
    cout << "Display elements with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
    cout << endl;
    cout << "Add one to each element with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) myList[i] += 1;
    cout << "And print it out again with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
    cout << endl;
    cout << "Now calling a function, printListSlow, to do the same thing\n";
    printListSlow(myList);
    cout << "Finally, for this task, using the index operator to modify\n"
        << "the data in the third item in the list\n"
        << "and then using printListSlow to display it again\n";
    myList[2] = 42;
    printListSlow(myList);


    // Task 5
    cout << "\n------Task Five------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i)  myList.push_back(i * i);
    printListInfo(myList);
    cout << "Now display the elements in a ranged for\n";
    for (int x : myList) cout << x << ' ';
    cout << endl;
    cout << "And again using the iterator type directly:\n";
    // Note you can choose to nest the iterator class or not, your choice.
    //for (iterator iter = myList.begin(); iter != myList.end(); ++iter) {
    for (List::Iterator iter = myList.begin(); iter != myList.end(); ++iter) {
        cout << *iter << ' ';
    }
    cout << endl;
    cout << "WOW!!! (I thought it was cool.)\n";

    // Task 6
    cout << "\n------Task Six------\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i * i);
    printListInfo(myList);
    cout << "Filling an empty list with insert at begin(): "
        << "i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.begin(), i * i);
    printListInfo(myList);
    // ***Need test for insert other than begin/end***
    cout << "===================\n";

    // Task 7
    cout << "\n------Task Seven------\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i * i);
    cout << "Erasing the elements in the list, starting from the beginning\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.erase(myList.begin());
    }
    // ***Need test for erase other than begin/end***
    cout << "===================\n";

    // // Task 8
    // cout << "\n------Task Eight------\n";
    // cout << "Copy control\n";
    // cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    // myList.clear();
    // for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    // printListInfo(myList);
    // cout << "Calling doNothing(myList)\n";
    // doNothing(myList);
    // cout << "Back from doNothing(myList)\n";
    // printListInfo(myList);

    // cout << "Filling listTwo with insert at begin: i*i for i from 0 to 9\n";
    // List listTwo;
    // for (int i = 0; i < 10; ++i) listTwo.insert(listTwo.begin(), i*i);
    // printListInfo(listTwo);
    // cout << "listTwo = myList\n";
    // listTwo = myList;
    // cout << "myList: ";
    // printListInfo(myList);
    // cout << "listTwo: ";
    // printListInfo(listTwo);
    // cout << "===================\n";
}
