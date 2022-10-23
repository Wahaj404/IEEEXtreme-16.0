#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct Dsu {
    int n;
    vector<vector<int>> rank;
    vector<vector<pair<int, int>>> parent;
    vector<vector<bool>> has_loop;
    Dsu(int n) :
        n(n), rank(n, vector<int>(n)), parent(n, vector<pair<int, int>>(n)),
        has_loop(n, vector<bool>(n, false)) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                parent[i][j] = {i, j};
            }
        }
    }

    pair<int, int> find(int i, int j) {
        if (parent[i][j] != make_pair(i, j)) {
            parent[i][j] = find(parent[i][j]);
        }
        return parent[i][j];
    }

    pair<int, int> find(pair<int, int> const &p) {
        return find(p.first, p.second);
    }

    bool loop(pair<int, int> p) {
        return has_loop[p.first][p.second];
    }

    void Union(int i, int j, int x, int y) {
        auto p1 = find(i, j), p2 = find(x, y);
        if (p1 == p2) {
            has_loop[p1.first][p1.second] = true;
            return;
        }
        if (rank[p1.first][p1.second] < rank[p2.first][p2.second]) {
            parent[p1.first][p1.second] = parent[p2.first][p2.second];
        } else if (rank[p1.first][p1.second] > rank[p2.first][p2.second]) {
            parent[p2.first][p2.second] = parent[p1.first][p1.second];
        } else {
            parent[p2.first][p2.second] = p1;
            ++rank[p1.first][p1.second];
        }
        if (has_loop[p1.first][p1.second] || has_loop[p2.first][p2.second]) {
            has_loop[p1.first][p1.second] = has_loop[p2.first][p2.second] =
                true;
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, w;
    cin >> n >> w;

    Dsu dsu(n);

    pair<int, int> const child(0, 0), monster(0, n - 1), toy(n - 1, n - 1);

    for (int i = 0; i < w; ++i) {
        int r, c;
        char ch;
        cin >> r >> c >> ch;
        pair<int, int> tgt(r, c);
        switch (ch) {
            case 'N':
                --tgt.first;
                break;
            case 'E':
                ++tgt.second;
                break;
            case 'W':
                --tgt.second;
                break;
            case 'S':
                ++tgt.first;
                break;
        }

        auto child_parent = dsu.find(child);
        auto monster_parent = dsu.find(monster);
        auto toy_parent = dsu.find(toy);

        auto cur_parent = dsu.find(r, c);
        auto tgt_parent = dsu.find(tgt);

        if ((child_parent == cur_parent || child_parent == tgt_parent) &&
            (monster_parent == cur_parent || monster_parent == tgt_parent)) {
            cout << "M\n";
        } else if ((child_parent == cur_parent && child_parent == tgt_parent) ||
                   ((child_parent == tgt_parent ||
                     child_parent == cur_parent) &&
                    (dsu.loop(cur_parent) || dsu.loop(tgt_parent)))) {
            cout << "L\n";
        } else if ((child_parent == cur_parent || child_parent == tgt_parent) &&
                   (toy_parent == cur_parent || toy_parent == tgt_parent)) {
            cout << "T\n";
            if (cur_parent == tgt_parent) {}
            dsu.Union(r, c, tgt.first, tgt.second);
        } else {
            cout << "K\n";
            dsu.Union(r, c, tgt.first, tgt.second);
        }
    }
}