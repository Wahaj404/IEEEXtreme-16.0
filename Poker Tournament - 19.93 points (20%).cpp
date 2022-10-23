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

void solve(int test) {
    int n, q;
    cin >> n >> q;
    vector<ll> a(n);
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    ll dp[n][51];
    while (q--) {
        ll type, l, r, c;
        cin >> type >> l >> r >> c;
        // --l;
        // --r;
        if (type == 0) {
            for(int i = l; i <= r; ++i) {
                a[i] = c;
            }
        } else if (type == 1) {
            for(int i = l; i <= r; ++i) {
                a[i] = max(a[i],c);
            }
        } else {

            dp[l][1] = a[l];
            dp[l][0] = 1;
            for(int j = 2;j<=c;++j)
                dp[l][j]=0;

            for(int i = l + 1; i <= r; ++i) {
                dp[i][0] = 1;
                for(int j = 1; j <= c; ++j) {
                    dp[i][j] = dp[i - 1][j] + (dp[i - 1][j - 1] * a[i]);
                    dp[i][j] %= mod;
                }
            }
            cout << dp[r][c] << "\n";
        }
    }
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