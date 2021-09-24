#include <bits/stdc++.h>
#include "point.h"

using namespace std;

template <class T1, class T2>
ostream& operator<<(ostream& os, pair<T1, T2> const& a) { return os << "[" << a.first << ", " << a.second << "]"; }
template <class Ch, class Tr, class Container>
basic_ostream<Ch, Tr>& operator<<(basic_ostream<Ch, Tr>& os, Container const& a) { os << "{ "; for (auto& i : a) os << i << " "; return os << "}"; }
template <class T> void out(T a) { cout << a << endl; }
template <class T, class... Args> void out(T a, Args... args) { cout << a << " "; out(args...); }
template <class T> void out(std::initializer_list<T> a) { for (auto i : a) { cout << i << " "; } cout << endl; }
template <class T> void out(vector<vector<T>> a) { for (vector<T> i : a) out(i); }
template <class T> void out_(T a[], int l, int r) { for (int i = l; i <= r; i++) cout << a[i] << " "; cout << endl; }
void out() { cout << "OK" << endl; }

int main() {
    Point<Int> a(1, 0);
    cout << a.is_zero() << endl;
    Point<Int> b(1, 0);
    cout << (a == b) << endl;
    out(zero(frac(1, 1)));
    Point<Real> c(1, 1);
    out(c.norm());
    c.normalize();
    out(c);

    return 0;
}
