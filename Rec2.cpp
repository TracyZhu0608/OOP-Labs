//  Tracy Zhu yz5698
//  Rec2: Conway's Game of life
//  A program which inplementes the Conway's Game of life fllowed by the rule of life

//  Created by Tracy Zhu on 11/09/20.
//  Copyright © 2020 Tracy Zhu. All rights reserved.


#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

void initialize(vector<string>& filelines, ifstream& initial_state) {
    string line;
    while (initial_state >> line) {
        filelines.push_back(line);
    }
}


void display_generation(const vector<string>& lines) {
    for (size_t i = 0; i < lines.size(); ++i) {
        for (size_t j = 0; j < lines[i].size(); ++j) {
            cout << lines[i][j];
        }
        cout << endl;
    }
    cout << "========================= \n";
}


int count_neighbours(const vector<string>& lines,size_t row, size_t col){
    int count = 0
    for (size_t i = row; i <= row + 2; ++i) {
        for (size_t j = col; j <= col + 2; ++j) {
            if (i - 1 == row && j - 1== col){
                continue;
            }
                
            if (i > 0 && i <= lines.size() && j > 0 && j <= lines[0].size()){
                if (lines[i-1][j-1] == '*') {
                    count = count + 1;
                }
           }
        }
    }
    return count;
 }

  
                   

vector<string> update_change(const vector<string>& lines){
    
    vector<string> linesCopy = lines;
    
    for (size_t i = 0; i < lines.size(); ++i) {
        for (size_t j = 0; j < lines[i].size(); ++j) {
            int count = count_neighbours(lines, i, j);
            
            if ((count > 3) && (lines[i][j] == '*')) {
                linesCopy[i][j] = '-';
            }
            else if ((count < 2) && (lines[i][j] == '*')) {
                linesCopy[i][j] = '-';
            }
            else if ((count == 3) && (lines[i][j] == '-')) {
                linesCopy[i][j] = '*';
            }
        
        }
    }
    return linesCopy;
}






int main() {
    ifstream initial_state;
    initial_state.open("life.txt");
    if (!initial_state) {
        cerr << "cannot find 'life.txt'";
        exit(1);
    }
     
    
    vector<string> lines;
    int num_generation = 10;
    initialize(lines, initial_state);
   
    initial_state.close();
    
    
    for (int gen = 0; gen < num_generation + 1; ++gen){
        display_generation(lines);
        lines = update_change(lines);
    }
}
