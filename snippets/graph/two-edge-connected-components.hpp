#include "../template.hpp"

template <typename Graph>
struct TwoEdgeConnectedComponents {
  using B = vector<pair<int, int>>;
  Graph &g;
  int n;
  vector<bool> seen;
  vector<int> group;
  set<pair<int, int>> b;
  TwoEdgeConnectedComponents(Graph &g) : g(g), n(g.n), group(n) {}
  void dfs(int v, int p, int k) {
    seen[v] = true;
    group[v] = k;
    for (auto e : g[v]) {
      int u = e.to;
      if (u == p) continue;
      if (seen[u]) continue;
      if (b.find(minmax(v, u)) != b.end()) continue;
      dfs(u, v, k);
    }
  }
  vector<int> decompose(B bridge) {
    seen.assign(n, false);
    b.clear();
    b.insert(bridge.begin(), bridge.end());
    int k = 0;
    for (int i = 0; i < n; i++) {
      if (seen[i]) continue;
      dfs(i, -1, k++);
    }
    return group;
  }
};