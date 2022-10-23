
/***********

  MK-1311

***********/
#include <bits/stdc++.h>
using namespace std;

void solve();

#define fi second
#define se first
#define pb push_back
#define nl '\n'

#ifdef LOCAL
    #include "debug.h"
#else
    #define debug(...)
#endif

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    // cin >> tt;
    for (int i = 0; i < tt; i++) {
        solve();
    }
    cerr << "time taken : " << (float) clock() / CLOCKS_PER_SEC << " secs"
         << endl;
    return 0;
}

// #define int long long

void solve() {
    int p = 5;
    vector<vector<pair<int, string>>> vec(5);
    int b; // budget
    // input
    cin >> b;
    for (int i = 0; i < p; i++) {
        int cnt;
        vector<pair<int, string>> v;
        cin >> cnt;
        while (cnt--) {
            string s;
            int x;
            cin >> s >> x;
            v.pb({x, s});
        }
        vec[i] = v;
    }
    int diff = INT_MAX;
    vector<string> ans;
    // sort(vec.begin(), vec.end(),
    //      [](auto a, auto b) { return a.size() > b.size(); });
    sort(vec[0].begin(), vec[0].end());
    for (int i = 0; i < (int) vec[4].size(); i++) {
        int si = vec[4][i].se;
        if (si > b) {
            continue;
        }
        for (int j = 0; j < (int) vec[3].size(); j++) {
            int sj = si + vec[3][j].se;
            if (sj > b) {
                continue;
            }
            for (int k = 0; k < (int) vec[2].size(); k++) {
                int sk = sj + vec[2][k].se;
                if (sk > b) {
                    continue;
                }
                for (int l = 0; l < (int) vec[1].size(); l++) {
                    int sl = sk + vec[1][l].se;
                    if (sl > b) {
                        continue;
                    }
                    // loop 5
                    int need = b - sl;
                    int lo = 0, hi = vec[0].size() - 1;
                    while (lo < hi) {
                        int mid = (lo + hi + 1) >> 1;
                        if (vec[0][mid].se > need)
                            hi = mid - 1;
                        else
                            lo = mid;
                    }
                    if (need >= vec[0][lo].se) {
                        int cur_diff = b - sl - vec[0][lo].se;
                        vector<string> alt = {vec[0][lo].fi, vec[1][l].fi,
                                              vec[2][k].fi, vec[3][j].fi,
                                              vec[4][i].fi};
                        if (diff > cur_diff) {
                            diff = cur_diff;
                            ans = alt;
                        } else if (diff == cur_diff) {
                            ans = min(ans, alt);
                        }
                    }
                }
            }
        }
    }
    for (string s : ans) {
        cout << s << endl;
    }
}

/*

*/
