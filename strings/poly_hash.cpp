#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define pb push_back
#define ppp pop_back
#define pii pair<int,int>
#define fi first
#define se second

template<int m>
struct mint {
	int x;
	mint(int x = 0) : x(x) {}
	mint operator-() const { return x ? m - x : 0; }
	mint operator+(const mint& a) const { int y = x; y += a.x; if (y >= m) y -= m; return y; }
	mint operator-(const mint& a) const { int y = x; y -= a.x; if (y < 0) y += m; return y; }
	mint operator*(const mint& a) const { return x * 1ll * a.x % m; }
	mint& operator++() { if (x + 1 == m) return 0; return x + 1; }
	mint operator++(int) { mint y(*this); operator++(); return y; }
	mint& operator+=(const mint& a) { x += a.x; if (x >= m) x -= m; return *this; }
	mint& operator-=(const mint& a) { x -= a.x; if (x < 0) x += m; return *this; }
	mint& operator*=(const mint& a) { x = x * 1ll * a.x % m; return *this; }
	bool operator==(const mint& a) { return x == a.x; }
	bool operator!=(const mint& a) { return x != a.x; }
};

template<int m>
ostream& operator<<(ostream& out, const mint<m>& a) {
	return out << a.x;
}

template<int m>
struct PolyHash {
	// mt19937 rnd;
	// mint<m> x = rnd() % int(sqrt(m)) + 1000;
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

void Solve() {

}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
#ifdef LOCAL
	freopen("input.txt", "r", stdin);
#endif
	Solve();
	return 0;
}
