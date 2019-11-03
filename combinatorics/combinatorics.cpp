#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define pb push_back
#define ppp pop_back
#define pii pair<int, int>
#define fi first
#define se second
#define div divi

const int N = 1e5 + 5;
const ll p = 1e9 + 7;

ll fac[N], inv[N];

inline ll mult(ll a, ll b) {
    return ((a * b) % p + p) % p;
}

inline ll add(ll a, ll b) {
    return ((a + b) % p + p) % p;
}

inline ll sub(ll a, ll b) {
    return ((a - b) % p + p) % p;
}

ll binpow(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) res = mult(res, a);
        b >>= 1;
        a = mult(a, a);
    }
    return res;
}

inline ll div(ll a, ll b) {
    return mult(a, binpow(b, p-2));
}

ll c(int a, int b) {
    if (b < 0 || a < b) return 0;
    return mult(mult(fac[a], inv[b]), inv[a-b]);
}

void precalc() {
    fac[0] = 1;
    for (int i=1; i<N; i++) fac[i] = mult(fac[i-1], i);
    inv[N-1] = binpow(fac[N-1], p-2);
    for (int i=N-1; i>=1; i--) inv[i-1] = mult(inv[i], i);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif
    precalc();
    return 0;
}