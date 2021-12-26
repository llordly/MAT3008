#include <iostream>
#include "nr.h"
#include <ctime>
#include <cmath>

using namespace std;
using namespace NR;

DP func(DP x) {
    return bessj0(x);
}

void funcd(DP x, DP &f, DP &df) {
    f = bessj0(x);
    df = -bessj1(x);
}

void bessel0(DP (*method)(DP (*func)(DP), DP, DP, DP), DP (*func)(DP), Vec_O_DP xb1, Vec_O_DP xb2, int nroot, double xacc) {
    clock_t start, end;
    
    start = clock();
    for (int i = 0; i < nroot; ++i) {
        double root = (*method)(func, xb1[i], xb2[i], xacc);
        cout << i + 1<< "'th root: " << root << "\n";
    }
    end = clock();
    cout << end - start << "ms passed\n\n";
}

void bessel1(DP (*method)(void (*funcd)(DP, DP &, DP &), DP, DP, DP), void (*funcd)(DP, DP &, DP &), Vec_O_DP xb1, Vec_O_DP xb2, int nroot, double xacc) {
    clock_t start, end;
    
    start = clock();
    for (int i = 0; i < nroot; ++i) {
        double root = (*method)(funcd, xb1[i], xb2[i], xacc);
        cout << i + 1<< "'th root: " << root << "\n";
    }
    end = clock();
    cout << end - start << "ms passed\n\n";
}

DP muller(DP func(const DP), const DP x1, const DP x2, const DP xacc) {
    const int MAXIT = 30;
    double a, b, c, p0, p1, p2, p3, h1, h2, d1, d2, rpe;
    p0 = x1;
    p1 = x2;
    p2 = (x1 + x2) / 2.0;
    
    for (int i = 0; i < MAXIT; ++i) {
        h1 = p1 - p0;
        h2 = p2 - p1;
        d1 = (func(p1) - func(p0)) / h1;
        d2 = (func(p2) - func(p1)) / h2;
        a = (d2 - d1) / h2 + h1;
        b = a * h2 + d2;
        c = func(p2);
        double temp = b * b - 4 * a * c;
        if (b < 0) {
            p3 = p2 + (-2.0 * c) / (b - sqrt(temp));
        } else {
            p3 = p2 + (-2.0 * c) / (b + sqrt(temp));
        }
        rpe = fabs((p3 - p2) / p3);
        if (rpe < xacc) return p3;
        p0 = p1;
        p1 = p2;
        p2 = p3;
    }
    nrerror("Maximum number of iterations exceeded in muller");
    return 0.0;
}

DP func1(DP x) {
    return 10 * exp(-x) * sin(2 * M_PI * x) - 2;
}

DP func2(DP x) {
    return x * x - 2 * x * exp(-x) + exp(-2 * x);
}

DP func3(DP x) {
    return cos(x + sqrt(2)) + x * (x/2 + sqrt(2));
}

DP func4(DP x) {
    return cos(x) * log(x) + sin(2 * x);
}

void funcd1(DP x, DP &f, DP &df) {
    f = func1(x);
    df = 10 * exp(-x) * (2 * M_PI * cos(2 * M_PI * x) - sin(2 * M_PI * x));
}

void funcd2(DP x, DP &f, DP &df) {
    f = func2(x);
    df = 2 * exp(-2 * x) * (exp(x) + 1) * (exp(x) * x - 1);
}

void funcd3(DP x, DP &f, DP &df) {
    f = func3(x);
    df = x - sin(x + sqrt(2)) + sqrt(2);
}

void funcd4(DP x, DP &f, DP &df) {
    f = func4(x);
    df = cos(x) / x + 2 * cos(2 * x) - log(x) * sin(x);
}


int main(void) {
    cout << setprecision(10);
    const DP x1 = 1.0;
    const DP x2 = 10.0;
    const int MAX_ROOT = 100;
    const int N = 10000;
    double xacc = 1.0e-6;
    int nroot;
    Vec_O_DP xb1(MAX_ROOT), xb2(MAX_ROOT);
    zbrak(func, x1, x2, N, xb1, xb2, nroot);
    
    cout << "Bisection Method\n";
    bessel0(rtbis, func, xb1, xb2, nroot, xacc);

    cout << "Linear interpolation\n";
    bessel0(rtflsp, func, xb1, xb2, nroot, xacc);
    
    cout << "Secant Method\n";
    bessel0(rtsec, func, xb1, xb2, nroot, xacc);

    cout << "Newton-Raphson Method\n";
    bessel1(rtnewt, funcd, xb1, xb2, nroot, xacc);

    cout << "Newton with bracketing Method\n";
    bessel1(rtsafe, funcd, xb1, xb2, nroot, xacc);
    
    cout << "Muller Method\n";
    bessel0(muller, func, xb1, xb2, nroot, xacc);
    
    
    cout << "func1 in [0.1, 1] \n";
    zbrak(func1, 0.1, 1, N, xb1, xb2, nroot);
    bessel1(rtsafe, funcd1, xb1, xb2, nroot, xacc);
    
    cout << "func2 in [0, 1] \n";
    zbrak(func2, 0.0, 1.0, N * 10000, xb1, xb2, nroot);
    bessel1(rtsafe, funcd2, xb1, xb2, nroot, xacc);
    
    cout << "func3 in [-2, -1] \n";
    zbrak(func3, -2.0, -1.0, N, xb1, xb2, nroot);
    bessel1(rtsafe, funcd3, xb1, xb2, nroot, xacc);
    
    cout << "func4 in [0, 2] \n";
    zbrak(func4, 0.0, 2.0, N, xb1, xb2, nroot);
    bessel1(rtsafe, funcd4, xb1, xb2, nroot, xacc);
    
    return 0;
}
