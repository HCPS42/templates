#include <bits/stdc++.h>
using namespace std;

struct point {
    double x = 0;
    double y = 0;
    double z = 0;
};

ostream& operator<<(ostream& out, point a) {
    out << a.x << " " << a.y << " " << a.z;
    return out;
}

point operator+(point a, point b) {
    return {a.x + b.x, a.y + b.y, a.z + b.z};
}

void operator+=(point& a, point b) {
    a.x += b.x;
    a.y += b.y;
    a.z += b.z;
}

point operator-(point a, point b) {
    return {a.x - b.x, a.y - b.y, a.z - b.z};
}

point operator/(point a, double b) {
    return {a.x / b, a.y / b, a.z / b};
}

double norm(point a) {
    return a.x * a.x + a.y * a.y + a.z * a.z;
}

double dot(point a, point b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

point cross(point a, point b) {
    return {a.y * b.z - a.z * b.y,
            a.z * b.x - a.x * b.z,
            a.x * b.y - a.y * b.x};
}

int main() {
    return 0;
}
