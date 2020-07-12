#include "cpt.cpp";

template <typename Graph>
struct StronglyConnectedComponents {
  Graph &g;
  int n;
  vector<vector<int>> gg;
  vector<vector<int>> rg;
  vector<bool> used;
  vector<int> order;
  vector<int> group;
  StronglyConnectedComponents(Graph &g)
    : g(g), n(g.n), gg(n), rg(n), used(n), order(n), group(n, -1) {
    for (int v = 0; v < n; v++) {
      for (auto e : g[v]) {
        gg[v].emplace_back(e.to);
        rg[e.to].emplace_back(v);
      }
    }
  }
  void dfs1(int v) {
    if (used[v]) return;
    used[v] = true;
    for (int u : gg[v]) dfs1(u);
    order.push_back(v);
  }
  void dfs2(int v, int c) {
    if (group[v] != -1) return;
    group[v] = c;
    for (int u : rg[v]) dfs2(u, c);
  }
  vector<int> build() {
    for (int i = 0; i < n; i++) {
      dfs1(i);
    }
    reverse(order.begin(), order.end());
    int ptr = 0;
    for (int v : order) {
      if (group[v] == -1) dfs2(v, ptr), ptr++;
    }
    return group;
  }
};