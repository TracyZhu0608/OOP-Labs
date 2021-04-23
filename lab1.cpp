
// Tracy Zhu yz5698

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;


int main() {

// Output
    cout << "Hello, World!\n";
    std::cout << "Hello, World!\n";
    
//Variables
    int x;    // when assign the string "felix" to x, it will be Semantic Issue (Compilation Error)
    int y = 17;
    int z = 2000000017;
    double pie = 3.14159;
    cout << "x: " << x << ", y: " << y << ", z: " << z << ", pie: " << pie << endl;
    cout << "x: " << sizeof(x) << ", y: " << sizeof(y) << ", z: " << sizeof(z) << ", pie: " << sizeof(pie) << endl;
    
//Conditions
    if ((y >= 10) && (y <= 20)) {
        cout << "y is true\n";
    }
    
    
//Lopps
// For loop
    for (int x = 10; x <= 20; ++x) {
        cout << x << ' ';
    }
    cout << endl;
    
// While loop
    int i = 10;
    while (i <= 20) {
    cout << i << ' ';
    ++i;
    }
    cout << endl;
    
//Do-while
    int m = 10;
    do {
    cout << m << ' ';
    ++m;
    } while (m <= 20); // Remember the semicolon
    cout << endl;
    

//Loop for openning files
    string filename;
    ifstream jab;
    do{
        cout << "filename: ";
        cin >> filename;
        jab.open(filename);
    } while(!jab);
        

//Loop for reading files
    string word;
    while (jab >> word) {
       cout << word << endl;
    }
    
    jab.close();
    

    
//Vector
//#10
    vector<int> v;
    for (i = 10; i <= 100; i=i+2) {
        v.push_back(i);
    }
    cout << endl;
//#11
    for (size_t i = 0; i < v.size(); ++i) {
    cout << v[i] << ' ';
    }
    cout << endl;
    
    for (int value : v) {
        cout << value << ' ';
    }
    cout << endl;
    
    for (size_t i = v.size(); i > 0; --i) {
    cout << v[i-1] << ' ';
    }
    cout << endl;
    
//#12
    vector<int> p{2, 3, 5, 7, 11, 13, 17, 19};
    for (int value : p) {
        cout << value << ' ';
    }
    cout << endl;
    
}



