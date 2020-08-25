#include <bits/stdc++.h>
using namespace std;

struct lint {
	static const int base = 1000000000;
	static const int base_digits = 9;
	static const int small_base = 1000000;
	static const int small_base_digits = 6;
	int sign;
	vector<int> a;
	lint() : sign(1) {}
	lint(int64_t b) {
		*this = b;
	}
	lint(const string& b) {
		read(b);
	}
	void read(const string& b) {
		sign = 1;
		a.clear();
		int ptr = 0;
		while (ptr < b.size() && (b[ptr] == '-' || b[ptr] == '+')) {
			if (b[ptr] == '-') {
				sign = -sign;
			}
			ptr++;
		}
		for (int i = b.size() - 1; i >= ptr; i -= base_digits) {
			int x = 0;
			for (int j = max(ptr, i - base_digits + 1); j <= i; j++) {
				x = x * 10 + b[j] - '0';
			}
			a.push_back(x);
		}
		trim();
    }
	friend istream& operator>>(istream& in, lint& a) {
		string b;
		in >> b;
		a.read(b);
		return in;
	}
	friend ostream& operator<<(ostream& out, lint& a) {
		if (a.sign == -1) {
			out << "-";
		}
		out << (a.a.empty() ? 0 : a.a.back());
		for (int i = (int) a.a.size() - 2; i >= 0; i--) {
			out << setw(base_digits) << setfill('0') << a.a[i];
		}
		return out;
    }
	void trim() {
		while (!a.empty() && !a.back()) {
			a.pop_back();
		}
		if (a.empty()) {
			sign = 1;
		}
	}
	bool is_zero() const {
		return a.empty() || (a.size() == 1 && !a[0]);
	}
	lint abs() const {
		lint res = *this;
		res.sign = 1;
		return res;
	}
	explicit operator int64_t() const {
		int64_t res = 0;
		for (int i = a.size() - 1; i >= 0; i--) {
			res = res * base + a[i];
		}
		return res * sign;
	}
	void operator=(const lint& b) {
		sign = b.sign;
		a = b.a;
	}
	void operator=(int64_t b) {
		sign = 1;
		a.clear();
		if (b < 0) {
			sign = -1;
			b = -b;
		}
		do {
			a.push_back(b % base);
			b /= base;
		} while (b);
	}
	lint operator+(const lint& b) const {
		if (sign != b.sign) {
			return *this - (-b);
		}
		lint res = b;
		for (int i = 0, carry = 0; i < max(a.size(), b.a.size()) || carry; i++) {
			if (i == res.a.size()) {
				res.a.push_back(0);
			}
			res.a[i] += carry + (i < a.size() ? a[i] : 0);
			carry = res.a[i] >= base;
			if (carry) res.a[i] -= base;
		}
		return res;
	}
	lint operator-(const lint& b) const {
		if (sign != b.sign) {
			return *this + (-b);
		}
		if (abs() < b.abs()) {
			return -(b - *this);
		}
		lint res = *this;
		for (int i = 0, carry = 0; i < b.a.size() || carry; i++) {
			res.a[i] -= carry + (i < b.a.size() ? b.a[i] : 0);
			carry = res.a[i] < 0;
			if (carry) res.a[i] += base;
		}
		res.trim();
		return res;
	}
	void operator*=(int64_t b) {
		if (b < 0) {
			sign = -sign;
			b = -b;
		}
		for (int i = 0, carry = 0; i < a.size() || carry; i++) {
			if (i == a.size()) {
				a.push_back(0);
			}
			int64_t cur = a[i] * (int64_t) b + carry;
			carry = cur / base;
			a[i] = cur % base;
			// asm("divl %%ecx" : "=a"(carry), "=d"(a[i]) : "A"(cur), "c"(base));
		}
		trim();
    }
	lint operator*(int64_t b) const {
		lint res = *this;
		res *= b;
		return res;
	}
	friend pair<lint, lint> div_mod(const lint& A, const lint& B) {
		int norm = base / (B.a.back() + 1);
		lint a = A.abs() * norm;
		lint b = B.abs() * norm;
		lint q;
		lint r;
		q.a.resize(a.a.size());
		for (int i = a.a.size() - 1; i >= 0; i--) {
			r *= base;
			r += a.a[i];
			int x = r.a.size() <= b.a.size() ? 0 : r.a[b.a.size()];
			int y = r.a.size() <= b.a.size() - 1 ? 0 : r.a[b.a.size() - 1];
			int d = ((int64_t) base * x + y) / b.a.back();
			r -= b * d;
			while (r < 0) {
				r += b;
				d--;
			}
			q.a[i] = d;
		}
		q.sign = A.sign * B.sign;
		r.sign = A.sign;
		q.trim();
		r.trim();
		return {q, r / norm};
    }
	lint operator/(const lint& b) const {
		return div_mod(*this, b).first;
	}
	lint operator%(const lint& b) const {
		return div_mod(*this, b).second;
	}
	void operator/=(int b) {
		if (b < 0) {
			sign = -sign;
			b = -b;
		}
		for (int i = a.size() - 1, rem = 0; i >= 0; i--) {
			int64_t cur = a[i] + rem * (int64_t) base;
			a[i] = cur / b;
			rem = cur % b;
		}
		trim();
	}
	lint operator/(int b) const {
		lint res = *this;
		res /= b;
		return res;
	}
	int operator%(int b) const {
		if (b < 0) b = -b;
		int res = 0;
		for (int i = a.size() - 1; i >= 0; i--) {
			res = (a[i] + res * (int64_t) base) % b;
		}
		return res * sign;
    }
	void operator+=(const lint& b) {
		*this = *this + b;
	}
	void operator-=(const lint& b) {
		*this = *this - b;
	}
	void operator*=(const lint& b) {
		*this = *this * b;
	}
	void operator/=(const lint& b) {
		*this = *this / b;
	}
	bool operator<(const lint& b) const {
		if (sign != b.sign) {
			return sign < b.sign;
		}
		if (a.size() != b.a.size()) {
			return a.size() * sign < b.a.size() * b.sign;
		}
		for (int i = a.size() - 1; i >= 0; i--) {
			if (a[i] != b.a[i]) {
				return a[i] * sign < b.a[i] * sign;
			}
		}
		return 0;
    }
	bool operator>(const lint& b) const {
		return b < *this;
	}
	bool operator<=(const lint& b) const {
		return !(b < *this);
	}
	bool operator>=(const lint& b) const {
		return !(*this < b);
	}
	bool operator==(const lint& b) const {
		return !(*this < b) && !(b < *this);
	}
	bool operator!=(const lint& b) const {
		return *this < b || b < *this;
	}
	lint operator-() const {
		lint res = *this;
		res.sign = -sign;
		return res;
	}
	static vector<int> convert_base(const vector<int>& a, int old_digits, int new_digits) {
		vector<int64_t> b(max(old_digits, new_digits) + 1);
		b[0] = 1;
		for (int i = 1; i < b.size(); i++) {
			b[i] = b[i - 1] * 10;
		}
		vector<int> res;
		int64_t cur = 0;
		int cur_digits = 0;
		for (int i = 0; i < a.size(); i++) {
			cur += a[i] * b[cur_digits];
			cur_digits += old_digits;
			while (cur_digits >= new_digits) {
				res.push_back(cur % b[new_digits]);
				cur /= b[new_digits];
				cur_digits -= new_digits;
			}
		}
		res.push_back(cur);
		while (!res.empty() && !res.back()) {
			res.pop_back();
		}
		return res;
	}
	typedef vector<int64_t> vll;
	static vll karatsuba_mult(const vll& a, const vll& b) {
		int n = a.size();
		vll res(n + n);
		if (n <= 32) {
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					res[i + j] += a[i] * b[j];
				}
			}
			return res;
		}
		int k = n >> 1;
		vll a1(a.begin(), a.begin() + k);
		vll a2(a.begin() + k, a.end());
		vll b1(b.begin(), b.begin() + k);
		vll b2(b.begin() + k, b.end());
		vll a1b1 = karatsuba_mult(a1, b1);
		vll a2b2 = karatsuba_mult(a2, b2);
		for (int i = 0; i < k; i++) {
			a2[i] += a1[i];
			b2[i] += b1[i];
		}
		vll c = karatsuba_mult(a2, b2);
		for (int i = 0; i < a1b1.size(); i++) {
			c[i] -= a1b1[i];
		}
		for (int i = 0; i < a2b2.size(); i++) {
			c[i] -= a2b2[i];
		}
		for (int i = 0; i < c.size(); i++) {
			res[i + k] += c[i];
		}
		for (int i = 0; i < a1b1.size(); i++) {
			res[i] += a1b1[i];
		}
		for (int i = 0; i < a2b2.size(); i++) {
			res[i + n] += a2b2[i];
		}
		return res;
	}
	lint operator*(const lint& B) const {
		vector<int> a6 = convert_base(this->a, base_digits, small_base_digits);
		vector<int> b6 = convert_base(B.a, base_digits, small_base_digits);
		vll a(a6.begin(), a6.end());
		vll b(b6.begin(), b6.end());
		while (a.size() < b.size()) {
			a.push_back(0);
		}
		while (b.size() < a.size()) {
			b.push_back(0);
		}
		while (a.size() & (a.size() - 1)) {
			a.push_back(0);
			b.push_back(0);
		}
		vll c = karatsuba_mult(a, b);
		lint res;
		res.sign = sign * B.sign;
		for (int i = 0, carry = 0; i < c.size(); i++) {
			int64_t cur = c[i] + carry;
			res.a.push_back(cur % small_base);
			carry = cur / small_base;
		}
		res.a = convert_base(res.a, small_base_digits, base_digits);
		res.trim();
		return res;
	}
	lint pow(lint b) const {
		lint res = 1;
		lint a = *this;
		while (!b.is_zero()) {
			if (b % 2) res *= a;
			a *= a;
			b /= 2;
		}
		return res;
	}
	int size() const {
		if (a.empty()) return 0;
		int res = (a.size() - 1) * base_digits;
		int b = a.back();
		while (b) {
			res++;
			b /= 10;
		}
		return res;
	}
	string to_string() {
		stringstream a;
		a << *this;
		string b;
		a >> b;
		return b;
	}
	friend lint gcd(const lint& a, const lint& b) {
		return b.is_zero() ? a : gcd(b, a % b);
	}
	friend lint lcm(const lint& a, const lint& b) {
		return a / gcd(a, b) * b;
	}
};

int main() {
	return 0;
}
