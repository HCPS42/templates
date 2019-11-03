#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define pb push_back
#define ppp pop_back
#define fi first
#define se second
#define pii pair<int, int>

typedef complex<double> C;
typedef vector<C> poly_C;
typedef vector<ll> poly;

const ll base = 1e6; // possible overflow
const int dig = 6;
const int K = 1 << 20; // check
const double pi = acos(-1);

C w[K];

void init() {
	for (int i=1; i<K; i*=2) {
		for (int j=0; j<i; j++) {
			w[i+j] = polar(1.0, pi * j / i);
		}
	}
}

poly norm(poly a) {
	ll carry = 0;
	for (ll &coef : a) {
		coef += carry;
		carry = coef / base;
		coef %= base;
	}
	while (carry) {
		a.pb(carry % base);
		carry /= base;
	}
	return a;
}

void align(poly &a, poly &b) {
	int n = a.size() + b.size() - 1;
	while (a.size() < n) a.pb(0);
	while (b.size() < n) b.pb(0);
}

string num_to_str(int a) {
	string res;
	while (a) {
		res += '0' + (a % 10);
		a /= 10;
	}
	while (res.size() < dig) res += '0';
	return res;
}

string poly_to_str(poly a) {
	a = norm(a);
	string res;
	for (ll &coef : a) {
		res += num_to_str(coef);
	}
	while (!res.empty() && res.back() == '0') res.ppp();
	if (res.empty()) res = "0";
	reverse(res.begin(), res.end());
	return res;
}

poly str_to_poly(string a) {
	poly res;
	int len = a.size();
	while (len >= dig) {
		int cur = atoi(a.substr(len-dig, dig).c_str());
		res.pb(cur);
		a.erase(len-dig, dig);
		len -= dig;
	}
	if (len) res.pb(atoi(a.c_str()));
	return res;
}

template<typename T>
void fft(T *in, C *out, int n, int k = 1) {
	if (n == 1) {
		*out = *in;
		return;
	}
	n /= 2;
	fft(in, out, n, 2*k);
	fft(in+k, out+n, n, 2*k);
	for (int i=0; i<n; i++) {
		C t = out[i+n] * w[i+n];
		out[i+n] = out[i] - t;
		out[i] += t;
	}
}

poly_C eval(poly a) {
	while (__builtin_popcount(a.size()) != 1) a.pb(0);
	poly_C res(a.size());
	fft(a.data(), res.data(), a.size());
	return res;
}

poly inter(poly_C a) {
	int n = a.size();
	poly_C inv(n);
	fft(a.data(), inv.data(), n);
	poly res(n);
	for (int i=0; i<n; i++) {
		res[i] = round(real(inv[i]) / n);
	}
	reverse(res.begin()+1, res.end());
	return res;
}

poly mult_poly(poly a, poly b) {
	align(a, b);
	poly_C A = eval(a);
	poly_C B = eval(b);
	for (int i=0; i<A.size(); i++) A[i] *= B[i];
	return inter(A);
}

poly mult(poly a, poly b) {
	return norm(mult_poly(norm(a), norm(b)));
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif
	init();
	int T;
	cin >> T;
	while (T--) {
		string s, t;
		cin >> s >> t;
		poly a = str_to_poly(s);
		poly b = str_to_poly(t);
		string ans = poly_to_str(mult(a, b));
		cout << ans << "\n";
	}
	return 0;
}
