#include <bits/stdc++.h>
using namespace std;

using ull = unsigned long long;
using ll = long long;
using vl = vector<ll>;
using vb = vector<bool>;
using vi = vector<int>;
using vvi = vector<vi>;
using vvl = vector<vl>;
using vi = vector<int>;
using vs = vector<string>;
using vb = vector<bool>;
using vvb = vector<vb>;
const ll mod = 998244353;
const ll INF = ll(1e16);
#define in(File) freopen(File, "r", stdin);
#define out(File) freopen(File, "w", stdout);


ll n, m;
ll P[500005], dp[500005];


void solve(int test) {

    cin >> n >> m;

    dp[0] = 1;
    dp[1] = m;
    for(int i = 2; i <= n; ++i) {
        dp[i] = (2 * m) % mod * dp[i - 1];
        ll sub = m * dp[i - 2];
        dp[i] %= mod;
        sub %= mod;
        dp[i] = (dp[i] - sub + mod) % mod;
    }
    cout << dp[n / 2] << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    #ifndef ONLINE_JUDGE
        in("input.txt");
    #endif

    bool mt =false;
    int tests = 1;
    if (mt) cin >> tests;
    for(int tt = 1; tt <= tests; ++tt)
        solve(tt);
    return 0;
}