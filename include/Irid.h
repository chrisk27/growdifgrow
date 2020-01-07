#ifndef __IRID_H_INCLUDED__
#define __IRID_H_INCLUDED__

#include"GrowArray.h"

class Irid : public GrowArray {
    
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

    //Existance Functions
    bool checkExist();

};

#endif