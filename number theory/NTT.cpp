#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define pb push_back
#define ppp pop_back
#define fi first
#define se second
#define pii pair<int,int>

const ll P[2] = {998244353, 985661441};
const ll G[2] = {518963131, 379359013};

typedef vector<ll> poly;

const int K = 1 << 20;

ll precalc_w[K/2];
ll w[K];

ll binpow(ll a, ll b, ll p) {
	ll res = 1;
	while (b) {
		if (b & 1) res = res * a % p;
		b >>= 1;
		a = a * a % p;
	}
	return res;
}

void init(ll p, ll g) {
	precalc_w[0] = 1;
	for (int i=1; i<K/2; i++) {
		precalc_w[i] = precalc_w[i-1] * g % p;
	}
	for (int i=1; i<K; i*=2) {
		for (int j=0; j<i; j++) {
			w[i+j] = precalc_w[K / (2 * i) * j];
		}
	}
}

void fft(ll *in, ll *out, int n, ll p, int k = 1) {
	if (n == 1) {
		*out = *in;
		return;
	}
	n /= 2;
	fft(in, out, n, p, 2*k);
	fft(in+k, out+n, n, p, 2*k);
	for (int i=0; i<n; i++) {
		ll t = out[i+n] * w[i+n] % p;
		out[i+n] = out[i] - t;
		if (out[i+n] < 0) out[i+n] += p;
		out[i] += t;
		if (out[i] >= p) out[i] -= p;
	}
}

void align(poly &a, poly &b) {
	int n = a.size() + b.size() - 1;
	while (a.size() < n) a.pb(0);
	while (b.size() < n) b.pb(0);
}

poly eval(poly a, ll p) {
	while (__builtin_popcount(a.size()) != 1) a.pb(0);
	poly res(a.size());
	fft(a.data(), res.data(), a.size(), p);
	return res;
}

poly inter(poly a, ll p) {
	int n = a.size();
	poly inv(n);
	fft(a.data(), inv.data(), n, p);
	poly res(n);
	for (int i=0; i<n; i++) {
		res[i] = inv[i] * binpow(n, p-2, p) % p;
	}
	reverse(res.begin()+1, res.end());
	return res;
}

poly mult(poly a, poly b, ll p) {
	align(a, b);
	a = eval(a, p);
	b = eval(b, p);
	for (int i=0; i<a.size(); i++) a[i] = a[i] * b[i] % p;
	return inter(a, p);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif
	init();
	
	return 0;
}
