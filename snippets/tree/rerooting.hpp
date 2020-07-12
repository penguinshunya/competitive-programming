#include "../template.hpp"

template <typename T, typename Data>
struct ReRooting {
  using M = function<T(T, T)>;
  using L = function<T(T, Data)>;
  struct Edge {
    int to;
    Data data;
  };
  int n;
  L lift;
  M merge;
  vector<vector<Edge>> g;
  vector<vector<T>> dp;
  vector<int> par;
  vector<T> ans;
  ReRooting(int n, M merge, L lift) : n(n), merge(merge), lift(lift) {
    g.resize(n);
  }
  void add_edge(int v, int u, Data e) {
    g[v].push_back((Edge) { u, e });
    g[u].push_back((Edge) { v, e });
  }
  vector<T> solve() {
    dp.resize(n);
    par.assign(n, -1);
    ans.resize(n);
    dfs(0);
    bfs(0);
    return ans;
  }
  T dfs(int v, int p = -1) {
    int m = g[v].size();
    dp[v] = vector<T>(m);
    T ret = T();
    for (int i = 0; i < m; i++) {
      auto e = g[v][i];
      if (e.to == p) {
        par[v] = i;
        continue;
      }
      dp[v][i] = lift(dfs(e.to, v), e.data);
      ret = merge(ret, dp[v][i]);
    }
    return ret;
  }
  void bfs(int v, T t = T()) {
    if (par[v] != -1) {
      dp[v][par[v]] = lift(t, g[v][par[v]].data);
    }
    int m = g[v].size();
    vector<T> dpl(m + 1);
    vector<T> dpr(m + 1);
    for (int i = 0; i < m; i++) {
      dpl[i + 1] = merge(dpl[i], dp[v][i]);
    }
    for (int i = m; i > 0; i--) {
      dpr[i - 1] = merge(dpr[i], dp[v][i - 1]);
    }
    ans[v] = lift(dpr[0], Data());
    for (int i = 0; i < m; i++) {
      if (i == par[v]) continue;
      int u = g[v][i].to;
      bfs(u, merge(dpl[i], dpr[i + 1]));
    }
  }
};