#ifndef __NEIGHBOR_H_INCLUDED__
#define __NEIGHBOR_H_INCLUDED__

#include "GrowArray.h"

class Neighbor : GrowArray {

public:
    // Constructors and Destructor
    Neighbor();
    Neighbor(int i);
    Neighbor(int i, int j);
    ~Neighbor();
    // Generators
    void Generate( short int lrshift = 0, short int udshift = 0);
    short int** array;  //** means it's dynamically allocated (really just defining the pointer I think)

private:
    int rows {0};
    int cols {0};

};


#endif