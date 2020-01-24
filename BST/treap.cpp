#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define pb push_back
#define ppp pop_back
#define fi first
#define se second
#define pii pair<int,int>

struct node {
	node *lef, *rig;
	int w, sz, val;
	node(int x) {
		lef = rig = NULL;
		w = rand();
		sz = 1;
		val = x;
	}
};

int size(node *v) {
	if (v == NULL) return 0;
	return v->sz;
}

void split(node *v, node *&lef, node *&rig, int k) {
	if (v == NULL) {
		lef = rig = NULL;
		return;
	}
	if (size(v->lef) < k) {
		split(v->rig, v->rig, rig, k - size(v->lef) - 1);
		lef = v;
	}
	else {
		split(v->lef, lef, v->lef, k);
		rig = v;
	}
	v->sz = size(v->lef) + size(v->rig) + 1;
}

void merge(node *&v, node *lef, node *rig) {
	if (!lef) {
		v = rig;
		return;
	}
	if (!rig) {
		v = lef;
		return;
	}
	if (lef->w < rig->w) {
		merge(lef->rig, lef->rig, rig);
		v = lef;
	}
	else {
		merge(rig->lef, lef, rig->lef);
		v = rig;
	}
	v->sz = size(v->lef) + size(v->rig) + 1;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif
	node *root = NULL;
	int n;
	cin >> n;
	for (int i=1; i<=n; i++) {
		merge(root, root, new node(i));
	}
	return 0;
}
