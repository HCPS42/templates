#include <bits/stdc++.h>
using namespace std;

// https://www.spoj.com/problems/VFMUL/

// multiply numbers up to 50'000
// maybe change fft to two ntts and test against lint

const int K = 1 << 20; // check
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

struct bigint {
    static const int base = 10'000; // possible overflow
    static const int dig = 4;
    poly a;
    bigint() {
        a.push_back(0);
    }
    bigint(const string& b) {
        a = str_to_poly(b);
    }
    bigint(int64_t b) {
        a = str_to_poly(to_string(b));
    }
    friend istream& operator>>(istream& in, bigint& a) {
        string b;
        in >> b;
        a = b;
        return in;
    }
    friend ostream& operator<<(ostream& out, bigint a) {
        return out << a.to_str();
    }
    void norm() {
        int64_t carry = 0;
        for (int64_t& i : a) {
            i += carry;
            carry = i / base;
            i %= base;
        }
        while (carry) {
            a.push_back(carry % base);
            carry /= base;
        }
    }
    static string int_to_str(int b) {
        string res;
        while (b) {
            res += '0' + (b % 10);
            b /= 10;
        }
        while (res.size() < dig) res += '0';
        return res;
    }
    static poly str_to_poly(string b) {
        poly res;
        int len = b.size();
        while (len >= dig) {
            res.push_back(stoi(b.substr(len - dig)));
            b.erase(len - dig);
            len -= dig;
        }
        if (len) res.push_back(stoi(b));
        return res;
    }
    string to_str() const {
        string res;
        for (int64_t i : a) {
            res += int_to_str(i);
        }
        while (!res.empty() && res.back() == '0') res.pop_back();
        if (res.empty()) res = "0";
        reverse(res.begin(), res.end());
        return res;
    }
    bigint& operator*=(const bigint& b) {
        a = mult(a, b.a);
        norm();
        return *this;
    }
    friend bigint operator*(bigint a, const bigint& b) {
        return a *= b;
    }
};

int main() {
    init();
    return 0;
}
