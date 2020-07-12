#include "../header.hpp"

template <typename T>
struct SegmentTree {
  vector<T> v;
  function<T(T, T)> f;
  T e;
  int n;
  SegmentTree(int size, function<T(T, T)> f, T e) : f(f), e(e) {
    n = 1;
    while (n < size) n <<= 1;
    v.resize(n * 2, e);
  }
  void set(int k, T x) {
    v[k + n] = x;
  }
  void build() {
    for (int i = n - 1; i > 0; i--) {
      v[i] = f(v[i * 2 + 0], v[i * 2 + 1]);
    }
  }
  void update(int k, T x) {
    v[k += n] = x;
    while (k >>= 1) v[k] = f(v[k * 2 + 0], v[k * 2 + 1]);
  }
  T query(int a, int b) {
    T l = e, r = e;
    for (a += n, b += n; a < b; a >>= 1, b >>= 1) {
      if (a & 1) l = f(l, v[a++]);
      if (b & 1) r = f(v[--b], r);
    }
    return f(l, r);
  }
  void reset(int k) {
    update(k, e);
  }
  T operator[](int k) {
    return query(k, k + 1);
  }
};