// Homework1
#include <iostream>
#include "machar.h"

using namespace std;

float get_eps_float() {
    float epsilon = 1.0;
    while ((float)(1.0 + 0.5 * epsilon) != 1.0) {
        epsilon *= 0.5;
    }
    return epsilon;
}

double get_eps_double() {
    double epsilon = 1.0;
    while ((1.0 + 0.5 * epsilon) != 1.0) {
        epsilon *= 0.5;
    }
    return epsilon;
}

int main(void) {
    
    int ibeta, it, irnd, ngrd, machep, negep, iexp, minexp, maxexp;
    float f_eps_1, f_epsneg, f_xmin, f_xmax;
    double d_eps_1, d_epsneg, d_xmin, d_xmax;
    machar(&ibeta, &it, &irnd, &ngrd, &machep, &negep, &iexp, &minexp, &maxexp, &f_eps_1, &f_epsneg, &f_xmin, &f_xmax);
    machar_double(&ibeta, &it, &irnd, &ngrd, &machep, &negep, &iexp, &minexp, &maxexp, &d_eps_1, &d_epsneg, &d_xmin, &d_xmax);
    cout << "method1" << "\n";
    cout << "machine accuracy of float with machar: " << f_eps_1 << "\n";
    cout << "machine accuracy of double with machar_double: " << d_eps_1 << "\n\n";
    cout << "method2" << "\n";
    cout << "machine accuracy of float with get_eps_float: " << get_eps_float() << "\n";
    cout << "machine accuracy of float with get_eps_double: " << get_eps_double() << "\n";
    return 0;
}

