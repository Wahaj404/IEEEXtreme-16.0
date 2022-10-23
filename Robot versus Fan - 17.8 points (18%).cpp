#include <bits/stdc++.h>

using namespace std;

pair<int, int> next(int x, int y, char ch) {
    switch (ch) {
        case '>':
            return {x, y + 1};
        case '<':
            return {x, y - 1};
        case '^':
            return {x - 1, y};
        case 'v':
            return {x + 1, y};
    }
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int r;
        cin >> r;
        vector<vector<char>> g(r, vector<char>(r));
        for (auto &ch : g) {
            for (auto &c : ch) {
                cin >> c;
            }
        }
        int d;
        cin >> d;
        vector<pair<int, int>> dt(d);
        for (auto &i : dt) {
            cin >> i.first >> i.second;
        }
        
        set<pair<int, int>> st;
        int rbt = 0;
        auto rx = 0, ry = 0;
        
        while (true) {
            if (st.count({rx, ry}) == 1) {
                break;
            }
            st.insert({rx, ry});
            auto [x, y] = next(rx, ry, g[rx][ry]);
            rx = x;
            ry = y;
            
            ++rbt;
        }
        
        auto LIMIT = std::lcm(rbt, d) * 2;
        // cout << rbt << ' ' << d << ' ' << LIMIT << '\n';
        
        int di = 0, t = 0;
        bool ok = false;
        rx = 0;
        ry = 0;
        while (t < LIMIT) {
            auto [dx, dy] = dt[di];
            di = (di + 1) % d;
            
            if (dx == rx && dy == ry) {
                ok = true;
                break;
            }
            
            auto [rrx, rry] = next(rx, ry, g[rx][ry]);
            rx = rrx;
            ry = rry;
            
            ++t;
        }
        if (!ok) {
            cout << "never\n";
        } else {
            cout << t << '\n';
        }
    }
}