#include <bits/stdc++.h>
using namespace std;

// PTZ 2019 Winter
// https://codeforces.com/gym/102156/problem/D

const int N = 5065; // vectors
const int K = 125; // colors

typedef int64_t Vec;

struct Elem {
    int color;
    Vec v;
    bool in_set = false;
    int set_pos;
    int par;
};

vector<Elem> ground;
vector<int> indep;

struct LinearMatroid {
    struct VectorSpace {
        vector<Vec> vs;
        void add_vector(Vec v) {
            vs.push_back(v);
        }
        void reset() {
            vs.clear();
        }
        int size() {
            return vs.size();
        }
        void gauss() {
            for (int i = 0; i < size(); i++) {
                for (int j = i; j < size(); j++) {
                    if (vs[i] < vs[j]) {
                        swap(vs[i], vs[j]);
                    }
                }
                for (int j = i + 1; j < size(); j++) {
                    vs[j] = min(vs[j], vs[j] ^ vs[i]);
                }
            }
        }
        bool indep_with(Vec v) {
            for (Vec u : vs) {
                v = min(v, v ^ u);
            }
            return v > 0;
        }
    };
    VectorSpace basis;
    VectorSpace basis_without[K];
    bool oracle(int add) {
        return basis.indep_with(ground[add].v);
    }
    bool oracle(int add, int rem) {
        int id = ground[rem].set_pos;
        return basis_without[id].indep_with(ground[add].v);
    }
    void init() {
        basis.reset();
        for (int i = 0; i < indep.size(); i++) {
            basis_without[i].reset();
        }
        for (int i = 0; i < indep.size(); i++) {
            basis.add_vector(ground[indep[i]].v);
            for (int j = 0; j < indep.size(); j++) {
                if (j != i) {
                    basis_without[j].add_vector(ground[indep[i]].v);
                }
            }
        }
        basis.gauss();
        for (int i = 0; i < indep.size(); i++) {
            basis_without[i].gauss();
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

LinearMatroid linear;
ColorfulMatroid color;

bool augment() {
    static const int kSource = -1;
    static const int kNotVisited = -2;
    static const int kNotFound = -3;
    linear.init();
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
        if (linear.oracle(cur)) {
            id = cur;
            break;
        }
        for (int to : indep) {
            if (ground[to].par != kNotVisited) continue;
            if (!linear.oracle(cur, to)) continue;
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

void add_element(Vec v, int color) {
    ground.emplace_back();
    ground.back().v = v;
    ground.back().color = color;
}

void matroid_intersection() {
    while (augment());
}

void Solve() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        Vec v;
        cin >> v;
        add_element(v, i);
    }
    int m;
    cin >> m;
    for (int i = 1; i <= m; i++) {
        int k;
        cin >> k;
        while (k--) {
            Vec v;
            cin >> v;
            add_element(v, n + i);
        }
    }
    matroid_intersection();
    if (indep.size() < n + m) {
        cout << "-1\n";
        return;
    }
    for (int i = n; i < ground.size(); i++) {
        if (ground[i].in_set) {
            cout << ground[i].v << "\n";
        }
    }
}

int main() {
    Solve();
    return 0;
}
