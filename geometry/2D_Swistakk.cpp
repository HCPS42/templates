#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define pb push_back
#define ppp pop_back
#define pii pair<int,int>
#define fi first
#define se second

typedef long double ld;

const ld kEps = 1e-10;
const ld kPi = 2 * acos(0);

ld Sq(ld x) {
	return x * x;
}

struct Point {
	ld x, y;
	Point() {}
	Point(ld a, ld b) : x(a), y(b) {}
	Point(const Point& a) : x(a.x), y(a.y) {}
	void operator=(const Point& a) { x = a.x; y = a.y; }
	Point operator+(const Point& a) const { Point p(x + a.x, y + a.y); return p; }
	Point operator-(const Point& a) const { Point p(x - a.x, y - a.y); return p; }
	Point operator*(ld a) const { Point p(x * a, y * a); return p; }
	Point operator/(ld a) const { assert(abs(a) > kEps); Point p(x / a, y / a); return p; }
	Point& operator+=(const Point& a) { x += a.x; y += a.y; return *this; }
	Point& operator-=(const Point& a) { x -= a.x; y -= a.y; return *this; }
	Point& operator*=(ld a) { x *= a; y *= a; return *this;}
	Point& operator/=(ld a) { assert(abs(a) > kEps); x /= a; y /= a; return *this; }

	bool IsZero() const {
		return abs(x) < kEps && abs(y) < kEps;
	}

	bool operator==(const Point& a) const {
		return (*this - a).IsZero();
	}

	ld CrossProd(const Point& a) const {
		return x * a.y - y * a.x;
	}

	ld CrossProd(Point a, Point b) const {
		a -= *this;
		b -= *this;
		return a.CrossProd(b);
	}

	ld DotProd(const Point& a) const {
		return x * a.x + y * a.y;
	}

	ld Norm() const {
		return sqrt(Sq(x) + Sq(y));
	}

	void NormalizeSelf() {
		*this /= Norm();
	}

	Point Normalize() {
		Point res(*this);
		res.NormalizeSelf();
		return res;
	}

	ld Dist(const Point& a) const {
		return (*this - a).Norm();
	}

	ld Angle() const {
		return atan2(y, x);
	}

	void RotateSelf(ld angle) {
		ld c = cos(angle);
		ld s = sin(angle);
		ld nx = x * c - y * s;
		ld ny = y * c + x * s;
		y = ny;
		x = nx;
	}

	Point Rotate(ld angle) const {
		Point res(*this);
		res.RotateSelf(angle);
		return res;
	}

	static bool LexCmp(const Point& a, const Point& b) {
		if (abs(a.x - b.x) > kEps) {
			return a.x < b.x;
		}
		return a.y < b.y;
	}

	ld SqNorm() {
		return x * x + y * y;
	}

	friend ostream& operator<<(ostream& out, Point m);
};

ostream& operator<<(ostream& out, Point p) {
  out << "(" << p.x << ", " << p.y << ")";
  return out;
}

struct Circle {
	Point center;
	ld r;

	Circle(ld x, ld y, ld rad) {
		center = Point(x, y);
		r = rad;
	}

	Circle(const Point& a, ld rad) : center(a), r(rad) {}
		ld Area() const {
		return kPi * Sq(r);
	}

	ld Perimeter() const {
		return 2 * kPi * r;
	}

	ld Diameter() const {
		return 2 * r;
	}

	Point RotateRightMost(ld ang) const {
		return center + Point{r * cos(ang), r * sin(ang)};
	}

	bool operator==(const Circle& c) const {
		return center == c.center && abs(r - c.r) < kEps;
	}
};

struct Line {
	Point p[2];
	bool is_seg;

	Line(Point a, Point b, bool is_seg_ = false) {
		p[0] = a;
		p[1] = b;
		is_seg = is_seg_;
	}

	Line() {}

	Point& operator[](int a) {
		return p[a];
	}

	Point NormalVector() {
		Point perp = p[1] - p[0];
		perp.RotateSelf(kPi / 2);
		perp.NormalizeSelf();
		return perp;
	}

	// (A, B, C) such that A^2 + B^2 = 1, (A, B) > (0, 0)
	vector<ld> LineEqNormLD() { // seems ok
		ld A = p[1].y - p[0].y;
		ld B = p[0].x - p[1].x;
		ld C = -(A * p[0].x + B * p[0].y);
		assert(abs(A * p[1].x + B * p[1].y + C) < kEps);
		ld norm = sqrt(Sq(A) + Sq(B));
		vector<ld> res{A, B, C};
		for (auto& x : res) { x /= norm; }
		if (A < -kEps || (abs(A) < kEps && B < -kEps)) {
			for (auto& x : res) { x *= -1; }
		}
		return res;
	}

	// assumes that coordinates are integers!
	vector<int> LineEqNormInt() { // seems ok
		int A = round(p[1].y - p[0].y);
		int B = round(p[0].x - p[1].x);
		int C = -(A * p[0].x + B * p[0].y);
		int gcd = abs(__gcd(A, __gcd(B, C)));
		vector<int> res{A, B, C};
		for (auto& x : res) { x /= gcd; }
		if (A < 0 || (A == 0 && B < 0)) {
			for (auto& x : res) { x *= -1; }
		}
		return res;
	}
};

struct Utils {
	// 0, 1, 2 or 3 pts. In case of 3 pts it means they are equal
	static vector<Point> InterCircleCircle(Circle a, Circle b) {
		if (a.r + kEps < b.r) {
			swap(a, b);
		}
		if (a == b) {
			return vector<Point>{a.RotateRightMost(0), a.RotateRightMost(2 * kPi / 3),
				a.RotateRightMost(4 * kPi / 3)};
		}
		Point diff = b.center - a.center;
		ld dis = diff.Norm();
		ld ang = diff.Angle();
		ld longest = max(max(a.r, b.r), dis);
		ld per = a.r + b.r + dis;
		if (2 * longest > per + kEps) {
			return vector<Point>();
		}
		if (abs(2 * longest - per) < 2 * kEps) {
			return vector<Point>{a.RotateRightMost(ang)};
		}
		ld ang_dev = acos((Sq(a.r) + Sq(dis) - Sq(b.r)) / (2 * a.r * dis));
		return vector<Point>{a.RotateRightMost(ang - ang_dev), a.RotateRightMost(ang + ang_dev)};
	}

	static vector<Point> InterLineLine(Line& a, Line& b) { // working fine
		Point vec_a = a[1] - a[0];
		Point vec_b1 = b[1] - a[0];
		Point vec_b0 = b[0] - a[0];
		ld tr_area = vec_b1.CrossProd(vec_b0);
		ld quad_area = vec_b1.CrossProd(vec_a) + vec_a.CrossProd(vec_b0);
		if (abs(quad_area) < kEps) { // parallel or coinciding
			if (PtBelongToLine(b, a[0])) {
				return {a[0], a[1]};
			} else {
				return {};
			}
		}
		return {a[0] + vec_a * (tr_area / quad_area)};
	}

	static Point ProjPointToLine(Point p, Line l) { ///Tested
		Point diff = l[1] - l[0];
		return l[0] + diff * (diff.DotProd(p - l[0]) / diff.DotProd(diff));
	}

	static Point ReflectPtWRTLine(Point p, Line l) {
		Point proj = ProjPointToLine(p, l);
		return proj * 2 - p;
	}

	static vector<Point> InterCircleLine(Circle c, Line l) { /// Tested here: http://c...content-available-to-author-only...s.com/gym/100554/submission/10197624
		Point proj = ProjPointToLine(c.center, l);
		ld dis_proj = c.center.Dist(proj);
		if (dis_proj > c.r + kEps) { return vector<Point>(); }
		ld a = sqrt(max((ld)0, Sq(c.r) - Sq(dis_proj)));
		Point dir = l[1] - l[0];
		ld dir_norm = dir.Norm();
		vector<Point> cands{proj + dir * (a / dir_norm), proj - dir * (a / dir_norm)};
		if (cands[0].Dist(cands[1]) < kEps) { return vector<Point>{proj}; }
		return cands;
	}

	static bool PtBelongToLine(Line l, Point p) {
		return abs(l[0].CrossProd(l[1], p)) < kEps;
	}

	static bool PtBelongToSeg(Line l, Point p) { // seems ok
		return abs(p.Dist(l[0]) + p.Dist(l[1]) - l[0].Dist(l[1])) < kEps;
	}

	static vector<Point> InterCircleSeg(Circle c, Line l) { //seems ok
		vector<Point> from_line = InterCircleLine(c, l);
		vector<Point> res;
		for (auto p : from_line) {
			if (PtBelongToSeg(l, p)) { res.pb(p); }
		}
		return res;
	}

	static vector<Point> TangencyPtsToCircle(Circle c, Point p) { // seems ok
		ld d = c.center.Dist(p);
		if (d < c.r - kEps) { return {}; }
		if (d < c.r + kEps) { return {p}; }
		ld from_cent = (p - c.center).Angle();
		ld ang_dev = acos(c.r / d);
		return {c.RotateRightMost(from_cent - ang_dev), c.RotateRightMost(from_cent + ang_dev)};
	}

	// outer and inner tangents tested only locally (however I believe that rigorously)
	static vector<Line> OuterTangents(Circle c1, Circle c2) {
		if (c1 == c2) { return {}; } // is it surely best choice?
		if (c1.r < c2.r) { swap(c1, c2); }
		if (c2.r + c1.center.Dist(c2.center) < c1.r - kEps) { return {}; }
		if (abs(c1.r - c2.r) < kEps) {
			Point diff = c2.center - c1.center;
			Point R = diff.Rotate(kPi / 2) * (c1.r / diff.Norm());
			return {{c1.center + R, c2.center + R}, {c1.center - R, c2.center - R}};
		}
		Point I = c1.center + (c2.center - c1.center) * (c1.r / (c1.r - c2.r));
		if (c2.r + c1.center.Dist(c2.center) < c1.r + kEps) {
			return {{I, I + (c2.center - c1.center).Rotate(kPi / 2)}};
		}
		vector<Point> to1 = TangencyPtsToCircle(c1, I);
		vector<Point> to2 = TangencyPtsToCircle(c2, I);
		vector<Line> res{{to1[0], to2[0]}, {to1[1], to2[1]}};
		assert(Utils::PtBelongToLine(res[0], I));
		assert(Utils::PtBelongToLine(res[1], I));
		return res;
	}

	// unfortunately big part of code is same as in previous function
	// can be joined when putting appropriate signs in few places
	// however those ifs differ a bit hence it may not be good idea
	// to necessarily join them
	static vector<Line> InnerTangents(Circle c1, Circle c2) {
		if (c1 == c2) { return {}; } // this time surely best choice
		if (c1.r < c2.r) { swap(c1, c2); }
		ld d = c1.center.Dist(c2.center);
		if (d < c1.r + c2.r - kEps) { return {}; }
		Point I = c1.center + (c2.center - c1.center) * (c1.r / (c1.r + c2.r));
		if (d < c1.r + c2.r + kEps) {
			return {{I, I + (c2.center - c1.center).Rotate(kPi / 2)}};
		}
		vector<Point> to1 = TangencyPtsToCircle(c1, I);
		vector<Point> to2 = TangencyPtsToCircle(c2, I);
		vector<Line> res{{to1[0], to2[0]}, {to1[1], to2[1]}};
		assert(Utils::PtBelongToLine(res[0], I));
		assert(Utils::PtBelongToLine(res[1], I));
		return res;
	}

	static bool AreParallel(Line l1, Line l2) { // seems ok
		return abs(l1[0].CrossProd(l2[0], l1[1]) - l1[0].CrossProd(l2[1], l1[1])) < kEps;
	}

	// returns a vector of points such that their convex hull is intersection of those segments
	// SZ(res) == 0 => empty intersection, SZ(res) == 1 => intersection is a point, SZ(res) == 2 => intersection is a segment
	static vector<Point> InterSegs(Line l1, Line l2) { // seems ok
		if (!Point::LexCmp(l1[0], l1[1])) { swap(l1[0], l1[1]); }
		if (!Point::LexCmp(l2[0], l2[1])) { swap(l2[0], l2[1]); }
		if (AreParallel(l1, l2)) {
			if (!PtBelongToLine(l1, l2[0])) { return vector<Point>(); }
			vector<Point> ends(2);
			for (int tr = 0; tr < 2; tr++) {
				if (Point::LexCmp(l1[tr], l2[tr]) ^ tr) {
					ends[tr] = l2[tr];
				} else {
					ends[tr] = l1[tr];
				}
			}
			if ((ends[1] - ends[0]).IsZero()) {
				ends.pop_back();
			}
			if (ends.size() == 2 && Point::LexCmp(ends[1], ends[0])) { return vector<Point>(); }
			return ends;
		} else {
			vector<Point> p = InterLineLine(l1, l2);
			if (PtBelongToSeg(l1, p[0]) && PtBelongToSeg(l2, p[0])) { return p; }
			return vector<Point>();
		}
	}

	static ld Angle(Point P, Point Q, Point R) { // angle PQR
		ld ang2 = (P - Q).Angle();
		ld ang1 = (R - Q).Angle();
		ld ans = ang1 - ang2;
		if (ans < kEps) {
			ans += 2 * kPi;
		}
		return ans;
	}

	// tested here: http://c...content-available-to-author-only...s.com/contest/600/submission/14961583
	// DON'T change anything as this will lead to precision errors
	// don't know why, but this is the only version which works precisely even for very mean cases
	static ld DiskInterArea(Circle c1, Circle c2) { // tested here: http://o...content-available-to-author-only...s.info/~ejudge/team.cgi?contest_id=006254 problem I
		if (c1.r < c2.r) {
			swap(c1, c2);
		}
		ld d = c1.center.Dist(c2.center);
		if (c1.r + c2.r < d + kEps) {
			return 0;
		}
		if (c1.r - c2.r > d - kEps) {
			return kPi * Sq(c2.r);
		}
		ld alpha = acos((Sq(d) + Sq(c1.r) - Sq(c2.r)) / (2 * d * c1.r));
		ld beta = acos((Sq(d) + Sq(c2.r) - Sq(c1.r)) / (2 * d * c2.r));
		return alpha * Sq(c1.r) + beta * Sq(c2.r) - sin(2 * alpha) * Sq(c1.r) / 2 - sin(2 * beta) * Sq(c2.r) / 2;
	}

	static Line RadAxis(Circle c1, Circle c2) {
		ld d = c1.center.Dist(c2.center);
		ld a = (Sq(c1.r) - Sq(c2.r) + Sq(d)) / (2 * d);
		Point Q = c1.center + (c2.center - c1.center) * (a / d);
		Point R = Q + (c2.center - c1.center).Rotate(kPi / 2);
		return Line(Q, R);
	}
};

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
