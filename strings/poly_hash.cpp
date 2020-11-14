#include <bits/stdc++.h>
using namespace std;

template<int m>
struct mint {
    int x = 0;
    mint(int64_t a = 0) { if (a < 0) a = a % m + m; if (a >= m) a %= m; x = a; }
    friend istream& operator>>(istream& in, mint& a) { int64_t y; cin >> y; a = y; return in; }
    friend ostream& operator<<(ostream& out, mint a) { return out << a.x; }
    explicit operator int() const { return x; }
    static int mod_inv(int a, int mod = m) {
        // https://en.wikipedia.org/wiki/Extended_Euclidean_algorithm#Example
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
#if !defined(_WIN32) || defined(_WIN64)
        return x % mod;
#endif
        // Optimized mod for Codeforces 32-bit machines.
        // x must be less than 2^32 * mod for this to work, so that x / mod fits in a 32-bit integer.
        unsigned x_high = x >> 32, x_low = (unsigned) x; unsigned quot, rem;
        asm("divl %4\n" : "=a" (quot), "=d" (rem) : "d" (x_high), "a" (x_low), "r" (mod));
        return rem;
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

template<int m>
struct PolyHash {
    mint<m> x;
    PolyHash(int x) : x(x) {}
    vector<mint<m>> pw;
    vector<mint<m>> pref;
    void init(vector<int>& a) {
        int n = a.size();
        pw.assign(n, 0);
        pref.assign(n, 0);
        pw[0] = 1;
        pref[0] = a[0];
        for (int i=1; i<n; i++) {
            pref[i] = pref[i - 1] * x + a[i];
            pw[i] = pw[i - 1] * x;
        }
    }
    mint<m> get(int l, int r) {
        return pref[r] - pref[l - 1] * pw[r - l + 1];
    }
};

/*
const int m1 = 1000000123;
const int m2 = 1000000321;
const int m3 = 5000101;
const int m4 = 7000003;
const int m5 = 5003;
const int m6 = 6007;
*/

const int m1 = 998244353;
const int m2 = 985661441;

PolyHash<m1> h1(518963131);
PolyHash<m2> h2(379359013);

int main() {
    return 0;
}
