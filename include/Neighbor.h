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
    void pickGenerator();
    void GeneratePeriodic();
    void Generate_Old();
    void GenerateZFBC();
    void GenerateZFBC_Old();
    std::string boundaryCondition;

    // Growth - Need to override from parent class since we use these differently
    void grow1D(bool extend);  // Should be the same essentially as grow1ColBack
    void grow2DBasic(bool vertextend, bool horizextend);
    void grow2DSquare(bool vertextend, bool horizextend);
    void grow1ColBack(bool horizextend);
    void grow1ColFront(bool horizextend);
    void grow2Rows(bool vertextend);
    void grow2Cols(bool horizextend);
    void growTrap(bool vertextend, bool horizextend);

    void growthSwitcher(bool vertextend, bool horizextend);

    // Shifts
    short lrshift {0};
    short udshift {0};

};


#endif