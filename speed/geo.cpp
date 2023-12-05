#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define con const
#define oper operator
#define fri friend

typedef long double R;

con R eps = 1e-10;
con R pi = acos(-1);

struct F {
    ll x = 0; ll y = 1;
    void norm() {
        if (!y) { x = 1; return; }
        if (y < 0) { x *= -1; y *= -1; }
        ll d = __gcd(x, y);
        if (d < 0) d *= -1;
        x /= d; y /= d;
    }
    F(ll x = 0, ll y = 1) : x(x), y(y) { norm(); }
    fri ostream& oper<<(ostream& out, F a) {
        return out << "(" << a.x << " / " << a.y << ")";
    }
    explicit oper long double() con {
        return (long double) x / y;
    }
    F oper-() con { return {-x, y}; }
    F& oper+=(con F& a) {
        x = x * a.y + a.x * y; y *= a.y;
        norm(); return *this;
    }
    F& oper-=(con F& a) {
        x = x * a.y - a.x * y; y *= a.y;
        norm(); return *this;
    }
    F& oper*=(con F& a) {
        x *= a.x; y *= a.y;
        norm(); return *this;
    }
    F& oper/=(con F& a) {
        x *= a.y; y *= a.x;
        norm(); return *this;
    }
    fri F oper+(F a, con F& b) { return a += b; }
    fri F oper-(F a, con F& b) { return a -= b; }
    fri F oper*(F a, con F& b) { return a *= b; }
    fri F oper/(F a, con F& b) { return a /= b; }
    fri bool oper==(con F& a, con F& b) {
        return a.x == b.x && a.y == b.y;
    }
    fri bool oper<(con F& a, con F& b) {
        return a.x * b.y < a.y * b.x;
    }
    fri F abs(F a) {
        if (a.x < 0) a.x *= -1;
        return a;
    }
};

template <class T> T sq(con T& a) { return a * a; }
template <class T>
bool zero(con T& a) {
    if constexpr (std::is_same<R, T>()) { return abs(a) < eps; }
    else return a == 0;
}
template <class T> bool is_eq(con T& a, con T& b) { return zero(a - b); }
template <class T>
bool is_less(con T& a, con T& b) {
    if constexpr (std::is_same<R, T>()) { return a - b <= -eps; }
    else return a < b;
}
template <class T>
bool is_pos(con T& a) { return is_less(T(0), a); }
template <class T>
bool is_neg(con T& a) { return is_less(a, T(0)); }

template <class T>
struct P {
    T x = 0; T y = 0;
    P() = default;
    P(T x, T y) : x(x), y(y) {}
    fri ostream& oper<<(ostream& out, P& a) {
        return out << a.x << " " << a.y;
    }
    P oper-() con { return {-x, -y}; }
       fri P oper+(P a, con P& b) {
        a.x += b.x; a.y += b.y; return a;
    }
    fri P oper-(P a, con P& b) {
        a.x -= b.x; a.y -= b.y; return a;
    }
    fri P oper*(con T& a, P b) {
        b.x *= a; b.y *= a; return b;
    }
    fri P oper/(P a, con T& b) {
        a.x /= b; a.y /= b; return a;
    }
    bool is_zero() con { return zero(x) && zero(y); }
    bool oper==(con P& a) con { return (*this - a).is_zero(); }
    fri bool oper<(con P& a, con P& b) {
        if (!is_eq(a.x, b.x)) return a.x < b.x; return a.y < b.y;
    }
    fri T dot(con P& a, con P& b) { return a.x * b.x + a.y * b.y; }
    //fri T dot(con P& a, con P& b, con P& c) { return dot(b - a, c - a); }
    fri T cro(con P& a, con P& b) { return a.x * b.y - a.y * b.x; }
    fri T cro (con P& a, con P& b, con P& c) { return cro(b - a, c - a); }
    //T norm2() con { return sq(x) + sq(y); }
    R norm() con { return sqrt(R(sq(x) + sq(y))); }
    //fri T dist2(con P& a, con P& b) { return (a - b).norm2(); }
    fri R dist(con P& a, con P& b) { return (a - b).norm(); }
    R angle() { return atan2(R(y), R(x)); }
    void rotate_self(R ang) {
        if constexpr (std::is_same<ll, T>()) {
            R c = cos(ang); R s = sin(ang);
            R nx = c * x - s * y; R ny = s * x + c * y;
            x = round(nx); y = round(ny);
        }
        else if constexpr (std::is_same<R, T>()) {
            R c = cos(ang); R s = sin(ang);
            R nx = c * x - s * y; R ny = s * x + c * y;
            x = nx; y = ny;
        }
        else {
            assert(0);
        }
    }
    P rotate(R ang) con {
        P<T> a(*this);
        a.rotate_self(ang);
        return a;
    }
};

template <class T>
R calc_angle(P<T> A, P<T> B, P<T> C) { // angle ABC
    R ang2 = (A - B).angle();
    R ang1 = (C - B).angle();
    R res = ang1 - ang2;
    if (res < eps) {
        res += 2 * pi;
    }
    return res;
}

template <class T>
struct Line {
    P<T> p[2];
    bool is_seg;
    Line(P<T> a, P<T> b, bool is_seg = false) : is_seg(is_seg) {
        p[0] = a; p[1] = b;
    }
    P<T>& oper[](int i) { return p[i]; }
    con P<T>& oper[](int i) con { return p[i]; }
    P<T> normal() {
        P<T> a = p[1] - p[0];
        return {-a.y, a.x};
    }
    vector<T> line_eq() {
        // (a, b) > (0, 0)
        T a = p[1].y - p[0].y;
        T b = p[0].x - p[1].x;
        T c = -(a * p[0].x + b * p[0].y);
        vector<T> res{a, b, c};
        if (is_less(a, T(0)) || (zero(a) && is_less(b, T(0)))) {
            for (auto& i : res) i *= -1;
        }
        return res;
    }
    vector<T> line_eq_norm();
};

template <>
vector<ll> Line<ll>::line_eq_norm() {
    // gcd(a, b, c) = 1
    vector<ll> res = line_eq();
    ll a = res[0], b = res[1], c = res[2];
    ll gcd = abs(__gcd(c, __gcd(a, b)));
    for (auto& i : res) i /= gcd;
    return res;
}

template <>
vector<R> Line<R>::line_eq_norm() {
    // a^2 + b^2 = 1
    vector<R> res = line_eq();
    R a = res[0], b = res[1], c = res[2];
    R norm = sqrt(sq(a) + sq(b));
    for (auto& i : res) i /= norm;
    return res;
}

template <class T>
P<T> proj_point_line(P<T> p, Line<T> l) {
    P<T> d = l[1] - l[0];
    return l[0] + d * (dot(d, p - l[0]) / dot(d, d));
}

template <class T>
bool is_on_line(P<T> p, Line<T> l) {
    return zero(cro(l[0], l[1], p));
}

template <class T>
vector<P<T>> inter_line_line(Line<T> a, Line<T> b) {
    P<T> va = a[1] - a[0];
    P<T> vb0 = b[0] - a[0];
    P<T> vb1 = b[1] - a[0];
    T quad = cro(vb1, va) + cro(va, vb0);
    if (zero(quad)) {
        if (is_on_line(a[0], b)) {
            return {a[0], a[1]};
        }
        return {};
    }
    T tri = cro(vb1, vb0);
    return {a[0] + (tri / quad) * va};
}

template <class T>
P<T> reflect_point_wrt_line(P<T> p, Line<T> l) {
    P<T> proj = proj_point_line(p, l);
    return proj * 2 - p;
}

template <class T>
bool is_on_seg(P<T> p, Line<T> l) {
    return zero(dist(p, l[0]) + dist(p, l[1]) - dist(l[0], l[1]));
}

template <class T>
bool are_parallel(Line<T> a, Line<T> b) {
    return is_eq(cro(a[0], b[0], a[1]), cro(a[0], b[1], a[1]));
}

template <class T>
vector<P<T>> inter_segs(Line<T> a, Line<T> b) {
    if (!(a[0] < a[1])) swap(a[0], a[1]);
    if (!(b[0] < b[1])) swap(b[0], b[1]);
    if (are_parallel(a, b)) {
        if (!is_on_line(b[0], a)) return {};
        vector<P<T>> res(2);
        for (int i = 0; i < 2; i++) {
            if ((a[i] < b[i]) ^ i) {
                res[i] = b[i];
            } else {
                res[i] = a[i];
            }
        }
        if (res[0] == res[1]) {
            res.pop_back();
        }
        if (res.size() == 2 && (res[1] < res[0])) return {};
        return res;
    }
    vector<P<T>> p = inter_line_line(a, b);
    if (is_on_seg(p[0], a) && is_on_seg(p[0], b)) return p;
    return {};
}

template <class T>
struct Circle {
    P<T> cen;
    T r = 0;
    Circle() = default;
    Circle(T x, T y, T r) : cen(x, y), r(r) {}
    Circle(P<T> cen, T r) : cen(cen), r(r) {}
    fri istream& oper>>(istream& in, Circle& a) { return in >> a.cen >> a.r; }
    fri ostream& oper<<(ostream& out, Circle& a) { return out << a.cen << " " << a.r; }
    R area() con { return pi * sq(r); }
    R perimeter() con { return 2 * pi * r; }
    T diameter() con { return 2 * r; }
    P<R> rotate_rightmost(R angle) {
        return P<R>(cen.x, cen.y) + P<R>(r * cos(angle), r * sin(angle));
    }
    fri bool oper==(con Circle& a, con Circle& b) {
        return a.cen == b.cen && is_eq(a.r, b.r);
    }
};

template <class T>
vector<P<R>> inter_circle_line(Circle<T> c, Line<T> l) {
    static_assert(std::is_same<R, T>());
    P<T> p = proj_point_line(c.cen, l);
    R d = dist(c.cen, p);
    if (is_less(c.r, d)) return {};
    R a = sqrt(max(R(), sq(c.r) - sq(d)));
    P<R> b = l[1] - l[0];
    a /= b.norm();
    P<R> A = p + a * b;
    P<R> B = p - a * b;
    if (A == B) return {A};
    return {A, B};
}

template <class T>
vector<P<T>> inter_circle_seg(Circle<T> c, Line<T> l) {
    static_assert(std::is_same<R, T>());
    vector<P<T>> from_line = inter_circle_line(c, l);
    vector<P<T>> res;
    for (auto p : from_line) {
        if (is_on_seg(p, l)) res.push_back(p);
    }
    return res;
}

template <class T>
vector<P<R>> inter_circle_circle(Circle<T> a, Circle<T> b) {
    static_assert(std::is_same<R, T>());
    if (a == b) return vector<P<R>>(3);
    if (is_less(a.r, b.r)) swap(a, b);
    P<T> dif = b.cen - a.cen;
    R dis = dif.norm();
    R ang = dif.angle();
    R mx = max(R(a.r), dis);
    R tot = a.r + b.r + dis;
    if (is_less(tot, 2 * mx)) return {};
    if (zero(2 * mx - tot)) return {a.rotate_rightmost(ang)};
    R beta = acos((sq(a.r) + sq(dis) - sq(b.r)) / (2 * a.r * dis));
    return {a.rotate_rightmost(ang - beta), a.rotate_rightmost(ang + beta)};
}

template <class T>
vector<P<T>> tangents_point_circle(P<T> p, Circle<T> c) {
    static_assert(std::is_same<R, T>());
    R d = dist(p, c.center);
    if (is_less(d, c.r)) return {};
    if (is_eq(d, c.r)) return {p};
    R from_cent = (p - c.center).angle();
    R ang_dev = acos(c.r / d);
    return {c.rotate_rightmost(from_cent - ang_dev), c.rotate_rightmost(from_cent + ang_dev)};
}

template <class T>
vector<Line<T>> outer_tangents(Circle<T> c1, Circle<T> c2) {
    static_assert(std::is_same<R, T>());
    if (c1 == c2) return {};
    if (c1.r < c2.r) swap(c1, c2);
    R d = dist(c1.center, c2.center);
    if (is_less(c2.r + d, c1.r)) return {};
    if (is_eq(c1.r, c2.r)) {
        P<T> diff = c2.center - c1.center;
        P<T> rad = diff.rotate(pi / 2) * (c1.r / diff.norm());
        return {{c1.center + rad, c2.center + rad}, {c1.center - rad, c2.center - rad}};
    }
    P<T> I = c1.center + (c2.center - c1.center) * (c1.r / (c1.r - c2.r));
    if (is_eq(c2.r + d, c1.r)) {
        return {{I, I + (c2.center - c1.center).rotate(pi / 2)}};
    }
    vector<P<T>> to1 = tangents_point_circle(I, c1);
    vector<P<T>> to2 = tangents_point_circle(I, c2);
    vector<Line<T>> res{{to1[0], to2[0]}, {to1[1], to2[1]}};
    assert(is_on_line(I, res[0]));
    assert(is_on_line(I, res[1]));
    return res;
}

template <class T>
vector<Line<T>> inner_tangents(Circle<T> c1, Circle<T> c2) {
    static_assert(std::is_same<R, T>());
    if (c1 == c2) return {};
    if (c1.r < c2.r) swap(c1, c2);
    R d = dist(c1.center, c2.center);
    if (is_less(d, c1.r + c2.r)) return {};
    P<T> I = c1.center + (c2.center - c1.center) * (c1.r / (c1.r + c2.r));
    if (is_eq(d, c1.r + c2.r)) {
        return {{I, I + (c2.center - c1.center).rotate(pi / 2)}};
    }
    vector<P<T>> to1 = tangents_point_circle(I, c1);
    vector<P<T>> to2 = tangents_point_circle(I, c2);
    vector<Line<T>> res{{to1[0], to2[0]}, {to1[1], to2[1]}};
    assert(is_on_line(I, res[0]));
    assert(is_on_line(I, res[1]));
    return res;
}

template <class T>
R disk_inter_area(Circle<T> c1, Circle<T> c2) {
    static_assert(std::is_same<R, T>());
    if (c1.r < c2.r) swap(c1, c2);
    R d = dist(c1.center, c2.center);
    if (c1.r + c2.r < d + eps) return 0;
    if (c1.r - c2.r > d - eps) return pi * sq(c2.r);
    R alpha = acos((sq(d) + sq(c1.r) - sq(c2.r)) / (2 * d * c1.r));
    R beta = acos((sq(d) + sq(c2.r) - Sq(c1.r)) / (2 * d * c2.r));
    return alpha * sq(c1.r) + beta * sq(c2.r) - sin(2 * alpha) * sq(c1.r) / 2 - sin(2 * beta) * sq(c2.r) / 2;
}

template <class T> 
Line<T> rad_axis(Circle<T> c1, Circle<T> c2) {
    static_assert(std::is_same<R, T>());
    R d = dist(c1.center, c2.center);
    R a = (sq(c1.r) - sq(c2.r) + sq(d)) / (2 * d);
    P<T> B = c1.center + (c2.center - c1.center) * (a / d);
    P<T> C = B + (c2.center - c1.center).rotate(pi / 2);
    return {B, C};
}

int main() {
    return 0;
}
