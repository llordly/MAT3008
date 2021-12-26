#include <iostream>
#include "nr.h"
#include <ctime>
#include <cmath>
#include <fstream>

using namespace std;
using namespace NR;

Mat_IO_DP use_gaussj(string fileName) {
    ifstream f(fileName);
    if(f.fail()) {
        cerr << "file not found\n";
        exit(100);
    }
    cout << "gaussj : root of Ax = b\n";
    int n, m;
    DP num;
    f >> n >> m;

    Mat_IO_DP A(n, m);
    Mat_IO_DP b(n, 1);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            f >> num;
            A[i][j] = num;
        }
    }

    for (int i = 0; i < n; ++i) {
        f >> num;
        b[i][0] = num;
    }

    gaussj(A, b);
    
    string result = "x: [";
    for (int i = 0; i < n; ++i) {
        result += to_string(b[i][0]);
        if (i != n - 1) result += ", ";
    }
    result += "]\n";
    cout << result;
    cout << "\n";
    return A;
}

void find_inverse(Mat_IO_DP inverse) {
    cout << "Inverse Matrix\n";
    for (int i = 0; i < inverse.nrows(); ++i) {
        for (int j = 0; j < inverse.ncols(); ++j) {
            cout << inverse[i][j] << " ";
        }
        cout << "\n";
    }
}

DP use_LU(string fileName) {
    ifstream f(fileName);
    if(f.fail()) {
        cerr << "file not found\n";
        exit(100);
    }
    cout << "LU decomposition : root of Ax = b\n";
    int n, m;
    DP num;
    DP d;
    f >> n >> m;

    Mat_IO_DP A(n, m);
    Vec_IO_DP b(n);
    Vec_O_INT indx(n);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            f >> num;
            A[i][j] = num;
        }
    }

    for (int i = 0; i < n; ++i) {
        f >> num;
        b[i] = num;
    }
    
    ludcmp(A, indx, d);
    lubksb(A, indx, b);
    
    for (int i = 0; i < n; ++i) {
        d *= A[i][i];
    }
    string result = "x: [";
    for (int i = 0; i < n; ++i) {
        result += to_string(b[i]);
        if (i != n - 1) result += ", ";
    }
    result += "]\n";
    cout << result;
    cout << "\n";
    return d;
}

void use_iterativeImprove(string fileName) {
    ifstream f(fileName);
    if(f.fail()) {
        cerr << "file not found\n";
        exit(100);
    }
    cout << "Iterative Improvement : root of Ax = b\n";
    int n, m;
    DP num;
    DP d;
    f >> n >> m;

    Mat_IO_DP A(n, m);
    Mat_IO_DP Adx(n, m);
    Vec_IO_DP b(n);
    Vec_IO_DP bdx(n);
    Vec_O_INT indx(n);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            f >> num;
            A[i][j] = Adx[i][j] = num;
        }
    }

    for (int i = 0; i < n; ++i) {
        f >> num;
        b[i] = bdx[i] = num;
    }
    
    ludcmp(Adx, indx, d);
    lubksb(Adx, indx, bdx);
    mprove(A, Adx, indx, b, bdx);
    
    string result = "x: [";
    for (int i = 0; i < n; ++i) {
        result += to_string(bdx[i]);
        if (i != n - 1) result += ", ";
    }
    result += "]\n";
    cout << result;
    cout << "\n";
}

void use_svd(string fileName) {
    ifstream f(fileName);
    if(f.fail()) {
        cerr << "file not found\n";
        exit(100);
    }
    cout << "Singular Value Decomposition : root of Ax = b\n";
    int n, m;
    DP num;
    DP wmax = 0.0;
    f >> n >> m;

    Mat_IO_DP u(n, m);
    Mat_IO_DP v(n, m);
    Vec_IO_DP b(n);
    Vec_IO_DP w(n);
    Vec_IO_DP x(n);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            f >> num;
            u[i][j] = num;
        }
    }

    for (int i = 0; i < n; ++i) {
        f >> num;
        b[i] = num;
    }
    
    svdcmp(u, w, v);
    for (int i = 0; i < n; ++i) {
        if (w[i] > wmax) wmax = w[i];
    }
    DP wmin = wmax * 1e-6;
    
    for (int i = 0; i < n; ++i) {
        if (w[i] < wmin) w[i] = 0.0;
    }
    
    svbksb(u, w, v, b, x);
    
    string result = "x: [";
    for (int i = 0; i < n; ++i) {
        result += to_string(x[i]);
        if (i != n - 1) result += ", ";
    }
    result += "]\n";
    cout << result;
    cout << "\n";
    
}

int main(void) {
    string data[3] = {"lineq1.dat", "lineq2.dat", "lineq3.dat"};
    for (int i = 0; i < 3; ++i) {
        cout << data[i] << "\n";
        Mat_IO_DP inverse = use_gaussj(data[i]);
        DP determinant = use_LU(data[i]);
        use_svd(data[i]);
        use_iterativeImprove(data[i]);
        find_inverse(inverse);
        cout << "\nDeterminant: " << determinant << "\n";
        cout << "-----------------------------------\n";
    }
   
    
    return 0;
}


