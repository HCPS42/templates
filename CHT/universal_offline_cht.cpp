#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// CHT<ll, MIN, INC> https://atcoder.jp/contests/dp/tasks/dp_z
// CHT<ll, MIN, RND> https://atcoder.jp/contests/dp/tasks/dp_z
// CHT<ll, MAX, INC> https://atcoder.jp/contests/dp/tasks/dp_z
// CHT<ll, MAX, RND> https://atcoder.jp/contests/dp/tasks/dp_z

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
enum Ord { INC, RND }; // Order of queries

template <class T, Pol pol, Ord ord>
struct CHT {
    static const T inf = numeric_limits<T>::max();
    int ptr = 0;
    vector<Line<T>> ls;
    vector<Line<T>> h;
    void clear() {
        ptr = 0;
        ls.clear();
        h.clear();
    }
    void add(Line<T> l) {
        if constexpr (pol == MAX) {
            l.a *= T(-1);
            l.b *= T(-1);
        }
        ls.push_back(l);
    }
    bool is_bad(int i, int j, int k) {
        // intersection(h[i], h[k]).x < intersection(h[i], h[j]).x
        return (h[k].b - h[i].b) * (h[i].a - h[j].a) < (h[j].b - h[i].b) * (h[i].a - h[k].a);
    }
    void build() {
        sort(ls.begin(), ls.end());
        for (auto& l : ls) {
            if (!h.empty() && h.back().a == l.a) {
                continue;
            }
            h.push_back(l);
            int sz = h.size();
            while (sz >= 3 && is_bad(sz - 3, sz - 2, sz - 1)) {
                h.erase(h.end() - 2);
                sz--;
            }
        }
        ls.clear();
    }
    T get(T x) {
        if (h.empty()) {
            return inf;
        }
        T res = 0;
        if constexpr (ord == INC) {
            while (ptr + 1 < h.size() && h[ptr + 1].eval(x) < h[ptr].eval(x)) {
                ptr++;
            }
            res = h[ptr].eval(x);
        }
        else if constexpr (ord == RND) {
            int l = 0;
            int r = h.size() - 1;
            while (l < r) {
                int m = (l + r) / 2;
                if (h[m].eval(x) < h[m + 1].eval(x)) {
                    r = m;
                }
                else {
                    l = m + 1;
                }
            }
            res = h[l].eval(x);
        }
        if constexpr (pol == MAX) {
            res *= T(-1);
        }
        return res;
    }
};

int main() {
    return 0;
}
