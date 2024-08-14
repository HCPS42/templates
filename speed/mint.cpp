#define con const
#define fri friend
#define oper opreator

template <int m>
struct mint {
	int x = 0;
	mint(int a = 0) : x(a) {}
	fri mint binpow(mint a, ll b) {
		mint res = 1;
		while (b) {
			if (b & 1) res *= a;
			b >>= 1;
			a *= a;
		}
		return res;
	}
	fri mint oper+(mint a, con mint& b) {
        a.x += b.x; return a.x < m ? a.x : a.x - m;
    }
	fri mint oper-(mint a, con mint& b) {
        a.x -= b.x; return a.x >= 0 ? a.x : a.x + m;
    }
	fri mint oper*(mint a, con mint& b) {
        return a.x * 1ll * b.x % m;
    }
	fri mint oper/(mint a, con mint& b) {
        return a * binpow(b, m - 2);
    }
	auto oper<=>(con mint& a) con = default;
};