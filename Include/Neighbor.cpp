#include <math.h>
#include <array>
#include <iostream>
#include "Neighbor.h"

using namespace std;

// Constructors
Neighbor::Neighbor() : rows(0), cols(0) {};  // Defaults to zero

Neighbor::Neighbor(int i) : rows(i), cols(i) {  // With one argument, makes square
    short int **array = new short int*[rows];
    for (int count=0; count < cols; ++count){
        array[count] = new short int [cols];
    }
}

Neighbor::Neighbor(int i, int j) : rows(i), cols(j) {  //With two arguments, makes rectangle
    short int **array = new short int*[rows];
    for (int count=0; count < cols; ++count){
        array[count] = new short int [cols];
    }
}


// Destructor
Neighbor::~Neighbor() {
    for(int count = 0; count < cols; ++count){
        delete [] array[count];
    }
    delete [] array;
}


// Generator
short int Neighbor::Generate(short int lrshift, short int udshift) {
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