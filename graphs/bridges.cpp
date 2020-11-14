#include <bits/stdc++.h>
using namespace std;

const int N = 2e4 + 5;

vector<pair<int,int>> g[N];
bool used[N];
int tin[N];
int dp[N];
int timer = 0;
vector<int> bridges;

void dfs(int v = 1, int par = 0) {
    used[v] = 1;
    tin[v] = dp[v] = timer++;
    for (auto e : g[v]) {
        int u = e.first;
        int id = e.second;
        if (u == par) continue;
        if (used[u]) {
            dp[v] = min(dp[v], tin[u]);
            continue;
        }
        dfs(u, v);
        dp[v] = min(dp[v], dp[u]);
        if (dp[u] > tin[v]) {
            bridges.push_back(id);
        }
    }
}

int main() {
    return 0;
}
