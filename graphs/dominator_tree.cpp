#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

vector<int> suc[N];
vector<int> pre[N];
int rea_v;
int sem[N];
int ver[N];
int par[N];
int dom[N];
set<int> bag[N];
int anc[N];
int lab[N];

void dfs_dom(int v = 1) {
    sem[v] = ++rea_v;
    ver[rea_v] = v;
    for (int u : suc[v]) {
        if (!sem[u]) {
            par[u] = v;
            dfs_dom(u);
        }
        pre[u].push_back(v);
    }
}

void init() {
    for (int i = 0; i < N; i++) {
        anc[i] = 0;
        lab[i] = i;
    }
}

void compress(int v) {
    if (!anc[anc[v]]) return;
    compress(anc[v]);
    if (sem[lab[anc[v]]] < sem[lab[v]]) {
        lab[v] = lab[anc[v]];
    }
    anc[v] = anc[anc[v]];
}

int eval(int v) {
    if (!anc[v]) return v;
    compress(v);
    return lab[v];
}

void link(int v, int u) {
    anc[u] = v;
}

void add_e(int u, int v) {
    suc[u].push_back(v);
}

void dominator_tree() {
    dfs_dom();
    init();
    for (int i = rea_v; i >= 2; i--) {
        int v = ver[i];
        for (int w : pre[v]) {
            int u = eval(w);
            if (sem[u] < sem[v]) {
                sem[v] = sem[u];
            }
        }
        bag[ver[sem[v]]].insert(v);
        link(par[v], v);
        for (int w : bag[par[v]]) {
            int u = eval(w);
            dom[w] = sem[u] < sem[w] ? u : par[v];
        }
        bag[par[v]].clear();
    }
    for (int i = 2; i <= rea_v; i++) {
        int v = ver[i];
        if (dom[v] != ver[sem[v]]) {
            dom[v] = dom[dom[v]];
        }
    }
    dom[1] = 1;
}

int main() {
    return 0;
}
