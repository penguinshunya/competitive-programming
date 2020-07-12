#include "../template.hpp"
#include "modint.cpp"

template <typename T>
struct ModCalc {
  vector<T> facc;
  vector<T> finv;
  ModCalc(int max) {
    facc.resize(max + 1);
    finv.resize(max + 1);
    facc[0] = 1;
    for (int i = 0; i < max; i++) {
      facc[i + 1] = facc[i] * (i + 1);
    }
    finv[max] = (T) 1 / facc[max];
    for (int i = max; i > 0; i--) {
      finv[i - 1] = finv[i] * i;
    }
  }
  T com(int a, int b) {
    if (a < 0 || b < 0 || b > a) return 0;
    return facc[a] * finv[a - b] * finv[b];
  }
};

using mcalc = ModCalc<mint>;