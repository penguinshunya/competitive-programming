#include "../template.hpp"

template <int mod>
struct ModInt {
  int x;
  ModInt(): x(0) {}
  ModInt(long long a) { x = a % mod; if (x < 0) x += mod; }
  ModInt &operator+=(ModInt that) { x = (x + that.x) % mod; return *this; }
  ModInt &operator-=(ModInt that) { x = (x + mod - that.x) % mod; return *this; }
  ModInt &operator*=(ModInt that) { x = (long long) x * that.x % mod; return *this; }
  ModInt &operator/=(ModInt that) { return *this *= that.inverse(); }
  ModInt inverse() {
    int a = x, b = mod, u = 1, v = 0;
    while (b) { int t = a / b; a -= t * b; u -= t * v; swap(a, b); swap(u, v); }
    return ModInt(u);
  }
  #define op(o, p) ModInt operator o(ModInt that) { return ModInt(*this) p that; }
    op(+, +=) op(-, -=) op(*, *=) op(/, /=)
  #undef op
  friend ostream& operator<<(ostream &os, ModInt m) { return os << m.x; }
  bool operator==(const ModInt& that) { return x == that.x; }
  bool operator!=(const ModInt& that) { return x != that.x; }
};

using mint = ModInt<1000000007>;