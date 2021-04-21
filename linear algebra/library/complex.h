#pragma once

#include <bits/stdc++.h>
#include "rational.h"
using namespace std;

typedef complex<frac> comp;
#define x() real()
#define y() imag()

frac abs(const comp& a) {
    return a.x() * a.x() + a.y() * a.y();
}
