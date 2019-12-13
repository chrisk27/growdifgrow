#ifndef __EXPPARAMETERS_H_INCLUDED__
#define __EXPPARAMETERS_H_INCLUDED__

#include<math.h>

using namespace std;

class ExpParameters {   
public:

    // This section relates to experimental parameters
    static const unsigned short rows;  // Rows in experimental array
    static const unsigned short cols;  // Columns in experimental array
    static const unsigned short h;  // Distance used for long-range interactions
    unsigned steps;  // Steps in the experiment used (standard is 10**9)

    // This section relates to reaction rates
    float bx;  // birth of xantophores
    float bm;  // birth of melanophores
    float dx;  // natural death of xantophores
    float dm;  // natural death of melanophores
    float sm;  // short-range killing of xantophore by melanophore
    float sx;  // short-range killing of melanophore by xantophore
    float lx;  // long-range activation/birth strength
    float sum_rates = bx + bm + dx + dm + sm + sx + lx;  // sum of all process reaction rates
    float prob(float rate);

};

#endif