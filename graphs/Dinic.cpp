#include <bits/stdc++.h>
using namespace std;

// O(n^2 * m)

typedef long long ll;

const int N = 205;
const ll inf = 1e18;

struct Edge {
    int s, e;
    ll cap, flow;
};

vector<int> g[N];
vector<Edge> edges;
int dist[N], ptr[N];
queue<int> q;

void add_edge(int s, int e, ll cap) {
    Edge forw = {s, e, cap, 0};
    Edge back = {e, s, 0, 0};
    g[s].push_back(edges.size());
    edges.push_back(forw);
    g[e].push_back(edges.size());
    edges.push_back(back);
}

bool bfs(int src, int sink) {
    while (!q.empty()) q.pop();
    q.push(src);
    for (int i = 0; i < N; i++) {
        dist[i] = -1;
    }
    dist[src] = 0;
    while (!q.empty() && dist[sink] == -1) {
        int v = q.front();
        q.pop();
        for (int i = 0; i < g[v].size(); i++) {
            int id = g[v][i];
            int u = edges[id].e;
            if (dist[u] == -1 && edges[id].flow < edges[id].cap) {
                q.push(u);
                dist[u] = dist[v] + 1;
            }
        }
    }
    return dist[sink] != -1;
}

ll dfs(int v, ll flow, int sink) {
    if (!flow) return 0;
    if (v == sink) return flow;
    while (ptr[v] < g[v].size()) {
        int id = g[v][ptr[v]];
        int u = edges[id].e;
        if (dist[u] != dist[v] + 1) {
            ptr[v]++;
            continue;
        }
        ll pushed = dfs(u, min(flow, edges[id].cap - edges[id].flow), sink);
        if (pushed) {
            edges[id].flow += pushed;
            edges[id^1].flow -= pushed;
            return pushed;
        }
        ptr[v]++;
    }
    return 0;
}

ll max_flow(int src, int sink) {
    ll flow = 0;
    while (1) {
        if (!bfs(src, sink)) break;
        for (int i = 0; i < N; i++) ptr[i] = 0;
        while (ll pushed = dfs(src, inf, sink)) {
            flow += pushed;
        }
    }
    return flow;
}

int main() {
    return 0;
}
