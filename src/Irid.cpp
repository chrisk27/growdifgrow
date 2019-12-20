#include <math.h>
#include <stdlib.h>
#include <array>
#include <ctime>
#include <random>
#include "Irid.h"

using namespace std;

// Constructors
Irid::Irid() : GrowArray() {}  // Defaults to zero

Irid::Irid(int i) : GrowArray(i) {}

Irid::Irid(int i, int j) : GrowArray(i, j) {}

// Destructor
Irid::~Irid() {}

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

