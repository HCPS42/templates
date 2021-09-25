#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef complex<ll> point;
#define x() real()
#define y() imag()

ll dot(point a, point b) {
    return (conj(a) * b).x();
}

ll cross(point a, point b) {
    return (conj(a) * b).y();
}

struct CHT {
    vector<point> hull;
    vector<point> vecs;
    void clear() {
        hull.clear();
        vecs.clear();
    }
    void add(ll k, ll b) {
        // add in sorted order
        point nw = {k, b};
        while (!vecs.empty() && dot(vecs.back(), nw - hull.back()) < 0) {
            hull.pop_back();
            vecs.pop_back();
        }
        if (!hull.empty()) {
            vecs.push_back(complex<ll>({0, 1}) * (nw - hull.back()));
        }
        hull.push_back(nw);
    }
    ll get_min(ll x) {
        point query = {x, 1};
        auto it = lower_bound(vecs.begin(), vecs.end(), query, [](point a, point b) {
            return cross(a, b) > 0;
        });
        return dot(query, hull[it - vecs.begin()]);
    }
};

int main() {
    return 0;
}
