//
//  main.cpp
//  Rec 3
//
//  Created by Tracy Zhu on 2/12/21.
//


#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

struct Hydrocarbon {
    vector<string> names;
    int numC;
    int numH;
};

void open_stream (ifstream& stream);
void fill_vector (ifstream& file, vector<Hydrocarbon>& vec);
void sort_vector (vector<Hydrocarbon>& vec);
size_t locate_formula(const vector<Hydrocarbon>& vec, int car, int hyd);
void display_vector (const vector<Hydrocarbon>& vec);
void insert_info (vector<Hydrocarbon>& vec, const string& name, int carbon, int hydrogen);
void display_formula(const vector<Hydrocarbon>& vec);


int main(){
    ifstream ifs;
    open_stream(ifs);
    
    vector<Hydrocarbon> hydrocarbons;
    fill_vector(ifs, hydrocarbons);
    ifs.close();
    sort_vector (hydrocarbons);
    display_vector (hydrocarbons);
}

void open_stream (ifstream& stream){
    string filename;
    cout << "Plese enter your file name:" << endl;
    cin >> filename;
    stream.open(filename);
    
    while (!stream){
        stream.clear();
        cerr << "Please try again!" << endl;
        cout << "Plese enter your file name:" << endl;
        cin >> filename;
        stream.open(filename);
    }
}


size_t locate_formula(const vector<Hydrocarbon>& vec, int car, int hyd) {
    size_t i = 0;
    while (i < vec.size()) {
        if (vec[i].numC == car && vec[i].numH == hyd) {
            return i;
        }
        ++i;
    }
    return i;
}



void fill_vector (ifstream& file, vector<Hydrocarbon>& vec){
    
    string name;
    int num_carbon, num_hydro;
    char carbon, hydrogen;
    
    while (file >> name >> carbon >> num_carbon >> hydrogen >> num_hydro) {
        insert_info(vec, name, num_carbon, num_hydro);
    }
}


void insert_info(vector<Hydrocarbon>& vec, const string& name, int num_carbon, int num_hydro){
    size_t location;
    location = locate_formula (vec, num_carbon, num_hydro);
    if (location == vec.size()) {
        Hydrocarbon newhydro;
        newhydro.numC = num_carbon;
        newhydro.numH = num_hydro;
        newhydro.names.push_back(name);
        vec.push_back(newhydro);
    }
    else {
        vec[location].names.push_back(name);
    }
}


//bubble sort
void sort_vector (vector<Hydrocarbon>& vec) {
    for (size_t i = 0; i < vec.size() - 1; i++) {
        
        size_t min = i;
        
        for (size_t j = i + 1; j < vec.size(); j++) {
            if (vec[j].numC < vec[min].numC) {
                min = j;
            }
            
            else if (vec[j].numC == vec[min].numC) {
                
                if (vec[j].numH < vec[min].numH) {
                    min = j;
                }
            }
        
        }
        Hydrocarbon temp = vec [i];
        vec [i] = vec [min];
        vec [min] = temp;
    }
}


void display_vector(const vector<Hydrocarbon>& vec) {
    display_formula(vec);
}

void display_formula(const vector<Hydrocarbon>& vec){
    for (size_t i = 0; i < vec.size(); ++i) {
        cout << "C" << vec[i].numC << "H" << vec[i].numH << " ";
        
        for (size_t j = 0; j < vec[i].names.size(); ++j) {
            cout << vec[i].names[j] << " ";
        }
        cout << endl;
    }
}
    
