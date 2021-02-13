#include <bits/stdc++.h>
using namespace std;

struct Node {
    int val;
    int64_t sum;
    Node* l;
    Node* r;
    Node* p;
    Node(int x) {
        val = x;
        sum = x;
        l = r = p = NULL;
    }
};

void upd(Node* v) {
    if (!v) return;
    v->sum = v->val + (v->l ? v->l->sum : 0) + (v->r ? v->r->sum : 0);
    if (v->l) v->l->p = v;
    if (v->r) v->r->p = v;
}

void small_rot(Node* v) {
    Node* p = v->p;
    if (!p) return;
    Node* gp = p->p;
    if (p->l == v) {
        p->l = v->r;
        v->r = p;
    }
    else {
        p->r = v->l;
        v->l = p;
    }
    upd(p);
    upd(v);
    v->p = gp;
    if (gp) {
        if (gp->l == p) gp->l = v;
        else gp->r = v;
    }
}

void big_rot(Node* v) {
    if ((v->p->l == v && v->p->p->l == v->p)
        || (v->p->r == v && v->p->p->r == v->p)) {
        small_rot(v->p);
    }
    else small_rot(v);
    small_rot(v);
}

void splay(Node*& root, Node* v) {
    if (!v) return;
    while (v->p) {
        if (!v->p->p) {
            small_rot(v);
            break;
        }
        big_rot(v);
    }
    root = v;
}

Node* find(Node*& root, int x) {
    Node* v = root;
    Node* last = root;
    Node* nxt = NULL;
    while (v) {
        if (v->val >= x && (!nxt || v->val < nxt->val)) nxt = v;
        last = v;
        if (v->val == x) break;
        if (v->val < x) v = v->r;
        else v = v->l;
    }
    splay(root, last);
    return nxt;
}

void split(Node* root, int x, Node*& l, Node*& r) {
    r = find(root, x);
    splay(root, r);
    if (!r) {
        l = root;
        return;
    }
    l = r->l;
    r->l = NULL;
    if (l) l->p = NULL;
    upd(l);
    upd(r);
}

Node* merge(Node* l, Node* r) {
    if (!l) return r;
    if (!r) return l;
    Node* mn = r;
    while (mn->l) mn = mn->l;
    splay(r, mn);
    r->l = l;
    upd(r);
    return r;
}

void insert(Node*& root, int x) {
    Node* l;
    Node* r;
    split(root, x, l, r);
    if (!r || r->val != x) {
        l = merge(l, new Node(x));
    }
    root = merge(l, r);
}

void erase(Node*& root, int x) {
    Node* l;
    Node* r;
    split(root, x, l, r);
    if (r && r->val == x) {
        r = r->r;
        if (r) r->p = NULL;
    }
    root = merge(l, r);
}

bool count(Node*& root, int x) {
    find(root, x);
    if (root && root->val == x) return 1;
    return 0;
}

int64_t sum(Node*& root, int L, int R) {
    if (!root) return 0;
    Node* l;
    Node* m;
    Node* r;
    split(root, L, l, m);
    split(m, R + 1, m, r);
    int64_t res = 0;
    if (m) res = m->sum;
    root = merge(merge(l, m), r);
    return res;
}

int main() {
    return 0;
}
