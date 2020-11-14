#include <bits/stdc++.h>
using namespace std;

const int K = 1 << 20; // be careful
const double pi = acos(-1);

typedef complex<double> C;
typedef vector<C> poly_C;
typedef vector<int64_t> poly;

C w[K];

void init() {
    for (int i = 1; i < K; i *= 2) {
        for (int j = 0; j < i; j++) {
            w[i + j] = polar(1.0, pi * j / i);
        }
    }
}

template<typename T>
void fft(T* in, C* out, int n, int k = 1) {
    if (n == 1) {
        *out = *in;
        return;
    }
    n /= 2;
    fft(in, out, n, 2 * k);
    fft(in + k, out + n, n, 2 * k);
    for (int i = 0; i < n; i++) {
        C t = out[i + n] * w[i + n];
        out[i + n] = out[i] - t;
        out[i] += t;
    }
}

void align(poly& a, poly& b) {
    int n = a.size() + b.size() - 1;
    while (a.size() < n) a.push_back(0);
    while (b.size() < n) b.push_back(0);
}

poly_C eval(poly& a) {
    while (__builtin_popcount(a.size()) != 1) {
        a.push_back(0);
    }
    poly_C res(a.size());
    fft(a.data(), res.data(), a.size());
    return res;
}

poly inter(poly_C a) {
    int n = a.size();
    poly_C inv(n);
    fft(a.data(), inv.data(), n);
    poly res(n);
    for (int i = 0; i < n; i++) {
        res[i] = round(inv[i].real() / n);
    }
    reverse(res.begin() + 1, res.end());
    return res;
}

poly mult(poly a, poly b) {
    align(a, b);
    poly_C A = eval(a);
    poly_C B = eval(b);
    for (int i = 0; i < A.size(); i++) {
        A[i] *= B[i];
    }
    return inter(A);
}

int main() {
    init();
    return 0;
}
