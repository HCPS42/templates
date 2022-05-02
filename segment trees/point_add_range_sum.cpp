#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 1e6 + 5;

struct seg_tree {
    static const int K = 1 << int(ceil(log2(N)));
    ll t[2 * K];
    void upd(int v, ll x) {
        v += K;
        while (v) {
            t[v] += x;
            v /= 2;
        }
    }
    ll get(int l, int r) {
        l += K;
        r += K;
        ll res = 0;
        while (l <= r) {
            if (l % 2 == 1) res += t[l++];
            if (r % 2 == 0) res += t[r--];
            l /= 2;
            r /= 2;
        }
        return res;
    }
};

int main() {
    return 0;
}
