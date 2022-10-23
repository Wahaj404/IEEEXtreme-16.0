#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int p, n;
    cin >> p >> n;
    int r, c;
    cin >> r;
    cin.get();
    cin >> c;
    char pos;
    cin >> pos;
    cin.ignore(1, '\n');
    vector<string> phrases(p);
    for (string &s : phrases) {
        getline(cin, s);
    }
    vector<string> xml(n);
    for (string &s : xml) {
        getline(cin, s);
    }
    vector<string> parsed(n);
    regex rgx("<[^>]*>");
    for (int i = 0; i < n; ++i) {
        regex_replace(back_inserter(parsed[i]), xml[i].begin(), xml[i].end(),
                      rgx, "");
    }
    erase_if(parsed, [](std::string const &s) { return s.empty(); });

    int ii = 0, jj = 0;
    vector<vector<char>> cipher(r, vector<char>(c));
    for (int i = 0; i < r && ii < parsed.size(); ++i) {
        for (int j = 0; j < c && ii < parsed.size(); ++j) {
            cipher[i][j] = parsed[ii][jj];
            ++jj;
            if (jj == parsed[ii].size()) {
                jj = 0;
                ++ii;
            }
        }
    }
    vector<pair<int, int>> coord(256, make_pair(-1, -1));
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            char ch = cipher[i][j];
            if (coord[ch].first == -1 || pos == 'L') {
                coord[ch] = make_pair(i, j);
            }
        }
    }
    for (int i = 0; i < p; ++i) {
        string ans;
        bool ok = true;
        for (int j = 0; j < phrases[i].size() && ok; ++j) {
            char ch = phrases[i][j];
            if (coord[ch].first == -1) {
                ok = false;
            }
            ans.append(to_string(coord[ch].first + 1));
            ans.push_back(',');
            ans.append(to_string(coord[ch].second + 1));
            ans.push_back(',');
        }
        if (ok) {
            ans.pop_back();
            cout << ans << '\n';
        } else {
            cout << 0 << '\n';
        }
    }
}