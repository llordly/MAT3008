// Homework#2
// 3-6

#include <iostream>
#include <stdio.h>

using namespace std;

double exp_1(int n, int term) {
    double ans = 1.0;

    for (int i = 1; i <= term; ++i) {
        double temp = 1;
        for (int j = 1; j <= i; ++j) {
            temp *= (double)n / j;
        }
        if (i % 2 == 1) {
            temp = -temp;
        }
        ans += temp;
    }
    return ans;
}

double exp_2(int n, int term) {
    double ans = 1.0;

    for (int i = 1; i <= term; ++i) {
        double temp = 1;
        for (int j = 1; j <= i; ++j) {
            temp *= (double)n / j;
        }
        ans += temp;
    }
    return 1 / ans;
}

void problem3_6() {
    double real_value = 6.737949e-3;
    double first = exp_1(5, 20);
    double second = exp_2(5, 20);
    cout << "problem 3.6\n";
    printf("true value: %e\n", real_value);
    printf("first method: %e\n", first);
    printf("second method: %e\n\n", second);
    
    printf("relative error of first method: %e\n", (real_value - first) / real_value);
    printf("relative error of second method: %e\n\n", (real_value - second) / real_value);
    
    printf("case of terms are 100\n");
    first = exp_1(5, 100);
    second = exp_2(5, 100);
    
    printf("first method: %e\n", first);
    printf("second method: %e\n\n", second);
    
    printf("relative error of first method: %e\n", (real_value - first) / real_value);
    printf("relative error of second method: %e\n\n", (real_value - second) / real_value);
}
