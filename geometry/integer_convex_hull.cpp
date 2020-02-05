#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define pb push_back
#define ppp pop_back
#define pii pair<int,int>
#define fi first
#define se second

typedef complex<ll> point;

#define x() real()
#define y() imag()

ll dot(point a, point b) {
	return (conj(a) * b).x();
}

ll cross(point a, point b) {
	return (conj(a) * b).y();
}

bool cmp(point& a, point& b) {
	if (a.y() < b.y()) return 1;
	if (a.y() > b.y()) return 0;
	return a.x() < b.x();
}

bool cmp_angle(point& a, point& b) {
	if (a.x() == 0 && b.x() == 0) {
		return a.y() < b.y();
	}
	if (a.x() == 0) {
		return b.x() < 0;
	}
	if (b.x() == 0) {
		return 0 < a.x();
	}
	if (a.y() * b.x() == b.y() * a.x()) {
		return cmp(a, b);
	}
	if (a.x() > 0 && b.x() > 0) {
		return a.y() * b.x() < b.y() * a.x();
	}
	if (a.x() > 0) {
		return 1;
	}
	if (b.x() > 0) {
		return 0;
	}
	return a.y() * b.x() < b.y() * a.x();
}

vector<point> convex_hull(vector<point> a) {
	sort(a.begin(), a.end(), cmp);
	point shift = a[0];
	for (point& A : a) {
		A -= shift;
	}
	vector<point> b;
	for (int i=1; i<a.size(); i++) {
		b.pb(a[i]);
	}
	sort(b.begin(), b.end(), cmp_angle);
	vector<point> hull;
	for (point A : b) {
		while (hull.size() >= 2) {
			point B = hull.back();
			point C = hull[hull.size()-2];
			if (cross(C, B) + cross(B, A) <= cross(C, A)) {
				hull.ppp();
			}
			else break;
		}
		hull.pb(A);
	}
	reverse(hull.begin(), hull.end());
	hull.pb(0);
	reverse(hull.begin(), hull.end());
	for (point& A : hull) {
		A += shift;
	}
	return hull;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
#ifdef LOCAL
	freopen("input.txt", "r", stdin);
#endif
	
	return 0;
}
