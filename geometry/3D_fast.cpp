#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define pb push_back
#define ppp pop_back
#define fi first
#define se second
#define pii pair<int,int>

struct point {
	double x = 0, y = 0, z = 0;
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
    ios_base::sync_with_stdio(0); cin.tie(0);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif
	
	return 0;
}
