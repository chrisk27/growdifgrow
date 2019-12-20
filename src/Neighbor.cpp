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
    unsigned short newcols = cols + 1;
    
    //Create new, larger array
    unsigned short** newarray = new unsigned short* [rows];
    for (int count = 0; count < newcols; ++count){
        newarray[count] = new unsigned short [newcols];
    }

    //Delete old array
    for(int delcount=0; delcount < cols; ++delcount){
        delete [] array[delcount];
    }
    delete [] array;

    //Reassign to proper names
    array = newarray;
    cols = newcols;

    //Re-generate new values
    Generate();
}

void Neighbor::grow2D(bool extend) {

}