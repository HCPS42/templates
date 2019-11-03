#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define pb push_back
#define ppp pop_back
#define fi first
#define se second
#define pii pair<int,int>

struct Node {
    int key;
    ll sum;
    Node *left, *right, *parent;
    Node(int key, ll sum, Node *left, Node *right, Node *parent) : key(key), sum(sum), left(left), right(right), parent(parent) {}
};

void update(Node *v) {
    if (v == NULL) return;
    v->sum = v->key + (v->left != NULL ? v->left->sum : 0) + (v->right != NULL ? v->right->sum : 0);
    if (v->left != NULL) v->left->parent = v;
    if (v->right != NULL) v->right->parent = v;
}

void small_rotation(Node *v) {
    Node* parent = v->parent;
    if (parent == NULL) return;
    Node *grandparent = v->parent->parent;
    if (parent->left == v) {
        parent->left = v->right;
        v->right = parent;
    }
    else {
        parent->right = v->left;
        v->left = parent;
    }
    update(parent);
    update(v);
    v->parent = grandparent;
    if (grandparent != NULL) {
        if (grandparent->left == parent) grandparent->left = v;
        else grandparent->right = v;
    }
}

void big_rotation(Node *v) {
    if (v->parent->left == v && v->parent->parent->left == v->parent) {
        small_rotation(v->parent);
        small_rotation(v);
    }
    else if (v->parent->right == v && v->parent->parent->right == v->parent) {
        small_rotation(v->parent);
        small_rotation(v);
    }
    else {
        small_rotation(v);
        small_rotation(v);
    }
}

void splay(Node *&root, Node *v) {
    if (v == NULL) return;
    while (v->parent != NULL) {
        if (v->parent->parent == NULL) {
            small_rotation(v);
            break;
        }
        big_rotation(v);
    }
    root = v;
}

Node* find(Node *&root, int key) {
    Node *v = root, *last = root, *next = NULL;
    while (v != NULL) {
        if (v->key >= key && (next == NULL || v->key < next->key)) next = v;
        last = v;
        if (v->key == key) break;
        if (v->key < key) v = v->right;
        else v = v->left;
    }
    splay(root, last);
    return next;
}

void split(Node *root, int key, Node *&left, Node *&right) {
    right = find(root, key);
    splay(root, right);
    if (right == NULL) {
        left = root;
        return;
    }
    left = right->left;
    right->left = NULL;
    if (left != NULL) left->parent = NULL;
    update(left);
    update(right);
}

Node* merge(Node *left, Node *right) {
    if (left == NULL) return right;
    if (right == NULL) return left;
    Node *min_right = right;
    while (min_right->left != NULL) min_right = min_right->left;
    splay(right, min_right);
    right->left = left;
    update(right);
    return right;
}

Node *root = NULL;

void insert(int x) {
    Node *left = NULL, *right = NULL, *new_node = NULL;
    split(root, x, left, right);
    if (right == NULL || right->key != x) new_node = new Node(x, x, NULL, NULL, NULL);
    root = merge(merge(left, new_node), right);
}

void erase(int x) {
    Node *left = NULL, *right = NULL;
    split(root, x, left, right);
    if (right != NULL && right->key == x) {
        right = right->right;
        if (right != NULL) right->parent = NULL;
    }
    root = merge(left, right);
}

bool find(int x) {
    find(root, x);
    if (root != NULL && root->key == x) return true;
    return false;
}

ll sum(int l, int r) {
    //returns the sum of all keys of the splay tree in the range of [l, r]
    if (root == NULL) return 0;
    Node *left = NULL, *middle = NULL, *right = NULL;
    split(root, l, left, middle);
    split(middle, r+1, middle, right);
    ll res = 0;
    if (middle != NULL) res = middle->sum;
    root = merge(merge(left, middle), right);
    return res;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif
    
}