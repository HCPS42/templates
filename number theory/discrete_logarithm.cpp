#include <bits/stdc++.h>
using namespace std;

vector<int> find_divs(int n) {
    vector<int> res;
    for (int64_t i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            res.push_back(i);
            if (i * i < n) res.push_back(n / i);
        }
    }
    sort(res.begin(), res.end());
    return res;
}

int binpow(int a, int b, int p) {
    int res = 1;
    while (b) {
        if (b & 1) res = res * 1ll * a % p;
        b >>= 1;
        a = a * 1ll * a % p;
    }
    return res;
}

int find_root(int p) {
    if (p == 2) return 1;
    mt19937 rnd;
    vector<int> d = find_divs(p - 1);
    while (1) {
        int g = rnd() % (p - 1) + 1;
        bool ok = 1;
        for (int i : d) {
            if (i == 1) continue;
            if (binpow(g, (p - 1) / i, p) == 1) {
                ok = 0;
                break;
            }
        }
        if (ok) return g;
    }
}

map<int, int> Map;
map<int, int> Dlog;

void precalc(int g, int p, int n) {
    n = sqrt(ld(p) / ld(n)) + 1;
    n *= 2;
    int gn = binpow(g, n, p);
    int cur = 1;
    for (int x = 0; (x - 1) * n < p - 1; x++) {
        Map[cur] = x * n;
        cur = cur * 1ll * gn % p;
    }
}

int dlog(int b, int g, int p) {
    int cur = b;
    int i = 0;
    while (1) {
        if (Map.count(cur)) {
            return Map[cur] - i;
        }
        cur = cur * 1ll * g % p;
        i++;
    }
}

void find_dlogs(vector<int> all, int p) {
    int g = find_root(p);
    int n = all.size();
    precalc(g, p, n);
    for (int i : all) {
        int x = dlog(i, g, p);
        if (x < 0) x += p - 1;
        if (x >= p - 1) x -= p - 1;
        Dlog[i] = x;
    }
}

int main() {
    return 0;
}
