#include <math.h>
#include <iostream>
#include <stdlib.h>
#include <array>
#include <ctime>
#include <random>
#include <string>
#include <fstream>

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


    // Create New Folder for this specific simulation
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


    //std::string runNum = to_string(cnt);
    //if (runNum.length() == 1){
    //    runNum = "000" + runNum;
    //} else if (runNum.length() == 2){
    //    runNum = "00" + runNum;
    //} else if (runNum.length() == 3){
    //    runNum = "0" + runNum;
    //}

    //std::string saveSim = mainDir + "/" + runNum;
    //boost::filesystem::path savePlace (saveSim);
    //if (not boost::filesystem::is_directory(savePlace)) {  // Creates the folder I'll actually save this simulation into
    //    boost::filesystem::create_directory(savePlace);
    //}

    // Ask for experimental parameters
    short unsigned int r;
    short unsigned int c;
    short unsigned int h;

    std::cout << "All initialization values should be integers."<< endl;
    std::cout << "Please enter the number of rows: ";
    cin >> r;
    std::cout << "Please enter the number of columns: ";
    cin >> c;
    std::cout << "Please enter the characteristic distance h: ";
    cin >> h;
    std::cout << endl;

    short unsigned int r0 = r;  //Initial Condtions (to export)
    short unsigned int c0 = c;

    unsigned long long int totalSteps = 1e9;
    unsigned long long int stepsPerGrowth = 2e7;
    unsigned long long int imgPerGrowth = stepsPerGrowth / 10;


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
    zebra.BlankArray();

    Irid ir(r, c); // Iridophore array, for guiding the patterns
    ir.Blank();

    Neighbor up(r, c); // A neighbor matrix to pull array values from
    up.udshift = -1;
    up.Generate();

    Neighbor down(r, c);
    down.udshift = 1;
    down.Generate();

    Neighbor left(r, c);
    left.lrshift = -1;
    left.Generate();

    Neighbor right(r, c);
    right.lrshift = 1;
    right.Generate();


    //Run Simulation by looping through each event. Will do 10^9 steps
    mt19937 generator ((int) time(0));
    uniform_real_distribution<float> dis(0.0, 1.0);
    srand(time(0));


    for (unsigned long long int iter = 0; iter < totalSteps; ++iter) {
        c = zebra.getCols();
        r = zebra.getRows();
 //       for (unsigned long int step=0; step < stepsPerGrowth; ++step) {
        float proc = dis(generator); // Chooses random process
        short int i = rand() % r; // Chooses random lattice point
        short int j = rand() % c;
        
        if (proc < lx_p) { //Tests to see if melanophore will form due to long-range effect
            if ((zebra.array[i][j] == 0) && (ir.array[i][j] == 0)) {
                float angle = dis(generator) * 2 * M_PI;
                float cosangle = cos(angle);
                float sinangle = sin(angle);
                short int inew = rint(cosangle * h + i);
                if (inew > r - 1){
                    inew = inew % r;    
                } else if (inew < 0) {
                    inew = inew + r;
                }
                short int jnew = rint(sinangle * h + j);
                if (jnew > c -1){
                    jnew = jnew % c;
                } else if (jnew < 0) {
                    jnew = jnew + c;
                }
                if (zebra.array[inew][jnew] == 1) {
                    zebra.array[i][j] = 2;
                }
            }
        }

        else if ((proc < lx_p + sm_p) && (proc >= lx_p)) { //Tests to see if local melanophore will kill xanthophore
            if (zebra.array[i][j] == 1) {
                switch(rand() % 4) {
                    case 0: { //Above Neighbor
                        if (zebra.array[i][up.array[i][j]] == 2) {
                            zebra.array[i][j] = 0;
                        }
                        break;
                    }
                    case 1: { //Below Neighbor
                        if (zebra.array[i][down.array[i][j]] == 2) {
                            zebra.array[i][j] = 0;
                        }
                        break;
                    }
                    case 2: { //Left Neighbor
                        if (zebra.array[left.array[i][j]][j] == 2) {
                            zebra.array[i][j] = 0;
                        }
                        break;
                    }
                    case 3: { //Right Neighbor
                        if (zebra.array[right.array[i][j]][j] == 2) {
                            zebra.array[i][j] = 0;  
                        }
                        break;
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
                        if (zebra.array[i][up.array[i][j]] == 1) {
                            zebra.array[i][j] = 0;
                        }
                        break;
                    }
                    case 1: { //Below Neighbor
                        if (zebra.array[i][down.array[i][j]] == 1) {
                            zebra.array[i][j] = 0;
                        }
                        break;
                    }
                    case 2: { //Left Neighbor
                        if (zebra.array[left.array[i][j]][j] == 1) {
                            zebra.array[i][j] = 0;
                        }
                        break;
                    }
                    case 3: { //Right Neighbor
                        if (zebra.array[right.array[i][j]][j] == 1) {
                            zebra.array[i][j] = 0;  
                        }
                        break;
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
//        }

        // Export image
        if (iter % imgPerGrowth == 0) {
            string iter_num = to_string(iter / imgPerGrowth);
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
            zebra.export2csv(outname);
        }

        // Perform Growth
        if (iter % stepsPerGrowth == 0) {
            zebra.grow1D(false);
            ir.grow1D(true);  //This should ALWAYS be true: the iridophores guide the pattern, so need to extend
            up.grow1D(false);
            down.grow1D(false);
            left.grow1D(false);
            right.grow1D(false);
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
    csvfile << "Total_Steps" << "," << "Steps_per_Growth" << "," << "Images_per_Growth" << "," ;
    csvfile << "Final_Rows" << "," << "Final_Columns" << "," << "Irid_Exist" << ",";
    csvfile << "bx" << "," << "bm" << "," << "dx" << "," << "dm" << "," ;
    csvfile << "sm" << "," << "sx" << "," << "lx" << endl;

    csvfile << to_string(r0) << "," << to_string(c0) << "," << to_string(h) << ",";
    csvfile << to_string(totalSteps) << "," << to_string(stepsPerGrowth) << "," << to_string(imgPerGrowth)<< "," ;
    csvfile << to_string(r) << "," << to_string(c) << "," << iridAns << "," ;
    csvfile << to_string(bx) << "," << to_string(bm) << "," << to_string(dx) << "," << to_string(dm) << "," ;
    csvfile << to_string(sm) << "," << to_string(sx) << "," << to_string(lx) << endl;

    csvfile.close();



    std::cout << "Completed Simulation" << endl;
}
