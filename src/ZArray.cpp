#include <math.h>
#include <array>
#include <cstring>
#include "ZArray.h"

using namespace std;

// Constructors
ZArray::ZArray() : rows(0), cols(0) {};  // Defaults to zero

ZArray::ZArray(int i) : rows(i), cols(i) {  // With one argument, makes square
    array = new uint8_t*[rows];
    for (int count=0; count < rows; count++){
        array[count] = new uint8_t[cols];
        memset(array[count], 0, cols*sizeof(uint8_t));
    }
}

ZArray::ZArray(int i, int j) : rows(i), cols(j) {  //With two arguments, makes rectangle
    array = new uint8_t*[rows];
    for (int count=0; count < rows; count++){
        array[count] = new uint8_t[cols];
        memset(array[count], 0, cols*sizeof(uint8_t));
    }
}


// Destructor
ZArray::~ZArray() {
    for(int count = 0; count < rows; count++){
        delete [] array[count];
    }
    delete [] array;
}


// Array Generation
void ZArray::BlankArray() {
    for (int i=0; i < rows; ++i){
        for (int j=0; j < cols; ++j) {
            array[i][j] = 0;
        }
    }
}

void ZArray::RandomArray() {
    for (int i=0; i < rows; ++i){
        for (int j=0; j < cols; ++j) {
            int randnum = floor( float (rand() * 3));
            switch (randnum) {
                case 0:
                    array[i][j] = 0;
                    break;
                case 1:
                    array[i][j] = 1;
                    break;
                case 2:
                    array[i][j] = 2;
                    break;
                default:
                    break;
            }
        }
    }
}


// Plotting Functions: Will add these in later!


