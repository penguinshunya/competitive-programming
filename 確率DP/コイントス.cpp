#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (n); i++)
#define rrep(i, n) for (int i = (n) - 1; i >= 0; i--)
#define reps(i, n) for (int i = 1; i <= (n); i++)
#define rreps(i, n) for (int i = (n); i >= 1; i--)
#define repi(i, a, b) for (int i = (a); i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define bit(b) (1ull << (b))

using namespace std;
using i32 = int;
using i64 = long long;
using f64 = double;
using vi32 = vector<i32>;
using vi64 = vector<i64>;
using vf64 = vector<f64>;
using vstr = vector<string>;

template<typename T, typename S> void amax(T &x, S y) { if (x < y) x = y; }
template<typename T, typename S> void amin(T &x, S y) { if (y < x) x = y; }

f64 dp[2010][2010];

void solve(int n, int K) {
  dp[1][1] = 1;
  rep(i, n) rep(j, n) {
    dp[i + 1][1] += dp[i][j] * 0.5;
    if (j + 1 < K) dp[i + 1][j + 1] += dp[i][j] * 0.5;
  }
  f64 ans = 0;
  rep(j, K) ans += dp[n][j];
  cout << 1.0 - ans << endl;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout << fixed << setprecision(16);
  int n, k;
  cin >> n >> k;
  solve(n, k);
  return 0;
}
