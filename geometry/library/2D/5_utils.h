#include "3_circle.h"
#include "4_line.h"

// https://official.contest.yandex.ru/contest/28976/problems/I/
// https://codeforces.com/group/EwxFGBAkWH/contest/205808/problem/B
template <class T>
vector<Point<Real>> inter_circle_circle(Circle<T> a, Circle<T> b) {
    static_assert(std::is_same<Real, T>());
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
    static_assert(std::is_same<Real, T>());
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

// new

template <class T>
Point<T> reflect_point_wrt_line(Point<T> p, Line<T> l) {
    Point<T> proj = proj_point_line(p, l);
    return proj * 2 - p;
}

template <class T>
bool is_on_seg(Point<T> p, Line<T> l) {
    return zero(dist(p, l[0]) + dist(p, l[1]) - dist(l[0], l[1]));
}

template <class T>
vector<Point<T>> inter_circle_seg(Circle<T> c, Line<T> l) {
    static_assert(std::is_same<Real, T>());
    vector<Point<T>> from_line = inter_circle_line(c, l);
    vector<Point<T>> res;
    for (auto p : from_line) {
        if (is_on_seg(p, l)) res.push_back(p);
    }
    return res;
}

template <class T>
vector<Point<T>> tangents_point_circle(Point<T> p, Circle<T> c) {
    static_assert(std::is_same<Real, T>());
    Real d = dist(p, c.center);
    if (is_less(d, c.r)) return {};
    if (is_eq(d, c.r)) return {p};
    Real from_cent = (p - c.center).angle();
    Real ang_dev = acos(c.r / d);
    return {c.rotate_rightmost(from_cent - ang_dev), c.rotate_rightmost(from_cent + ang_dev)};
}

template <class T>
vector<Line<T>> outer_tangents(Circle<T> c1, Circle<T> c2) {
    static_assert(std::is_same<Real, T>());
    if (c1 == c2) return {};
    if (c1.r < c2.r) swap(c1, c2);
    Real d = dist(c1.center, c2.center);
    if (is_less(c2.r + d, c1.r)) return {};
    if (is_eq(c1.r, c2.r)) {
        Point<T> diff = c2.center - c1.center;
        Point<T> R = diff.rotate(pi / 2) * (c1.r / diff.norm());
        return {{c1.center + R, c2.center + R}, {c1.center - R, c2.center - R}};
    }
    Point<T> I = c1.center + (c2.center - c1.center) * (c1.r / (c1.r - c2.r));
    if (is_eq(c2.r + d, c1.r)) {
        return {{I, I + (c2.center - c1.center).rotate(pi / 2)}};
    }
    vector<Point<T>> to1 = tangents_point_circle(I, c1);
    vector<Point<T>> to2 = tangents_point_circle(I, c2);
    vector<Line<T>> res{{to1[0], to2[0]}, {to1[1], to2[1]}};
    assert(is_on_line(I, res[0]));
    assert(is_on_line(I, res[1]));
    return res;
}

template <class T>
vector<Line<T>> inner_tangents(Circle<T> c1, Circle<T> c2) {
    static_assert(std::is_same<Real, T>());
    if (c1 == c2) return {};
    if (c1.r < c2.r) swap(c1, c2);
    Real d = dist(c1.center, c2.center);
    if (is_less(d, c1.r + c2.r)) return {};
    Point<T> I = c1.center + (c2.center - c1.center) * (c1.r / (c1.r + c2.r));
    if (is_eq(d, c1.r + c2.r)) {
        return {{I, I + (c2.center - c1.center).rotate(pi / 2)}};
    }
    vector<Point<T>> to1 = tangents_point_circle(I, c1);
    vector<Point<T>> to2 = tangents_point_circle(I, c2);
    vector<Line<T>> res{{to1[0], to2[0]}, {to1[1], to2[1]}};
    assert(is_on_line(I, res[0]));
    assert(is_on_line(I, res[1]));
    return res;
}

template <class T>
bool are_parallel(Line<T> l1, Line<T> l2) {
    return is_eq(cross(l1[0], l2[0], l1[1]), cross(l1[0], l2[1], l1[1]));
}

template <class T>
vector<Point<T>> inter_segs(Line<T> l1, Line<T> l2) {
    if (l1[0] >= l1[1]) swap(l1[0], l1[1]);
    if (l2[0] >= l2[1]) swap(l2[0], l2[1]); 
    if (are_parallel(l1, l2)) {
        if (!is_on_line(l2[0], l1)) return {};
        vector<Point<T>> ends(2);
        for (int i = 0; i < 2; i++) {
            if ((l1[i] < l2[i]) ^ i) {
                ends[i] = l2[i];
            } else {
                ends[i] = l1[i];
            }
        }
        if (ends[0] == ends[1]) {
            ends.pop_back();
        }
        if (ends.size() == 2 && (ends[1] < ends[0])) return {};
        return ends;
    }
    vector<Point<T>> p = inter_line_line(l1, l2);
    if (is_on_seg(p[0], l1) && is_on_seg(p[0], l2)) return p;
    return {};
}

template <class T>
Real calc_angle(Point<T> P, Point<T> Q, Point<T> R) { // angle PQR
    Real ang2 = (P - Q).angle();
    Real ang1 = (R - Q).angle();
    Real res = ang1 - ang2;
    if (res < eps) {
        res += 2 * pi;
    }
    return res;
}

template <class T>
Real disk_inter_area(Circle<T> c1, Circle<T> c2) {
    static_assert(std::is_same<Real, T>());
    if (c1.r < c2.r) swap(c1, c2);
    Real d = dist(c1.center, c2.center);
    if (c1.r + c2.r < d + eps) return 0;
    if (c1.r - c2.r > d - eps) return pi * sq(c2.r);
    Real alpha = acos((sq(d) + sq(c1.r) - sq(c2.r)) / (2 * d * c1.r));
    Real beta = acos((sq(d) + sq(c2.r) - Sq(c1.r)) / (2 * d * c2.r));
    return alpha * sq(c1.r) + beta * sq(c2.r) - sin(2 * alpha) * sq(c1.r) / 2 - sin(2 * beta) * sq(c2.r) / 2;
}

template <class T> 
Line<T> rad_axis(Circle<T> c1, Circle<T> c2) {
    static_assert(std::is_same<Real, T>());
    Real d = dist(c1.center, c2.center);
    Real a = (sq(c1.r) - sq(c2.r) + sq(d)) / (2 * d);
    Point<T> Q = c1.center + (c2.center - c1.center) * (a / d);
    Point<T> R = Q + (c2.center - c1.center).rotate(pi / 2);
    return {Q, R};
}
