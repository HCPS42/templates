#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

vector<int> g[N];
int sz[N];
int tin[N];
int tout[N];
int nxt[N];
int timer = 1;
int par[N];
// nxt[v] --- the highest vertex in the heavy path corresponding to v
// [tin[v]; tout[v]] --- subtree of v
// [tin[nxt[v]]; tin[v]] --- path from nxt[v] to v

void dfs_par(int v = 1, int p = 1) {
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

void init() {
    dfs_par();
    for (int i = 0; i < N; i++) {
        vector<int> cur;
        for (int u : g[i]) {
            if (u != par[i]) {
                cur.push_back(u);
            }
        }
        g[i] = cur;
    }
    dfs_sz();
    nxt[1] = 1;
    dfs_hld();
    par[1] = 0;
}

int main() {
    // read
    init();
    return 0;
}
