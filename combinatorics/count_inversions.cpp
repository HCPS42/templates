#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define pb push_back
#define ppp pop_back
#define pii pair<int,int>
#define fi first
#define se second

ll merge(int a[], int l, int r) {
    ll res = 0;
    int mid = (l+r)/2;
    int n1 = mid-l+1, n2 = r-mid;
    int L[n1], R[n2];
    for (int i=0; i<n1; i++) L[i] = a[l+i];
    for (int i=0; i<n2; i++) R[i] = a[mid+1+i];
    int i=0, j=0, k=l, cnt_prev=0, cnt_cur=0, cur=0;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            a[k] = L[i];
            i++;
            if (a[k] > cur) {
                cnt_prev += cnt_cur;
                cnt_cur = 0;
            }
            res += cnt_prev;
        }
        else {
            a[k] = R[j];
            j++;
            if (a[k] > cur) {
                cnt_prev += cnt_cur;
                cnt_cur = 0;
                cur = a[k];
            }
            cnt_cur++;
        }
        k++;
    }
    while (i < n1) {
        a[k] = L[i];
        i++;
        if (a[k] > cur) {
            cnt_prev += cnt_cur;
            cnt_cur = 0;
        }
        res += cnt_prev;
        k++;
    }
    while (j < n2) {
        a[k] = R[j];
        j++;
        k++;
    }
    return res;
}

ll merge_sort(int a[], int l, int r) {
    if (l>=r) return 0;
    int mid = (l+r)/2;
    ll res = 0;
    res += merge_sort(a, l, mid);
    res += merge_sort(a, mid+1, r);
    res += merge(a, l, r);
    return res;
}

ll count_inversions(int n, int a[]) {
    return merge_sort(a, 0, n-1);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif
    int n;
    cin >> n;
    int a[n];
    for (int i=0; i<n; i++) cin >> a[i];
    cout << count_inversions(n, a);
}