#include <bits/stdc++.h>
using namespace std;

typedef long double Real;

const Real eps = 1e-10;

Real f(Real x) {
    
}

Real simpson(Real a, Real b) {
    return Real(1) / Real(6) * (b - a) * (f(a) + Real(4) * f((a + b) / Real(2)) + f(b));
}

Real integral(Real l, Real r) {
    Real m  = (l + r) / Real(2);
    Real tot = simpson(l, r);
    Real sum = simpson(l, m) + simpson(m, r);
    if (abs(tot - sum) < eps) return sum;
    return integral(l, m) + integral(m, r);
}

int main() {
    mt19937 rnd;
    uniform_real_distribution<Real> dist(0.0, 1.0);
    Real num = dist(rnd);
    cout << num << endl;
    return 0;
}
