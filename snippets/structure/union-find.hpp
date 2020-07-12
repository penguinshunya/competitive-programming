#include "../template.hpp"

struct UnionFind {
  vector<int> data;
  UnionFind(int n) {
    data.assign(n, -1);
  }
  int root(int k) {
    if (data[k] < 0) return k;
    return data[k] = root(data[k]);
  }
  void unite(int x, int y) {
    x = root(x);
    y = root(y);
    if (x == y) return;
    if (data[x] > data[y]) swap(x, y);
    data[x] += data[y];
    data[y] = x;
  }
  bool same(int x, int y) {
    return root(x) == root(y);
  }
  int size(int k) {
    return -data[root(k)];
  }
};