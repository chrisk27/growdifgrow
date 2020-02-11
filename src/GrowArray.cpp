#include <math.h>
#include <fstream>
#include <cstring>
#include <deque>

#include "GrowArray.h"

using namespace std;

// Constructors
GrowArray::GrowArray() : rows(0), cols(0) {};

GrowArray::GrowArray(int i) : rows(i), cols(i) {  //with one argument, makes square
    deque<unsigned short> blankRow;
    for (unsigned short k = 0; k < cols; ++k){  //Constructs blank row deque
        blankRow.push_back(0);
    }
    for (unsigned short ll = 0; ll < rows; ++ll){  //fills array with blank deque
        array.push_back(blankRow);
    }
}

GrowArray::GrowArray(int i, int j) : rows(i), cols(j) {
    deque<unsigned short> blankRow;
    for (unsigned short k = 0; k < cols; ++k){  //Constructs blank row deque
        blankRow.push_back(0);
    }
    for (unsigned short ll = 0; ll < rows; ++ll){  //fills array with blank deque
        array.push_back(blankRow);
    }
}

// Destructor
GrowArray::~GrowArray() {}

// Growth Functions
void GrowArray::grow1D(bool extend) { // will grow cols by 1
    
    //Add one more to each column deque
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
    if (array[rows -1].size() != cols){
        throw invalid_argument( "Error: column definition incorrect");
    }
}

void GrowArray::grow2DSquare(bool vertextend, bool horizextend) {
    // This function grows the square system "radially", i.e. by adding new elements around the previously existing system

    // Add new rows
    if (vertextend == false) {
        deque<unsigned short> newRow(cols, 0);
        array.push_front(newRow);
        array.push_back(newRow);
    } else {
        deque<unsigned short> topRow = array.front();
        array.push_front(topRow);
        deque<unsigned short> bottomRow = array.back();
        array.push_back(bottomRow);
    }
    rows = rows + 2;

    // Add new columns
    if (horizextend == false) {
        for (int j = 0; j < rows; ++j) {
            array[j].push_front(0);
            array[j].push_back(0);
        }
    } else {
        for (int j = 0; j < rows; ++j) {
            array[j].push_front(array[j][0]);
            array[j].push_back(array[j][cols - 1]);
        }
    }
    cols = cols + 2;

    // Error-check
    if (rows != array.size()){
        throw invalid_argument("Error in row indexing");
    }
    if (cols != array[rows-1].size()){
        throw invalid_argument("Error in column indexing");
    }
}

void GrowArray::grow2Rows(bool vertextend) {
    // This function will only grow the number of rows (in both dimensions)

    if (vertextend == false) {
        deque<unsigned short> newRow(cols, 0);
        array.push_front(newRow);
        array.push_back(newRow);
    } else {
        deque<unsigned short> topRow = array.front();
        array.push_front(topRow);
        deque<unsigned short> bottomRow = array.back();
        array.push_back(bottomRow);
    }
    rows = rows + 2;

    if (rows != array.size()) {
        throw invalid_argument("Error in row indexing");
    }
}

void GrowArray::grow2Cols(bool horizextend) {
    // This function will only grow the number of cols (in both directions)

    if (horizextend == false) {
        for (int j = 0; j < rows; ++j) {
            array[j].push_front(0);
            array[j].push_back(0);
        }
    } else {
        for (int j = 0; j < rows; ++j) {
            array[j].push_front(array[j][0]);
            array[j].push_back(array[j][cols - 1]);
        }
    }

    cols = cols + 2;

    if (cols != array[0].size()) {
        throw invalid_argument("Error in column indexing");
    }
}

void GrowArray::grow1Col(bool horizextend) {
    //This function will only grow by one column (on the right)

    if (horizextend == false) {
        for (int j = 0; j < rows; ++j) {
            array[j].push_back(0);
        }
    } else {
        for (int j = 0; j < rows; ++j) {
            array[j].push_back(array[j][cols - 1]);
        }
    }
    cols = cols + 1;

    if (cols != array[0].size()) {
        throw invalid_argument("Error in column indexing");
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



