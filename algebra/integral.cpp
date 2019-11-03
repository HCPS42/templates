#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define pb push_back
#define ppp pop_back
#define pii pair<int,int>
#define fi first
#define se second

const double eps = 1e-10;

double f(double x) {

}

double simpson(double a, double b) {
    return 1.0/6 * (b-a) * (f(a) + 4 * f((a+b)/2.0) + f(b));
}

double integral(double a, double b) {
    double mid  = (a + b)/2.0;
    double a1 = simpson(a, b);
    double b1 = simpson(a, mid) + simpson(mid, b);
    if(abs(a1-b1) < eps) return b1;
    else return integral(a, mid) + integral(mid, b);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif
    default_random_engine generator;
    uniform_real_distribution<double> distribution(0.0, 1.0);
    double number = distribution(generator);
    cout << fixed << setprecision(12);

}
