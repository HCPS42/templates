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
#include <array>
#include <stack>
#include <sstream>
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
#define oper operator
#define fri friend
#define tem template
#define temt tem <class T>
#define temtv temt void

temtv mini(T& a, T b) { a = min(a, b); }
temtv maxi(T& a, T b) { a = max(a, b); }
temt T gcd(T a, T b) { return b == 0 ? a : gcd(b, a % b); }
tem <class T1, class T2>
ostream& operator<<(ostream& os, pair<T1, T2> con& a) {
    return os << "[" << a.fi << ", " << a.se << "]";
}
tem <class Ch, class Tr, class Container>
basic_ostream<Ch, Tr>& operator<<(basic_ostream<Ch, Tr>& os, Container con& a) {
    os << "{ "; for (auto& i : a) os << i << " "; return os << "}";
}
temtv out(T a) { cout << a << endl; }
tem <class T, class... Args> void out(T a, Args... b) { cout << a << " "; out(b...); }
temtv out(vec<vec<T>> a) { for (vec<T> i : a) out(i); }
temtv out_(T a[], int l, int r) { forn(i, l, r) cout << a[i] << " "; cout << endl; }
void out() { cout << "OK" << endl; }
temtv sort(vec<T>& a) { sort(a.beg(), a.end()); }
temtv rever(vec<T>& a) { reverse(a.beg(), a.end()); }
temtv uniq(vec<T>& a) { sort(a); a.era(unique(a.beg(), a.end()), a.end()); }
clock_t start_time; void start_timer() { start_time = clock(); }
double get_time() { return (double)(clock() - start_time) / CLOCKS_PER_SEC; }
temt using min_pque = priority_queue<T, vec<T>, greater<T>>;

void Solve();

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
#ifdef LOCAL
    freopen("usr/share/man/man1/input.txt", "r", stdin);
#endif
    start_timer();
    Solve();
    return 0;
}

// do something, stay focused
// look for stupid bugs
// guess, slow, stress
// don't overgeneralize
// don't rush

// 1. Understand the problem
// 2. Devise a plan
// 3. Carry out the plan
// 4. Look back

// don't waste time on standings

// SOLVE THE PROBLEM OR DIE TRYING
// THE SOLUTION IS ALWAYS SIMPLE
// THE CODE IS ALWAYS SHORT

void Solve() {
    
}
