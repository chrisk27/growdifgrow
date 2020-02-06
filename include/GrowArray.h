#ifndef __GROWARRAY_H_INCLUDED__
#define __GROWARRAY_H_INCLUDED__

#include<string>
#include<vector>

class GrowArray{

public:
    //Constructor and Destructor
    GrowArray();
    GrowArray(int i);
    GrowArray(int i, int j);
    ~GrowArray();

    //Growth Functions-blank cells
    void grow1D(bool extend = false);
    void grow2DBasic(bool vertextend = false, bool horizextend = false);

    //Vector (for Dynamic Allocation)
    std::vector<std::vector<unsigned short> > array;
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