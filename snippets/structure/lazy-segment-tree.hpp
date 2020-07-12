#include "../header.hpp"

template <typename T, typename S>
struct LazySegmentTree {
  vector<T> v;
  vector<S> z;
  function<T(T, T)> f;
  function<T(T, S, int)> g;
  function<S(S, S)> h;
  T e;
  S d;
  int n;
  LazySegmentTree(
    int size,
    function<T(T, T)> f,
    function<T(T, S, int)> g,
    function<S(S, S)> h,
    T e, 
    S d
  ) : f(f), g(g), h(h), e(e), d(d) {
    n = 1;
    while (n < size) n <<= 1;
    v.resize(n * 2, e);
    z.resize(n * 2, d);
  }
  void set(int k, T x) {
    v[k + n] = x;
  }
  void build() {
    for (int i = n - 1; i >= 0; i--) {
      v[i] = f(v[i * 2 + 0], v[i * 2 + 1]);
    }
  }
  void propagate(int k, int l, int r) {
    v[k] = g(v[k], z[k], r - l);
    if (k < n) {
      z[k * 2 + 0] = h(z[k * 2 + 0], z[k]);
      z[k * 2 + 1] = h(z[k * 2 + 1], z[k]);
    }
    z[k] = d;
  }
  T update(int a, int b, S x, int k = 1, int l = 0, int r = -1) {
    if (r == -1) r = n;
    propagate(k, l, r);
    if (b <= l || r <= a) return v[k];
    if (a <= l && r <= b) { z[k] = x; propagate(k, l, r); return v[k]; }
    return v[k] = f(
      update(a, b, x, k * 2 + 0, l, (l + r) / 2),
      update(a, b, x, k * 2 + 1, (l + r) / 2, r)
    );
  }
  T query(int a, int b, int k = 1, int l = 0, int r = -1) {
    if (r == -1) r = n;
    propagate(k, l, r);
    if (b <= l || r <= a) return e;
    if (a <= l && r <= b) return v[k];
    return f(
      query(a, b, k * 2 + 0, l, (l + r) / 2),
      query(a, b, k * 2 + 1, (l + r) / 2, r)
    );
  }
};