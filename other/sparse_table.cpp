#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
const int K = 18;

int log_2[N];
int st[N][K];
int a[N];

void init() {
    for (int i = 2; i < N; i++) {
        log_2[i] = log_2[i / 2] + 1;
    }
    for (int i = 0; i < N; i++) {
        st[i][0] = a[i];
    }
    for (int j = 1; j < K; j++) {
        for (int i = 0; i + (1 << j) < N; i++) {
            st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
        }
    }
}

int get_min(int l, int r) {
    int j = log_2[r - l + 1];
    return min(st[l][j], st[r - (1 << j) + 1][j]);
}

int main() {
    // read
    init();
    return 0;
}
