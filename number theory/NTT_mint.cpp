#include <bits/stdc++.h>
using namespace std;

template<int m>
struct mint {
	int x;
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
	friend mint operator+(const mint& a, const mint& b) { return mint(a) += b; }
	friend mint operator-(const mint& a, const mint& b) { return mint(a) -= b; }
	friend mint operator*(const mint& a, const mint& b) { return mint(a) *= b; }
	friend mint operator/(const mint& a, const mint& b) { return mint(a) /= mint(b); }
	mint& operator++() { x = x == m - 1 ? 0 : x + 1; return *this; }
	mint& operator--() { x = x == 0 ? m - 1 : x - 1; return *this; }
	mint operator++(int) { mint a = *this; ++*this; return a; }
	mint operator--(int) { mint a = *this; --*this; return a; }
	mint operator-() const { return x ? m - x : 0; }
	bool operator==(const mint& a) const { return x == a.x; }
	bool operator!=(const mint& a) const { return x != a.x; }
};

const int p = 998244353; // 985661441
const mint<p> root = 518963131; // 379359013
const int K = 1 << 20; // be careful

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
	align(a, b);
	a = eval(a);
	b = eval(b);
	for (int i = 0; i < a.size(); i++) {
		a[i] *= b[i];
	}
	a = inter(a);
	return a;
}

int main() {
	init();
	return 0;
}
