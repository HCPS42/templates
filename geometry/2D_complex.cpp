#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define pb push_back
#define ppp pop_back
#define pii pair<int, int>
#define fi first
#define se second

const double pi = acos(-1);
typedef complex<double> point;
#define x() real()
#define y() imag()

double dot(point a, point b) {
	return (conj(a) * b).x();
}

double cross(point a, point b) {
	return (conj(a) * b).y();
}

double dist(point a, point b) {
	return sqrt(dot(a - b, a - b));
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif

    return 0;
}
