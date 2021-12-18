#include "5_utils.h"

#include <bits/stdc++.h>
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

#define pli pair<Line<Int>, int>
#define pfi pair<frac, int>

con int N = 2e6 + 5;
Line<Int> kek = {{0, 0}, {N - 1, 0}};
con Int inf = 1e9;

frac f(Line<Int> a, frac x) {
    if (a[0] == kek[0] && a[1] == kek[1]) return inf;
    if (x < a[0].x) {
        return a[0].x - x;
    }
    if (x > a[1].x) {
        return x - a[1].x;
    }
    Line<frac> b({x, 0}, {x, 1});
    Line<frac> c({a[0].x, a[0].y}, {a[1].x, a[1].y});
    vec<Point<frac>> d = inter_line_line(b, c);
    return d[0].y;
}

pli t[4 * N];

void build() {
    for (int i = 0; i < 4 * N; i++) {
        t[i].fi = kek;
        t[i].se = 0;
    }
}

void add_line(pli nw, int v = 1, int l = 0, int r = N - 1) {
    int m = (l + r) / 2;
    bool lef = f(nw.fi, l) < f(t[v].fi, l);
    bool mid = f(nw.fi, m) < f(t[v].fi, m);
    if (mid) swap(t[v], nw);
    if (r - l == 1) return;
    if (lef != mid) add_line(nw, v + v, l, m);
    else add_line(nw, v + v + 1, m, r);
}

pfi get_min(frac x, int v = 1, int l = 0, int r = N - 1) {
    int m = (l + r) / 2;
    if (r - l == 1) return {f(t[v].fi, x), t[v].se};
    else if (x < m) return min({f(t[v].fi, x), t[v].se}, get_min(x, v + v, l, m));
    return min({f(t[v].fi, x), t[v].se}, get_min(x, v + v + 1, m, r));
}

bool cmp(Line<Int>& a, Line<Int>& b) {
    frac mx_a = max(a[0].y, a[1].y);
    frac mx_b = max(b[0].y, b[1].y);
    return mx_a > mx_b;
}

Line<Int> a[N];
Int dp[N];
vec<int> all;
vec<int> lol;
map<int, int> Map;
int inv[N];

void Solve() {
    freopen("input.txt", "r", stdin);
    build();
    int n;
    cin >> n;
    forn(i, 1, n) {
        cin >> a[i][0] >> a[i][1];
        all.pb(a[i][0].x);
        all.pb(a[i][1].x);
        a[i][0].y *= -1;
        a[i][1].y *= -1;
    }
    uniq(all);
    lol.pb(all[0] - 1);
    forn(i, 0, all.size() - 1) {
        lol.pb(all[i]);
        if (i == all.size() - 1) {
            lol.pb(N - 1);
        }
        else {
            if (all[i] + 1 < all[i + 1]) {
                lol.pb(all[i + 1] - 1);
            }
        }
    }
    forn(i, 0, lol.size() - 1) {
        Map[lol[i]] = i;
        inv[i] = lol[i];
    }
    forn(i, 1, n) {
        a[i][0].x = Map[a[i][0].x];
        a[i][1].x = Map[a[i][1].x];
    }
    sort(a + 1, a + n + 1, cmp);
    forn(i, 1, n) {
        Int x = a[i][0].x;
        if (a[i][1].y > a[i][0].y) {
            x = a[i][1].x;
        }
        auto lol = get_min(x);
        int id = lol.se;
        if (lol.fi >= 0) id = 0;
        if (!id) {
            dp[i] = x;
        }
        else {
            dp[i] = dp[id];
        }
        add_line({a[i], i});
    }
    int T;
    cin >> T;
    while (T--) {
        int x;
        cin >> x;
        auto it = lowb(lol.beg(), lol.end(), x);
        int X = x;
        if (it != lol.end())        x = Map[*it];
        else x = *lol.rbegin();
        auto lol = get_min(x);
        int id = lol.se;
        if (lol.fi >= 0) id = 0;
        Int ans = X;
        if (id) ans = inv[dp[id]];
        cout << ans << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif
    start_timer();
    Solve();
    return 0;
}
