#include <iostream>
#include <iomanip>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <queue>
#include <deque>
#include <cmath>
#include <algorithm>
#include <cassert>
#include <chrono>
#include <random>
#include <string>
#include <numeric>
#include <complex>
#include <tuple>
#include <utility>
#include <bitset>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef string str;

#define pb push_back
#define ppp pop_back
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fi first
#define se second
#define stie std::tie
#define vec vector
#define forn(i, l, r) for (int i=l; i<=r; i++)
#define forb(i, r, l) for (int i=r; i>=l; i--)
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
#define ass assign
#define lowb lower_bound
#define uppb upper_bound

#if __SIZEOF_INT128__ >= 16
typedef __int128 LL;
istream& operator>>(istream& in, __int128& a) { int64_t b; in >> b; a = b; return in; }
ostream& operator<<(ostream& out, const __int128 a) {
    unsigned __int128 b = a < 0 ? -a : a; char buf[128]; char* c = end(buf); do { --c; *c = "0123456789"[b % 10]; b /= 10; } while (b);
    if (a < 0) { --c; *c = '-'; } int64_t len = end(buf) - c; out.rdbuf()->sputn(c, len); return out;
}
#endif
template <class T> void mini(T& a, T b) { a = min(a, b); }
template <class T> void maxi(T& a, T b) { a = max(a, b); }
template <class T> T gcd(T a, T b) { return b == 0 ? a : gcd(b, a % b); }
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
template <class T> void sort(vector<T>& a) { sort(a.begin(), a.end()); }
template <class T> void rever(vector<T>& a) { reverse(a.begin(), a.end()); }
template <class T> void uniq(vector<T>& a) { sort(a); a.erase(unique(a.begin(), a.end()), a.end()); }
template <class T> vector<T> set_int(vector<T> a, vector<T> b) { sort(a); sort(b); vector<T> res;
set_intersection(a.begin(), a.end(), b.begin(), b.end(), back_inserter(res)); return res; }
clock_t start_time; void start_timer() { start_time = clock(); }
double get_time() { return (double)(clock() - start_time) / CLOCKS_PER_SEC; }
template <class T> using min_pque = priority_queue<T, vector<T>, greater<T>>;

// solve the problem or die trying
// do something, stay focused
// look for stupid bugs
// guess, slow, stress
// the solution is always simple
// don't overgeneralize

void Solve() {
    
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
#ifdef LOCAL
    freopen("usr/share/man/man1/input.txt", "r", stdin);
#endif
    start_timer();
    Solve();
    return 0;
}
