#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
const int L = ceil(log2(N)) + 2;

vector<int> g[N];
int sz[N];
int tin[N];
int tout[N];
int nxt[N];
int timer = 1;
int par[N];
int up[N][L];
// nxt[v] --- the highest vertex in the heavy path corresponding to v
// [tin[v]; tout[v]] --- subtree of v
// [tin[nxt[v]]; tin[v]] --- path from nxt[v] to v

void dfs_par(int v = 1, int p = 0) {
    par[v] = p;
    for (int u : g[v]) {
        if (u == p) continue;
        dfs_par(u, v);
    }
}

void dfs_sz(int v = 1) {
    sz[v] = 1;
    for (int& u : g[v]) {
        dfs_sz(u);
        sz[v] += sz[u];
        if (sz[u] > sz[g[v][0]]) {
            swap(u, g[v][0]);
        }
    }
}

void dfs_hld(int v = 1) {
    tin[v] = timer++;
    for (int u : g[v]) {
        nxt[u] = (u == g[v][0] ? nxt[v] : u);
        dfs_hld(u);
    }
    tout[v] = timer - 1;
}

void dfs_lca(int v = 1) {
    up[v][0] = par[v];
    for (int i = 1; i < L; i++) {
        up[v][i] = up[up[v][i - 1]][i - 1];
    }
    for (int u : g[v]) dfs_lca(u);
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

void init() {
    dfs_par();
    for (int i = 0; i < N; i++) {
        vector<int> cur;
        for (int u : g[i]) {
            if (u != par[i]) cur.push_back(u);
        }
        g[i] = cur;
    }
    dfs_sz();
    dfs_hld();
    dfs_lca();
}

int main() {
    // read
    init();
    return 0;
}
