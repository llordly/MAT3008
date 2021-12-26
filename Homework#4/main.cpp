#include <iostream>
#include "nr.h"
#include <ctime>
#include <cmath>

using namespace std;
using namespace NR;


void bessel0(DP (*method)(DP (*func)(DP), DP, DP, DP), DP (*func)(DP), DP x1, DP x2, double xacc) {
    double root = (*method)(func, x1, x2, xacc);
    cout << "root: " << root << "\n";
    cout << "\n";
}

void bessel1(DP (*method)(void (*funcd)(DP, DP &, DP &), DP, DP, DP), void (*funcd)(DP, DP &, DP &), DP x1, DP x2, double xacc) {
    double root = (*method)(funcd, x1, x2, xacc);
    cout << "root: " << root << "\n";
    cout << "\n";
}

DP funcR(DP x) {
    return exp(-0.005 * x) * cos(sqrt(2000 - 0.01 * x * x) * 0.05) - 0.01;
}

void funcdR(DP x, DP &f, DP &df) {
    f = funcR(x);
    DP temp = sqrt(2000 - 0.01 * x * x);
    df = exp(-0.005 * x) * (0.0005 * x * sin(0.05 * temp) / temp - 0.005 * cos(0.05 * temp));
}

DP func1(DP x) {
    return x / pow((x*x + 0.81), 1.5) - 8.85 * M_PI / 100;
}

void funcd1(DP x, DP &f, DP &df) {
    f = func1(x);
    double temp = x*x + 0.81;
    df = 1 / pow(temp, 1.5) - 3 * x*x / pow(temp, 2.5);
}

DP func2(DP x) {
    return 1.9520e-14*pow(x, 4) - 9.5848e-11*pow(x, 3) + 9.7215e-8*x*x + 1.671e-4*x - 0.20597;
}

void funcd2(DP x, DP &f, DP &df) {
    f = func2(x);
    df = 1.9520e-14*pow(x, 3) * 4 - 9.5848e-11*pow(x, 2) * 3 + 9.7215e-8*x * 2 + 1.671e-4;
}

int main(void) {
    cout << setprecision(10);
    DP x1 = 0;
    DP x2 = 400;
    double xacc = 1.0e-4;
    
    cout << "Find the root of f(R) = 0\n";
    cout << "Bisection Method, accuracy 1.0e-4\n";
    bessel0(rtbis, funcR, x1, x2, xacc);

    cout << "Linear interpolation, accuracy 1.0e-4\n";
    bessel0(rtflsp, funcR, x1, x2, xacc);

    cout << "Secant Method, accuracy 1.0e-4\n";
    bessel0(rtsec, funcR, x1, x2, xacc);

    cout << "Newton-Raphson Method, accuracy 1.0e-4\n";
    bessel1(rtnewt, funcdR, x1, x2, xacc);

    cout << "Newton with bracketing Method, accuracy 1.0e-4\n";
    bessel1(rtsafe, funcdR, x1, x2, xacc);
    
    xacc = 1.0e-6;
    
    cout << "Bisection Method, accuracy 1.0e-6\n";
    bessel0(rtbis, funcR, x1, x2, xacc);

    cout << "Linear interpolation, accuracy 1.0e-6\n";
    bessel0(rtflsp, funcR, x1, x2, xacc);

    cout << "Secant Method, accuracy 1.0e-6\n";
    bessel0(rtsec, funcR, x1, x2, xacc);

    cout << "Newton-Raphson Method, accuracy 1.0e-6\n";
    bessel1(rtnewt, funcdR, x1, x2, xacc);

    cout << "Newton with bracketing Method, accuracy 1.0e-6\n";
    bessel1(rtsafe, funcdR, x1, x2, xacc);
    
    cout << "problem 8-32\n";
    xacc = 1.0e-4;
    x1 = 0.0;
    x2 = 0.5;
    cout << "Bisection Method in [0.0, 0.5], accuracy 1.0e-4\n";
    bessel0(rtbis, func1, x1, x2, xacc);

    cout << "Linear interpolation in [0.0, 0.5], accuracy 1.0e-4\n";
    bessel0(rtflsp, func1, x1, x2, xacc);

    cout << "Secant Method in [0.0, 0.5], accuracy 1.0e-4\n";
    bessel0(rtsec, func1, x1, x2, xacc);

    cout << "Newton-Raphson Method in [0.0, 0.5], accuracy 1.0e-4\n";
    bessel1(rtnewt, funcd1, x1, x2, xacc);

    cout << "Newton with bracketing Method in [0.0, 0.5], accuracy 1.0e-4\n";
    bessel1(rtsafe, funcd1, x1, x2, xacc);
    
    x1 = 1.0;
    x2 = 2.0;
    
    cout << "Bisection Method in [1.0, 2.0], accuracy 1.0e-4\n";
    bessel0(rtbis, func1, x1, x2, xacc);

    cout << "Linear interpolation in [1.0, 2.0], accuracy 1.0e-4\n";
    bessel0(rtflsp, func1, x1, x2, xacc);

    cout << "Secant Method in [1.0, 2.0], accuracy 1.0e-4\n";
    bessel0(rtsec, func1, x1, x2, xacc);

    cout << "Newton-Raphson Method in [1.0, 2.0], accuracy 1.0e-4\n";
    bessel1(rtnewt, funcd1, x1, x2, xacc);

    cout << "Newton with bracketing Method in [1.0, 2.0], accuracy 1.0e-4\n";
    bessel1(rtsafe, funcd1, x1, x2, xacc);
    
    cout << "problem 8-36\n";
    x1 = 1000.0;
    x2 = 1500.0;
    cout << "Bisection Method in [1000.0, 1500.0], accuracy 1.0e-4\n";
    bessel0(rtbis, func2, x1, x2, xacc);

    cout << "Linear interpolation in [1000.0, 1500.0], accuracy 1.0e-4\n";
    bessel0(rtflsp, func2, x1, x2, xacc);

    cout << "Secant Method in [1000.0, 1500.0], accuracy 1.0e-4\n";
    bessel0(rtsec, func2, x1, x2, xacc);

    cout << "Newton-Raphson Method in [1000.0, 1500.0], accuracy 1.0e-4\n";
    bessel1(rtnewt, funcd2, x1, x2, xacc);

    cout << "Newton with bracketing Method in [1000.0, 1500.0], accuracy 1.0e-4\n";
    bessel1(rtsafe, funcd2, x1, x2, xacc);

    
    return 0;
}
