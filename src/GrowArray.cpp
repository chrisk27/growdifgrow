#include <math.h>
#include <fstream>
#include <cstring>
#include <vector>

#include "GrowArray.h"

using namespace std;

// Constructors
GrowArray::GrowArray() : rows(0), cols(0) {};

GrowArray::GrowArray(int i) : rows(i), cols(i) {  //with one argument, makes square
    vector<unsigned short> blankRow;
    for (unsigned short k = 0; k < cols; ++k){  //Constructs blank row vector
        blankRow.push_back(0);
    }
    for (unsigned short ll = 0; ll < rows; ++ll){  //fills array with blank vector
        array.push_back(blankRow);
    }
}

GrowArray::GrowArray(int i, int j) : rows(i), cols(j) {
    vector<unsigned short> blankRow;
    for (unsigned short k = 0; k < cols; ++k){  //Constructs blank row vector
        blankRow.push_back(0);
    }
    for (unsigned short ll = 0; ll < rows; ++ll){  //fills array with blank vector
        array.push_back(blankRow);
    }
}

// Destructor
GrowArray::~GrowArray() {}

// Growth Functions
void GrowArray::grow1D(bool extend) { // will grow cols by 1
    
    //Add one more to each column vector
    int numRows = array.size();
    for (int i =0; i < numRows; ++i){
        if (extend == false){
            array[i].push_back(0);
        } else {
            unsigned short oldVal = array[i].back();
            array[i].push_back(oldVal);
        }
    }
    //Increases column size
    cols = cols + 1;
    if (array[0].size() != cols){
        throw invalid_argument( "Error: column definition incorrect");
    }
}

void GrowArray::grow2DBasic(bool vertextend, bool horizextend) {
    // This function will add one row to the bottom of the array (since it's periodic BC currently) and then increase the column width by 1

    // Create a new row
    vector<unsigned short> newRow;
    if (vertextend == false) {
        for (unsigned short k = 0; k < cols; ++k) {
            newRow.push_back(0);
        }
    } else {
        for (unsigned short k = 0; k < cols; ++k) {
            newRow.push_back(array[rows - 1][k]);
        }
    }

    // Add new row to the end of the array
    array.push_back(newRow);

    // Add one more column to each vector
    int numRows = array.size();
    for (int i =0; i < numRows; ++i){
        if (horizextend == false){
            array[i].push_back(0);
        } else {
            unsigned short oldVal = array[i].back();
            array[i].push_back(oldVal);
        }
    }

    // Increase rows and cols size
    rows = rows + 1;
    cols = cols + 1;
    if (array.size() != rows){
        throw invalid_argument("Error: row definition incorrect");
    }
    if (array[rows - 1].size() != cols){
        throw invalid_argument("Error: column definition incorrect");
    }

}

// Access Protected Dimensions
unsigned short int GrowArray::getCols() {
    return cols;
}

unsigned short int GrowArray::getRows() {
    return rows;
}

// Cleanup and Export
void GrowArray::export2csv(string name) {
    ofstream tmpfilee;
    tmpfilee.open(name);
    for (int i=0; i<rows; ++i) {
        tmpfilee << to_string(array[i][0]);
        for (int j=1; j<cols; ++j) {
            tmpfilee << "," << to_string(array[i][j]);    
        }
        tmpfilee << endl;
    }
    tmpfilee.close();
}

unsigned short GrowArray::Rectangularize() {
    return 0;
}



