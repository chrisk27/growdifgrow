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

// Growth Functions - Blank
void GrowArray::grow1D(bool extend) {
    
}

void GrowArray::grow2D(bool extend) {

}

// Cleanup and Export
void GrowArray::export2csv(string name) {
    ofstream tmpfilee;
    tmpfilee.open(name);
    for (int i=0; i<rows; i++) {
        tmpfilee << to_string(array[i][0]);
        for (int j=1; j<cols; j++) {
            tmpfilee << "," << to_string(array[i][j]);    
        }
        tmpfilee << endl;
    }
    tmpfilee.close();
}

unsigned short GrowArray::Rectangularize() {
    return 0;
}



