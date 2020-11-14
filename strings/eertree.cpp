#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

int to[N][26];
int len[N];
int link[N];
int s[N];
int sz;
int m;
int last;

void init() {
    link[0] = 1;
    len[1] = -1;
    s[m++] = -1;
    sz = 2;
}

int get_link(int v) {
    while (s[m - len[v] - 2] != s[m - 1]) v = link[v];
    return v;
}

void add_letter(char c) {
    c -= 'a';
    s[m++] = c;
    last = get_link(last);
    if (!to[last][c]) {
        len[sz] = len[last] + 2;
        link[sz] = to[get_link(link[last])][c];
        to[last][c] = sz++;
    }
    last = to[last][c];
}

int main() {
    init();
    return 0;
}
