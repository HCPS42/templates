#include <bits/stdc++.h>
using namespace std;

template <int m>
struct mint {
	int x = 0;
	mint(int a = 0) : x(a) {}
	friend istream& operator>>(istream& is, mint& a) { return is >> a.x; }
	friend ostream& operator<<(ostream& os, mint& a) { return os << a.x; }
	friend mint binpow(mint a, ll b) {
		mint res = 1;
		while (b) {
			if (b & 1) res *= a;
			b >>= 1;
			a *= a;
		}
		return res;
	}
	mint pow(ll a) con { return binpow(*this, a); }
	mint inv() con { return pow(m - 2); }
	mint operator-() con { return x ? m - x : 0; }
	mint& operator+=(con mint& a) { x += a.x; if (x >= m) x -= m; return *this; }
	mint& operator-=(con mint& a) { x -= a.x; if (x < 0) x += m; return *this; }
	mint& operator*=(con mint& a) { x = x * 1ll * a.x % m; return *this; }
	mint& operator/=(con mint& a) { return *this *= a.inv(); }
	friend mint operator+(mint a, con mint& b) { return a += b; }
	friend mint operator-(mint a, con mint& b) { return a -= b; }
	friend mint operator*(mint a, con mint& b) { return a *= b; }
	friend mint operator/(mint a, con mint& b) { return a /= b; }
	bool operator==(con mint& a) con { return x == a.x; }
	bool operator!=(con mint& a) con { return x != a.x; }
};

int main() {
    return 0;
}
