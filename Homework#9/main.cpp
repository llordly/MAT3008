#include <iostream>
#include "nr.h"
#include <ctime>
#include <cmath>
#include <fstream>
#include <vector>


using namespace std;
using namespace NR;

vector<vector<double>> read_input(string fileName) {
    ifstream f(fileName);
    if(f.fail()) {
        cerr << "file not found\n";
        exit(100);
    }
    vector<vector<double>> arr;
    double num;
    int line = 0;
    int cnt = 0;
    while (f >> num) {
        if (cnt == 0) {
            arr.push_back(vector<double>());
        }
        arr[line].push_back(num);
        cnt++;
        if (cnt == 4) {
            line++;
            cnt = 0;
        }
    }
    return arr;
}

vector<vector<double>> make_leastSquare(vector<vector<double>> arr) {
    int n = arr.size();
    vector<vector<double>> J(n, vector<double>(3, 0));
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < 2; ++j) {
            J[i][j] = arr[i][j];
        }
        J[i][2] = 1;
    }
    return J;
}

vector<double> make_xPrime(vector<vector<double>> arr) {
    int n = arr.size();
    vector<double> x(n);
    for (int i = 0; i < n; ++i) {
        x[i] = arr[i][2];
    }
    return x;
}

vector<double> make_yPrime(vector<vector<double>> arr) {
    int n = arr.size();
    vector<double> y(n);
    for (int i = 0; i < n; ++i) {
        y[i] = arr[i][3];
    }
    return y;
}

void cal_x(vector<vector<double>> J, vector<double> x) {
    Mat_IO_DP A(3, 3);
    Mat_IO_DP b(3, 1);
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            DP temp = 0;
            for (int k = 0; k < J.size(); ++k) {
                temp += J[k][i] * J[k][j];
            }
            A[i][j] = temp;
        }
    }
    
    for (int i = 0; i < 3; ++i) {
        DP temp = 0;
        for (int j = 0; j < J.size(); ++j) {
            temp += J[j][i] * x[j];
        }
        b[i][0] = temp;
    }
    
    gaussj(A, b);
    string a[3] = {"a1", "a2", "a3"};
    
    for (int i = 0; i < 3; ++i) {
        cout << a[i] << ": " << b[i][0] << " ";
    }
    cout << "\n";
}

void cal_y(vector<vector<double>> J, vector<double> y) {
    Mat_IO_DP A(3, 3);
    Mat_IO_DP b(3, 1);
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            DP temp = 0;
            for (int k = 0; k < J.size(); ++k) {
                temp += J[k][i] * J[k][j];
            }
            A[i][j] = temp;
        }
    }
    
    for (int i = 0; i < 3; ++i) {
        DP temp = 0;
        for (int j = 0; j < J.size(); ++j) {
            temp += J[j][i] * y[j];
        }
        b[i][0] = temp;
    }
    
    gaussj(A, b);
    string a[3] = {"a4", "a5", "a6"};
    
    for (int i = 0; i < 3; ++i) {
        cout << a[i] << ": " << b[i][0] << " ";
    }
    cout << "\n";
}


int main(void) {
    string data[3] = {"fitdata1.dat", "fitdata2.dat", "fitdata3.dat"};
    for (int i = 0; i < 3; ++i) {
        cout << data[i] << "\n";
        vector<vector<double>> arr = read_input(data[i]);
        vector<vector<double>> J = make_leastSquare(arr);
        vector<double> x = make_xPrime(arr);
        vector<double> y = make_yPrime(arr);
        cal_x(J, x);
        cal_y(J, y);
        cout << "\n";
    }
    
    return 0;
}
