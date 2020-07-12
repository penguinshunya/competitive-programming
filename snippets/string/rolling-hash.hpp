#include "../template.hpp"

struct RollingHash {
  const int h = 1000000007;
  const int b = 10007;
  vector<int> ha;
  vector<int> po;
  RollingHash(const string &s) {
    int n = (int) s.size();
    ha.assign(n + 1, 0);
    po.assign(n + 1, 1);
    for (int i = 0; i < n; i++) {
      ha[i + 1] = ((long long) ha[i] * b + s[i]) % h;
      po[i + 1] = ((long long) po[i] * b) % h;
    }
  }
  int get(int l, int r) {
    return (ha[r] + h - ((long long) ha[l] * po[r - l]) % h) % h;
  }
};