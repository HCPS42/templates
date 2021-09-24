#include <bits/stdc++.h>
using namespace std;

// https://www.spoj.com/problems/PSEGTREE/

typedef long long ll;

const int N = 1e5 + 5;
const int log_N = 20;
const int K = N * log_N;

struct seg_tree {
    ll a[N];
    ll t[K];
    int lef[K];
    int rig[K];
    int root[N];
    int sz = 0;
    int rt = 0;
    void build(int v = 0, int l = 0, int r = N - 1) {
        if (l == r) {
            t[v] = a[l];
            return;
        }
        int m = (l + r) / 2;
        lef[v] = ++sz;
        rig[v] = ++sz;
        build(lef[v], l, m);
        build(rig[v], m + 1, r);
        t[v] = t[lef[v]] + t[rig[v]];
    }
    int copy(int v) {
        sz++;
        lef[sz] = lef[v];
        rig[sz] = rig[v];
        t[sz] = t[v];
        return sz;
    }
    int make_root(int r = -1) {
        if (r == -1) r = rt;
        return root[++rt] = copy(root[r]);
    }
    void upd(int id, ll x, int v, int l = 0, int r = N - 1) {
        if (l == r) {
            t[v] += x;
            return;
        }
        int m = (l + r) / 2;
        if (id <= m) upd(id, x, lef[v] = copy(lef[v]), l, m);
        else upd(id, x, rig[v] = copy(rig[v]), m + 1, r);
        t[v] = t[lef[v]] + t[rig[v]];
    }
    ll get(int L, int R, int v, int l = 0, int r = N - 1) {
        if (R < l || r < L) return 0;
        if (L <= l && r <= R) return t[v];
        int m = (l + r) / 2;
        return get(L, R, lef[v], l, m) + get(L, R, rig[v], m + 1, r);
    }
};

seg_tree t;

int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> t.a[i];
    }
    t.build();
    int T;
    cin >> T;
    while (T--) {
        int tp;
        cin >> tp;
        if (tp == 1) {
            int prev, id;
            ll x;
            cin >> prev >> id >> x;
            t.upd(id, x, t.make_root(prev));
        }
        else {
            int ver, l, r;
            cin >> ver >> l >> r;
            ll ans = t.get(l, r, t.root[ver]);
            cout << ans << "\n";
        }
    }
    return 0;
}
