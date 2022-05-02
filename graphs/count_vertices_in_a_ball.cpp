#include <bits/stdc++.h>
using namespace std;

// Problem: https://codeforces.com/group/qcIqFPYhVr/contest/203881/problem/X
// Count the number of vertices at the distance of at most max_dist from given vertex v.

typedef long long ll;

const int N = 1e5 + 5;
const int inf = 1e9;
const int L = ceil(log2(N)) + 2;
 
vector<pair<int, ll>> g[N];
int tin[N];
int tout[N];
int up[N][L];
int timer = 1;
ll dep[N];
bool used[N];
int sz[N];
int msz[N];
vector<int> vis;
map<int, vector<ll>> sub[N];
vector<ll> Sub[N];
pair<int, int> par[N];
 
void dfs_lca(int v = 1, int p = 1) {
    tin[v] = timer++;
    up[v][0] = p;
    for (int i = 1; i < L; i++) {
        up[v][i] = up[up[v][i - 1]][i - 1];
    }
    for (auto [u, w] : g[v]) {
        if (u != p) {
            dep[u] = dep[v] + w;
            dfs_lca(u, v);
        }
    }
    tout[v] = timer - 1;
}
 
bool is_anc(int u, int v) {
    return tin[u] <= tin[v] && tin[v] <= tout[u];
}
 
int lca(int u, int v) {
    if (is_anc(u, v)) return u;
    if (is_anc(v, u)) return v;
    for (int i = L - 1; i >= 0; i--) {
        if (!is_anc(up[u][i], v)) u = up[u][i];
    }
    return up[u][0];
}
 
ll dis(int u, int v) {
    return dep[u] + dep[v] - 2 * dep[lca(u, v)];
}
 
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
 
void calc_sub(int v, int p, ll d, int cen, int kid) {
    sub[cen][kid].push_back(d);
    Sub[cen].push_back(d);
    for (auto [u, w] : g[v]) {
        if (u == p || used[u]) continue;
        calc_sub(u, v, d + w, cen, kid);
    }
}
 
void cen_dec() {
    dfs_lca();
    queue<int> q;
    q.push(get_cen(1));
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (auto [u, w] : g[v]) {
            if (!used[u]) {
                calc_sub(u, v, w, v, u);
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
 
int calc_vec(vector<ll>& a, ll d) {
    return upper_bound(a.begin(), a.end(), d) - a.begin();
}
 
int calc_ball(int s, ll mx) {
    int kid = 0;
    int v = s;
    int res = 0;
    while (v) {
        ll d = mx - dis(s, v);
        if (d >= 0) res++;
        res += calc_vec(Sub[v], d);
        res -= calc_vec(sub[v][kid], d);
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
    cen_dec();
    while (T--) {
        int v;
        ll max_dist;
        cin >> v >> max_dist;
        int ans = calc_ball(v, max_dist);
        cout << ans << "\n";
    }
    return 0;
}
