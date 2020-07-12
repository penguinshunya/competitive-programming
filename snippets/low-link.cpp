#include "header.hpp"

template <typename Graph>
struct LowLink {
  using A = vector<int>;
  using B = vector<pair<int, int>>;
  Graph &g;
  int n;
  vector<bool> seen;
  vector<int> ord, low;
  A articulation;
  B bridge;
  LowLink(Graph &g) : g(g), n(g.n) {}
  void dfs(int v, int p, int &k) {
    seen[v] = true;
    ord[v] = k++;
    low[v] = ord[v];
    bool is = false;
    int cnt = 0;
    for (auto e : g[v]) {
      int u = e.to;
      if (seen[u])  {
        if (u != p) low[v] = min(low[v], ord[u]);
        continue;
      }
      cnt++;
      dfs(u, v, k);
      low[v] = min(low[v], low[u]);
      if (p != -1 && ord[v] <= low[u]) is = true;
      if (ord[v] < low[u]) bridge.emplace_back(minmax(v, u));
    }
    if (p == -1 && cnt > 1) is = true;
    if (is) articulation.push_back(v);
  }
  pair<A, B> build() {
    seen.assign(n, false);
    ord.assign(n, 0);
    low.assign(n, 0);
    articulation.clear();
    bridge.clear();
    int k = 0;
    dfs(0, -1, k);
    return pair<A, B>(articulation, bridge);
  }
};