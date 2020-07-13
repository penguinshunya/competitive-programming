#include "./z-algorithm.hpp"

int main() {
  freopen("./input/01.txt", "r", stdin);
  freopen("./output/01.txt", "w", stdout);
  string t, p;
  cin >> t >> p;
  int n = (int) t.size();
  t = p + t;
  auto za = z_algorithm(t);
  for (int i = p.size(); i < n + p.size(); i++) {
    if (za[i] >= p.size()) {
      cout << i - p.size() << endl;
    }
  }
  return 0;
}