#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5;

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

template <class T, Pol pol>
struct LiChao {
    static const T inf = numeric_limits<T>::max();
    Line<T> t[4 * N];
    void build() {
        for (int i = 0; i < 4 * N; i++) {
            t[i] = {0, inf};
        }
    }
    LiChao() {
        build();
    }
    void _add(Line<T> line, int v = 1, int l = 0, int r = N) {
        int m = (l + r) / 2;
        bool L = line.eval(l) < t[v].eval(l);
        bool M = line.eval(m) < t[v].eval(m);
        if (M) {
            swap(t[v], line);
        }
        if (r - l == 1) return;
        if (L != M) {
            _add(line, v + v, l, m);
        }
        else {
            _add(line, v + v + 1, m, r);
        }
    }
    void add(Line<T> line) {
        if constexpr (pol == MAX) {
            line.a *= T(-1);
            line.b *= T(-1);
        }
        _add(line);
    }
    T _get(int x, int v = 1, int l = 0, int r = N) {
        int m = (l + r) / 2;
        if (r - l == 1) {
            return t[v].eval(x);
        }
        else if (x < m) {
            return min(t[v].eval(x), _get(x, v + v, l, m));
        }
        return min(t[v].eval(x), _get(x, v + v + 1, m, r));
    }
    T get(int x) {
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
    uniform_int_distribution<ll> x_distr(0, N - 1);
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
    for (int i = 1; i <= 500; i++) {
        auto d = gen();
        tree.build();
        assert(slow(d) == fast(d, tree));
    }
}

int main() {
    stress();
    return 0;
}
