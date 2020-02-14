#include <math.h>
#include <iostream>
#include <stdlib.h>
#include <list>
#include <array>
#include <ctime>
#include <random>
#include <string>
#include <fstream>
#include <limits.h>

#include<boost/filesystem.hpp>

#include "include/GrowArray.h"
#include "include/ZArray.h"
#include "include/Irid.h"
#include "include/Neighbor.h"

using namespace std;

int main()
{

    // Make new folder to put today's simulations
    time_t now = time(0);

    tm *ltm = localtime(&now);

    std::string basepath = "/home/chris/projects/difgrow_mc_sims/";  // This is the basic path, where I will dump all of the simulations that I run
    std::string Year = to_string(1900 + ltm->tm_year);
    std::string Month = to_string(1 + ltm->tm_mon);
    if (Month.length() == 1) {
        Month = "0" + Month;
    }
    std::string Day = to_string(ltm->tm_mday);
    if (Day.length() == 1){
        Day = "0" + Day;
    }
    std::string folderName = Year.substr(2, 2) + "_" + Month + "_" + Day;
    std::string mainDir = basepath + folderName;

    boost::filesystem::path destination (mainDir);
    if (not boost::filesystem::is_directory(destination)) {  // Creates a new folder for the day if one doesn't already exist
        boost::filesystem::create_directory(destination);
    }


    // Start loop over h values
    list<unsigned short> hList {10, 12, 14, 16, 18, 20};

    for (auto hL = hList.begin(); hL != hList.end(); ++hL) {
        unsigned short h = *hL;

        // Start loop for each specific stepsPerGrowth
        list<unsigned short> slopes {1, 2, 5, 10};

        for (auto slps = slopes.begin(); slps != slopes.end(); ++slps) {
            unsigned short slopeRatio = *slps;

            // Create New Folder for this specific simulation 
            // NOTE:: This is really ugly, there's got to be a better way to do this with boost::filesystem::directory_iterator
            bool foundFile = true;
            short unsigned cnt = 1;
            std::string saveSim;
            
            while (foundFile) {

                //Transforms Count into a Path String
                std::string runNum = to_string(cnt);
                if (runNum.length() == 1){
                    runNum = "000" + runNum;
                } else if (runNum.length() == 2){
                    runNum = "00" + runNum;
                } else if (runNum.length() == 3){
                    runNum = "0" + runNum;
                }
                saveSim = mainDir + "/" + runNum;
                boost::filesystem::path CheckPath (saveSim);

                //Checks to see if it's already a directory. If not, make one and then end
                if (boost::filesystem::is_directory(CheckPath)) {
                    cnt = cnt + 1;
                } else {
                    boost::filesystem::create_directory(CheckPath);
                    foundFile = false;
                }
            }

            // Ask for experimental parameters
            short unsigned int r = 1;
            short unsigned int c = 1;
//            short unsigned int h = 15;

            short unsigned int r0 = r;  //Initial Condtions (to export)
            short unsigned int c0 = c;

            unsigned long long int stepsPerGrowth = 2e7;
            unsigned long long int totalSteps = stepsPerGrowth * 200;
            unsigned long long int imgPerSim = totalSteps / 1000;


            // Define rates and probabilities. Note: will want to make this as a flow in later, instead of hardcoded.
            //rates
            float bx = 1; //natural birth of xanthophores
            float bm = 0; //natural birth of melanophores
            float dx = 0; //natural death of xanthophores
            float dm = 0; //natural death of melanophores
            float sm = 1; //killing of xanthophores by melanophores
            float sx = 1; //killing of melanophores by xanthophores
            float lx = 2.5; //promotion of melanophore birth by long-range xanthophores
            //probabilities
            float rate_sum = bx + bm + dx + dm + sm + sx + lx;
            float bx_p = bx / rate_sum;
            float bm_p = bm / rate_sum;
            float dx_p = dx / rate_sum;
            float dm_p = dm / rate_sum;
            float sm_p = sm / rate_sum;
            float sx_p = sx / rate_sum;
            float lx_p = lx / rate_sum;


            //Create Initial Arrays. Note: Doing basics now, can change the initialization later.
            ZArray zebra(r, c); // The main array where it stores the values of the chromatophores
            zebra.ratio = slopeRatio;
            zebra.BlankArray();

            Irid ir(r, c); // Iridophore array, for guiding the patterns
            ir.ratio = slopeRatio;
            ir.Blank();

            Neighbor up(r, c); // A neighbor matrix to pull array values from
            up.ratio = slopeRatio;
            up.udshift = -1;
            up.GenerateZFBC();

            Neighbor down(r, c);
            down.ratio = slopeRatio;
            down.udshift = 1;
            down.GenerateZFBC();

            Neighbor left(r, c);
            left.ratio = slopeRatio;
            left.lrshift = -1;
            left.GenerateZFBC();

            Neighbor right(r, c);
            right.ratio = slopeRatio;
            right.lrshift = 1;
            right.GenerateZFBC();


            //Run Simulation by looping through each event. Will do 10^9 steps
            mt19937 generator ((int) time(0));
            uniform_real_distribution<float> dis(0.0, 1.0);
            srand(time(0));


            for (unsigned long long int iter = 0; iter < totalSteps; ++iter) {
                c = zebra.getCols();
                r = zebra.getRows();

                float proc = dis(generator); // Chooses random process
                short int i = rand() % r; // Chooses random lattice point
                short int j = rand() % c;
                
                if (zebra.checkExist(i, j) == true) {
                    if (proc < lx_p) { //Tests to see if melanophore will form due to long-range effect
                        if ((zebra.array[i][j] == 0) && (ir.array[i][j] == 0)) {
                            float angle = dis(generator) * 2 * M_PI;
                            float cosangle = cos(angle);
                            float sinangle = sin(angle);
                            short int inew = rint(sinangle * h + i);
                            short int jnew = rint(cosangle * h + j);
                            if (zebra.checkExist(inew, jnew)) {
                                if (zebra.array[inew][jnew] == 1) {
                                    zebra.array[i][j] = 2;  // Creates melanophore
                                }
                            }
                        }
                    }

                    else if ((proc < lx_p + sm_p) && (proc >= lx_p)) { //Tests to see if local melanophore will kill xanthophore
                        if (zebra.array[i][j] == 1) {
                            switch(rand() % 4) {
                                case 0: { //Above Neighbor
                                    if ((up.array[i][j] != SHRT_MAX) && (up.checkExist(i, j) == true)) {
                                        if (zebra.array[up.array[i][j]][j] == 2) {
                                            zebra.array[i][j] = 0;
                                        }
                                        break;
                                    }
                                }
                                case 1: { //Below Neighbor
                                    if ((down.array[i][j] != SHRT_MAX) && (down.checkExist(i, j) == true)) {
                                        if (zebra.array[down.array[i][j]][j] == 2) {
                                            zebra.array[i][j] = 0;
                                        }
                                        break;    
                                    }
                                }
                                case 2: { //Left Neighbor
                                    if ((left.array[i][j] != SHRT_MAX) && (left.checkExist(i, j) == true)) {
                                        if (zebra.array[i][left.array[i][j]] == 2) {
                                            zebra.array[i][j] = 0;
                                        }
                                        break;
                                    }
                                }
                                case 3: { //Right Neighbor
                                    if ((right.array[i][j] != SHRT_MAX) && (right.checkExist(i, j) == true)) {
                                        if (zebra.array[i][right.array[i][j]] == 2) {
                                            zebra.array[i][j] = 0;  
                                        }
                                        break;
                                    }
                                }
                                default: {
                                    break;
                                }
                            }
                        }
                    } 

                    else if ((proc < lx_p + sm_p + sx_p) && (proc >= lx_p + sm_p)) { //Tests to see if local xanthophore will kill melanophore
                        if (zebra.array[i][j] == 2) {
                            switch(rand() % 4) {
                                case 0: { //Above Neighbor
                                    if ((up.array[i][j] != SHRT_MAX) && (up.checkExist(i, j) == true)) {
                                        if (zebra.array[up.array[i][j]][j] == 1) {
                                            zebra.array[i][j] = 0;
                                        }
                                        break;
                                    }
                                }
                                case 1: { //Below Neighbor
                                    if ((down.array[i][j] != SHRT_MAX) && (down.checkExist(i, j) == true)) {
                                        if (zebra.array[down.array[i][j]][j] == 1) {
                                            zebra.array[i][j] = 0;
                                        }
                                        break;    
                                    }
                                }
                                case 2: { //Left Neighbor
                                    if ((left.array[i][j] != SHRT_MAX) && (left.checkExist(i, j) == true)) {
                                        if (zebra.array[i][left.array[i][j]] == 1) {
                                            zebra.array[i][j] = 0;
                                        }
                                        break;
                                    }
                                }
                                case 3: { //Right Neighbor
                                    if ((right.array[i][j] != SHRT_MAX) && (right.checkExist(i, j) == true)) {
                                        if (zebra.array[i][right.array[i][j]] == 1) {
                                            zebra.array[i][j] = 0;  
                                        }
                                        break;
                                    }
                                }
                                default: {
                                    break;
                                }
                            }
                        }
                    }

                    else if ((proc < lx_p + sm_p + sx_p + bx_p) && (proc >= lx_p + sm_p + sx_p)) { //Tests for birth of xanthophore
                        if (zebra.array[i][j] == 0) {
                            zebra.array[i][j] = 1;
                        }
                    }

                    else if ((proc < lx_p + sm_p + sx_p + bx_p + bm_p) && (proc >= lx_p + sm_p + sx_p + bx_p)) { //Tests for birth of melanophore
                        if ((zebra.array[i][j] == 0) && (ir.array[i][j] == 0)) {
                            zebra.array[i][j] = 2;
                        }
                    }

                    else if ((proc < lx_p + sm_p + sx_p + bx_p + bm_p + dx_p) && (proc >= lx_p + sm_p + sx_p + bx_p + bm_p)) { //Tests for death of xanthophore
                        if (zebra.array[i][j] == 1) {
                            zebra.array[i][j] = 0;
                        }
                    }

                    else if ((proc < lx_p + sm_p + sx_p + bx_p + bm_p + dx_p + dm_p) && (proc >= lx_p + sm_p + sx_p + bx_p + bm_p + dx_p)) { //Tests for death of melanophore
                        if (zebra.array[i][j] == 2) {
                            zebra.array[i][j] = 0;
                        }
                    }

                    else {
                        std::cout << "Error: Incorrect number generated" << endl;
                    }
                }

                // Export image
                if (iter % imgPerSim == 0) {
                    string iter_num = to_string(iter / imgPerSim);
                    if (iter_num.length() == 1){
                        iter_num = "0000" + iter_num;
                    } else if (iter_num.length() == 2){
                        iter_num = "000" + iter_num;
                    } else if (iter_num.length() == 3){
                        iter_num = "00" + iter_num;
                    }else if (iter_num.length() == 4){
                        iter_num = "0" + iter_num;
                    }

                    string outname = saveSim + "/img_" + iter_num + ".csv";
                    zebra.Rectangular_Export(outname);
                }

                // Perform Growth
                if (iter % (stepsPerGrowth / 2) == 0) {
                    zebra.growthSwitcher(false,false);
                    ir.growthSwitcher(true, true);  //This should ALWAYS be true: the iridophores guide the pattern, so need to extend
                    up.growthSwitcher(false,false);
                    down.growthSwitcher(false,false);
                    left.growthSwitcher(false,false);
                    right.growthSwitcher(false,false);
                }
            }

            // Check if there are iridophores
            string iridAns;
            if (ir.checkExist()) {
                iridAns = "True";
            } else {
                iridAns = "False";
            }

            // Export conditions to csv
            string csvCondTitle = saveSim + "/conditions.csv";
            ofstream csvfile;
            csvfile.open(csvCondTitle);

            csvfile << "Initial_Rows" << "," << "Initial_Columns" << "," << "h" << "," ; 
            csvfile << "Total_Steps" << "," << "Steps_per_Growth" << "," << "Slope_Ratio"<< "," << "Images_Per_Sim" << "," ;
            csvfile << "Final_Rows" << "," << "Final_Columns" << "," << "Irid_Exist" << ",";
            csvfile << "bx" << "," << "bm" << "," << "dx" << "," << "dm" << "," ;
            csvfile << "sm" << "," << "sx" << "," << "lx" << "Boundary Conditions" << endl;

            csvfile << to_string(r0) << "," << to_string(c0) << "," << to_string(h) << ",";
            csvfile << to_string(totalSteps) << "," << to_string(stepsPerGrowth) << "," << to_string(slopeRatio)<< "," << to_string(1000)<< "," ;
            csvfile << to_string(r) << "," << to_string(c) << "," << iridAns << "," ;
            csvfile << to_string(bx) << "," << to_string(bm) << "," << to_string(dx) << "," << to_string(dm) << "," ;
            csvfile << to_string(sm) << "," << to_string(sx) << "," << to_string(lx) << "Zero Flux" << endl;

            csvfile.close();



            std::cout << "Completed Simulation with slope ratio = " << to_string(slopeRatio) << endl;
        }

        std::cout << "Completed Simulations with h = " << to_string(h) << endl;
    }

   std::cout << "Completed All Simulations in Double Loop" << endl;
}
