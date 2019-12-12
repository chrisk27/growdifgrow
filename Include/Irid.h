#ifndef __IRID_H_INCLUDED__
#define __IRID_H_INCLUDED__

#include<array>
#include<math.h>


using namespace std;

class Irid {
    
public:
    //Constructor and Destructor Functions
    Irid();
    Irid(int i);
    Irid(int i, int j);
    ~Irid();
    //Generator Functions
    bool Blank();
    bool Band(int bandwidth = 1);
    bool Random(float probability = 0);

    //Should also add a plotting/coloring function here

private:
    int rows {0};
    int cols {0};
    bool** array;  //** means it's dynamically allocated (really just defining the pointer I think)

};

#endif