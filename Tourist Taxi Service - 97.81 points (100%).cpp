#include <bits/stdc++.h>

using namespace std;

vector<vector<pair<int, int>>> g;
unordered_map<int, int> dist;

vector<pair<int, int>> dijk;

void dfs(set<pair<int, int>> & st, int u, int c) {
    if (st.size() == 5) {
        if (dist[u] > c) {
            // pq.push({c, u});
            dist[u] = c;
            dijk.emplace_back(c, u);
        }
        return;
    }
    for (auto [v, l] : g[u]) {
        if (st.count({u, v}) || st.count({v, u})) {
            continue;
        }
        st.insert({u, v});
        dfs(st, v, c + l);
        st.erase({u, v});
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    g = vector<vector<pair<int, int>>>(n);
    for (int i = 0; i < m; ++i) {
        int s, d, l;
        cin >> s >> d >> l;
        --s; --d;
        g[s].emplace_back(d, l);
        g[d].emplace_back(s, l);
        dist[s] = dist[d] = INT_MAX;
    }
    set<pair<int, int>> st;
    dfs(st, 0, 0);
    sort(dijk.begin(), dijk.end());
    for (auto [cost, start] : dijk) {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({cost, start});
        while (!pq.empty()) {
            auto [c, u] = pq.top();
            pq.pop();
            for (auto [v, l] : g[u]) {
                auto alt = c + l;
                if (alt < dist[v]) {
                    dist[v] = alt;
                    pq.push({alt, v});
                }
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        cout << dist[i] << '\n';
    }
}