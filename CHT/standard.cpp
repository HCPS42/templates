#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct CHT {
    int ptr = 0;
    vector<ll> K;
    vector<ll> B;
    void clear() {
        ptr = 0;
        K.clear();
        B.clear();
    }
    bool bad(int l1, int l2, int l3) {
        return (B[l3] - B[l1]) * (K[l1] - K[l2]) < (B[l2] - B[l1]) * (K[l1] - K[l3]);
    }
    void add(ll k, ll b) {
        // add in sorted order
        if (!K.empty() && K.back() == k) return;
        K.push_back(k);
        B.push_back(b);
        while (K.size() >= 3 && bad(K.size() - 3, K.size() - 2, K.size() - 1)) {
            K.erase(K.end() - 2);
            B.erase(B.end() - 2);
        }
    }
    ll get_min(ll x) {
        while (ptr < K.size() - 1 && K[ptr + 1] * x + B[ptr + 1] < K[ptr] * x + B[ptr]) ptr++;
        return K[ptr] * x + B[ptr];
    }
};

int main() {
    return 0;
}
