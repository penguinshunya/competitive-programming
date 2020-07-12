#include "../header.hpp"

template <typename T>
struct Matrix {
  vector<vector<T>> v;
  int r, c;
  Matrix(int r, int c) : r(r), c(c) {
    v.assign(r, vector<T>(c));
  }
  Matrix(vector<vector<T>> v) : v(v) {
    assert(v.size() > 0 && v[0].size() > 0);
    r = v.size();
    c = v[0].size();
  }
  vector<T>& operator[](int x) {
    return v[x];
  }
  Matrix<T> operator*=(Matrix<T> that) {
    assert(c == that.r);
    auto ret = Matrix<T>(r, that.c);
    for (int i = 0; i < r; i++) {
      for (int j = 0; j < that.c; j++) {
        for (int k = 0; k < c; k++) {
          ret[i][j] += v[i][k] * that[k][j];
        }
      }
    }
    return *this = ret;
  }
  Matrix<T> operator*(Matrix<T> that) {
    return Matrix(*this) *= that;
  }
  Matrix<T> pow(long long n) {
    assert(r == c);
    auto ret = Matrix<T>(r, c);
    for (int i = 0; i < r; i++) {
      ret[i][i] = 1;
    }
    auto temp = *this;
    while (n) {
      if (n & 1) ret *= temp;
      n >>= 1;
      temp *= temp;
    }
    return ret;
  }
  Matrix<T> transpose() {
    Matrix<T> ret(c, r);
    for (int i = 0; i < r; i++) {
      for (int j = 0; j < c; j++) {
        ret[j][i] = v[i][j];
      }
    }
    return ret;
  }
};