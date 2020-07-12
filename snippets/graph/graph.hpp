#include "../template.hpp"

template <typename Cap, typename Cost>
struct Graph {
  const Cost INF = numeric_limits<Cost>::max();
  struct Edge {
    int to, rev;
    Cap cap;
    Cost cost;
    Edge(int to, Cap cap, Cost cost, int rev)
      : to(to), cap(cap), cost(cost), rev(rev) {}
  };
  vector<vector<Edge>> g;
  int n;
  Graph(int n) : n(n) {
    g.assign(n, vector<Edge>());
  }
  void add_edge(int v, int u, Cap cap = 1, Cost cost = 0) {
    g[v].emplace_back(u, cap, cost, (int) g[u].size());
    g[u].emplace_back(v, 0, -cost, (int) g[v].size() - 1);
  }
  vector<Edge>& operator[](int x) {
    return g[x];
  }
  Cost min_cost_flow(int s, int t, Cap f) {
    Cost ret = 0;
    while (f > 0) {
      vector<Cost> dist(n, INF);
      vector<int> prevv(n), preve(n);
      dist[s] = 0;
      while (true) {
        bool update = false;
        for (int v = 0; v < n; v++) {
          for (int i = 0; i < g[v].size(); i++) {
            auto &e = g[v][i];
            if (e.cap == 0) continue;
            if (dist[v] == INF || dist[e.to] <= dist[v] + e.cost) continue;
            dist[e.to] = dist[v] + e.cost;
            prevv[e.to] = v, preve[e.to] = i;
            update = true;
          }
        }
        if (!update) break;
      }
      if (dist[t] == INF) return INF;
      Cap cap = f;
      for (int v = t; v != s; v = prevv[v]) {
        cap = min(cap, g[prevv[v]][preve[v]].cap);
      }
      f -= cap;
      ret += cap * dist[t];
      for (int v = t; v != s; v = prevv[v]) {
        auto &e = g[prevv[v]][preve[v]];
        e.cap -= cap;
        g[v][e.rev].cap += cap;
      }
    }
    return ret;
  }
};