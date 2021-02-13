#include <bits/stdc++.h>
using namespace std;

// https://codeforces.com/gym/100851 task C
// https://codeforces.com/group/hqhmagxI71/contest/288871/problem/G

// no edge lies on two cycles

const int N = 2e5 + 5;

struct Cactus {
    vector<pair<int, int>> g[N];
    vector<pair<int, int>> es;
    bool used[N];
    int tin[N];
    int dp[N];
    int sz[N];
    int dep[N];
    int timer = 0;
    bool is_bridge[N];
    vector<int> bridges;
    vector<vector<int>> cycles;
    void add_e(int u, int v) {
        g[u].push_back({v, es.size()});
        g[v].push_back({u, es.size()});
        es.push_back({u, v});
    }
    void find_bridges(int v = 1, int p = 0) {
        used[v] = 1;
        tin[v] = dp[v] = timer++;
        sz[v] = 1;
        for (auto [u, id] : g[v]) {
            if (u == p) continue;
            if (used[u]) {
                dp[v] = min(dp[v], tin[u]);
                continue;
            }
            find_bridges(u, v);
            dp[v] = min(dp[v], dp[u]);
            sz[v] += sz[u];
            if (dp[u] > tin[v]) {
                bridges.push_back(id);
            }
        }
    }
    void find_cycles(int v, int p = 0) {
        static vector<int> path;
        used[v] = 1;
        path.push_back(v);
        for (auto [u, id] : g[v]) {
            if (u == p || is_bridge[id]) continue;
            if (!used[u]) {
                dep[u] = dep[v] + 1;
                find_cycles(u, v);
                continue;
            }
            int len = dep[v] - dep[u] + 1;
            vector<int> cycle;
            for (int i = 0; i < len; i++) {
                cycle.push_back(path[path.size() - 1 - i]);
            }
            if (!cycle.empty()) {
                cycles.push_back(cycle);
            }
        }
        path.pop_back();
    }
    void parse(int n) {
        find_bridges();
        for (auto& [u, v] : es) {
            if (tin[u] > tin[v]) {
                swap(u, v);
            }
        }
        for (int i : bridges) {
            is_bridge[i] = 1;
        }
        for (int i = 1; i <= n; i++) {
            used[i] = 0;
        }
        for (int i = 1; i <= n; i++) {
            if (used[i]) continue;
            find_cycles(i);
        }
    }
};

int main() {
    return 0;
}
