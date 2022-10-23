#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        ll n, L, price;
        cin >> n >> L >> price;

        ++n;
        vector<vector<ll>> arr(n, vector<ll>(2));
        vector<ll> dp(n, -1);
        arr[0] = {L, price};

        for (auto i = 1; i < n; ++i) {
            cin >> arr[i][0] >> arr[i][1];
        }

        for (auto i = n - 1; i >= 0; --i) {
            ll ans = 1e16, r = L, rf = (i > 0) * 500;
            for (auto j = i + 1; j < n; ++j) {
                r -= arr[j][0];
                if (r < 0) {
                    break;
                }
                if (j == n - 1) {
                    ans = rf;
                } else {
                    ans = min(ans, rf + (L - r) * arr[j][1] + dp[j]);
                }
            }
            dp[i] = ans;
        }
        cout << (L * arr[0][1] + dp[0]) << "\n";
    }
    return 0;
}