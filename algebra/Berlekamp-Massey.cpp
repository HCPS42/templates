#include <bits/stdc++.h>
using namespace std;

// https://official.contest.yandex.com/ptz-winter-2022/contest/34820/problems/M1

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

const int mod = 998244353;

// https://codeforces.com/blog/entry/61306
namespace LinearRecurrence {
    const int K = 230'000;
    vector<mint<mod>> BerlekampMassey(vector<mint<mod>> x) {
        vector<mint<mod>> ls;
        vector<mint<mod>> cur;
        int lf;
        mint<mod> ld;
        for (int i = 0; i < x.size(); i++) {
            mint<mod> t = 0;
            for (int j = 0; j < cur.size(); j++) {
                t += x[i - j - 1] * cur[j];
            }
            if (t == x[i]) continue;
            if (cur.empty()) {
                cur.resize(i + 1);
                lf = i;
                ld = t - x[i];
                continue;
            }
            mint<mod> k = -(x[i] - t) / ld;
            vector<mint<mod>> c(i - lf - 1);
            c.push_back(k);
            for (int j = 0; j < ls.size(); j++) {
                c.push_back(-ls[j] * k);
            }
            if (c.size() < cur.size()) {
                c.resize(cur.size());
            }
            for (int j = 0; j < cur.size(); j++) {
                c[j] += cur[j];
            }
            if (i - lf + ls.size() >= cur.size()) {
                ls = cur;
                lf = i;
                ld = t - x[i];
            }
            cur = c;
        }
        return cur;
    }
    int m;
    mint<mod> a[K];
    mint<mod> h[K];
    mint<mod> t_[K];
    mint<mod> s[K];
    mint<mod> t[K];
    void mult(mint<mod>* p, mint<mod>* q) {
        for (int i = 0; i < m + m; i++) {
            t_[i] = 0;
        }
        for (int i = 0; i < m; i++) {
            if (p[i] == 0) continue;
            for (int j = 0; j < m; j++) {
                t_[i + j] += p[i] * q[j];
            }
        }
        for (int i = m + m - 1; i >= m; i--) {
            if (t_[i] == 0) continue;
            for (int j = m - 1; ~j; j--) {
                t_[i - j - 1] += t_[i] * h[j];
            }
        }
        for (int i = 0; i < m; i++) {
            p[i] = t_[i];
        }
    }
    mint<mod> calc(int64_t k) {
        for (int i = m; ~i; i--) {
            s[i] = t[i] = 0;
        }
        s[0] = 1;
        if (m != 1) t[1] = 1;
        else t[0] = h[0];
        while(k) {
            if (k & 1) mult(s, t);
            mult(t, t);
            k >>= 1;
        }
        mint<mod> res = 0;
        for (int i = 0; i < m; i++) {
            res += s[i] * a[i];
        }
        return res;
    }
    mint<mod> find_kth(vector<mint<mod>> x, int64_t k) {
        if (k < x.size()) return x[k];
        vector<mint<mod>> v = BerlekampMassey(x);
        m = v.size();
        if (!m) return 0;
        for (int i = 0; i < m; i++) {
            h[i] = v[i];
            a[i] = x[i];
        }
        return calc(k);
    }
}

using LinearRecurrence::BerlekampMassey;
using LinearRecurrence::find_kth;

int main() {
    return 0;
}
