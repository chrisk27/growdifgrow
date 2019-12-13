#include <math.h>
#include <iostream>
#include <stdlib.h>
#include <array>
#include <ctime>
#include <random>

#include "ZArray.h"
#include "Irid.h"
#include "Neighbor.h"

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
    up.Generate(0, -1);

    Neighbor down(r, c);
    down.Generate(0, 1);

    Neighbor left(r, c);
    left.Generate(-1, 0);

    Neighbor right(r, c);
    right.Generate(1, 0);


    //Run Simulation by looping through each event. Will do 10^9 steps
    mt19937 generator ((int) time(0));
    uniform_real_distribution<float> dis(0.0, 1.0);
    srand(time(0));
    for (unsigned int step=0; step<1e9; ++step) {
        float proc = dis(generator); // Chooses random process
        short int i = rand() % r; // Chooses random lattice point
        short int j = rand() % c;
        
        if (proc < lx_p) { //Tests to see if melanophore will form due to long-range effect
            if ((zebra.array[i][j] == 0) && (ir.array[i][j] == false)) {
                float angle = dis(generator) * 2 * M_PI;
                float cosangle = cos(angle);
                float sinangle = sin(angle);
                short int inew = rint(cosangle * h + i);
                inew = inew % r;
                short int jnew = rint(sinangle * h + j);
                jnew = jnew % c;
                if (zebra.array[inew][jnew] == 1) {
                    zebra.array[i][j] = 2;
                }
            }
            break;
        }
    }





    cout << "Completed Simulation" << endl;
}
