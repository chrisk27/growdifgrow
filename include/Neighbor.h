#ifndef __NEIGHBOR_H_INCLUDED__
#define __NEIGHBOR_H_INCLUDED__

#include<array>
#include<math.h>


using namespace std;

class Neighbor {

public:
    // Constructors and Destructor
    Neighbor();
    Neighbor(int i);
    Neighbor(int i, int j);
    ~Neighbor();
    // Generators
    void Generate( short int lrshift = 0, short int udshift = 0);

private:
    int rows {0};
    int cols {0};
    short int** array;  //** means it's dynamically allocated (really just defining the pointer I think)

};


#endif