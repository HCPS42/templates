#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

vector<int> g[2][N];
bool used[N];
vector<int> post;
vector<vector<int>> comps;

void dfs_inv(int v) {
    used[v] = 1;
    for (int u : g[1][v]) {
        if (!used[u]) dfs_inv(u);
    }
    post.push_back(v);
}

void dfs(int v, vector<int> &comp) {
    used[v] = 1;
    comp.push_back(v);
    for (int u : g[0][v]) {
        if (!used[u]) dfs(u, comp);
    }
}

void kosaraju(int n) {
    for (int i = 1; i <= n; i++){
        used[i] = 0;
    }
    for (int i = 1; i <= n; i++) {
        if (!used[i]) dfs_inv(i);
    }
    reverse(post.begin(), post.end());
    for (int i = 1; i <= n; i++){
        used[i] = 0;
    }
    for (int v : post) {
        if (!used[v]) {
            vector<int> comp;
            dfs(v, comp);
            comps.push_back(comp);
        }
    }
    // comps = reversed topsort
}

int main() {
    return 0;
}
