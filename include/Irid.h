#ifndef __IRID_H_INCLUDED__
#define __IRID_H_INCLUDED__

#include"GrowArray.h"

class Irid : GrowArray {
    
public:
    //Constructor and Destructor Functions
    Irid();
    Irid(int i);
    Irid(int i, int j);
    ~Irid();
    //Generator Functions
    void Blank();
    void Band(int bandwidth = 1);
    void Random(float probability = 0);
    bool ** array;  //** means it's dynamically allocated (really just defining the pointer I think)
    //Should also add a plotting/coloring function here

private:
    int rows {0};
    int cols {0};
    

};

#endif