#ifndef __HITTRACKER_H_INCLUDED__
#define __HITTRACKER_H_INCLUDED__

#include <string>
#include <vector>

class HitTracker {

public:
    //Generators
    HitTracker();
    HitTracker(unsigned long long hitCount, unsigned long long iterValue);
    HitTracker(std::vector<unsigned long long> hits, std::vector<unsigned long long> iters);
    ~HitTracker();

    //Things to track
    std::vector<unsigned long long> hitCounts;
    std::vector<unsigned long long> iterValues;

    void export2csv(std::string name = "HitTracker.csv");
};

#endif