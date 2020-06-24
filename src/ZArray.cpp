#include <math.h>
#include <array>
#include <ctime>
#include <random>
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

void ZArray::MelanoBand(unsigned short bandwidth, float randomXan) {
    // First, create a bunch of random xanthophores all over the domain
    mt19937 generator ((int) time(0));
    uniform_real_distribution<float> dis(0.0, 1.0);
    for (int i=0; i < rows; i++) {
        for (int j=0; j < cols; j++) {
            float randnum = dis(generator);
            if (randnum < randomXan) {
                array[i][j] = 1;
            } else {
                array[i][j] = 0;
            }
        }
    }
    // Next, add the middle band of melanophores
    if (bandwidth > 0) {
        for (int i = ((rows - bandwidth) / 2); i < ((rows + bandwidth) / 2); ++i) {
            for (int j=0; j < cols; ++j) {
                array[i][j] = 2;
            }
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


// Ablation Function
void ZArray::Ablate(float widthRatio, float heightRatio){
    //First, calculate the rows that will have something ablated in them
    unsigned short rowRange = floor(heightRatio * rows);
    unsigned short minRow = ceil(((rows - rowRange) / 2));
    unsigned short maxRow = minRow + rowRange;

    //Then, loop through each row and figure out which columns to ablate
    for (unsigned short abRow = minRow; abRow <= maxRow; abRow++) {
        unsigned short rowLength = array[abRow].size();
        unsigned short colRange = floor(widthRatio * rowLength);
        unsigned short minCol = ceil(((rowLength - colRange) / 2));
        unsigned short maxCol = minCol + colRange;

        //Now, replace each value in the array with a zero (empty spot)
        for (unsigned short abCol = minCol; abCol <= maxCol; abCol++) {
            array[abRow][abCol] = 0;
        }
    }
}
