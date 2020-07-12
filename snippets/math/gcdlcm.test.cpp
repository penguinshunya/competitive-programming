#include "gcdlcm.hpp"

int main() {
  assert(gcd(12, 18) == 6);
  assert(gcd(0, 100) == 100);
  assert(gcd(100, 0) == 100);
  assert(gcd(0, 0) == 0);
  assert(lcm(12, 18) == 36);
  assert(lcm(0, 100) == 100);
  assert(lcm(100, 0) == 100);
  assert(lcm(0, 0) == 0);
  return 0;
}