#include <math.h>
#include <iostream>
#include <stdlib.h>
#include <array>
#include <ctime>
#include <random>
#include <string>

#include "include/GrowArray.h"
#include "include/ZArray.h"
#include "include/Irid.h"
#include "include/Neighbor.h"

using namespace std;

int main()
{
    // Ask for experimental parameters
    short unsigned int r;
    short unsigned int c;
    short unsigned int h;

    cout << "All initialization values should be integers."<< endl;
    cout << "Please enter the number of rows: ";
    cin >> r;
    cout << "Please enter the number of columns: ";
    cin >> c;
    cout << "Please enter the characteristic distance h: ";
    cin >> h;


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
    for (unsigned int iter = 0; iter < 100; ++iter) {
        c = zebra.getCols();
        r = zebra.getRows();
        for (unsigned int step=0; step<1e7; ++step) {
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
                cout << "Error: Incorrect number generated" << endl;
            }
        }
        string iter_num = to_string(iter + 1);
        if (iter_num.length() == 1){
            iter_num = "000" + iter_num;
        } else if (iter_num.length() == 2){
            iter_num = "00" + iter_num;
        } else if (iter_num.length() == 3){
            iter_num = "0" + iter_num;
        }

        string outname = "csvOutputs/img_" + iter_num + ".csv";
        zebra.export2csv(outname);

        // Perform Growth
        if (iter != 99) {
            zebra.grow1D(false);
            ir.grow1D(false);
            up.grow1D(false);
            down.grow1D(false);
            left.grow1D(false);
            right.grow1D(false);
        }
    }
    cout << "Completed Simulation" << endl;
}
