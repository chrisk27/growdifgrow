#include <math.h>
#include <array>
#include <fstream>
#include <cstring>
#include "ZArray.h"

using namespace std;

// Constructors
ZArray::ZArray() : GrowArray() {};  // Defaults to zero

ZArray::ZArray(int i) : GrowArray(i) {};

ZArray::ZArray(int i, int j) : GrowArray(i, j) {};

// Destructor
ZArray::~ZArray() {};

// Array Generation
void ZArray::BlankArray() {
    for (int i=0; i < rows; i++){
        for (int j=0; j < cols; j++) {
            array[i][j] = 0;
        }
    }
}

void ZArray::RandomArray() {
    for (int i=0; i < rows; i++){
        for (int j=0; j < cols; j++) {
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

