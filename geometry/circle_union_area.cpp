#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define pb push_back
#define ppp pop_back
#define pii pair<int,int>
#define fi first
#define se second

// task: https://official.contest.yandex.com/mw2020prefinals/contest/18101/problems/I1/

typedef double ld;

const ld eps = 1e-8;
const ld pi = acos(-1);

int sig(ld x) {
	if (x < -eps) return -1;
	if (x > eps) return 1;
	return 0;
}

template<class T>
T sq(T x) {
	return x * x;
}

struct Point {
	ld x, y;

	Point() {}
	Point(ld x, ld y) : x(x), y(y) {}

	Point operator-() const { return Point(-x, -y); }
	Point operator+(const Point& a) const { return {x + a.x, y + a.y}; }
	Point operator-(const Point& a) const { return {x - a.x, y - a.y}; }
	Point operator*(const ld& a) const { return {a * x, a * y}; }
	Point operator/(const ld& a) const { return {x / a, y / a}; }
	Point rot(ld co, ld si) { return {co * x + si * y, co * y - si * x}; }
	Point rot(ld th) { return rot(cos(th), sin(th)); }
	Point elon(ld a = 1) { return *this / len() * a; }

	ld operator*(const Point& a) const { return x * a.x + y * a.y; }
	ld operator^(const Point& a) const { return x * a.y - y * a.x; }
	ld len2() { return x * x + y * y; }
	ld len() { return sqrt(len2()); }
	ld ang() { return atan2(y, x); }
};

struct Line {
	Point a, b;

	Line() {}
	Line(Point a, Point b) : a(a), b(b) {}
};

struct Circle {
	Point cen;
	ld r;

	Circle() {}
	Circle(Point cen, ld r) : cen(cen), r(r) {}

	// (d < R - r)         ----> -2
    // (d = R - r)         ----> -1
    // (d = 0)
    // (R - r < d < R + r) ---->  0
    // (d = R + r)         ---->  1
    // (d > R + r)         ---->  2
	int pos(Circle& a) {
		ld d = (cen - a.cen).len();
		int in = sig(d - abs(r - a.r));
		int ex = sig(d - (r + a.r));
		if (in < 0) return -2;
		if (in == 0) return -1;
		if (ex == 0) return 1;
		if (ex > 0) return 2;
		return 0;
	}

	Line inter(Circle& a) {
		Point b = a.cen - cen;
		ld th = acos((sq(r) + b.len2() - sq(a.r)) / (2 * r * b.len()));
		return {cen + b.rot(th).elon(r), cen + b.rot(-th).elon(r)};
	}
};

// -pi <= t <= pi
struct Range {
	ld t;
	int evt;
	Point p;

	Range() {}
	Range(ld t, int evt, Point p) : t(t), evt(evt), p(p) {}

	bool operator<(const Range& a) const {
        return sig(t - a.t) < 0 || (sig(t - a.t) == 0 && evt > a.evt);
    }
};

bool cmp_r(const Circle& a, const Circle& b) {
	return a.r < b.r;
}

ld segment_area(ld r, ld t) {
	return sq(r) * (t - sin(t)) / 2;
}

ld circle_union_area(vector<Circle> a) {
	sort(a.rbegin(), a.rend(), cmp_r);
	int ptr = 0;
	for (Circle& b : a) {
		if (sig(b.r) == 0) break;
		int j = 0;
		do {
			if (b.pos(a[j]) < 0 || sig((b.cen - a[j].cen).len()) == 0) {
				break;
			}
		} while (++j < ptr);
		if (j == ptr) a[ptr++] = b;
	}
	while (a.size() > ptr) a.ppp();
	ld res = 0;
	vector<Range> ran;
	for (int i=0; i<a.size(); i++) {
		ran.clear();
		Point lef = a[i].cen;
		lef.x -= a[i].r;
		int cnt = 0;
		ran.pb({-pi, 1, lef});
		ran.pb({pi, -1, lef});
		for (int j=0; j<a.size(); j++) {
			if (j == i || a[i].pos(a[j])) continue;
			Line l = a[i].inter(a[j]);
			ld L = (l.b - a[i].cen).ang();
			ld R = (l.a - a[i].cen).ang();
			if (sig(R - L) > 0) cnt++;
			ran.pb({R, 1, l.a});
			ran.pb({L, -1, l.b});
        }
		sort(ran.begin(), ran.end());
		ld phi = -pi;
		Point cur = lef;
		for (Range& b : ran) {
			cnt += b.evt;
			if ((cnt == 2 && b.evt > 0) || cnt == 0) {
				res += segment_area(a[i].r, b.t - phi) + (cur ^ b.p) / 2;
			}
			phi = b.t;
			cur = b.p;
		}
    }
    return res;
}

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
