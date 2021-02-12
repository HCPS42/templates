#include <bits/stdc++.h>
using namespace std;

// https://codeforces.com/problemset/problem/914/G

// const int N = 1 << 20;
// int a[N];

const int p = 1e9 + 7;

int add(int a, int b) {
    a += b;
    if (a >= p) a -= p;
    return a;
}

int sub(int a, int b) {
    a -= b;
    if (a < 0) a += p;
    return a;
}

int mult(int a, int b) {
    return a * 1ll * b % p;
}

int binpow(int a, int64_t b) {
    int res = 1;
    while (b) {
        if (b & 1) res = mult(res, a);
        b >>= 1;
        a = mult(a, a);
    }
    return res;
}

int divi(int a, int b) {
    return mult(a, binpow(b, p - 2));
}

void tr_xor(int* l, int* r) {
    if (r - l == 1) return;
    int* m = l + (r - l) / 2;
    tr_xor(l, m);
    tr_xor(m, r);
    for (int i = 0; i < m - l; i++) {
        int a = *(l + i);
        int b = *(m + i);
        *(l + i) = add(a, b);
        *(m + i) = sub(a, b);
    }
}

void inv_xor(int* l, int* r) {
    tr_xor(l, r);
    int n = r - l;
    int inv_n = divi(1, n);
    for (int i = 0; i < n; i++) {
        *(l + i) = mult(*(l + i), inv_n);
    }
}

void conv_xor(int* l1, int* r1, int* l2, int* r2) {
    tr_xor(l1, r1);
    tr_xor(l2, r2);
    int n = r1 - l1;
    for (int i = 0; i < n; i++) {
        *(l1 + i) = mult(*(l1 + i), *(l2 + i));
    }
    inv_xor(l1, r1);
    inv_xor(l2, r2);
}

void tr_or(int* l, int* r) {
    if (r - l == 1) return;
    int* m = l + (r - l) / 2;
    tr_or(l, m);
    tr_or(m, r);
    for (int i = 0; i < m - l; i++) {
        *(m + i) = add(*(m + i), *(l + i));
    }
}

void inv_or(int* l, int* r) {
    if (r - l == 1) return;
    int* m = l + (r - l) / 2;
    for (int i = 0; i < m - l; i++) {
        *(m + i) = sub(*(m + i), *(l + i));
    }
    inv_or(l, m);
    inv_or(m, r);
}

void conv_or(int* l1, int* r1, int* l2, int* r2) {
    tr_or(l1, r1);
    tr_or(l2, r2);
    int n = r1 - l1;
    for (int i = 0; i < n; i++) {
        *(l1 + i) = mult(*(l1 + i), *(l2 + i));
    }
    inv_or(l1, r1);
    inv_or(l2, r2);
}

void conv_and(int* l1, int* r1, int* l2, int* r2) {
    int n = r1 - l1;
    int mask = n - 1;
    for (int i = 0; i < n / 2; i++) {
        swap(*(l1 + i), *(l1 + (i ^ mask)));
        swap(*(l2 + i), *(l2 + (i ^ mask)));
    }
    conv_or(l1, r1, l2, r2);
    for (int i = 0; i < n / 2; i++) {
        swap(*(l1 + i), *(l1 + (i ^ mask)));
        swap(*(l2 + i), *(l2 + (i ^ mask)));
    }
}

int main() {
    return 0;
}
