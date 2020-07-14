#include "./matrix.hpp"
#include "./modint.hpp"

int main() {
  Matrix<mint> m({
    {  1,  1, -1 },
    { -2,  0,  1 },
    {  0,  2,  1 },
  });
  auto inv = m.inverse();
  // 
  Matrix<mint> result({
    { (mint) -1 / 2, (mint) -3 / 4, (mint) 1 / 4 },
    { (mint)  1 / 2, (mint)  1 / 4, (mint) 1 / 4 },
    { (mint)     -1, (mint) -1 / 2, (mint) 1 / 2 },
  });
  assert(inv == result);
  return 0;
}