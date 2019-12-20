#ifndef __ZARRAY_H_INCLUDED__
#define __ZARRAY_H_INCLUDED__

#include"GrowArray.h"

class ZArray : public GrowArray {

public:
    // Constructor and Destructor functions
    ZArray(); 
    ZArray(int i);
    ZArray(int i, int j);
    ~ZArray();
    // Initialization functions
    void BlankArray(); 
    void RandomArray();
    
};

#endif