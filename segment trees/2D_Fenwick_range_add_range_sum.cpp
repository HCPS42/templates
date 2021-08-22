#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 1005;

struct Fenwick_2D {
    ll t[4][N][N];
    void add(int tp, int x, int y, ll d) {
        // (i, j) += d in array #tp
        for (int i = x; i < N; i += i & -i) {
            for (int j = y; j < N; j += j & -j) {
                t[tp][i][j] += d;
            }
        }
    }
    ll sum(int tp, int x, int y) {
        // sum of [1, x] \times [1, y] in array #tp
        ll res = 0;
        for (int i = x; i >= 1; i -= i & -i) {
            for (int j = y; j >= 1; j -= j & -j) {
                res += t[tp][i][j];
            }
        }
        return res;
    }
    void upd(int x, int y, ll d) {
        // [x, n] \times [y, m] += d
        add(0, x, y, d);
        add(1, x, y, d * (1 - y));
        add(2, x, y, d * (1 - x));
        add(3, x, y, d * (1 - x) * (1 - y));
    }
    void upd(int x1, int y1, int x2, int y2, ll d) {
        // [x1, x2] \times [y1, y2] += d
        upd(x1, y1, d);
        upd(x1, y2 + 1, -d);
        upd(x2 + 1, y1, -d);
        upd(x2 + 1, y2 + 1, d);
    }
    ll get(int x, int y) {
        // sum of [1, x] \times [1, y]
        return sum(0, x, y) * x * y + sum(1, x, y) * x + sum(2, x, y) * y + sum(3, x, y);
    }
    ll get(int x1, int y1, int x2, int y2) {
        // sum of [x1, x2] \times [y1, y2]
        return get(x2, y2) - get(x2, y1 - 1) - get(x1 - 1, y2) + get(x1 - 1, y1 - 1);
    }
};

int main() {
    return 0;
}
