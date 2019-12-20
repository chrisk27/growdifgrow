#ifndef __ZARRAY_H_INCLUDED__
#define __ZARRAY_H_INCLUDED__

#include"GrowArray.h"

class ZArray : GrowArray {

public:
    // Constructor and Destructor functions
    ZArray(); 
    ZArray(int i);
    ZArray(int i, int j);
    ~ZArray();
    // Initialization functions
    void BlankArray(); 
    void RandomArray();
    
    // Output functions
    int GeneratePlot();
    void ShowPlot(uint8_t array);
    void tempExport();

    uint8_t **array;  //** means it's dynamically allocated (really just defining the pointer I think)
    
    //Also may need to add a growing command here, i.e. have substantiated a new object and fill it in with values

private:
    int rows {0};
    int cols {0}; 
    
};

#endif