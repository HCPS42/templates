#include <bits/stdc++.h>
using namespace std;

struct frac {
    int64_t x = 0;
    int64_t y = 1;
    void norm() {
        if (!y) {
            x = 1;
            return;
        }
        if (y < 0) {
            x *= -1;
            y *= -1;
        }
        int64_t d = __gcd(x, y);
        if (d < 0) d *= -1;
        x /= d;
        y /= d;
    }
    frac(int64_t x_ = 0, int64_t y_ = 1) : x(x_), y(y_) {
        norm();
    }
    friend istream& operator>>(istream& in, frac& a) {
        int64_t x;
        in >> x;
        a = {x, 1};
        return in;
    }
    friend ostream& operator<<(ostream& out, frac a) {
        return out << "(" << (a.x >= 0 ? " " : "-") <<
                   (to_string(abs(a.x)).size() == 1 ? " " : "") << abs(a.x) << " / " <<
                   (to_string(abs(a.y)).size() == 1 ? " " : "") << abs(a.y) << ")";
    }
    frac operator-() const {
        return {-x, y};
    }
    frac& operator+=(const frac& a) {
        x = x * a.y + a.x * y;
        y *= a.y;
        norm();
        return *this;
    }
    frac& operator-=(const frac& a) {
        x = x * a.y - a.x * y;
        y *= a.y;
        norm();
        return *this;
    }
    frac& operator*=(const frac& a) {
        x *= a.x;
        y *= a.y;
        norm();
        return *this;
    }
    frac& operator/=(const frac& a) {
        x *= a.y;
        y *= a.x;
        norm();
        return *this;
    }
    friend frac operator+(frac a, const frac& b) {
        return a += b;
    }
    friend frac operator-(frac a, const frac& b) {
        return a -= b;
    }
    friend frac operator*(frac a, const frac& b) {
        return a *= b;
    }
    friend frac operator/(frac a, const frac& b) {
        return a /= b;
    }
    friend bool operator==(const frac& a, const frac& b) {
        return a.x == b.x && a.y == b.y;
    }
    friend bool operator!=(const frac& a, const frac& b) {
        return !(a == b);
    }
    friend bool operator<(const frac& a, const frac& b) {
        return a.x * b.y < a.y * b.x;
    }
    friend bool operator>(const frac& a, const frac& b) {
        return b < a;
    }
    friend bool operator<=(const frac& a, const frac& b) {
        return !(a > b);
    }
    friend bool operator>=(const frac& a, const frac& b) {
        return !(a < b);
    }
    friend frac sq(frac x) {
        return x * x;
    }
    friend frac abs(frac x) {
        if (x < 0) x *= -1;
        return x;
    }
};

template <class T>
struct Vec {
    vector<T> a;
    Vec() = default;
    Vec(int n) {
        a.resize(n, 0);
    }
    Vec(const vector<T>& b) : a(b) {
    }
    int size() const {
        return a.size();
    }
    T& operator[](int i) {
        return a[i];
    }
    const T& operator[](int i) const {
        return a[i];
    }
    Vec& operator+=(const Vec& b) {
        for (int i = 0; i < size(); i++) {
            a[i] += b[i];
        }
        return *this;
    }
    Vec& operator-=(const Vec& b) {
        for (int i = 0; i < size(); i++) {
            a[i] -= b[i];
        }
        return *this;
    }
    Vec& operator*=(const T& b) {
        for (int i = 0; i < size(); i++) {
            a[i] *= b;
        }
        return *this;
    }
    Vec& operator/=(const T& b) {
        for (int i = 0; i < size(); i++) {
            a[i] /= b;
        }
        return *this;
    }
    friend Vec operator+(Vec a, const Vec& b) {
        return a += b;
    }
    friend Vec operator-(Vec a, const Vec& b) {
        return a -= b;
    }
    friend Vec operator*(Vec a, const T& b) {
        return a *= b;
    }
    friend Vec operator*(const T& a, Vec b) {
        return b *= a;
    }
    friend Vec operator/(Vec a, const T& b) {
        return a /= b;
    }
    friend bool operator==(const Vec& a, const Vec& b) {
        return a.a == b.a;
    }
    friend ostream& operator<<(ostream& ou, const Vec& b) {
        ou << "(";
        for (int i = 0; i < b.size(); i++) {
            if (i) ou << ", ";
            ou << b[i];
        }
        ou << ")";
        return ou;
    }
};

template <class T>
struct Mat {
    vector<Vec<T>> a;
    Mat() = default;
    Mat(int n, int m) {
        a.resize(n, m);
    }
    Mat(const vector<vector<T>>& b) {
        a.resize(b.size());
        for (int i = 0; i < a.size(); i++) {
            a[i] = b[i];
        }
    }
    Mat(const vector<Vec<T>>& b) : a(b) {
    }
    Mat(const Vec<T>& b) {
        a.resize(b.size(), 1);
        for (int i = 0; i < a.size(); i++) {
            a[i][0] = b[i];
        }
    }
    int rows() const {
        return a.size();
    }
    int cols() const {
        return a[0].size();
    }
    Vec<T>& operator[](int i) {
        return a[i];
    }
    const Vec<T>& operator[](int i) const {
        return a[i];
    }
    Mat& operator+=(const Mat& b) {
        for (int i = 0; i < rows(); i++) {
            a[i] += b[i];
        }
        return *this;
    }
    Mat& operator-=(const Mat& b) {
        for (int i = 0; i < rows(); i++) {
            a[i] -= b[i];
        }
        return *this;
    }
    Mat& operator*=(const Mat& b) {
        Mat c(rows(), b.cols());
        for (int i = 0; i < c.rows(); i++) {
            for (int j = 0; j < c.cols(); j++) {
                for (int k = 0; k < cols(); k++) {
                    c[i][j] += a[i][k] * b[k][j];
                }
            }
        }
        return *this = c;
    }
    Mat& operator*=(const T& b) {
        for (Vec<T>& i : a) {
            i *= b;
        }
        return *this;
    }
    friend Mat operator+(Mat a, const Mat& b) {
        return a += b;
    }
    friend Mat operator-(Mat a, const Mat& b) {
        return a -= b;
    }
    friend Mat operator*(Mat a, const Mat& b) {
        return a *= b;
    }
    friend Mat operator*(Mat a, const T& b) {
        return a *= b;
    }
    friend Mat operator*(const T& a, Mat b) {
        return b *= a;
    }
    friend bool operator==(const Mat& a, const Mat& b) {
        return a.a == b.a;
    }
    friend ostream& operator<<(ostream& ou, const Mat& b) {
        for (int i = 0; i < b.rows(); i++) {
            for (int j = 0; j < b.cols(); j++) {
                ou << b[i][j] << " ";
            }
            ou << "\n";
        }
        return ou;
    }
    Mat t() {
        Mat b(cols(), rows());
        for (int i = 0; i < b.rows(); i++) {
            for (int j = 0; j < b.cols(); j++) {
                b[i][j] = a[j][i];
            }
        }
        return b;
    }
    static Mat I(int n) {
        Mat b(n, n);
        for (int i = 0; i < n; i++) {
            b[i][i] = 1;
        }
        return b;
    }
    static Mat O(int n, int m = -1) {
        if (m == -1) {
            return Mat(n, n);
        }
        return Mat(n, m);
    }
};

template <class T>
struct SLE {
    Mat<T> a;
    Vec<T> b;
    SLE() = default;
    SLE(const Mat<T>& a, const Vec<T>& b) : a(a), b(b) {}
    friend bool operator==(const SLE& a, const SLE& b) {
        return a.a == b.a && a.b == b.b;
    }
    int rows() const {
        return a.rows();
    }
    int cols() const {
        return a.cols();
    }
    int rank() const {
        int res = 0;
        for (int i = 0; i < rows(); i++) {
            bool nonz = 0;
            for (int j = 0; j < cols(); j++) {
                if (a[i][j] != 0) {
                    nonz = 1;
                    break;
                }
            }
            if (nonz) res++;
            else if (b[i] != 0) {
                return -1;
            }
        }
        return res;
    }
    friend ostream& operator<<(ostream& ou, const SLE& sle) {
        ou << "rank: " << sle.rank();
        if (sle.rank() == -1) {
            ou << " (inconsistent system)";
        }
        ou << "\n";
        for (int i = 0; i < sle.rows(); i++) {
            for (int j = 0; j < sle.cols(); j++) {
                ou << sle.a[i][j] << " ";
            }
            ou << "| " << sle.b[i] << "\n";
        }
        return ou;
    }
};

template <class T>
void gauss(SLE<T>& sle) {
    Mat<T>& a = sle.a;
    Vec<T>& b = sle.b;
    int m = a.rows();
    int n = a.cols();
    int r = 0, c = 0;
    while (r < m && c < n) {
        T mx = 0;
        int id = r;
        for (int i = r; i < m; i++) {
            if (abs(a[i][c]) > mx) {
                mx = abs(a[i][c]);
                id = i;
            }
        }
        swap(a[id], a[r]);
        swap(b[id], b[r]);
        if (a[r][c] == 0) {
            c++;
            continue;
        }
        T pivot = a[r][c];
        for (int j = c; j < n; j++) {
            a[r][j] /= pivot;
        }
        b[r] /= pivot;
        for (int i = 0; i < m; i++) {
            if (i == r) continue;
            T coef = a[i][c];
            for (int j = c; j < n; j++) {
                a[i][j] -= coef * a[r][j];
            }
            b[i] -= coef * b[r];
        }
        r++;
        c++;
    }
    int sz = sle.rank();
    if (sz >= 0) {
        sle.a.a.resize(sz);
        sle.b.a.resize(sz);
    }
}

template <class T>
Mat<T> inverse(Mat<T> a) {
    int n = a.rows();
    Mat<T> b = Mat<T>::I(n);
    int r = 0, c = 0;
    while (r < n && c < n) {
        T mx = 0;
        int id = r;
        for (int i = r; i < n; i++) {
            if (abs(a[i][c]) > mx) {
                mx = abs(a[i][c]);
                id = i;
            }
        }
        swap(a[id], a[r]);
        swap(b[id], b[r]);
        if (a[r][c] == 0) {
            c++;
            continue;
        }
        T pivot = a[r][c];
        for (int j = c; j < n; j++) {
            a[r][j] /= pivot;
        }
        b[r] /= pivot;
        for (int i = 0; i < n; i++) {
            if (i == r) continue;
            T coef = a[i][c];
            for (int j = c; j < n; j++) {
                a[i][j] -= coef * a[r][j];
            }
            b[i] -= coef * b[r];
        }
        r++;
        c++;
    }
    return b;
}

int main() {
    return 0;
}
