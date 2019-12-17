#include <math.h>
#include <stdlib.h>
#include <array>
#include <ctime>
#include <random>
#include "Irid.h"

using namespace std;

// Constructors
Irid::Irid() : rows(0), cols(0) {};  // Defaults to zero

Irid::Irid(int i) : rows(i), cols(i) {  // With one argument, makes square
    array = new bool*[rows];
    for (int count=0; count < cols; ++count){
        array[count] = new bool [cols];
    }
}

Irid::Irid(int i, int j) : rows(i), cols(j) {  //With two arguments, makes rectangle
    array = new bool*[rows];
    for (int count=0; count < cols; ++count){
        array[count] = new bool [cols];
    }
}

// Destructor
Irid::~Irid() {
    for(int count = 0; count < cols; ++count){
        delete [] array[count];
    }
    delete [] array;
}

// Iridophore Array Generators
void Irid::Blank() {
    for (int i=0; i < rows; ++i){
        for (int j=0; j < cols; ++j) {
            array[i][j] = false;
        }
    }
}

void Irid::Band(int bandwidth) {
    for (int i=0; i < rows; ++i){
        for (int j=0; j < cols; ++j) {
            array[i][j] = false;
        }
    }
    if (bandwidth > 0) {
        for (int i=floor(rows/2 - bandwidth/2); i < floor(rows/2 + bandwidth/2 - 1); ++i) {
            for (int j=0; j<cols; ++j) {
                array[i][j] = true;
            }
        }
    }
}

void Irid::Random(float probability) {
    mt19937 generator ((int) time(0));
    uniform_real_distribution<float> dis(0.0, 1.0);
    for (int i=0; i < rows; ++i){
        for (int j=0; j < cols; ++j) {
            float randNum = dis(generator);
            if (randNum < probability) {
                array[i][j] = true;
            } else {
                array[i][j] = false;
            }
        }
    }
}

