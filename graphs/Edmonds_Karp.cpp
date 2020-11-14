#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 220;
const ll inf = 8e18;

ll dist[N];
pair<int, ll> par[N];
bool used[N];

struct Edge {
    int s, e;
    ll cap, flow;
};

vector<int> g[N];
vector<Edge> edges;

void add_edge(int s, int e, ll cap) {
    Edge forw = {s, e, cap, 0};
    Edge back = {e, s, 0, 0};
    int k = edges.size();
    edges.push_back(forw);
    g[s].push_back(k++);
    edges.push_back(back);
    g[e].push_back(k);
}

void add_flow(int id, ll flow) {
    edges[id].flow += flow;
    edges[id].cap -= flow;
    edges[id ^ 1].flow -= flow;
    edges[id ^ 1].cap += flow;
}

ll max_flow(int src, int sink) {
    ll flow = 0;
    while (1) {
        for (int i = 0; i < N; i++) {
            dist[i] = inf;
            used[i] = 0;
            par[i] = {0, inf};
        }
        bool ok = 0;
        dist[src] = 0;
        queue<int> q;
        q.push(src);
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            if (used[v]) continue;
            used[v] = 1;
            for (int id : g[v]) {
                Edge& edge = edges[id];
                if (edge.cap && dist[edge.e] > dist[v] + 1) {
                    par[edge.e] = {id, min(par[v].second, edge.cap)};
                    dist[edge.e] = dist[v] + 1;
                    q.push(edge.e);
                    if (edge.e == sink) {
                        ok = 1;
                        break;
                    }
                }
            }
            if (ok) break;
        }
        if (!ok) break;
        ll w = par[sink].second;
        int v = sink;
        flow += w;
        while (v != src) {
            int id = par[v].first;
            add_flow(id, w);
            v = edges[id].s;
        }
    }
    return flow;
}

int main() {
    return 0;
}
