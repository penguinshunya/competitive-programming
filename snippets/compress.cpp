#include "header.hpp"

template <typename T>
struct Compress {
  vector<T> v;
  Compress() {}
  Compress(vector<T> _v) : v(_v) {
    build();
  }
  void insert(T x) {
    v.push_back(x);
  }
  void insert(vector<T> x) {
    for (int i = 0; i < (int) x.size(); i++) {
      v.push_back(x[i]);
    }
  }
  void build() {
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
  }
  int get(T x) {
    return lower_bound(v.begin(), v.end(), x) - v.begin();
  }
  int size() {
    return (int) v.size();
  }
  T& operator[](int k) {
    return v[k];
  }
};