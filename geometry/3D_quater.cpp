#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

typedef double ftype;
typedef complex<ftype> point;
typedef complex<point> quater;
#define qA real()
#define qB imag()
#define qs qA.real()
#define qx qA.imag()
#define qy qB.real()
#define qz qB.imag()

const ftype pi = acos(-1);
const ftype eps = 1e-9;

quater operator*(quater a, quater b) {
    return {{a.qA * b.qA - a.qB * conj(b.qB)},
            {a.qA * b.qB + a.qB * conj(b.qA)}};
}

quater conj(quater a) {
    return {conj(a.qA), - a.qB};
}

ftype norm(quater a) {
    return (a * conj(a)).qs;
}

ftype abs(quater a) {
    return sqrt(norm(a));
}

quater operator/(quater a, quater b) {
    return a * conj(b) / point(norm(b));
}

quater vec(ftype x, ftype y, ftype z) {
    return {{0, x}, {y, z}};
}

const quater ex = vec(1, 0, 0);
const quater ey = vec(0, 1, 0);
const quater ez = vec(0, 0, 1);

quater vec(quater a) {
    return a -= a.qs;
}

ftype dot(quater a, quater b) {
    return -(a * b).qs;
}

quater cross(quater a, quater b) {
    return vec(a * b);
}

ftype mix(quater a, quater b, quater c) {
    return dot(a, cross(b, c));
}

quater conj(quater a, quater g) {
    return g * a / g;
}

// Кватернион, задающий вращение вокруг i на phi против часовой стрелки.
quater rotation(quater i, ftype phi) {
    return point(cos(phi / 2)) + i * point(sin(phi / 2));
}

// Вращать a вокруг i на phi против часовой стрелке.
quater rotate(quater a, quater i, ftype phi) {
    return conj(a, rotation(i, phi));
}

// Проверка двух кватернионов на равенство.
bool cmp(const quater &a, const quater &b) {
    return abs(a - b) < eps;
}

// Любой вектор, ортогональный данному.
quater ortho(quater v) {
    if(abs(v.qy) > eps)
        return vec(v.qy, -v.qx, 0);
    else
        return vec(v.qz, 0, -v.qx);
}

// Кватернион, задающий вращение от a к b по минимальному углу. 
quater min_rotation(quater a, quater b) {
    a /= abs(a);
    b /= abs(b);
    if(cmp(a, -b)) // Вырожденный случай :(
        return rotation(ortho(b), pi);
    else 
		return conj(a * (a + b));
}

// Угол поворота из [-pi; pi], который задаётся кватернионом.
ftype get_angle(quater a) {
    a /= abs(a);
    return remainder(2 * acos(a.qs), 2 * pi);
}

// Кватернион, задающий вращение, переводящее ось nx в x, ось ny в y и ось [nx, ny] в z.
quater basis_rotation(quater nx, quater ny) {
    nx /= abs(nx);
    ny /= abs(ny);
    quater a = min_rotation(nx, ex);
    ny = conj(ny, a);
    quater b = min_rotation(ny, ey);
    if(cmp(ny, -ey))
        b = rotation(ex, pi);
    return b * a;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
#ifdef LOCAL
	freopen("input.txt", "r", stdin);
#endif
    
	
    return 0;
}
