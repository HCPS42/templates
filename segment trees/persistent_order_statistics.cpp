#include <bits/stdc++.h>
using namespace std;

// https://www.spoj.com/problems/MKTHNUM/

const int N = 1e5 + 5;
const int log_N = 20;
const int K = N * log_N;

struct seg_tree {
    int t[K];
    int lef[K];
    int rig[K];
    int root[N];
    int sz = 0;
    int rt = 0;
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
    void upd(int id, int x, int v, int l = 0, int r = N - 1) {
        if (l == r) {
            t[v] += x;
            return;
        }
        int m = (l + r) / 2;
        if (id <= m) upd(id, x, lef[v] = copy(lef[v]), l, m);
        else upd(id, x, rig[v] = copy(rig[v]), m + 1, r);
        t[v] = t[lef[v]] + t[rig[v]];
    }
    int get(int u, int v, int k, int l = 0, int r = N - 1) {
        if (l == r) return l;
        int m = (l + r) / 2;
        int cnt = t[lef[v]] - t[lef[u]];
        if (cnt >= k) return get(lef[u], lef[v], k, l, m);
        return get(rig[u], rig[v], k - cnt, m + 1, r);
    }
};

int a[N];
int inv[N];
seg_tree t;

void compress(int n) {
    vector<int> all;
    map<int, int> Map;
    for (int i = 1; i <= n; i++) {
        all.push_back(a[i]);
    }
    sort(all.begin(), all.end());
    all.erase(unique(all.begin(), all.end()), all.end());
    for (int i = 0; i < all.size(); i++) {
        Map[all[i]] = i;
        inv[i] = all[i];
    }
    for (int i = 1; i <= n; i++) {
        a[i] = Map[a[i]];
    }
}

int main() {
    int n, T;
    cin >> n >> T;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    compress(n);
    for (int i = 1; i <= n; i++) {
        t.upd(a[i], 1, t.make_root());
    }
    while (T--) {
        int l, r, k;
        cin >> l >> r >> k;
        int ans = t.get(t.root[l - 1], t.root[r], k);
        ans = inv[ans];
        cout << ans << "\n";
    }
    return 0;
}
