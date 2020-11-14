#include <bits/stdc++.h>
using namespace std;

unordered_map<char, int> f;

struct Node {
    int l;
    int r;
    int start;
    Node* next[27];
    bool good;
    Node(int l_, int r_, int start_) {
        l = l_;
        r = r_;
        start = start_;
        for (int i = 0; i <= 26; i++){
            next[i] = NULL;
        }
        good = false;
    }
};

void init() {
    for (int i = 0; i <= 25; i++){
        f['a' + i] = i;
    }
    f['$'] = 26;
}

void build_suff_tree(Node*& root, string text) {
    root = new Node(-1, -1, -1);
    int n = text.length();
    for (int i = 0; i < n; i++) {
        Node* v = root;
        int j = i;
        while (j < n) {
            if (!v->next[f[text[j]]]) {
                v->next[f[text[j]]] = new Node(j, n-1, i);
                break;
            }
            v = v->next[f[text[j]]];
            int l = v->l;
            int r = v->r;
            for (int k = l; k <= r; k++) {
                if (text[k] != text[j]) {
                    Node* u = new Node(k, r, v->start);
                    for (int t = 0; t <= 26; t++) {
                        u->next[t] = v->next[t];
                        v->next[t] = NULL;
                    }
                    v->r = k - 1;
                    v->next[f[text[k]]] = u;
                    v->next[f[text[j]]] = new Node(j, n-1, i);
                    j = n;
                    break;
                }
                j++;
            }
        }
    }
}

void dfs(Node* v, string& text) {
    for (int i = 0; i <= 26; i++) {
        if (v->next[i]) {
            for (int j = v->next[i]->l; j <= v->next[i]->r; j++) {
                cout << text[j];
            }
            cout << "\n";
            dfs(v->next[i], text);
        }
    }
}

int main() {
    init();
    string text;
    cin >> text;
    text += '$';
    Node* root;
    build_suff_tree(root, text);
    dfs(root, text);
    return 0;
}
