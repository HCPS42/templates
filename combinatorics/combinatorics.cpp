#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 1e5 + 5;
const int p = 1e9 + 7;

int fac[N]
int inv[N];

int mult(int a, int b) {
    return a * 1ll * b % p;
}

int add(int a, int b) {
    a += b;
    if (a >= p) a -= p;
    return a;
}

int sub(int a, int b) {
    a -= b;
    if (a < 0) a += p;
    return a;
}

int binpow(int a, int64_t b) {
    int res = 1;
    while (b) {
        if (b & 1) res = mult(res, a);
        b >>= 1;
        a = mult(a, a);
    }
    return res;
}

int divi(int a, int b) {
    return mult(a, binpow(b, p - 2));
}

int c(int a, int b) {
    if (b < 0 || a < b) return 0;
    return mult(mult(fac[a], inv[b]), inv[a - b]);
}

void init() {
    fac[0] = 1;
    for (int i = 1; i < N; i++) {
        fac[i] = mult(fac[i - 1], i);
    }
    inv[N - 1] = divi(1, fac[N - 1]);
    for (int i = N - 1; i >= 1; i--) {
        inv[i - 1] = mult(inv[i], i);
    }
}

int main() {
    init();
    return 0;
}
