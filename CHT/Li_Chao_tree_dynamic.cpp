#include <bits/stdc++.h>
using namespace std;

template <class T>
struct Line {
    T a;
    T b;
    T eval(T x) const {
        return a * x + b;
    }
    friend bool operator<(const Line& l, const Line& r) {
        return std::tie(r.a, l.b) < std::tie(l.a, r.b);
    }
};

enum Pol { MIN, MAX }; // Get policy

template <class T, Pol pol, T abs_max = 1'000'000'000> // |line.a|, |line.b| <= abs_max
struct LiChao {
    static const T inf = numeric_limits<T>::max();
    static const T kLef = numeric_limits<T>::min() / abs_max + 1;
    static const T kRig = numeric_limits<T>::max() / abs_max - 1;
    vector<Line<T>> t;
    vector<int> lef_kid;
    vector<int> rig_kid;
    void build() {
        t.assign(1, {0, inf});
        lef_kid.assign(1, 0);
        rig_kid.assign(1, 0);
    }
    LiChao() {
        build();
    }
    int add_ver() {
        t.push_back({0, inf});
        lef_kid.push_back(0);
        rig_kid.push_back(0);
        return t.size() - 1;
    }
    int lef(int v) {
        if (lef_kid[v] == 0) {
            lef_kid[v] = add_ver();
        }
        return lef_kid[v];
    }
    int rig(int v) {
        if (rig_kid[v] == 0) {
            rig_kid[v] = add_ver();
        }
        return rig_kid[v];
    }
    void _add(Line<T> line, int v = 0, T l = kLef, T r = kRig) { // [l, r)
        T m = l + r;
        if (m < T(0) && m % T(2) == T(1)) {
            m--;
        }
        m /= T(2);
        bool L = line.eval(l) < t[v].eval(l);
        bool M = line.eval(m) < t[v].eval(m);
        if (M) {
            swap(t[v], line);
        }
        if (r - l == 1) return;
        if (L != M) {
            _add(line, lef(v), l, m);
        }
        else {
            _add(line, rig(v), m, r);
        }
    }
    void add(Line<T> line) {
        if constexpr (pol == MAX) {
            line.a *= T(-1);
            line.b *= T(-1);
        }
        _add(line);
    }
    T _get(T x, int v = 0, T l = kLef, T r = kRig) { // [l, r)
        T m = l + r;
        if (m < T(0) && m % T(2) == T(1)) {
            m--;
        }
        m /= T(2);
        if (r - l == 1) {
            return t[v].eval(x);
        }
        else if (x < m) {
            return min(t[v].eval(x), _get(x, lef(v), l, m));
        }
        return min(t[v].eval(x), _get(x, rig(v), m, r));
    }
    T get(T x) {
        T res = _get(x);
        if constexpr (pol == MAX) {
            res *= T(-1);
        }
        return res;
    }
};

// STRESS

typedef long long ll;

struct Data {
    vector<Line<ll>> lines;
    vector<ll> xs;
};

mt19937 rnd;

Data gen() {
    const ll MAX = 1e9;
    uniform_int_distribution<ll> distr(-MAX, MAX);
    Data res;
    int n = rnd() % 100;
    for (int i = 0; i < n; i++) {
        res.lines.push_back({distr(rnd), distr(rnd)});
    }
    int m = rnd() % 100;
    uniform_int_distribution<ll> x_distr(-MAX, MAX);
    for (int i = 0; i < m; i++) {
        res.xs.push_back(x_distr(rnd));
    }
    return res;
}

vector<ll> slow(Data d) {
    vector<ll> res;
    for (ll x : d.xs) {
        ll mn = numeric_limits<ll>::max();
        for (auto& l : d.lines) {
            mn = min(mn, l.eval(x));
        }
        res.push_back(mn);
    }
    return res;
}

template <Pol pol>
vector<ll> fast(Data d, LiChao<ll, pol> tree) {
    vector<ll> res;
    for (auto& l : d.lines) {
        tree.add(l);
    }
    for (ll x : d.xs) {
        res.push_back(tree.get(x));
    }
    return res;
}

void stress() {
    LiChao<ll, MIN> tree;
    for (int i = 1; i <= 10'000; i++) {
        auto d = gen();
        tree.build();
        auto slow_res = slow(d);
        auto fast_res = fast(d, tree);
        assert(slow(d) == fast(d, tree));
    }
}

int main() {
    stress();
    return 0;
}
