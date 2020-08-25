#include <bits/stdc++.h>
using namespace std;

const int p = 998244353; // 985661441
const int root = 518963131; // 379359013
const int K = 1 << 20; // be careful

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

int mult(int a, int b) {
	return a * 1ll * b % p;
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

typedef vector<int> poly;

int prec_w[K / 2];
int w[K];

void init() {
	prec_w[0] = 1;
	for (int i = 1; i < K / 2; i++) {
		prec_w[i] = mult(prec_w[i - 1], root);
	}
	for (int i = 1; i < K; i *= 2) {
		for (int j = 0; j < i; j++) {
			w[i + j] = prec_w[K / (2 * i) * j];
		}
	}
}

void fft(int* in, int* out, int n, int k = 1) {
	if (n == 1) {
		*out = *in;
		return;
	}
	n /= 2;
	fft(in, out, n, 2 * k);
	fft(in + k, out + n, n, 2 * k);
	for (int i = 0; i < n; i++) {
		int t = mult(out[i + n], w[i + n]);
		out[i + n] = sub(out[i], t);
		out[i] = add(out[i], t);
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
	poly inv(n);
	fft(a.data(), inv.data(), n);
	poly res(n);
	for (int i = 0; i < n; i++) {
		res[i] = divi(inv[i], n);
	}
	reverse(res.begin() + 1, res.end());
	return res;
}

poly mult(poly a, poly b) {
	align(a, b);
	a = eval(a);
	b = eval(b);
	for (int i = 0; i < a.size(); i++) {
		a[i] = mult(a[i], b[i]);
	}
	return inter(a);
}

int main() {
    init();
	return 0;
}
