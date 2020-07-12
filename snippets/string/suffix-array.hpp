#include "../template.hpp"

struct SuffixArray {
  vector<int> sa;
  SuffixArray(const string &s) {
    sa = sa_is(s);
  }
  int operator[](int k) {
    return sa[k];
  }
  vector<int> sa_is(const string &s) {
    vector<char> c(s.begin(), s.end());
    c.push_back('\0');
    return sa_is(c, 128);
  }
  template <typename T>
  vector<int> sa_is(vector<T> &s, int k) {
    int n = s.size();
    vector<bool> t(n);
    t[n - 1] = 1;
    for (int i = n - 2; i >= 0; i--) {
      t[i] = s[i] < s[i + 1] || s[i] == s[i + 1] && t[i + 1];
    }
    vector<int> lmss;
    for (int i = 0; i < n; i++) {
      if (is_lms(t, i)) lmss.push_back(i);
    }
    vector<int> sa = induced_sort(s, k, t, lmss);
    int n1 = 0;
    for (int i = 0; i < n; i++) {
      if (is_lms(t, sa[i])) sa[n1++] = sa[i];
    }
    for (int i = n1; i < n; i++) {
      sa[i] = -1;
    }
    int name = 0, prev = -1;
    for (int i = 0; i < n1; i++) {
      int pos = sa[i];
      bool diff = false;
      for (int d = 0; d < n; d++) {
        if (prev == -1 || s[pos + d] != s[prev + d] || t[pos + d] != t[prev + d]) {
          diff = true;
          break;
        } else if (d > 0 && (is_lms(t, pos + d) || is_lms(t, prev + d))) {
          break;
        }
      }
      if (diff) name++, prev = pos;
      pos = (pos % 2 == 0) ? pos / 2 : (pos - 1) / 2;
      sa[n1 + pos] = name - 1;
    }
    vector<int> nums;
    for (int i = n1; i < n; i++) {
      if (sa[i] >= 0) nums.push_back(sa[i]);
    }
    if (name < n1) {
      sa = sa_is(nums, name + 1);
    } else {
      for (int i = 0; i < n1; i++) {
        sa[nums[i]] = i;
      }
    }
    vector<int> seed;
    for (int i = 0; i < n1; i++) {
      seed.push_back(lmss[sa[i]]);
    }
    return induced_sort(s, k, t, seed);
  }
  template <typename T>
  vector<int> induced_sort(vector<T> &s, int k, vector<bool> &t, vector<int> &lmss) {
    int n = s.size();
    vector<int> sa(n, -1);
    vector<int> bin(k + 1);
    for (int i = 0; i < n; i++) bin[s[i] + 1]++;
    for (int i = 0; i < k; i++) bin[i + 1] += bin[i];
    vector<int> cnt(k);
    for (int i = lmss.size() - 1; i >= 0; i--) {
      auto c = s[lmss[i]];
      sa[bin[c + 1] - cnt[c] - 1] = lmss[i];
      cnt[c]++;
    }
    cnt.assign(k, 0);
    for (int i = 0; i < n; i++) {
      if (sa[i] <= 0 || t[sa[i] - 1]) continue;
      auto c = s[sa[i] - 1];
      sa[bin[c] + cnt[c]] = sa[i] - 1;
      cnt[c]++;
    }
    cnt.assign(k, 0);
    for (int i = n - 1; i >= 0; i--) {
      if (sa[i] <= 0 || !t[sa[i] - 1]) continue;
      auto c = s[sa[i] - 1];
      sa[bin[c + 1] - cnt[c] - 1] = sa[i] - 1;
      cnt[c]++;
    }
    return sa;
  }
  inline bool is_lms(vector<bool> &t, int i) {
    return i > 0 && t[i] && !t[i - 1];
  }
};