#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
const int L = ceil(log2(N)) + 2;

vector<int> g[N];
int tin[N];
int tout[N];
int up[N][L];
int timer = 1;

void dfs_lca(int v = 1, int p = 1) {
    tin[v] = timer++;
    up[v][0] = p;
    for (int i = 1; i < L; i++) {
        up[v][i] = up[up[v][i - 1]][i - 1];
    }
    for (int u : g[v]) {
        if (u != p) dfs_lca(u, v);
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

int main() {
    // read
    dfs_lca();
    return 0;
}
