#include "../template.hpp"

template <typename C, typename D>
C max_flow(Graph<C, D> &g, int s, int t) {
  const int n = g.n;

  C flow = 0;
  vector<int> used(n);
  int ui = 0;
  function<C(int, int, C)> dfs = [&](int v, int t, C f) {
    if (v == t) return f;
    used[v] = ui;
    for (int i = 0; i < g[v].size(); i++) {
      auto &e = g[v][i];
      if (used[e.to] == ui || e.cap == 0) continue;
      int d = dfs(e.to, t, min(f, e.cap));
      if (d == 0) continue;
      e.cap -= d;
      g[e.to][e.rev].cap += d;
      return d;
    }
    return 0;
  };
  while (true) {
    ui++;
    int f = dfs(s, t, numeric_limits<C>::max());
    if (f == 0) return flow;
    flow += f;
  }
}