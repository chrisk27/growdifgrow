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
//    if (array[rows -1].size() != cols){
//        throw invalid_argument( "Error: column definition incorrect");
//    }
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
//    if (cols != array[rows-1].size()){
//        throw invalid_argument("Error in column indexing");
//    }
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

//    if (rows != array.size()) {
//        throw invalid_argument("Error in row indexing");
//    }
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

//    if (cols != array[0].size()) {
//        throw invalid_argument("Error in column indexing");
//    }
}

void GrowArray::grow1ColBack(bool horizextend) {
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

//    if (cols != array[0].size()) {
//        throw invalid_argument("Error in column indexing");
//    }
}

void GrowArray::grow1ColFront(bool horizextend) {
    //This function will grow by one column (on the left)

    if (horizextend == false) {
        for (int j = 0; j < rows; ++j) {
            array[j].push_front(0);
        }
    } else {
        for (int j = 0; j < rows; ++j) {
            array[j].push_front(array[j].front());
        }
    }
    cols = cols + 1;
}

void GrowArray::grow2DBasic(bool vertextend, bool horizextend) {
    // This function will add one row to the bottom of the array (since it's periodic BC currently) and then increase the column width by 1

    // Create a new row
    deque<unsigned short> newRow;
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
void GrowArray::growTrap(bool vertextend, bool horizextend) {
    //Grows the system by a singular column with an extra row and column at the end, so it expands the size

    //First, add new column to the existing rows
    for (unsigned short i = 0; i < rows; ++i) {
        if (horizextend == false) {
            array[i].push_front(0);
        } else {
            array[i].push_front(array[i].front());
        }
    }

    //Then, add a new deque above and below
    if (vertextend == false) {
        deque<unsigned short> newDeque(1, 0);
        array.push_front(newDeque);
        array.push_back(newDeque);
    } else {
        deque<unsigned short> topDeque(1, array[0].front());
        array.push_front(topDeque);
        deque<unsigned short> bottomDeque(1, array[rows-1].front());
        array.push_back(bottomDeque);
    }

    //Update indices
    rows = rows + 2;
    cols = cols + 1;

    if (rows != array.size()) {
        throw invalid_argument("Error in row indexing");
    }
}


// Switch between two different types of growth
void GrowArray::growthSwitcher(bool vertextend, bool horizextend) {
    growthCounter = growthCounter + 1;

    if (growthCounter != ratio) {
        grow1ColFront(horizextend);
    } else {
        growTrap(vertextend, horizextend);
        growthCounter = 0;
    }
}


// Access Protected Dimensions
bool GrowArray::checkExist(int i, int j) {
    if ((i < rows) && (i >= 0)) {
        if ((j >= 0) && (j < array[i].size())) {
            return true;
        } else {
            return false;
        }
    } else {
    return false;
    }
}

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

void GrowArray::Rectangular_Export(string name) {
    //Rectangularize
    deque<deque<unsigned short>> output;
    for (unsigned short i = 0; i < rows; ++i){
        deque<unsigned short> thisRow = array[i];
        for (unsigned short j = thisRow.size() -1; j < cols; ++j) {
            thisRow.push_back(100);
        }
        output.push_back(thisRow);
    }

    //Export
    ofstream tmpfilee;
    tmpfilee.open(name);
    for (int i=0; i<rows; ++i) {
        tmpfilee << to_string(output[i][0]);
        for (int j=1; j<cols; ++j) {
            tmpfilee << "," << to_string(output[i][j]);    
        }
        tmpfilee << endl;
    }
    tmpfilee.close();
}



