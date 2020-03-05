#include <math.h>
#include <array>
#include <deque>
#include <iostream>
#include <limits.h>
#include "Neighbor.h"

using namespace std;

// Constructors
Neighbor::Neighbor() : GrowArray() {};

Neighbor::Neighbor(int i) : GrowArray(i) {};

Neighbor::Neighbor(int i, int j) : GrowArray(i, j) {};

// Destructor
Neighbor::~Neighbor() {};

// Generator
void Neighbor::GeneratePeriodic() {
    // If it's a left or right shift
    if ((lrshift != 0) && (udshift == 0)) {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < array[i].size(); ++j) {
                if (j + lrshift < 0) {
                    array[i][j] = array[i].size() + j + lrshift;
                } else {
                    array[i][j] = (j + lrshift) % array[i].size();
                }
            }
        }
    }
    else if ((lrshift == 0) && (udshift != 0)) {  // Note: For right now, I'm not sure if this works with anything but a +/- 1 for udshift
    // Also note: in its current form, a column with only one element will become its own neighbor. Not sure if I care, but worth noting
        if (array.size() != 1){
            for (int i = 0; i < rows; ++ i) {
                for (int j = 0; j < array[i].size(); ++j) {
//                    unsigned int multiplier = 1; 
                    int idx2test = i + udshift;
                    if (checkExist(idx2test, j) == true) { //if it's a valid array point
                        array[i][j] = idx2test;
                    } else {
                        while (checkExist(idx2test, j) == false) {
                            if (idx2test < 0) {  // circles back to bottom row of the array
                                idx2test = rows - 1;
//                                multiplier = 1;
                            }
                            else if (idx2test > rows - 1) {  // circles back to 0th row of array
                                idx2test = idx2test % rows;
//                                multiplier = 1;
                            } else {
//                                multiplier = multiplier + 1;
                                idx2test = idx2test + udshift;
                            }
                        }
                        array[i][j] = idx2test;
                    }
                }
            }
        }
        else {
             for (int i = 0; i < rows; ++ i) {
                for (int j = 0; j < cols; ++j) {
                    array[i][j] = 0;
                }
            }
        }
    }
    else if ((lrshift == 0) && (udshift == 0)) {
        cout << "Need to define a shift for Neighbors" << endl;
    } else {
        cout << "Error: Only one directional shift supported at this time" << endl;
    }
}

void Neighbor::Generate_Old() {
    for (short int i=0; i < rows; ++i){
        for (short int j=0; j < array[i].size(); ++j){
            if ((lrshift != 0) && (udshift == 0)) {
                if (j + lrshift < 0) {
                    array[i][j] = cols + j + lrshift;    
                } else {
                    array[i][j] = (j + lrshift) % cols;
                }                              
            } else if ((lrshift == 0) && (udshift != 0)) {
                if (i + udshift < 0) {
                    array[i][j] = rows + i + udshift;
                } else {
                    array[i][j] = (i + udshift) % rows;
                }
            } else if ((lrshift == 0) && (udshift == 0)) {
                cout << "Need to define a shift for Neighbors" << endl;
            } else {
                cout << "Error: Only one directional shift supported at this time" << endl;
            }
        }
    }
}

// Zero-Flux Boundary Condition Generator
void Neighbor::GenerateZFBC_Old() {
    for (short int i=0; i < rows; ++i){
        for (short int j=0; j < cols; ++j){
            if ((lrshift != 0) && (udshift == 0)) {
                if ((i + lrshift < 0) | (i + lrshift > rows - 1)) {
                    array[i][j] = USHRT_MAX;
                } else {
                    array[i][j] = i + lrshift;
                }                   
            } else if ((lrshift == 0) && (udshift != 0)) {
                if ((j + udshift < 0) | (j + udshift > cols - 1)) {
                    array[i][j] = USHRT_MAX;
                } else {
                    array[i][j] = j + udshift;
                }
            } else if ((lrshift == 0) && (udshift == 0)) {
                cout << "Need to define a shift for Neighbors" << endl;
            } else {
                cout << "Error: Only one directional shift supported at this time" << endl;
            }
        }
    }
}

// New ZFBC Generator (to work with nonconstant column size)
void Neighbor::GenerateZFBC() {
    //First, if it's a left-right shift
    if ((lrshift != 0) && (udshift == 0)) {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < array[i].size(); ++j) {
                if ((j + lrshift < 0) | (j + lrshift > array[i].size() - 1)) {
                    array[i][j] = SHRT_MAX;
                } else {
                    array[i][j] = j + lrshift;
                }
            }
        }
    }
    else if ((lrshift == 0) && (udshift != 0)) {
        for (int i = 0; i < rows; ++i) {
            int idx2test = i + udshift;
            for (int j = 0; j < array[i].size(); ++j) {
                if ((idx2test < 0) | (idx2test > rows -1)) {
                    array[i][j] = SHRT_MAX;
                }
                else if (checkExist(idx2test, j) == true) {
                    array[i][j] = idx2test;
                }
                else {
                    array[i][j] = SHRT_MAX;
                }
            }
        }
    }
}

void Neighbor::pickGenerator(){
    if (boundaryCondition == "Periodic") {
        GeneratePeriodic();
    }
    else if (boundaryCondition == "ZeroFlux") {
        GenerateZFBC();
    }
    else {
        cout << "Error in Boundary Condition Choice" << endl;
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
//   if (cols != array[0].size()){
//        cout << "Error in column indexing" << endl;
//    }
    
    //Re-generate new values
    pickGenerator();
}

void Neighbor::grow2DSquare(bool vertextend, bool horizextend) {

    // Add new rows to top and bottom
    deque<unsigned short> newRow(cols, 0);
    array.push_front(newRow);
    array.push_back(newRow);
    rows = rows + 2;

    // Adds new columns on sides
    for (int j = 0; j < rows; ++j) {
        array[j].push_front(0);
        array[j].push_back(0);
    }
    cols = cols + 2;

    // Re-generate new values
    pickGenerator();

    // Error-check
    if (rows != array.size()){
        cout << "Error in row indexing" << endl;
    }
//    if (cols != array.front().size()){
//        cout << "Error in column indexing" << endl;
//    }
}

void Neighbor::grow2Rows(bool vertextend) {
    deque<unsigned short> newRow(cols, 0);
    array.push_front(newRow);
    array.push_back(newRow);
    rows = rows + 2;

    pickGenerator();

    if (rows != array.size()) {
        cout << "Error in row indexing" << endl;
    }
}

void Neighbor::grow2Cols(bool horizextend) {
    for (int j = 0; j < rows; ++j) {
        array[j].push_front(0);
        array[j].push_back(0);
    }
    cols = cols + 2;

    pickGenerator();

//    if (cols != array[0].size()) {
//        cout << "Error in column indexing" << endl;
//    }
}

void Neighbor::grow2DBasic(bool vertextend, bool horizextend) {

    //Add a new row
    deque<unsigned short> newRow;
    for (unsigned short k = 0; k < cols; ++k) {
        newRow.push_back(0);
    }
    array.push_back(newRow);
    rows = rows + 1;

    //Add new column
    for (int i = 0; i < rows; ++i){
        array[i].push_back(0);
    }
    cols = cols + 1;

    if (array.size() != rows){
        throw invalid_argument("Error: row definition incorrect");
    }
    if (array[rows - 1].size() != cols){
        throw invalid_argument("Error: column definition incorrect");
    }

    // Re-generate values (for rectangular array)
    pickGenerator();
}

void Neighbor::grow1ColBack(bool horizextend) {
    for (int j = 0; j < rows; ++j) {
        array[j].push_back(0);
    }
    cols = cols + 1;
    pickGenerator();

//    if (cols != array[0].size()) {
//        throw invalid_argument("Error in column indexing");
//    }
}

void Neighbor::grow1ColFront(bool horizextend) {
    for (int j = 0; j < rows; ++j) {
        array[j].push_front(0);
    }
    cols = cols + 1;
    pickGenerator();
}

void Neighbor::growTrap(bool vertextend, bool horizextend) {
    //First, add a column to the left
    for (unsigned short i = 0; i < rows; ++i) {
        array[i].push_front(0);
    }

    //Then, add new rows
    deque<unsigned short> newDeque(1, 0);
    array.push_front(newDeque);
    array.push_back(newDeque);

    //Update indices
    rows = rows + 2;
    cols = cols + 1;

    pickGenerator();

    if (rows != array.size()) {
        cout << "Error in row indexing" << endl;
    }
}

// Switch between two different types of growth
void Neighbor::growthSwitcher(bool vertextend, bool horizextend) {
    growthCounter = growthCounter + 1;

    if (growthCounter != ratio) {
        grow1ColFront(false);
    } else {
        growTrap(false, false);
        growthCounter = 0;
    }
}