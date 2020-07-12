#include "cpt.cpp"

struct HeavyLightDecomposition {
  vector<vector<int>> g;
  vector<int> vid;
  vector<int> out;
  vector<int> head;
  vector<int> par;
  vector<int> ddep;
  HeavyLightDecomposition(vector<vector<int>> g) : g(g) {
    int n = g.size();
    vid = vector<int>(n);
    out = vector<int>(n);
    head = vector<int>(n);
    par = vector<int>(n, -1);
    ddep = vector<int>(n);
    {
      vector<int> size(n);
      auto dfs = [&](auto dfs, int u, int p) -> void {
        size[u] = 1;
        for (auto &v : g[u]) if (v != p) {
          par[v] = u;
          dfs(dfs, v, u);
          size[u] += size[v];
          if (size[v] > size[g[u][0]]) swap(v, g[u][0]);
        }
      };
      dfs(dfs, 0, -1);
    }
    {
      int t = 0;
      auto dfs = [&](auto dfs, int u, int p) -> void {
        vid[u] = t++;
        for (auto v : g[u]) if (v != p) {
          if (v == g[u][0]) {
            head[v] = head[u];
            ddep[v] = ddep[u];
          } else {
            head[v] = v;
            ddep[v] = ddep[u] + 1;
          }
          dfs(dfs, v, u);
        }
        out[u] = t;
      };
      dfs(dfs, 0, -1);
    }
  }
  void for_each(int u, int v, function<void(int, int)> f) {
    while (true) {
      if (ddep[u] > ddep[v]) swap(u, v);
      if (head[u] == head[v]) {
        f(min(vid[u], vid[v]), max(vid[u], vid[v]) + 1);
        return;
      }
      f(vid[head[v]], vid[v] + 1);
      v = par[head[v]];
    }
  }
  void for_each_edge(int u, int v, function<void(int, int)> f) {
    while (true) {
      if (ddep[u] > ddep[v]) swap(u, v);
      if (head[u] == head[v]) {
        f(min(vid[u], vid[v]) + 1, max(vid[u], vid[v]) + 1);
        return;
      }
      f(vid[head[v]], vid[v] + 1);
      v = par[head[v]];
    }
  }
  int lca(int u, int v) {
    while (true) {
      if (ddep[u] > ddep[v]) swap(u, v);
      if (head[u] == head[v]) {
        return vid[u] < vid[v] ? u : v;
      }
      v = par[head[v]];
    }
  }
  pair<int, int> subtree(int u) {
    return make_pair(vid[u], out[u]);
  }
  pair<int, int> subtree_edge(int u) {
    return make_pair(vid[u] + 1, out[u]);
  }
  int operator[](int k) {
    return vid[k];
  }
};