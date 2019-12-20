#ifndef __NEIGHBOR_H_INCLUDED__
#define __NEIGHBOR_H_INCLUDED__

#include "GrowArray.h"

class Neighbor : public GrowArray {

public:
    // Constructors and Destructor
    Neighbor();
    Neighbor(int i);
    Neighbor(int i, int j);
    ~Neighbor();

    // Generators
    void Generate( short int lrshift = 0, short int udshift = 0);

    // Growth - Need to override from parent class since we use these differently
    void grow1D(bool extend);
    void grow2D(bool extend);

};


#endif