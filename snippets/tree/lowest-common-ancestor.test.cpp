#include "./lowest-common-ancestor.hpp"

int main() {
  freopen("./input/01.txt", "r", stdin);
  freopen("./output/01.txt", "w", stdout);
  int n;
  cin >> n;
  LowestCommonAncestor lca(n);
  rep(u, n) {
    int k;
    cin >> k;
    rep(j, k) {
      int v;
      cin >> v;
      lca.add_edge(u, v);
    }
  }
  lca.build();
  int q;
  cin >> q;
  rep(i, q) {
    int u, v;
    cin >> u >> v;
    cout << lca(u, v) << endl;
  }
  return 0;
}