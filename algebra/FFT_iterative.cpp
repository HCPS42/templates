#include <bits/stdc++.h>
using namespace std;

// https://habr.com/ru/post/113642/
// https://codeforces.com/problemset/problem/528/D

const int K = 1 << 20; // check
const double pi = acos(-1);

typedef complex<double> C;
typedef vector<C> poly_C;
typedef vector<int64_t> poly;

C w[K];
int id[K];

void init(int n) {
    for (int i = 0; i < n; i++) {
        w[i] = polar(1.0, 2 * pi * i / n);
    }
    int k = 0;
    while ((1 << k) < n) k++;
    id[0] = 0;
    int bit = -1;
    for (int i = 1; i < n; i++) {
        if ((i & (i - 1)) == 0) bit++;
        id[i] = id[i ^ (1 << bit)];
        id[i] |= 1 << (k - bit - 1);
    }
}

poly_C fft(const poly_C& a) {
    int n = a.size();
    poly_C cur(n, 0);
    poly_C nxt(n, 0);
    for (int i = 0; i < n; i++) {
        if (id[i] < n) {
            cur[i] = a[id[i]];
        }
    }
    for (int len = 1; len < n; len *= 2) {
        int k = n / (len * 2);
        int ptr = 0;
        while (ptr < n) {
            for (int i = 0; i < len; i++) {
                C t = w[i * k] * cur[ptr + len];
                nxt[ptr] = cur[ptr] + t;
                nxt[ptr + len] = cur[ptr] - t;
                ptr++;
            }
            ptr += len;
        }
        swap(cur, nxt);
    }
    return cur;
}

poly inter(const poly_C& a) {
    int n = a.size();
    poly_C inv = fft(a);
    poly res(n);
    for (int i = 0; i < n; i++) {
        res[i] = round(inv[i].real() / n);
    }
    reverse(res.begin() + 1, res.end());
    return res;
}

void align(poly_C& a, poly_C& b) {
    int n = a.size() + b.size() - 1;
    while (__builtin_popcount(n) != 1) n++;
    while (a.size() < n) a.push_back(0);
    while (b.size() < n) b.push_back(0);
}

poly mult(poly a, poly b) {
    poly_C A(a.size());
    poly_C B(b.size());
    for (int i = 0; i < a.size(); i++) A[i] = a[i];
    for (int i = 0; i < b.size(); i++) B[i] = b[i];
    align(A, B);
    int n = A.size();
    init(n);
    A = fft(A);
    B = fft(B);
    for (int i = 0; i < n; i++) A[i] *= B[i];
    return inter(A);
}

int main() {
    return 0;
}