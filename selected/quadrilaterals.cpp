#include <bits/stdc++.h>
using namespace std;

// Quadrilaterals
// Seoul Regional 2019 Problem F
// https://www.acmicpc.net/problem/17973
// MW Prefinals 2020 Day 6 Problem F
// https://official.contest.yandex.com/mw2020prefinals/contest/18101/problems/F6/

typedef long long ll;
typedef complex<ll> poi;
#define x() real()
#define y() imag()

poi read_poi() {
    ll x, y;
    cin >> x >> y;
    return {x, y};
}

ll dot(poi a, poi b) {
    return (conj(a) * b).x();
}

ll cro(poi a, poi b) {
    return (conj(a) * b).y();
}

bool cmp(poi& a, poi& b) {
    return make_pair(a.x(), a.y()) < make_pair(b.x(), b.y());
}

ll cro(poi a, poi b, poi c) {
    return cro(b - a, c - a);
}

int pos(ll a) {
    return a > 0 ? 1 : -1;
}

bool convex(poi a, poi b, poi c, poi d) {
    return pos(cro(a, c, b)) * pos(cro(a, c, d)) < 0 &&
           pos(cro(b, d, a)) * pos(cro(b, d, c)) < 0;
}

struct Event {
    poi a;
    int s, e;
};

ll cro(Event a, Event b) {
    return cro(a.a, b.a);
}

bool operator<(Event& a, Event& b) {
    return cro(a.a, b.a) > 0;
}

const int N = 1005;

poi a[N];
int rev[N];
vector<Event> es;

void Solve() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        a[i] = read_poi();
    }
    sort(a + 1, a + n + 1, cmp);
    for (int i = 1; i <= n; i++) {
        for(int j = i + 1; j <= n; j++) {
            es.push_back({a[j] - a[i], i, j});
        }
    }
    sort(es.begin(), es.end());
    for (int i = 1; i <= n; i++) rev[i] = i;
    ll ans = 0;
    ll minv = 8e18;
    ll ec = 0;
    ll en = 0;
    for (Event e : es) {
        int i = e.s;
        int j = e.e;
        swap(a[rev[i]], a[rev[j]]);
        swap(rev[i], rev[j]);
        int k = min(rev[i], rev[j]);
        if (k == 1 || k == n - 1) continue;
        ans += (k - 1) * (n - k - 1);
        vector<int> lef = {k - 1};
        vector<int> rig = {k + 2};
        if (k >= 3 && cro(a[k - 2], a[k], a[k + 1]) == cro(a[k - 1], a[k], a[k + 1])) {
            lef.push_back(k - 2);
        }
        if (k <= n - 3 && cro(a[k + 3], a[k], a[k + 1]) == cro(a[k + 2], a[k], a[k + 1])) {
            rig.push_back(k + 3);
        }
        ll area = abs(cro(a[k - 1], a[k], a[k + 1])) + abs(cro(a[k + 2], a[k], a[k + 1]));
        if (area > minv) continue;
        if (area < minv) {
            minv = area;
            ec = en = 0;
        }
        for (int l : lef) {
            for (int r : rig) {
                if (convex(a[k], a[l], a[k + 1], a[r])) ec++;
                else en++;
            }
        }
    }
    ans += ec + 2 * en;
    cout << ans << "\n";
}

int main() {
    Solve();
    return 0;
}
