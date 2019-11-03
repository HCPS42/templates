#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define pb push_back
#define ppp pop_back
#define fi first
#define se second
#define pii pair<int,int>

typedef long double ldb;
const ldb eps = 1e-9;
const int N = 1e5 + 5;

inline bool gt(const ldb &x, const ldb &y) {
    return x > y + eps;
}

inline bool ls(const ldb &x, const ldb &y) {
    return y > x + eps;
}

inline ldb safe_sqrt(const ldb &x) {
    return x < 0 ? 0 : sqrt(x);
}

struct Point {
    ldb x, y;
    Point(){}
    Point(ldb _x, ldb _y) : x(_x), y(_y) {}
};

int n;
Point p[N];

inline bool can(ldb R) {
    ldb l = -1e16 - 1, r = 1e16 + 1;
    for (int i=1; i<=n; i++) {
        ldb b = -2 * p[i].x;
        ldb c = p[i].x * p[i].x + p[i].y * p[i].y - 2 * p[i].y * R;
        ldb D = b * b - 4 * c;
        if (ls(D, 0)) return 0;
        D = safe_sqrt(D);
        ldb x1 = p[i].x - D/2, x2 = p[i].x + D/2;
        l = max(l, x1);
        r = min(r, x2);
    }
    return !gt(l, r);
}

void no() {
    cout << "-1\n";
    exit(0);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif
    cin >> n;
    bool pos=0, neg=0;
    for (int i=1; i<=n; i++) {
        ldb x, y;
        cin >> x >> y;
        p[i] = Point(x, y);
        if (y > 0) pos = 1;
        else neg = 1;
    }
    if (pos && neg) no();
    if (neg) {
        for (int i=1; i<=n; i++) p[i].y = -p[i].y;
    }
    ldb l = 0, r =  1e16;
    function<ldb(ldb, ldb)> get_mid;
    if (can(1)) {
        r = 1;
        get_mid = [](ldb l, ldb r) {
            return (l + r)/2.0;
        };
    }
    else {
        l = 1;
        get_mid = [](ldb l, ldb r) {
            return sqrt(l * r);
        };
    }
    for (int i=1; i<=200; i++) {
        ldb mid = get_mid(l, r);
        if (can(mid)) r = mid;
        else l = mid;
    }
    cout << fixed << setprecision(12);
    cout << get_mid(l, r) << "\n";
    return 0;
}
