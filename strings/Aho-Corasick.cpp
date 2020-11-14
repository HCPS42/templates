#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;

int to[N][26];
int link[N];
int sz = 1;
queue<int> q;

void add_str(string s) {
    int v = 0;
    for (char c : s) {
        c -= 'a';
        if (!to[v][c]) to[v][c] = sz++;
        v = to[v][c];
    }
}

void push_links() {
    q.push(0);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        int u = link[v];
        for (int c = 0; c < 26; c++) {
            if (to[v][c]) {
                link[to[v][c]] = v ? to[u][c] : 0;
                q.push(to[v][c]);
            }
            else to[v][c] = to[u][c];
        }
    }
}

int main() {
    return 0;
}
