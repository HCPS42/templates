tem <int m>
struct M {
	int x = 0;
	M(int a = 0) : x(a) {}
	fri istream& oper>>(istream& is, M& a) { return is >> a.x; }
	fri ostream& oper<<(ostream& os, M& a) { return os << a.x; }
	fri M binpow(M a, ll b) {
		M res = 1;
		while (b) {
			if (b & 1) res *= a;
			b >>= 1;
			a *= a;
		}
		return res;
	}
	M pow(ll a) con { return binpow(*this, a); }
	M inv() con { return pow(m - 2); }
	M oper-() con { return x ? m - x : 0; }
	M& oper+=(con M& a) { x += a.x; if (x >= m) x -= m; return *this; }
	M& oper-=(con M& a) { x -= a.x; if (x < 0) x += m; return *this; }
	M& oper*=(con M& a) { x = x * 1ll * a.x % m; return *this; }
	M& oper/=(con M& a) { return *this *= a.inv(); }
	fri M oper+(M a, con M& b) { return a += b; }
	fri M oper-(M a, con M& b) { return a -= b; }
	fri M oper*(M a, con M& b) { return a *= b; }
	fri M oper/(M a, con M& b) { return a /= b; }
	bool oper==(con M& a) con { return x == a.x; }
	bool oper!=(con M& a) con { return x != a.x; }
};

con int mod = 998244353;
#define mi M<Mod>