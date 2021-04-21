#include <bits/stdc++.h>
#include "permutation.h"
#include "modular.h"
#include "rational.h"
#include "complex.h"
#include "polynomial.h"
#include "vector.h"
#include "matrix.h"
#include "SLE.h"
#include "linear_algebraic_algorithms.h"
#include "space.h"
#include "Jordan.h"
using namespace std;

typedef long long ll;
typedef long double ld;
typedef string str;

#define pb push_back
#define ppp pop_back
#define pii pair<int,int>
#define fi first
#define se second
#define stie std::tie
#define vec vector
#define	forn(i, l, r) for (int i=l; i<=r; i++)
#define emp empty
#define beg begin
#define ins insert
#define cle clear
#define era erase
#define que queue
#define pque priority_queue
#define mset multiset
#define deq deque
#define sta stack
#define con const
#define rsz resize
#define lowb lower_bound
#define uppb upper_bound

template<class T> void mini(T& a, T b) { a = min(a, b); }
template<class T> void maxi(T& a, T b) { a = max(a, b); }
template<class T1, class T2> ostream& operator<<(ostream &out, pair<T1, T2> a) { return out << a.first << " " << a.second; }
template<class T> ostream& operator<<(ostream& out, vector<T> a) { for (auto& i : a) out << i << " "; return out; }
template<class T> ostream& operator<<(ostream& out, set<T> a) { for (auto& i : a) out << i << " "; return out; }
template<class T> ostream& operator<<(ostream& out, multiset<T> a) { for (auto& i : a) out << i << " "; return out; }
template<class T1, class T2> ostream& operator<<(ostream& out, map<T1, T2> a) { for (auto& i : a) out << i << "\n"; return out; }
template<class T1, class T2> ostream& operator<<(ostream& out, unordered_map<T1, T2> a) { for (auto& i : a) out << i << "\n"; return out; }
template<class T> ostream& operator<<(ostream& out, queue<T> a) { while (!a.empty()) { out << a.front() << " "; a.pop(); } return out; }
template<class T> ostream& operator<<(ostream& out, deque<T> a) { while (!a.empty()) { out << a.front() << " "; a.pop_front(); } return out; }
template<class T> ostream& operator<<(ostream& out, priority_queue<T> a) { while (!a.empty()) { out << a.top() << "\n"; a.pop(); } return out; }
template<class T> void out(T a) { cout << a << endl; }
template<class T1, class T2> void out(T1 a, T2 b) { cout << a << " " << b << endl; }
template<class T1, class T2, class T3> void out(T1 a, T2 b, T3 c) { cout << a << " " << b << " " << c << endl; }
template<class T1, class T2, class T3, class T4> void out(T1 a, T2 b, T3 c, T4 d) { cout << a << " " << b << " " << c << " " << d << endl; }
template<class T> void out(vector<vector<T>> a) { for (vector<T> i : a) out(i); }
void out() { cout << "OK" << endl; }
template<class T> void sort(vector<T>& a) { sort(a.begin(), a.end()); }
template<class T> void uniq(vector<T>& a) { sort(a); a.erase(unique(a.begin(), a.end()), a.end()); }
template<class T> vector<T> set_int(vector<T> a, vector<T> b) { sort(a); sort(b); vector<T> res; set_intersection(a.begin(), a.end(), b.begin(), b.end(), back_inserter(res)); return res; }
clock_t start_time; double get_time() { return (double)(clock() - start_time) / CLOCKS_PER_SEC; }
#if __SIZEOF_INT128__ >= 16
typedef __int128 LL;
istream& operator>>(istream& in, __int128& a) { int64_t b; cin >> b; a = b; return in; }
ostream& operator<<(ostream& out, const __int128 a) {
	unsigned __int128 b = a < 0 ? -a : a; char buf[128]; char* c = end(buf); do { --c; *c = "0123456789"[b % 10]; b /= 10; } while (b);
	if (a < 0) { --c; *c = '-'; } int len = end(buf) - c; out.rdbuf()->sputn(c, len); return out;
}
#endif

template <class T>
T dot(Vec<T> a, Vec<T> b) {
    T res = 0;
    for (int i = 0; i < a.size(); i++) {
        res += a[i] * b[i];
    }
    return res;
}

/*
TODO:
1) write jordan from with templates
2) bilinear forms, diagonalization, change of basis
3) Gram-Schmidt
4) complement to orthogonal basis
5) add dot product to vector
*/

// hw 27

void task_2() {
    // Gram-Schmidt
    Vec<frac> v1({1, -2, 2, -3});
    Vec<frac> v2({2, -3, 2, 4});
    Space<frac> space;
    space.add(v1);
    space.add(v2);
    Space<frac> comp = space.complement();
    Vec<frac> v3 = comp.a[0];
    Vec<frac> v4 = comp.a[1];
    v3 -= dot(v1, v3) / dot(v1, v1) * v1 + dot(v2, v3) / dot(v2, v2) * v2;
    v4 -= dot(v1, v4) / dot(v1, v1) * v1 + dot(v2, v4) / dot(v2, v2) * v2 + dot(v3, v4) / dot(v4, v4) * v3;
    out(dot(v1, v3));
    out(dot(v2, v3));
    out(dot(v1, v4));
    out(dot(v2, v4));
    out(v3);
    out(v4);
}

/*
(  0 /  1)
(  0 /  1)
(  0 /  1)
(  0 /  1)
(( 163 / 198), ( 29 / 99), (-23 / 99), (- 5 / 66))
(( 1015 / 19602), ( 4109 / 9801), ( 4627 / 9801), ( 343 / 6534))
*/



void Solve() {
    task_2();



    Mat<frac> B({{
                         2, -1, 1
                 }, {
                         -1, 0, 0
                 }, {
                         1, 0, 3
                 }});
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
#ifdef LOCAL
	freopen("input.txt", "r", stdin);
#endif
	start_time = clock();
	Solve();
	return 0;
}
