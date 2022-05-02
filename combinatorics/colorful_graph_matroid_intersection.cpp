#include <bits/stdc++.h>
using namespace std;

// MW 2020 Fall Day 3 Problem K
// https://official.contest.yandex.com/mw2020fall/contest/23193/problems/K3

const int N = 5005; // edges
const int K = 105; // vertices / colors

struct Edge {
    int u, v;
};

struct Elem {
    int color;
    Edge edge;
    bool in_set = 0;
    int set_pos;
    int par;
};

vector<Elem> ground;
vector<int> indep;

struct GraphMatroid {
    struct Graph {
        vector<Edge> es;
        int par[K];
        int dep[K];
        int find(int v) {
            if (par[v] == v) return v;
            return par[v] = find(par[v]);
        }
        void unite(int u, int v) {
            u = find(u);
            v = find(v);
            if (u == v) return;
            if (dep[u] < dep[v]) swap(u, v);
            par[v] = u;
            if (dep[u] == dep[v]) dep[u]++;
        }
        void add_edge(Edge e) {
            es.push_back(e);
        }
        void reset() {
            es.clear();
        }
        int size() {
            return es.size();
        }
        void build_dsu() {
            for (int i = 0; i < K; i++) {
                par[i] = i;
                dep[i] = 0;
            }
            for (Edge e : es) {
                unite(e.u, e.v);
            }
        }
        bool indep_with(Edge e) {
            return find(e.u) != find(e.v);
        }
    };
    Graph basis;
    Graph basis_without[K];
    bool oracle(int add) {
        return basis.indep_with(ground[add].edge);
    }
    bool oracle(int add, int rem) {
        int id = ground[rem].set_pos;
        return basis_without[id].indep_with(ground[add].edge);
    }
    void init() {
        basis.reset();
        for (int i = 0; i < indep.size(); i++) {
            basis_without[i].reset();
        }
        for (int i = 0; i < indep.size(); i++) {
            basis.add_edge(ground[indep[i]].edge);
            for (int j = 0; j < indep.size(); j++) {
                if (j != i) {
                    basis_without[j].add_edge(ground[indep[i]].edge);
                }
            }
        }
        basis.build_dsu();
        for (int i = 0; i < indep.size(); i++) {
            basis_without[i].build_dsu();
        }
    }
};

struct ColorfulMatroid {
    bool used[K];
    bool oracle(int add) {
        return !used[ground[add].color];
    }
    bool oracle(int add, int rem) {
        int add_col = ground[add].color;
        int rem_col = ground[rem].color;
        if (!used[add_col]) return 1;
        return add_col == rem_col;
    }
    void init() {
        for (int i = 0; i < K; i++) {
            used[i] = 0;
        }
        for (int i : indep) {
            used[ground[i].color] = 1;
        }
    }
};

GraphMatroid graph;
ColorfulMatroid color;

bool augment() {
    static const int kSource = -1;
    static const int kNotVisited = -2;
    static const int kNotFound = -3;
    graph.init();
    color.init();
    for (int i = 0; i < ground.size(); i++) {
        ground[i].par = kNotVisited;
    }
    int id = kNotFound;
    queue<int> q;
    for (int i = 0; i < ground.size(); i++) {
        if (color.oracle(i)) {
            ground[i].par = kSource;
            q.push(i);
        }
    }
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        if (ground[cur].in_set) {
            for (int to = 0; to < ground.size(); to++) {
                if (ground[to].par != kNotVisited) continue;
                if (!color.oracle(to, cur)) continue;
                ground[to].par = cur;
                q.push(to);
            }
            continue;
        }
        if (graph.oracle(cur)) {
            id = cur;
            break;
        }
        for (int to : indep) {
            if (ground[to].par != kNotVisited) continue;
            if (!graph.oracle(cur, to)) continue;
            ground[to].par = cur;
            q.push(to);
        }
    }
    if (id == kNotFound) {
        return 0;
    }
    do {
        ground[id].in_set ^= 1;
        id = ground[id].par;
    } while (id != kSource);
    indep.clear();
    for (int i = 0; i < ground.size(); i++) {
        if (!ground[i].in_set) continue;
        ground[i].set_pos = indep.size();
        indep.push_back(i);
    }
    return 1;
}

void add_element(Edge edge, int color) {
    ground.emplace_back();
    ground.back().edge = edge;
    ground.back().color = color;
}

void matroid_intersection() {
    while (augment());
}

void Solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        add_element({u, v}, w);
    }
    matroid_intersection();
    cout << indep.size() << "\n";
    for (int i : indep) {
        cout << i + 1 << " ";
    }
    cout << "\n";
}

int main() {
    Solve();
    return 0;
}
