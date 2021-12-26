// Homework#2
// 4.2

#include <iostream>
#include <stdio.h>
#include <math.h>

using namespace std;

double exp_1(double n, int term) {
    double ans = 1.0;

    for (int i = 2; i <= term * 2; i += 2) {
        double temp = 1;
        for (int j = 1; j <= i; ++j) {
            temp *= n / (double)j;
        }
        if (i % 4 != 0) {
            temp = -temp;
        }
        ans += temp;
    }
    return ans;
}

void problem4_2() {
    cout << "problem 4.2\n";
    double real_value = 0.5;
    double estimated_value = 1;
    double es = 0.005;
    double et = 1;
    double before = estimated_value;
    double ea = 1;
    int i = 1;
    while (es < ea) {
        estimated_value = exp_1(M_PI / 3, i++);
        et = (real_value - estimated_value) / real_value;
        ea = fabs((estimated_value - before) / estimated_value);
        before = estimated_value;
        printf("estimated value: %e, ", estimated_value);
        cout << "relative error: " << et * 100 << "% ";
        cout << "approximate relative error: " << ea << "\n";
    }
}
