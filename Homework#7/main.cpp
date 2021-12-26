#include <iostream>
#include "nr.h"
#include <ctime>
#include <cmath>
#include <ctime>
#include <vector>


using namespace std;
using namespace NR;

int main(void) {
    int idum = time(0);
    int n = 11;
    DP m = 0.0;
    DP s = 1.0;
    int nroot;
    
    Mat_IO_DP A(n, n);
    Mat_IO_DP v(n, n);
    Vec_IO_DP d(n);
    
    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            A[i][j] = A[j][i] = gasdev(idum) * s + m;
        }
    }
    cout << "Random Symmetric Matrix A (mean = 0.0, standard deviation = 1.0)" << "\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << A[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
    
    jacobi(A, d, v, nroot);
    eigsrt(d, v);
    
    cout << "Eigen vectors" << "\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << v[i][j] << " ";
        }
        cout << "\n";
    }
    
    cout << "\n";
    cout << "Eigen values\n";
    
    for (int i = 0; i < n; ++i) {
        cout << d[i] << " ";
    }
    cout << "\n";
    return 0;
}
