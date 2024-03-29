#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct seg_tree {
    static const ll kLef = -2e18;
    static const ll kRig = 2e18;
    vector<ll> t;
    vector<int> lef_kid;
    vector<int> rig_kid;
    seg_tree() : t(1, 0), lef_kid(1, 0), rig_kid(1, 0) {
    }
    int add_ver() {
        t.push_back(0);
        lef_kid.push_back(0);
        rig_kid.push_back(0);
        return t.size() - 1;
    }
    int lef(int v) {
        if (!lef_kid[v]) {
            int kid = add_ver();
            lef_kid[v] = kid;
        }
        return lef_kid[v];
    }
    int rig(int v) {
        if (!rig_kid[v]) {
            int kid = add_ver();
            rig_kid[v] = kid;
        }
        return rig_kid[v];
    }
    void upd(ll id, ll x, int v = 0, ll l = kLef, ll r = kRig) {
        t[v] += x;
        if (l == r) return;
        ll m = l + r;
        if (m < 0 && m & 1) m--;
        m /= 2;
        if (id <= m) {
            upd(id, x, lef(v), l, m);
        }
        else {
            upd(id, x, rig(v), m + 1, r);
        }
    }
    ll get(ll L, ll R, int v = 0, ll l = kLef, ll r = kRig) {
        if (R < l || r < L) return 0;
        if (L <= l && r <= R) return t[v];
        ll m = l + r;
        if (m < 0 && m & 1) m--;
        m /= 2;
        return get(L, R, lef(v), l, m) + get(L, R, rig(v), m + 1, r);
    }
};

int main() {
    return 0;
}
