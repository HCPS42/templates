#include <bits/stdc++.h>
using namespace std;

// task: https://official.contest.yandex.com/mw2020prefinals/contest/18101/problems/G5b/

const int N = 1e5 + 5;
const int K = 50 * N;

struct Treap {
    int sz = 1;
    int L[K];
    int R[K];
    int cnt[K];
    int val[K];
    void clear() {
        sz = 1;
    }
    bool cmp(int u, int v) {
        return rand() * 1ll * (cnt[u] + cnt[v]) < cnt[u] * 1ll * RAND_MAX;
    }
    int make(int v) {
        L[sz] = R[sz] = 0;
        cnt[sz] = 1;
        val[sz] = v;
        return sz++;
    }
    int copy(int v) {
        if (!v) return 0;
        L[sz] = L[v];
        R[sz] = R[v];
        cnt[sz] = cnt[v];
        val[sz] = val[v];
        return sz++;
    }
    void push(int v) {
        cnt[v] = 1;
        if (L[v]) cnt[v] += cnt[L[v]];
        if (R[v]) cnt[v] += cnt[R[v]];
    }
    void merge(int& v, int l, int r) {
        if (!l || !r) {
            v = 0;
            if (l) v = copy(l);
            if (r) v = copy(r);
        }
        else if (cmp(l, r)) {
            v = copy(l);
            merge(R[v], R[l], r);
            push(v);
        }
        else {
            v = copy(r);
            merge(L[v], l, L[r]);
            push(v);
        }
    }
    void split(int v, int& l, int& r, int k) {
        if (!k) {
            l = 0;
            r = copy(v);
            return;
        }
        if (cnt[L[v]] >= k) {
            r = copy(v);
            split(L[v], l, L[r], k);
            push(r);
        }
        else {
            l = copy(v);
            split(R[v], R[l], r, k - cnt[L[v]] - 1);
            push(l);
        }
    }
    void build(vector<int>& a, int& v, int l, int r) {
        int m = (l + r) / 2;
        v = make(a[m]);
        if (l < m) build(a, L[v], l, m - 1);
        if (m < r) build(a, R[v], m + 1, r);
        push(v);
    }
    int build(vector<int>& a) {
        if (a.empty()) return 0;
        int v = 0;
        build(a, v, 0, a.size() - 1);
        return v;
    }
    void get(int v, vector<int>& a) {
        if (L[v]) get(L[v], a);
        a.push_back(val[v]);
        if (R[v]) get(R[v], a);
    }
    vector<int> get(int v) {
        vector<int> a;
        get(v, a);
        return a;
    }
    int rebuild(int v) {
        vector<int> a = get(v);
        clear();
        return build(a);
    }
};

int root[N];

Treap t;
int ver = 0;

struct Query {
    int cnt, from, to;
};

vector<Query> qs;
vector<int> b;

void Solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int cnt, from, to;
        cin >> cnt >> from >> to;
        qs.push_back({cnt, to, from});
    }
    reverse(qs.begin(), qs.end());
    for (int i = 1; i <= n; i++) b.push_back(i);
    root[++ver] = t.build(b);
    int kek = 0;
    for (auto q : qs) {
        kek++;
        if (kek % 1000 == 0) {
            int lol = t.rebuild(root[ver]);
            ver = 0;
            root[++ver] = lol;
        }
        int l, m, r;
        t.split(root[ver], l, m, q.from - 1);
        t.split(m, m, r, q.cnt);
        int M;
        t.split(root[ver], l, M, q.to - 1);
        t.split(M, M, r, q.cnt);
        t.merge(l, l, m);
        t.merge(root[++ver], l, r);
    }
    b = t.get(root[ver]);
    for (int i : b) {
        cout << i << " ";
    }
    cout << "\n";
}

int main() {
    Solve();
    return 0;
}
