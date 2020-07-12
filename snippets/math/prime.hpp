#include "../template.hpp"

struct Prime {
  int n;
  vector<int> pri;
  Prime(int n) : n(n) {
    vector<bool> f(n, true);
    f[0] = f[1] = false;
    for (int i = 2; i < n; i++) {
      if (!f[i]) continue;
      pri.push_back(i);
      for (int j = i * 2; j < n; j += i) {
        f[j] = false;
      }
    }
  }
  map<int, int> factor(int k) {
    map<int, int> so;
    for (auto p : pri) {
      while (k % p == 0) k /= p, so[p]++;
    }
    if (k != 1) so[k] = 1;
    return so;
  }
};
