#include "cpt.cpp"

long long gcd(long long a, long long b) {
  if (min(a, b) == 0) {
    return max(a, b);
  }
  if (a % b == 0) {
    return b;
  } else {
    return gcd(b, a % b);
  }
}

long long lcm(long long a, long long b) {
  if (min(a, b) == 0) {
    return max(a, b);
  }
  return a / gcd(a, b) * b;
}
