#include "./modint.hpp"

int main() {
  mint a;
  mint b;
  a = 0, b = 0;
  assert(a == b);
  a = 0, b = 1;
  assert(a != b);
  return 0;
}