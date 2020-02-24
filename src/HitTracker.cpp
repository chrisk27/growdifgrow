#include <string>
#include <vector>
#include <fstream>

#include "HitTracker.h"

//Constructors and Destructor
HitTracker::HitTracker() { //with no add ons, just set length to 1

}

HitTracker::HitTracker(unsigned long long hitCount, unsigned long long iterValue) { //with ints, fill first part of vectors
    hitCounts.push_back(hitCount);
    iterValues.push_back(iterValue);
}

HitTracker::HitTracker(std::vector<unsigned long long> hits, std::vector<unsigned long long> iters) {
    //with vectors, just gives vector to what it means. Can edit this later
    hitCounts = hits;
    iterValues = iters;
}

HitTracker::~HitTracker() {};


//Functions
void HitTracker::export2csv(std::string name) {
    std::ofstream outputFile;
    outputFile.open(name);
    for (int i = 0; i < iterValues.size(); ++i) {
        outputFile << std::to_string(iterValues[i]);
        outputFile << ",";
        outputFile << std::to_string(hitCounts[i]);
        outputFile << std::endl;
    }
    outputFile.close();
}

