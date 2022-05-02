friend bool operator!=(const frac& a, const frac& b) { return !(a == b); }
    friend bool operator<(const frac& a, const frac& b) { return a.x * b.y < a.y * b.x; }
    friend bool operator>(const frac& a, const frac& b) { return b < a; }
    friend bool operator<=(const frac& a, const frac& b) { return !(a > b); }
    friend bool operator>=(const frac& a, const frac& b) { return !(a < b); }