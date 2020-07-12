#include "header.hpp"

struct LowestCommonAncestor {
  vector<vector<int>> g;
  int n;
  int l = 0;
  vector<vector<int>> par;
  vector<int> dep;
  LowestCommonAncestor(int n) : n(n), g(n), dep(n) {
    while ((1 << l) < n) l++;
    par.assign(n + 1, vector<int>(l, n));
  }
  void add_edge(int u, int v) {
    g[u].push_back(v);
    g[v].push_back(u);
  }
  void build(int root = 0) {
    auto dfs = [&](auto dfs, int u, int p, int d) -> void {
      if (p != -1) par[u][0] = p;
      dep[u] = d;
      for (auto v : g[u]) if (v != p) {
        dfs(dfs, v, u, d + 1);
      }
    };
    dfs(dfs, root, -1, 0);
    for (int i = 0; i < l - 1; i++) {
      for (int u = 0; u < n; u++) {
        par[u][i + 1] = par[par[u][i]][i];
      }
    }
  }
  int operator()(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    int gap = dep[u] - dep[v];
    for (int i = l - 1; i >= 0; i--) {
      if ((1 << i) & gap) u = par[u][i];
    }
    if (u == v) return u;
    for (int i = l - 1; i >= 0; i--) {
      int pv = par[u][i];
      int pu = par[v][i];
      if (pv != pu) u = pv, v = pu;
    }
    return par[u][0];
  }
  int dist(int u, int v) {
    int a = (*this)(u, v);
    return dep[u] + dep[v] - dep[a] * 2;
  }
};