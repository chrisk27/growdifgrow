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
    void MelanoBand(unsigned short bandwidth = 1, float randomXanProb = 0);

    // Ablation Function
    void Ablate(float widthRatio = 0.5, float heightRatio = 0.5);
    
};

#endif