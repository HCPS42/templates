#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define pb push_back
#define ppp pop_back
#define pii pair<int,int>
#define fi first
#define se second

struct Edge {
    int to, id;
};

class Graph {
public:
    explicit Graph(int n) : g(n+5), tin(n+5), used(n+5), dp(n+5) {
    }
    void add_edge(int u, int v, int id) {
        g[u].push_back({v, id});
        g[v].push_back({u, id});
    }
    void dfs(int v = 1, int par = 0) {
        used[v] = 1;
        tin[v] = dp[v] = timer++;
        for (Edge e : g[v]) {
            int u = e.to, id = e.id;
            if (u == par) continue;
            if (used[u]) dp[v] = min(dp[v], tin[u]);
            else {
                dfs(u, v);
                dp[v] = min(dp[v], dp[u]);
                if (dp[u] > tin[v]) bridges.push_back(id);
            }
        }
    }
    vector<int> find_bridges() {
        dfs();
        return bridges;
    }

private:
    vector<vector<Edge>> g;
    vector<int> tin, dp;
    vector<bool> used;
    int timer = 0;
    vector<int> bridges;
};

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
#ifdef LOCAL
	freopen("input.txt", "r", stdin);
#endif
    
	return 0;
}
