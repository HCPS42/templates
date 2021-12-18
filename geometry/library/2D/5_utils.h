#include "3_circle.h"
#include "4_line.h"

// https://official.contest.yandex.ru/contest/28976/problems/I/
// https://codeforces.com/group/EwxFGBAkWH/contest/205808/problem/B
template <class T>
vector<Point<Real>> inter_circle_circle(Circle<T> a, Circle<T> b) {
    if (a == b) return vector<Point<Real>>(3);
    if (is_less(a.r, b.r)) swap(a, b);
    Point<T> dif = b.cen - a.cen;
    Real dis = dif.norm();
    Real ang = dif.angle();
    Real mx = max(Real(a.r), dis);
    Real tot = a.r + b.r + dis;
    if (is_more(2 * mx, tot)) return {};
    if (zero(2 * mx - tot)) return {a.rotate_rightmost(ang)};
    Real beta = acos((sq(a.r) + sq(dis) - sq(b.r)) / (2 * a.r * dis));
    return {a.rotate_rightmost(ang - beta), a.rotate_rightmost(ang + beta)};
}

template <class T>
Point<T> proj_point_line(Point<T> p, Line<T> l) {
    Point<T> d = l[1] - l[0];
    return l[0] + d * (dot(d, p - l[0]) / dot(d, d));
}

// https://official.contest.yandex.ru/contest/28976/problems/C/
template <class T>
vector<Point<Real>> inter_circle_line(Circle<T> c, Line<T> l) {
    Point<T> p = proj_point_line(c.cen, l);
    Real d = dist(c.cen, p);
    if (is_more(d, c.r)) return {};
    Real a = sqrt(max(Real(), sq(c.r) - sq(d)));
    Point<Real> b = l[1] - l[0];
    a /= b.norm();
    Point<Real> A = p + b * a;
    Point<Real> B = p - b * a;
    if (A == B) return {A};
    return {A, B};
}

template <class T>
bool is_on_line(Point<T> p, Line<T> l) {
    return zero(cross(l[0], l[1], p));
}

template <class T>
vector<Point<T>> inter_line_line(Line<T> a, Line<T> b) {
    Point<T> va = a[1] - a[0];
    Point<T> vb0 = b[0] - a[0];
    Point<T> vb1 = b[1] - a[0];
    T quad = cross(vb1, va) + cross(va, vb0);
    if (zero(quad)) {
        if (is_on_line(a[0], b)) {
            return {a[0], a[1]};
        }
        return {};
    }
    T tri = cross(vb1, vb0);
    return {a[0] + va * (tri / quad)};
}
