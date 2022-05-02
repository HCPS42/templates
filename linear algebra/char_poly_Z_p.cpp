#include <bits/stdc++.h>
using namespace std;

// task: https://official.contest.yandex.com/ptz-summer-2020/contest/19423/problems/K6/?success=33867899#7/2020_08_27/MTr3ZtBTrK

template <int m>
struct mint {
    int x = 0;
    mint(int64_t a = 0) { if (a < 0) a = a % m + m; if (a >= m) a %= m; x = a; }
    friend istream& operator>>(istream& in, mint& a) { int64_t y; in >> y; a = y; return in; }
    friend ostream& operator<<(ostream& out, mint a) { return out << a.x; }
    explicit operator int() const { return x; }
    static int mod_inv(int a, int mod = m) {
        int g = mod, r = a, z = 0, y = 1;
        while (r != 0) { int q = g / r; g %= r; swap(g, r); z -= q * y; swap(z, y); }
        return z < 0 ? z + mod : z;
    }
    mint inv() const { return mod_inv(x, m); }
    friend mint binpow(mint a, int64_t b) { mint res = 1; while (b) { if (b & 1) res *= a; b >>= 1; a *= a; } return res; }
    mint pow(int64_t b) const { return binpow(*this, b); }
    mint operator-() const { return x ? m - x : 0; }
    mint& operator+=(const mint& a) { x += a.x; if (x >= m) x -= m; return *this; }
    mint& operator-=(const mint& a) { x -= a.x; if (x < 0) x += m; return *this; }
    static unsigned fast_mod(uint64_t x, unsigned mod = m) {
#if defined(_WIN32) && !defined(_WIN64)
        // Optimized mod for Codeforces 32-bit machines.
        // x must be less than 2^32 * mod for this to work, so that x / mod fits in a 32-bit integer.
        unsigned x_high = x >> 32, x_low = (unsigned) x; unsigned quot, rem;
        asm("divl %4\n" : "=a" (quot), "=d" (rem) : "d" (x_high), "a" (x_low), "r" (mod));
        return rem;
#else
        return x % mod;
#endif
    }
    mint& operator*=(const mint& a) { x = fast_mod((uint64_t) x * a.x); return *this; }
    mint& operator/=(const mint& a) { return *this *= a.inv(); }
    friend mint operator+(mint a, const mint& b) { return a += b; }
    friend mint operator-(mint a, const mint& b) { return a -= b; }
    friend mint operator*(mint a, const mint& b) { return a *= b; }
    friend mint operator/(mint a, const mint& b) { return a /= b; }
    mint& operator++() { x = x == m - 1 ? 0 : x + 1; return *this; }
    mint& operator--() { x = x == 0 ? m - 1 : x - 1; return *this; }
    mint operator++(int) { mint a = *this; ++*this; return a; }
    mint operator--(int) { mint a = *this; --*this; return a; }
    bool operator==(const mint& a) const { return x == a.x; }
    bool operator!=(const mint& a) const { return x != a.x; }
};

const int p = 998244353; // 985661441
const int K = 1 << 20; // be careful
const mint<p> root = binpow(mint<p>(3), (p - 1) / K); // 3 is a primitive root mod p

typedef vector<mint<p>> poly;

mint<p> prec_w[K / 2];
mint<p> w[K];

void init() {
    prec_w[0] = 1;
    for (int i = 1; i < K / 2; i++) {
        prec_w[i] = prec_w[i - 1] * root;
    }
    for (int i = 1; i < K; i *= 2) {
        for (int j = 0; j < i; j++) {
            w[i + j] = prec_w[K / (2 * i) * j];
        }
    }
}

void fft(mint<p>* in, mint<p>* out, int n, int k = 1) {
    if (n == 1) {
        *out = *in;
        return;
    }
    n /= 2;
    fft(in, out, n, 2 * k);
    fft(in + k, out + n, n, 2 * k);
    for (int i = 0; i < n; i++) {
        mint<p> t = out[i + n] * w[i + n];
        out[i + n] = out[i] - t;
        out[i] += t;
    }
}

void align(poly& a, poly& b) {
    int n = a.size() + b.size() - 1;
    while (a.size() < n) a.push_back(0);
    while (b.size() < n) b.push_back(0);
}

void trim(poly& a) {
    while (a.size() > 1 && a.back() == 0) {
        a.pop_back();
    }
}

poly eval(poly& a) {
    while (__builtin_popcount(a.size()) != 1) {
        a.push_back(0);
    }
    poly res(a.size());
    fft(a.data(), res.data(), a.size());
    return res;
}

poly inter(poly a) {
    int n = a.size();
    poly res(n);
    fft(a.data(), res.data(), n);
    for (int i = 0; i < n; i++) {
        res[i] /= n;
    }
    reverse(res.begin() + 1, res.end());
    trim(res);
    return res;
}

poly mult(poly a, poly b) {
    align(a, b);
    a = eval(a);
    b = eval(b);
    for (int i = 0; i < a.size(); i++) {
        a[i] *= b[i];
    }
    a = inter(a);
    trim(a);
    return a;
}

poly add(poly a, poly b) {
    while (a.size() < b.size()) a.push_back(0);
    while (b.size() < a.size()) b.push_back(0);
    for (int i = 0; i < a.size(); i++) {
        a[i] += b[i];
    }
    trim(a);
    return a;
}

typedef vector<vector<mint<p>>> matrix;
typedef vector<vector<poly>> matrix_poly;

poly slow_char_poly(matrix_poly a) {
    int n = a.size();
    if (n == 1) {
        return a[0][0];
    }
    poly res = {0};
    for (int i = 0; i < n; i++) {
        poly cur = a[0][i];
        if (i & 1) {
            for (mint<p>& j : cur) {
                j *= -1;
            }
        }
        matrix_poly adj(n - 1, vector<poly>(n - 1, {0}));
        for (int j = 1; j < n; j++) {
            int c = 0;
            for (int k = 0; k < n; k++) {
                if (k == i) continue;
                adj[j - 1][c] = a[j][k];
                c++;
            }
        }
        cur = mult(cur, slow_char_poly(adj));
        res = add(res, cur);
    }
    return res;
}

poly slow_char_poly(matrix a) {
    // det(A - x I)
    int n = a.size();
    matrix_poly b(n, vector<poly>(n, {0}));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                b[i][j] = {a[i][j], -1};
            }
            else {
                b[i][j] = {a[i][j]};
            }
        }
    }
    return slow_char_poly(b);
}

void hess(matrix& a) {
    // Reduction to upper Hessenberg form
    // xxxxx
    // xxxxx
    // oxxxx
    // ooxxx
    // oooxx
    // O(n^3)
    int n = a.size();
    for (int j = 0; j <= n - 3; j++) {
        for (int i = j + 2; i <= n - 1; i++) {
            if (a[i][j] == 0) continue;
            swap(a[i], a[j + 1]);
            for (int k = 0; k <= n - 1; k++) {
                swap(a[k][i], a[k][j + 1]);
            }
            break;
        }
        if (a[j + 1][j] == 0) continue;
        for (int i = j + 2; i <= n - 1; i++) {
            if (a[i][j] == 0) continue;
            mint<p> b = a[i][j] / a[j + 1][j];
            for (int k = j; k <= n - 1; k++) {
                a[i][k] -= b * a[j + 1][k];
            }
            for (int k = 0; k <= n - 1; k++) {
                a[k][j + 1] += b * a[k][i];
            }
        }
    }
}

mint<p> det_hess(matrix a) {
    // Determinant of Hessenberg matrix
    // O(n^2)
    int n = a.size();
    vector<mint<p>> d(n + 1, 0);
    d[0] = 1;
    d[1] = a[0][0];
    for (int k = 2; k <= n; k++) {
        mint<p> suf = 1;
        for (int i = k - 1; i >= 0; i--) {
            mint<p> cur = d[i] * suf * a[i][k - 1];
            if ((i + k - 1) & 1) {
                d[k] -= cur;
            }
            else {
                d[k] += cur;
            }
            if (i) {
                suf *= a[i][i - 1];
            }
        }
    }
    return d[n];
}

poly char_poly(matrix a) {
    // Characteristic polynomial
    // det(A - x I)
    // O(n^3)
    hess(a);
    int n = a.size();
    int k = n + 1;
    while (__builtin_popcount(k) != 1) k++;
    poly b(k, 0);
    mint<p> g = root.pow(K / k);
    mint<p> cur = 1;
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < n; j++) {
            a[j][j] -= cur;
        }
        b[i] = det_hess(a);
        for (int j = 0; j < n; j++) {
            a[j][j] += cur;
        }
        cur *= g;
    }
    b = inter(b);
    return b;
}

int main() {
    init();
    return 0;
}
