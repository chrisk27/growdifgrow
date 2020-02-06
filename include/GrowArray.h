#ifndef __GROWARRAY_H_INCLUDED__
#define __GROWARRAY_H_INCLUDED__

#include<string>
#include<deque>

class GrowArray{

public:
    //Constructor and Destructor
    GrowArray();
    GrowArray(int i);
    GrowArray(int i, int j);
    ~GrowArray();

    //Growth Functions-blank cells
    void grow1D(bool extend = false);
    void grow2DSquare(bool vertextend = false, bool horizextend = false);

    //Deque (for Dynamic Allocation and addition on both sides)
    std::deque<std::deque<unsigned short> > array;
    unsigned short int getCols();
    unsigned short int getRows();
    
    //Finish, clean, and export
    unsigned short int Rectangularize();
    void export2csv(std::string name = "Ouput.csv");

protected:
    unsigned short int rows {0};
    unsigned short int cols {0};
    
};


#endif