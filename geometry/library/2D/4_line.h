#include "2_point.h"

template <class T>
struct Line {
    Point<T> p[2];
    bool is_seg;
    Line(Point<T> a = Point<T>(), Point<T> b = Point<T>(), bool is_seg = false) : is_seg(is_seg) { // remove default args
        p[0] = a; p[1] = b;
    }
    Point<T>& operator[](int i) { return p[i]; }
    Point<T> normal() { return (p[1] - p[0]).rotate(pi / 2); }
    vector<T> line_eq() {
        // (a, b) > (0, 0)
        T a = p[1].y - p[0].y;
        T b = p[0].x - p[1].x;
        T c = -(a * p[0].x + b * p[0].y);
        vector<T> res{a, b, c};
        if (is_neg(a) || (zero(a) && is_neg(b))) {
            for (auto& i : res) i *= -1;
        }
        return res;
    }
    vector<T> line_eq_norm();
};

template <>
vector<Int> Line<Int>::line_eq_norm() {
    // gcd(a, b, c) = 1
    vector<Int> res = line_eq();
    Int a = res[0], b = res[1], c = res[2];
    Int gcd = abs(__gcd(a, __gcd(b, c)));
    for (auto& i : res) i /= gcd;
    return res;
}

template <>
vector<Real> Line<Real>::line_eq_norm() {
    // a^2 + b^2 = 1
    vector<Real> res = line_eq();
    Real a = res[0], b = res[1], c = res[2];
    Real norm = sqrt(sq(a) + sq(b));
    for (auto& i : res) i /= norm;
    return res;
}
