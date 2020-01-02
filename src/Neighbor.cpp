#include <math.h>
#include <array>
#include <iostream>
#include "Neighbor.h"

using namespace std;

// Constructors
Neighbor::Neighbor() : GrowArray() {};

Neighbor::Neighbor(int i) : GrowArray(i) {};

Neighbor::Neighbor(int i, int j) : GrowArray(i, j) {};

// Destructor
Neighbor::~Neighbor() {};

// Generator
void Neighbor::Generate() {
    for (short int i=0; i < rows; ++i){
        for (short int j=0; j < cols; ++j){
            if ((lrshift != 0) && (udshift == 0)) {
                if (i + lrshift < 0) {
                    array[i][j] = rows + i + lrshift;    
                } else {
                    array[i][j] = (i + lrshift) % rows;
                }                              
            } else if ((lrshift == 0) && (udshift != 0)) {
                if (j + udshift < 0) {
                    array[i][j] = cols + j + udshift;
                } else {
                    array[i][j] = (j + udshift) % cols;
                }
            } else if ((lrshift == 0) && (udshift == 0)) {
                cout << "Need to define a shift for Neighbors" << endl;
            } else {
                cout << "Error: Only one directional shift supported at this time" << endl;
            }
        }
    }
}

//Growth functions  //Note: extend shouldn't do anything, just there as placeholder to match form of parent function (necessary to override)
void Neighbor::grow1D(bool extend) { 

    //Add one space to each row
     int numRows = array.size();
    for (int i =0; i < numRows; ++i){
        array[i].push_back(0);
    }
    cols = cols+1;
    if (cols != array[1].size()){
        cout << "Error in column indexing" << endl;
    }
    
    //Re-generate new values
    Generate();
}

void Neighbor::grow2D(bool extend) {

}