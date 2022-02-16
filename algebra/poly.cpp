#include <bits/stdc++.h>
using namespace std;

// inv: https://official.contest.yandex.com/ptz-winter-2022/contest/34820/problems/M1

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

const int mod = 998244353; // 985661441

namespace NTT {
    const int K = 1 << 20; // be careful
    const mint<mod> root = binpow(mint<mod>(3), (mod - 1) / K);
    // 3 is a primitive root modulo mod

    typedef vector<mint<mod>> poly;

    mint<mod> prec_w[K / 2];
    mint<mod> w[K];

    bool initialized = 0;
    void init() {
        if (initialized) {
            return;
        }
        initialized = 1;
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

    void fft(mint<mod>* in, mint<mod>* out, int n, int k = 1) {
        if (n == 1) {
            *out = *in;
            return;
        }
        n /= 2;
        fft(in, out, n, 2 * k);
        fft(in + k, out + n, n, 2 * k);
        for (int i = 0; i < n; i++) {
            mint<mod> t = out[i + n] * w[i + n];
            out[i + n] = out[i] - t;
            out[i] += t;
        }
    }

    void align(poly& a, poly& b) {
        int n = a.size() + b.size() - 1;
        while (a.size() < n) a.push_back(0);
        while (b.size() < n) b.push_back(0);
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
        return res;
    }

    poly mult(poly a, poly b) {
        init();
        align(a, b);
        a = eval(a);
        b = eval(b);
        for (int i = 0; i < a.size(); i++) {
            a[i] *= b[i];
        }
        a = inter(a);
        return a;
    }
}

template <class T>
vector<T> mult_fft(const vector<T>& a, const vector<T>& b);

template <>
vector<mint<mod>> mult_fft(const vector<mint<mod>>& a,
        const vector<mint<mod>>& b) {
    return NTT::mult(a, b);
}

template <class T>
vector<T> mult_slow(const vector<T>& a, const vector<T>& b) {
    if (a.empty() || b.empty()) {
        return {};
    }
    vector<T> res = a;
    res.resize(a.size() + b.size() - 1);
    for (int k = res.size() - 1; k >= 0; k--) {
        res[k] *= b[0];
        for (int j = 1; j < min(k + 1, (int) b.size()); j++) {
            res[k] += res[k - j] * b[j];
        }
    }
    return res;
}

template <class T>
struct poly {
    vector<T> a;
    void trim() {
        while (!a.empty() && a.back() == T(0)) {
            a.pop_back();
        }
    }
    poly() = default;
    poly(const T& b) : a{b} {
        trim();
    }
    poly(const vector<T>& b) : a(b) {
        trim();
    }
    poly(initializer_list<T> b) : a(b) {
        trim();
    }
    friend ostream& operator<<(ostream& out, poly a) {
        out << "{";
        for (int i = 0; i <= a.deg(); i++) {
            if (i > 0) {
                out << ", ";
            }
            out << a[i];
        }
        out << "}";
        return out;
    }
    int deg() const {
        if (a.empty()) {
            return -1;
        }
        return a.size() - 1;
    }
    T& operator[](size_t i) {
        if (i < 0 || deg() < i) {
            assert(0);
        }
        return a[i];
    }
    T operator[](size_t i) const {
        if (i < 0 || deg() < i) {
            return T(0);
        }
        return a[i];
    }
    T operator()(const T& b) const {
        T res(0);
        T pow_b(1);
        for (int i = 0; i <= deg(); i++) {
            res += a[i] * pow_b;
            pow_b *= b;
        }
        return res;
    }
    poly operator-() const {
        poly res = *this;
        for (int i = 0; i <= deg(); i++) {
            res[i] = -res[i];
        }
        return res;
    }
    poly& operator+=(const poly& b) {
        while (deg() < b.deg()) {
            a.push_back(T(0));
        }
        for (int i = 0; i <= b.deg(); ++i) {
            a[i] += b[i];
        }
        trim();
        return *this;
    }
    poly& operator-=(const poly& b) {
        while (deg() < b.deg()) {
            a.push_back(T(0));
        }
        for (int i = 0; i <= b.deg(); ++i) {
            a[i] -= b[i];
        }
        trim();
        return *this;
    }
    poly& operator*=(const poly& b) {
        if (deg() == -1 || b.deg() == -1) {
            a.clear();
            return *this;
        }
        // a = mult_slow(a, b.a);
        a = mult_fft(a, b.a);
        trim();
        return *this;
    }
    friend poly operator+(poly a, const poly& b) { return a += b; }
    friend poly operator-(poly a, const poly& b) { return a -= b; }
    friend poly operator*(poly a, const poly& b) { return a *= b; }
    friend bool operator==(const poly& a, const poly& b) { return a.a == b.a; }
    friend bool operator!=(const poly& a, const poly& b) { return !(a == b); }
    poly pow(int64_t b) const {
        poly res(1);
        poly cur = *this;
        while (b) {
            if (b & 1) {
                res *= cur;
            }
            cur *= *this;
            b >>= 1;
        }
        return res;
    }
    poly mod_xk(int k) const { // get first k coefficients
        return vector<T>(a.begin(), a.begin() + min(k, (int) a.size()));
    }
    poly mul_xk(int k) const { // multiply by x^k
        vector<T> res = a;
        res.insert(res.begin(), k, 0);
        return res;
    }
    poly div_xk(int k) const { // drop first k coefficients
        return vector<T>(a.begin() + min(k, (int) a.size()), a.end());
    }
    poly substr(int l, int r) const { // return mod_xk(r).div_xk(l)
        return vector<T>(a.begin() + min(l, (int) a.size()),
            a.begin() + min(r, (int) a.size()));
    }
    poly inv(int n) const {
        assert((*this)[0] != T(0));
        poly res{T(1) / a[0]};
        int k = 1;
        while (k < n) {
            poly b = (res * mod_xk(2 * k)).substr(k, 2 * k);
            res -= (res * b).mod_xk(k).mul_xk(k);
            k *= 2;
        }
        return res.mod_xk(n);
    }
};

int main() {
    return 0;
}
