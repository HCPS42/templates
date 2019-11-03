#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define pb push_back
#define ppp pop_back
#define pii pair<int, int>
#define fi first
#define se second

typedef complex<ll> point;
#define x real
#define y imag

ll dot(point a, point b) {
    return (conj(a) * b).x();
}

ll cross(point a, point b) {
    return (conj(a) * b).y();
}

struct CHT {
	vector<point> hull, vecs;
	void clear() {
		hull.clear();
		vecs.clear();
	}
	void add(ll k, ll b) {
		point nw = {k, b};
		while (!vecs.empty() && dot(vecs.back(), nw - hull.back()) < 0) {
			hull.ppp();
			vecs.ppp();
		}
		if (!hull.empty()) {
			vecs.pb(complex<ll>(1i) * (nw - hull.back()));
		}
		hull.pb(nw);
	}
	ll get(ll x) {
		point query = {x, 1};
		auto it = lower_bound(vecs.begin(), vecs.end(), query, [](point a, point b) {
			return cross(a, b) > 0;
		});
		return dot(query, hull[it - vecs.begin()]);
	}
};

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif
	
    return 0;
}
