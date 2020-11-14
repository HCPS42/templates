#include <bits/stdc++.h>
using namespace std;

struct Node {
    int key;
    int64_t sum;
    Node *left, *right, *parent;
    Node(int key, int64_t sum, Node *left, Node *right, Node *parent) : key(key), sum(sum), left(left), right(right), parent(parent) {}
};

void update(Node *v) {
    if (!v) return;
    v->sum = v->key + (v->left ? v->left->sum : 0) + (v->right ? v->right->sum : 0);
    if (v->left) v->left->parent = v;
    if (v->right) v->right->parent = v;
}

void small_rotation(Node *v) {
    Node* parent = v->parent;
    if (!parent) return;
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
    if (grandparent) {
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
    if (!v) return;
    while (v->parent) {
        if (!v->parent->parent) {
            small_rotation(v);
            break;
        }
        big_rotation(v);
    }
    root = v;
}

Node* find(Node *&root, int key) {
    Node *v = root, *last = root, *next = NULL;
    while (v) {
        if (v->key >= key && (!next || v->key < next->key)) next = v;
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
    if (!right) {
        left = root;
        return;
    }
    left = right->left;
    right->left = NULL;
    if (left) left->parent = NULL;
    update(left);
    update(right);
}

Node* merge(Node *left, Node *right) {
    if (!left) return right;
    if (!right) return left;
    Node *min_right = right;
    while (min_right->left) min_right = min_right->left;
    splay(right, min_right);
    right->left = left;
    update(right);
    return right;
}

Node *root = NULL;

void insert(int x) {
    Node *left = NULL, *right = NULL, *new_node = NULL;
    split(root, x, left, right);
    if (!right || right->key != x) new_node = new Node(x, x, NULL, NULL, NULL);
    root = merge(merge(left, new_node), right);
}

void erase(int x) {
    Node *left = NULL, *right = NULL;
    split(root, x, left, right);
    if (right && right->key == x) {
        right = right->right;
        if (right) right->parent = NULL;
    }
    root = merge(left, right);
}

bool find(int x) {
    find(root, x);
    if (root && root->key == x) return true;
    return false;
}

int64_t sum(int l, int r) {
    //returns the sum of all keys of the splay tree in the range of [l, r]
    if (!root) return 0;
    Node *left = NULL, *middle = NULL, *right = NULL;
    split(root, l, left, middle);
    split(middle, r + 1, middle, right);
    int64_t res = 0;
    if (middle) res = middle->sum;
    root = merge(merge(left, middle), right);
    return res;
}

int main() {
    return 0;
}
