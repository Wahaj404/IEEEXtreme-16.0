/***********

  MK-1311

***********/
#include <bits/stdc++.h>
using namespace std;

void solve();

#define fi first
#define se second
#define pb push_back
#define nl '\n'

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...)
#endif

int32_t main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int tt = 1; 
  // cin >> tt;
  for(int i = 0; i < tt; i++) {
    solve();
  }
  cerr << "time taken : " << (float)clock() / CLOCKS_PER_SEC << " secs" << endl;
  return 0;
}


#define int long long 


long long binpow(long long a, long long b, long long m) {
    a %= m;
    long long res = 1LL;
    while (b > 0LL) {
        if (b & 1LL)
            res = res * a % m;
        a = a * a % m;
        b >>= 1LL;
    }
    return res;
}

const long long mod = 1e9 + 7;


void solve() {
  int n, m;
  cin >> n >> m;
  vector<int> a(n);
  for(int i = 0; i < n; i++) {
    cin >> a[i];
  }
  sort(a.rbegin(), a.rend());
  int wId = 0, ans = 0, need = 0, jId = 0;
  int prevNeed = 0;
  int prev = 0;
  while(jId < n) {
    if(wId == 0) {
      debug(jId);
      debug(m);
      need = 1LL;
      prevNeed = a[jId];
      prev = a[jId];
      ans = (ans +  binpow(2LL, a[jId],  mod)) % mod;
      wId = (wId + 1LL) % m;
      jId++;
      continue;
    }
    if(prev != a[jId]) {
      if(prev - a[jId] > 16 || a[jId] == 0) break;
      need = ((1 << (prev - a[jId])) * need) % mod;
      prev = a[jId];
    }
    need--;
    if(need == 0) {
      wId = (wId + 1LL) % m;
      need = (1 << (prevNeed - a[jId])) % mod;
    }
    jId++;
  }
  cout << ans << endl;
}

/*o

*/  


