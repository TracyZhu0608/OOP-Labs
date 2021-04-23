//
//  main.cpp
//  rec 13
//
//  Created by Tracy Zhu on 4/12/20.
//

#include <iostream>
#include <fstream>
#include <vector>      // task 1
#include <list>        // task 2
#include <algorithm>   // task 3
#include <string>      // task 21
#include <set>         // task 22
#include <map>         // task 23
using namespace std;

//task 9
void printList(const list<int>& nums) {
    for (list<int>::const_iterator iter = nums.begin(); iter != nums.end(); ++iter) {
        cout << *iter << ' ';
    }
}

//task 10
void printList2(const list<int>& nums) {
    for (const int myNum : nums) {
        cout << myNum << ' ';
    }
}

//task 11
void printEveryOther(const list<int>& nums) {
    for (auto iter = nums.begin(); iter != nums.end(); ++iter) {
        cout << *iter << ' ';
        ++iter;
    }
    cout << endl;
}

//task 12
list<int>::const_iterator myFind(const list<int>& nums, int target) {
    for (list<int>::const_iterator p = nums.begin(); p != nums.end(); ++p) {
        if (*p == target) {
            return p;
        }
    }
    return nums.end();
}

//task 13
auto myFind2(const list<int>& nums, int target) {
    for (auto p = nums.begin(); p != nums.end(); ++p){
        if (*p == target) {
            return p;
        }
    }
    return nums.end();
}

//task 15
bool isEven(int val) {
    return val % 2 == 0;
}

//task 16
class isEvenFunctor {
public:
    bool operator()(int n) const {
        return n % 2 == 0;
    }
};

//task 19
list<int>::const_iterator ourFind( list<int>::iterator start,  list<int>::iterator stop,  int target) {
    cout << "My Find is running\n";
    for (list<int>::iterator p = start; p != stop; ++p) {
        if (*p == target) {
            return p;
        }
    }
    return stop;
}

//task 20
template<typename T, typename U>
T ourFind(T start, T stop, U target) {
    cout << "My Find Template is running\n";
    for (T p = start; p != stop; ++p) {
        if (*p == target) {
            return p;
        }
    }
    return stop;
}

int main() {
    // 1. Create a vector with some values and display using ranged for
    cout << "Task 1:\n";
    vector<int> nums = { 1,3,6,2,4,5 };
    for (int num : nums) {
        cout << num << ' ';
    }
    cout << "\n=======\n";

    // 2. Initalize a list as a copy of values from the vector
    cout << "Task 2:\n";
    list<int> nums2(nums.begin(), nums.end());
    for (const int& num : nums) {
        cout << num << ' ';
    }
    cout << "\n=======\n";


    // 3. Sort the original vector.  Display both the vector and the list
    cout << "Task 3:\n";
    sort(nums.begin(), nums.end());
    cout << "Sorted Vector: " << endl;
    for (int num : nums) {
        cout << num << ' ';
    }
    cout << "\nList: " << endl;
    for (int num : nums2) {
        cout << num << ' ';
    }
    cout << "\n=======\n";


    // 4. print every other element of the vector.
    cout << "Task 4:\n";
    for (size_t i = 0; i < nums.size(); i += 2) {
        cout << nums[i] << ' ';
    }
    cout << "\n=======\n";


    // 5. Attempt to print every other element of the list using the
    //    same technique.
    cout << "Task 5:\n";
    /*for (size_t i = 0; i < nums2.size(); i += 2) {
    cout << nums2[i] << ' ';
    }*/
    cout << "does not work because list does not have an operator[]";
    cout << "\n=======\n";

    //
    // Iterators
    //

    // 6. Repeat task 4 using iterators.  Do not use auto;
    cout << "Task 6:\n";
    for (vector<int>::iterator iter = nums.begin(); iter != nums.end(); iter += 2) {
        cout << *iter << ' ';
    }
    cout << "\n=======\n";

    // 7. Repeat the previous task using the list.  Again, do not use auto.
    //    Note that you cannot use the same simple mechanism to bump
    //    the iterator as in task 6.
    cout << "Task 7:\n";
    for (list<int>::iterator iter = nums2.begin(); iter != nums2.end(); ++iter) {
        cout << *iter << ' ';
        ++iter;
    }
    cout << "\n=======\n";

    // 8. Sorting a list
    cout << "Task 8:\n";
    nums2.sort();
    for (int num : nums2) {
        cout << num << ' ';
    }
    cout << "\n=======\n";

    // 9. Calling the function to print the list
    cout << "Task 9:\n";
    printList(nums2);
    cout << endl;
    cout << "=======\n";

    // 10. Calling the function that prints the list, using ranged-for
    cout << "Task 10:\n";
    printList2(nums2);
    cout << endl;
    cout << "=======\n";

    //
    // Auto
    //

    // 11. Calling the function that, using auto, prints alterate
    // items in the list
    cout << "Task 11:\n";
    printEveryOther(nums2);
    cout << endl;
    cout << "=======\n";


    // 12.  Write a function find that takes a list and value to search for.
    //      What should we return if not found
    cout << "Task 12:\n";
    if (myFind(nums2, 4) == nums2.end()) {
        cout << "not found";
    }
    else {
        cout << *myFind(nums2, 4);
    }

    if (myFind(nums2, 8) == nums2.end()) {
        cout << "not found";
    }
    else {
        cout << *myFind(nums2, 8);
    }

    cout << endl;
    cout << "=======\n";

    // 13.  Write a function find that takes a list and value to search for.
    //      What should we return if not found
    cout << "Task 13:\n";
    if (myFind2(nums2, 4) == nums2.end()) {
        cout << "not found";
    }
    else {
        cout << *myFind2(nums2, 4);
    }

    cout << "Task 13:\n";
    if (myFind2(nums2, 8) == nums2.end()) {
        cout << "not found";
    }
    else {
        cout << *myFind2(nums2, 8);
    }

    cout << endl;
    cout << "=======\n";

    //
    // Generic Algorithms
    //

    // 14. Generic algorithms: find
    cout << "Task 14:\n";
    if (find(nums2.begin(), nums2.end(), 3) == nums2.end()) {
        cout << "not found";
    }
    else {
        cout << *find(nums2.begin(), nums2.end(), 3);
    }

    cout << endl;
    cout << "=======\n";



    // 15. Generic algorithms: find_if
    cout << "Task 15:\n";
    if (find_if(nums2.begin(), nums2.end(), isEven) == nums2.end()) {
        cout << "not found";
    }
    else {
        cout << *find_if(nums2.begin(), nums2.end(), isEven);
    }
    cout << "\n=======\n";

    // 16. Functor
    cout << "Task 16:\n";
    cout << *find_if(nums2.begin(), nums2.end(), isEvenFunctor());
    cout << endl;
    cout << "=======\n";

    // 17. Lambda
    cout << "Task 17:\n";
    cout << *find_if(nums2.begin(), nums2.end(), [](int n)->bool {return n % 2 == 0; });
    cout << "\n=======\n";
    cout << "=======\n";

    // 18. Generic algorithms: copy to an array
    cout << "Task 18:\n";
    int arr[6];
    copy(nums.begin(), nums.end(), arr);
    for (int num : arr) {
        cout << num << ' ';
    }
    cout << endl;
    cout << *find(arr, arr + 6, 3);
    cout << endl;


    cout << "=======\n";

    //
    // Templated Functions
    //

    // 19. Implement find as a function for lists
    cout << "Task 19:\n";
    if (ourFind(nums2.begin(), nums2.end(), 3) == nums2.end()) {
        cout << "not found";
    }
    else {
        cout << *ourFind(nums2.begin(), nums2.end(), 3);
    }
    cout << "\n=======\n";


    // 20. Implement find as a templated function
    if (ourFind(nums.begin(), nums.end(), 3) == nums.end()) {
        cout << "not found";
    }
    else {
        cout << *ourFind(nums.begin(), nums.end(), 3);
    }
    if (ourFind(nums2.begin(), nums2.end(), 3) == nums2.end()) {
        cout << "not found";
    }
    else {
        cout << *ourFind(nums2.begin(), nums2.end(), 3);
    }
    cout << "\n=======\n";
    //
    // Associative collections
    //



    // 21. Using a vector of strings, print a line showing the number
    //     of distinct words and the words themselves.
    cout << "Task 21:\n";
    vector<string> pooh;
    string word;
    vector<string>::iterator newWord;
    ifstream ifs("pooh-nopunc.txt");
    if (!ifs) {
        cerr << "failed to open pooh";
        exit(1);
    }

    while (ifs >> word) {
        newWord = find(pooh.begin(), pooh.end(), word);
        if (newWord == pooh.end()) {
            pooh.push_back(word);
        }

    }
    int count = 0;
    for (const string& word : pooh) {
        cout << word << ' ';
        count += 1;
    }
    cout << "\n" << count << "\n";
    ifs.close();
    cout << "\n=======\n";



    // 22. Repeating previous step, but using the set
    cout << "Task 22:\n";
    set<string> pooh2;
    string word2;
    set<string>::iterator newWord2;
    ifstream ifs2("pooh-nopunc.txt");
    if (!ifs2) {
        cerr << "failed to open life";
        exit(1);
    }

    while (ifs2 >> word2) {
        pooh2.insert(word2);

    }

    for (const string& word : pooh2) {
        cout << word << ' ';
    }
    cout << "\n" << pooh2.size() << "\n";

    ifs2.close();
    cout << "=======\n";


    // 23. Word co-occurence using map
    cout << "Task 23:\n";
    map<string, vector<int>> pooh3;
    string word3;
    int pos = 0;
    ifstream ifs3("pooh-nopunc.txt");
    if (!ifs3) {
        cerr << "failed to open life";
        exit(1);
    }

    while (ifs3 >> word3) {
        pooh3[word3].push_back(pos);
        pos += 1;
    }

    for (const auto& word : pooh3) {
        cout << word.first << "; ";
        for (const int& location : word.second) {
            cout << location << ' ';
        }
        cout << endl;
    }
    cout << "\n" << pooh3.size() << "\n";

    ifs3.close();
    cout << "=======\n";
}
