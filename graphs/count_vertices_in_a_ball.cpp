#include <bits/stdc++.h>
using namespace std;

// Problem: https://codeforces.com/group/qcIqFPYhVr/contest/203881/problem/X
// Count the number of vertices at the distance of at most max_dist from given vertex v.

typedef long long ll;

const int N = 1e5 + 5;
const int inf = 1e9;

vector<pair<int, int>> g[N];
bool used[N];
int sz[N];
int msz[N];
vector<int> vis;
map<int, vector<ll>> sub[N];
vector<ll> Sub[N];
pair<int, int> par[N];
map<pair<int, int>, ll> dist;

void calc_sz(int v, int p = 0) {
    vis.push_back(v);
    sz[v] = 1;
    msz[v] = 0;
    for (auto [u, w] : g[v]) {
        if (u == p || used[u]) continue;
        calc_sz(u, v);
        sz[v] += sz[u];
        msz[v] = max(msz[v], sz[u]);
    }
}

int get_cen(int v) {
    vis.clear();
    calc_sz(v);
    int min_sz = inf;
    int cen = -1;
    for (int u : vis) {
        int size = max(msz[u], int(vis.size()) - sz[u]);
        if (min_sz > size) {
            min_sz = size;
            cen = u;
        }
    }
    used[cen] = 1;
    return cen;
}

void calc_dist(int v, int p, ll d, int cen, int kid) {
    sub[cen][kid].push_back(d);
    Sub[cen].push_back(d);
    dist[{v, cen}] = d;
    for (auto [u, w] : g[v]) {
        if (u == p || used[u]) continue;
        calc_dist(u, v, d + w, cen, kid);
    }
}

void centroid_decomposition() {
    queue<int> q;
    q.push(get_cen(1));
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (auto [u, w] : g[v]) {
            if (!used[u]) {
                calc_dist(u, v, w, v, u);
                sort(sub[v][u].begin(), sub[v][u].end());
            }
        }
        sort(Sub[v].begin(), Sub[v].end());
        for (auto [u, w] : g[v]) {
            if (!used[u]) {
                int new_cen = get_cen(u);
                par[new_cen] = {v, u};
                q.push(new_cen);
            }
        }
    }
}

int solve(int start, ll max_dist) {
    int kid = 0;
    int v = start;
    int res = 0;
    while (v) {
        ll d = max_dist - dist[{start, v}];
        if (d >= 0) res++;
        res += upper_bound(Sub[v].begin(), Sub[v].end(), d) - Sub[v].begin();
        res -= upper_bound(sub[v][kid].begin(), sub[v][kid].end(), d) - sub[v][kid].begin();
        kid = par[v].second;
        v = par[v].first;
    }
    return res;
}

int main() {
    int n, T;
    cin >> n >> T;
    for (int i = 1; i <= n - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }
    centroid_decomposition();
    while (T--) {
        int v;
        ll max_dist;
        cin >> v >> max_dist;
        int ans = solve(v, max_dist);
        cout << ans << "\n";
    }
    return 0;
}
