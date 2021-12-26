#include <iostream>
#include "nr.h"
#include <ctime>
#include <cmath>
#include <fstream>
#include <ctime>
#include <vector>


using namespace std;
using namespace NR;

int main(void) {
    int idum = time(0);
    vector<int> n = {100, 1000, 10000, 100000};
    DP a = -3;
    DP b = 2;
    DP m = 0.5;
    DP s = 1.5;
    
    string uniform = "uniform_distribution_";
    string gauss = "gauss_distribution_";
    
    
    for (int i = 0; i < n.size(); ++i) {
        int sample = n[i];
        string u = uniform + to_string(sample) + ".txt";
        string g = gauss + to_string(sample) + ".txt";
        ofstream uni(u);
        ofstream gas(g);
        
        for (int j = 0; j < sample; ++j) {
            uni << ran1(idum) * (b - a) + a << "\n";
        }
        
        for (int j = 0; j <sample; ++j) {
            gas << gasdev(idum) * s + m << "\n";
        }
        
        uni.close();
        gas.close();
    }
    
    return 0;
}
