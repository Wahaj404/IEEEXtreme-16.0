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
const ll mod = 1000000007;
const ll INF = ll(1e16);
#define in(File) freopen(File, "r", stdin);
#define out(File) freopen(File, "w", stdout);
vector<vector<int>> edges(100000);
vl a(100000);
vector<bool> vis(1e5 + 1, false);

ll dfs(int u, int v, ll product){
    if (u == v) {
        return (product * a[u]) % mod;
    }
    vis[u] = true;
    ll prod = -1;
    for(auto e : edges[u]) {
        if (!vis[e]) {
            prod = dfs(e, v, (product * a[u]) % mod);
            if (prod != -1) break;
        }
    }
    vis[u] = false;
    return prod;
}

void solve(int test) {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        /* code */
        cin >> a[i];
        edges[i].clear();
        vis[i]=false;
    }
    for(int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        --u;
        --v;
        edges[u].push_back(v);
        edges[v].push_back(u);
    }
    int q;
    cin >> q;
    while (q--) {
        int type, u, v;
        cin >> type >> u >> v;
        if (type == 1) {
            --u;
            a[u] = v;
        } else {
            --u;--v;
            cout << dfs(u,v,1) << "\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    #ifndef ONLINE_JUDGE
        in("input.txt");
    #endif

    bool mt =true;
    int tests = 1;
    if (mt) cin >> tests;
    for(int tt = 1; tt <= tests; ++tt)
        solve(tt);
    return 0;
}