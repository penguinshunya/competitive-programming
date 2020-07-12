#include "cpt.cpp";

template <typename T>
struct FenwickTree {
  vector<T> v;
  int n;
  FenwickTree(int n) : n(n) {
    v = vector<T>(n);
  }
  void update(int i, T x) {
    for (i++; i <= n; i += i & -i) v[i - 1] += x;
  }
  T query(int i) {
    T r = 0;
    for (; i >= 1; i -= i & -i) r += v[i - 1];
    return r;
  }
};