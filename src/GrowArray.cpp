#include <math.h>
#include <fstream>
#include <cstring>

#include "GrowArray.h"

using namespace std;

// Constructors
GrowArray::GrowArray() : rows(0), cols(0) {};

GrowArray::GrowArray(int i) : rows(i), cols(i) {  //with one argument, makes square
    array = new unsigned short* [rows];
    for (int count=0; count < cols; ++count){
        array[count] = new unsigned short [cols];
        memset(array[count], 0, cols*sizeof(unsigned short));
    }
}

GrowArray::GrowArray(int i, int j) : rows(i), cols(j) {
    array = new unsigned short* [rows];
    for (int count = 0; count < cols; ++count){
        array[count] = new unsigned short [cols];
        memset(array[count], 0, cols*sizeof(unsigned short));
    }
}

// Destructor
GrowArray::~GrowArray() {
    for(int count = 0; count < cols; ++count){
        delete [] array[count];
    }
    delete [] array;
    delete &rows;
    delete &cols;
}

// Growth Functions
void GrowArray::grow1D(bool extend) { // will grow cols by 1
    unsigned short newcols = cols + 1;
    
    //Create new, larger array
    unsigned short** newarray = new unsigned short* [rows];
    for (int count = 0; count < newcols; ++count){
        newarray[count] = new unsigned short [newcols];
        memset(newarray[count], 0, newcols*sizeof(unsigned short));
    }

    //Fill New array
    for (int i=0; i<rows; ++i) { 
        for (int j=0; j<cols; ++j) {
            newarray[i][j] = array[i][j];
        }
        if (extend == false) {
            newarray[i][newcols - 1] = 0;
        } else {
            newarray[i][cols] = newarray[i][cols];
        }
    }

    //Delete old values and re-aim
    for(int delcount=0; delcount < cols; ++delcount){
        delete [] array[delcount];
        array[delcount] = newarray[delcount];
    }
    

    //Reassign to proper names
    cols = newcols;
}

void GrowArray::grow2D(bool extend) {

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



