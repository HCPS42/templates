#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5;
const int inf = 1e9;

vector<int> g[N];
bool used[N];
int sz[N];
int msz[N];
vector<int> vis;

void calc_sz(int v, int p = 0) {
    vis.push_back(v);
    sz[v] = 1;
    msz[v] = 0;
    for (int u : g[v]) {
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

int main() {
    return 0;
}
