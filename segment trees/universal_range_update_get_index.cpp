#include <bits/stdc++.h>
using namespace std;

// seg_tree<int, ADD_EQ, MAX> https://codeforces.com/contest/1615/problem/E

const int N = 2e5 + 5;

enum Upd_pol { ADD_EQ, EQ };
enum Get_pol { MIN, MAX };

template <class T, Upd_pol upd_pol, Get_pol get_pol>
struct seg_tree {
    static const T inf = numeric_limits<T>::max() / 2;
    static const T ch_def = numeric_limits<T>::max();
    pair<T, int> t[4 * N];
    T ch[4 * N];
    seg_tree() {
        build();
    }
    void build(int v = 1, int l = 0, int r = N - 1) {
        if constexpr (upd_pol == ADD_EQ) {
            ch[v] = 0;
        }
        else if constexpr (upd_pol == EQ) {
            ch[v] = ch_def;
        }
        if (l == r) {
            t[v] = {0, l};
            return;
        }
        int m = (l + r) / 2;
        build(v + v, l, m);
        build(v + v + 1, m + 1, r);
        if constexpr (get_pol == MIN) {
            t[v] = min(t[v + v], t[v + v + 1]);
        }
        else if constexpr (get_pol == MAX) {
            t[v] = max(t[v + v], t[v + v + 1]);
        }
    }
    pair<T, int> merge(pair<T, int> a, pair<T, int> b) {
        if constexpr (get_pol == MIN) {
            return min(a, b);
        }
        else if constexpr (get_pol == MAX) {
            return max(a, b);
        }
    }
    void push(int v, int l, int r) {
        if constexpr (upd_pol == ADD_EQ) {
            if (ch[v] == 0) return;
        }
        else if constexpr (upd_pol == EQ) {
            if (ch[v] == ch_def) return;
        }
        if constexpr (upd_pol == ADD_EQ) {
            if constexpr (get_pol == MIN || get_pol == MAX) {
                t[v].first += ch[v];
            }
        }
        else if constexpr (upd_pol == EQ) {
            if constexpr (get_pol == MIN || get_pol == MAX) {
                t[v].first = ch[v];
            }
        }
        if (l == r) {
            if constexpr (upd_pol == ADD_EQ) {
                ch[v] = 0;
            }
            else if constexpr (upd_pol == EQ) {
                ch[v] = ch_def;
            }
            return;
        }
        if constexpr (upd_pol == ADD_EQ) {
            ch[v + v] += ch[v];
            ch[v + v + 1] += ch[v];
            ch[v] = 0;
        }
        else if constexpr (upd_pol == EQ) {
            ch[v + v] = ch[v];
            ch[v + v + 1] = ch[v];
            ch[v] = ch_def;
        }
    }
    void upd(int L, int R, T x, int v = 1, int l = 0, int r = N - 1) {
        push(v, l, r);
        if (R < l || r < L) return;
        if (L <= l && r <= R) {
            if constexpr (upd_pol == ADD_EQ) {
                ch[v] += x;
            }
            else if constexpr (upd_pol == EQ) {
                ch[v] = x;
            }
            push(v, l, r);
            return;
        }
        int m = (l + r) / 2;
        upd(L, R, x, v + v, l, m);
        upd(L, R, x, v + v + 1, m + 1, r);
        t[v] = merge(t[v + v], t[v + v + 1]);
    }
    pair<T, int> get(int L, int R, int v = 1, int l = 0, int r = N - 1) {
        push(v, l, r);
        if (R < l || r < L) {
            if constexpr (get_pol == MIN) {
                return {inf, -1};
            }
            else if constexpr (get_pol == MAX) {
                return {-inf, -1};
            }
        }
        if (L <= l && r <= R) return t[v];
        int m = (l + r) / 2;
        pair<T, int> res = merge(get(L, R, v + v, l, m), get(L, R, v + v + 1, m + 1, r));
        t[v] = merge(t[v + v], t[v + v + 1]);
        return res;
    }
};

int main() {
    return 0;
}
