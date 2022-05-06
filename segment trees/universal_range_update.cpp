#include <bits/stdc++.h>
using namespace std;

// seg_tree<int, EQ, SUM> https://codeforces.com/contest/1641/problem/C
// seg_tree<int, EQ, MIN> https://codeforces.com/contest/1641/problem/C
// seg_tree<ll, ADD_EQ, MIN> https://codeforces.com/contest/1110/problem/F
// seg_tree<int, ADD_EQ, MAX> https://codeforces.com/contest/1326/problem/E
// seg_tree<int, ADD_EQ, SUM> https://codeforces.com/contest/1326/problem/E
// seg_tree<int, ADD_EQ, SUM> https://codeforces.com/contest/1326/problem/E

const int N = 2e5 + 5;

enum Upd_pol { ADD_EQ, EQ };
enum Get_pol { SUM, MIN, MAX };

template <class T, Upd_pol upd_pol, Get_pol get_pol>
struct seg_tree {
    static const T inf = numeric_limits<T>::max() / 2;
    static const T ch_def = numeric_limits<T>::max();
    T t[4 * N];
    T ch[4 * N];
    void build(int v = 1, int l = 0, int r = N - 1) {
        t[v] = 0;
        if constexpr (upd_pol == ADD_EQ) {
            ch[v] = 0;
        }
        else if constexpr (upd_pol == EQ) {
            ch[v] = ch_def;
        }
        if (l == r) return;
        int m = (l + r) / 2;
        build(v + v, l, m);
        build(v + v + 1, m + 1, r);
    }
    T merge(T a, T b) {
        if constexpr (get_pol == SUM) {
            return a + b;
        }
        else if constexpr (get_pol == MIN) {
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
            if constexpr (get_pol == SUM) {
                t[v] += ch[v] * (r - l + 1);
            }
            else if constexpr (get_pol == MIN || get_pol == MAX) {
                t[v] += ch[v];
            }
        }
        else if constexpr (upd_pol == EQ) {
            if constexpr (get_pol == SUM) {
                t[v] = ch[v] * (r - l + 1);
            }
            else if constexpr (get_pol == MIN || get_pol == MAX) {
                t[v] = ch[v];
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
    T get(int L, int R, int v = 1, int l = 0, int r = N - 1) {
        push(v, l, r);
        if (R < l || r < L) {
            if constexpr (get_pol == SUM) {
                return 0;
            }
            else if constexpr (get_pol == MIN) {
                return inf;
            }
            else if constexpr (get_pol == MAX) {
                return -inf;
            }
        }
        if (L <= l && r <= R) return t[v];
        int m = (l + r) / 2;
        T res = merge(get(L, R, v + v, l, m), get(L, R, v + v + 1, m + 1, r));
        t[v] = merge(t[v + v], t[v + v + 1]);
        return res;
    }
};
