#include <bits/stdc++.h>
using namespace std;

struct Node {
    Node* l;
    Node* r;
    int w, sz, val;
    Node(int x) {
        l = r = NULL;
        w = rand();
        sz = 1;
        val = x;
    }
};

int sz(Node* v) {
    if (!v) return 0;
    return v->sz;
}

void split(Node* v, Node*& l, Node*& r, int k) {
    if (!v) {
        l = r = NULL;
        return;
    }
    if (sz(v->l) < k) {
        split(v->r, v->r, r, k - sz(v->l) - 1);
        l = v;
    }
    else {
        split(v->l, l, v->l, k);
        r = v;
    }
    v->sz = sz(v->l) + sz(v->r) + 1;
}

void merge(Node*& v, Node* l, Node* r) {
    if (!l) {
        v = r;
        return;
    }
    if (!r) {
        v = l;
        return;
    }
    if (l->w < r->w) {
        merge(l->r, l->r, r);
        v = l;
    }
    else {
        merge(r->l, l, r->l);
        v = r;
    }
    v->sz = sz(v->l) + sz(v->r) + 1;
}

int main() {
    Node* root = NULL;
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        merge(root, root, new Node(i));
    }
    return 0;
}
