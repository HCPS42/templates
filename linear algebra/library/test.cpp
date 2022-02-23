#include <bits/stdc++.h>
#include "1_int.h"
#include "2_frac.h"
#include "3_comp.h"
#include "4_mint.h"
#include "10_space.h"
using namespace std;

void test_int() {
    Int mx = numeric_limits<int64_t>::max();
    Int mn = numeric_limits<int64_t>::min();
    Int cur = 0;
    cur = mx - 1;
    cur = mn + 1;
    cur = -mx;
    cur = mx / -1;
    //cur = mn - 1;
    //cur = mx + 1;
    //cur = -mn;
    //cur = 2 * mx;
    //cur = 2 * mn;
    //cur = mn / -1;
    assert(mn < mx);
    assert(mx > mn);
    assert(mn <= mx);
    assert(mx >= mn);
    assert(mx <= mx);
    assert(mx >= mx);
    assert(mn == mn);
    assert(mn != mx);
}

void test_frac() {
    
}

void test_comp() {
    Comp<Int> a;
    Comp<frac> b;
    Comp<int64_t> c;
    Comp<Real> d;
}

void test_mint() {

}

void test() {
    test_int();
    test_frac();
    test_comp();
    test_mint();
}

int main() {
    test();
    return 0;
}
