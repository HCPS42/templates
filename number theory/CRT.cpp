#include <bits/stdc++.h>
using namespace std;

template<class T>
void red(T& r, T a) {
	r = ((r % a) + a) % a;
}

template<class T>
T mod_inv(T r, T a) {
	T g = a;
	T z = 0;
	T y = 1;
	while (r != 0) {
		T q = g / r;
		g %= r;
		swap(g, r);
		z -= q * y;
		swap(z, y);
	}
	return z < 0 ? z + a : z;
}

template<class T>
pair<T, T> crt(T ra, T a, T rb, T b) {
	red(ra, a);
	red(rb, b);
	T d = __gcd(a, b);
	if (ra % d != rb % d) {
		return {0, 0};
	}
	T mod = (a / d) * (b / d);
	T r = 0;
	r = (r + ((ra / d) * (b / d) % mod) * mod_inv(b / d, a / d) % mod) % mod;
	r = (r + ((rb / d) * (a / d) % mod) * mod_inv(a / d, b / d) % mod) % mod;
	mod *= d;
	T res = (r * d % mod + ra % d) % mod;
	return {res, mod};
}

template<class T>
pair<T, T> CRT(vector<T> r, vector<T> a) {
	int n = a.size();
	for (int i=0; i<n; i++) {
		red(r[i], a[i]);
	}
	pair<T, T> res = {0, 1};
	for (int i=0; i<n; i++) {
		res = crt(res.fi, res.se, r[i], a[i]);
		if (res.se == 0) {
			return {0, 0};
		}
	}
	return res;
}

int main() {
	return 0;
}
