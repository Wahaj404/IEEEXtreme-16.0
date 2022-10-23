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
    int n;
    cin >> n;
    map<string, pair<int, int>> mp;
    for(int i = 0; i < n; i++) {
        string s;
        cin >> s;
        int x;
        cin >> x;
        for(int j = 0; j < x; j++) {
            string s2;
            cin >> s2;
            mp[s2].first++;
            mp[s].second++;
        }
    }
    int sum = 0;
    int mx = -1;
    for(auto [s, x] : mp) {
        int diff = abs(x.first - x.second);
        sum += diff;
        mx = max(mx, x.second - x.first);
    }
    sum /= 2;
    cout << sum << " " << mx << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);


    #ifndef ONLINE_JUDGE
        in("input.txt");
    #endif

    bool mt =1;
    int tests = 1;
    if (mt) cin >> tests;
    for(int tt = 1; tt <= tests; ++tt)
        solve(tt);
    return 0;
}