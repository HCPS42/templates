#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-10;

double f(double x) {

}

double simpson(double a, double b) {
    return 1.0 / 6.0 * (b - a) * (f(a) + 4 * f((a + b) / 2.0) + f(b));
}

double integral(double a, double b) {
    double mid  = (a + b) / 2.0;
    double a1 = simpson(a, b);
    double b1 = simpson(a, mid) + simpson(mid, b);
    if (abs(a1 - b1) < eps) return b1;
    return integral(a, mid) + integral(mid, b);
}

int main() {
    mt19937 rnd;
    uniform_real_distribution<double> dist(0.0, 1.0);
    double num = dist(rnd);
    return 0;
}
