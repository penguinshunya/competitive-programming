#include "../template.hpp"

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
  Matrix<T> inverse() {
    assert(r == c);
    int n = r;
    Matrix<T> m(n, n * 2);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        m[i][j] = v[i][j];
      }
    }
    for (int i = 0; i < n; i++) {
      m[i][i + n] = 1;
    }
    for (int i = 0; i < n; i++) {
      for (int j = i; j < n; j++) {
        if (m[j][i] != (T) 0) {
          swap(m[i], m[j]);
          break;
        }
      }
      T div = m[i][i];
      assert(div != (T) 0);
      for (int j = 0; j < n * 2; j++) {
        m[i][j] /= div;
      }
      for (int j = 0; j < n; j++) {
        if (i == j) continue;
        T mul = m[j][i];
        for (int k = 0; k < n * 2; k++) {
          m[j][k] -= m[i][k] * mul;
        }
      }
    }
    Matrix<T> ret(n, n);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        ret[i][j] = m[i][j + n];
      }
    }
    return ret;
  }
  bool operator==(Matrix<T> that) {
    if (r != that.r) return false;
    if (c != that.c) return false;
    for (int i = 0; i < r; i++) {
      for (int j = 0; j < c; j++) {
        if (v[i][j] != that[i][j]) {
          return false;
        }
      }
    }
    return true;
  }
};