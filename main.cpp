//
//  main.cpp
//  rec 14
//
//  Created by Tracy Zhu on 11/12/20.
//

#include <iostream>
#include <vector>
#include <exception>
using namespace std;

struct Node {
    Node(int data = 0, Node* next = nullptr) : data(data), next(next) {}
    int data;
    Node* next;
};

struct TNode {
    TNode(int data = 0, TNode* left = nullptr, TNode* right = nullptr)
        : data(data), left(left), right(right) {}
    int data;
    TNode *left, *right;
};

//task1
bool has_even_ones (int num) {
    if (num == 0) return true;
    if (num == 1) return false;

    return (!((num % 2) == has_even_ones(num / 2)));
}



//taks2
Node* sum_up(Node* l1, Node* l2){

    if (!l1 && !l2) return nullptr;
   
    if (!l2) {
        Node* result = new Node(l1->data, sum_up(l1->next, l2));
        return result;
    }
    
    if (!l1) {
        Node* result = new Node(l2->data, sum_up(l1, l2->next));
        return result;
    }
  
    Node* result = new Node(l1->data + l2->data, sum_up(l1->next, l2->next));
    return result;
}



void listAddHead(Node*& headPtr, int entry) {
    headPtr = new Node(entry, headPtr);
}
// create a list
Node* listBuild(const vector<int>& vals) {
    Node* result = nullptr;
    for (size_t index = vals.size(); index > 0; --index) {
        listAddHead(result, vals[index-1]);
    }
    return result;
}


void listDisplay(const Node* headptr) {
    while (headptr) {
        cout << headptr->data << ' ';
        headptr = headptr->next;
    }
    cout << endl;
}


//task 3
int maxTree(TNode* root) {
    if (!root) throw invalid_argument("Empty Tree");
    
    int maxVal = root->data;

    if (root->left){
        maxVal = max(maxVal, maxTree(root->left));
    }
    if (root->right){
        maxVal = max(maxVal, maxTree(root->right));
    }

    return maxVal;
}



//task 4
bool palindrome(char* word, int length) {
    if (length < 2){
        return true;
    }
    
    return (word[0] == word[length - 1]) && palindrome(word + 1, length - 2);
}

//task 5
int towers(int n, char start , char target, char spare){
    if (n == 0){
        return 0;
    }
    return towers(n-1, start, spare, target) + 1 + towers(n-1, spare, target, start);
}

//task 6
void mystery(int n) {
    if (n > 1) {
        cout << 'a';
        mystery(n / 2);
        cout << 'b';
        mystery(n / 2);
    }
    cout << 'c';
}
// n = 4

/*
n = 1, c
n = 2, a c b c c
n = 4, a acbcc b acbcc c
*/

int main() {
    cout << "TASK 1 TEST CASES" << endl;
    cout << boolalpha;
    cout << has_even_ones(15) << endl; // T
    cout << boolalpha;
    cout << has_even_ones(16) << endl; // F
    cout << boolalpha;
    cout << has_even_ones(5) << endl; // T
    cout << boolalpha;
    cout << has_even_ones(11) << endl; // F
    cout << "====================" << endl;



    cout << "TASK 2 TEST CASES" << endl;
    Node* aL = listBuild({1, 2});
    Node* bL = listBuild({3, 4});
    Node* cL = sum_up(aL, bL);
    listDisplay(cL); // {4, 6}
    Node* dL = listBuild({1, 3, 4});
    Node* eL = listBuild({2});
    Node* fL = sum_up(dL, eL);
    listDisplay(fL); //  {3, 3, 4}
    Node* gL = listBuild({1});
    Node* hL = listBuild({2, 3});
    Node* iL = sum_up(gL, hL);
    listDisplay(iL); // {3, 3}
    cout << "====================" << endl;

    cout << "TASK 3 TEST CASES" << endl;
    TNode a(1), b(2), c(4), d(8, &a, &b), e(16, &c), f(32, &d, &e);
    try {
        cout << maxTree(&f) << endl;
    }
    catch (invalid_argument ex){
        cerr << "Caught exception " << ex.what() << endl;
    }
    TNode* test= nullptr;
    try {
        cout << maxTree(test) << endl;
    }
    catch (invalid_argument ex){
        cerr << "Caught exception " << ex.what() << endl;
    }
    cout << "====================" << endl;

    cout << "TASK 4 TEST CASES" << endl;
    char s[] = "racecar";
    if (palindrome(s, 7)){
        cout << "Yes" << endl;
    }
    else cout << "No" << endl;
    
    char t[] = "noon";
    if (palindrome(t, 4)){
        cout << "Yes" << endl;
    }
    else cout << "No" << endl;
    
    
    char u[] = "abcde";
    if (palindrome(u, 5)){
        cout << "Yes" << endl;
    }
    else cout << "No" << endl;
    cout << "====================" << endl;

    cout << "TASK 5 TEST CASES" << endl;
    cout << towers(1, 'a', 'b', 'c') << endl; // 1
    cout << towers(2, 'a', 'b', 'c') << endl; // 3
    cout << towers(3, 'a', 'b', 'c') << endl; // 7
    cout << towers(4, 'a', 'b', 'c') << endl; // 15
    cout << towers(5, 'a', 'b', 'c') << endl; // 31
    cout << towers(6, 'a', 'b', 'c') << endl; // 63
    cout << towers(7, 'a', 'b', 'c') << endl; // 127
    cout << towers(8, 'a', 'b', 'c') << endl; // 255
    cout << towers(9, 'a', 'b', 'c') << endl; // 511
    cout << towers(10, 'a', 'b', 'c') << endl; // 1023
    cout << "====================" << endl;

    cout << "TASK 6 TEST CASES" << endl;
    for (int i = 0; i < 11; ++i) {
        mystery(i);
        cout << endl;
    }
    cout << "====================" << endl;
}
