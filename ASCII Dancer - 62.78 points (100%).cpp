#include <bits/stdc++.h>

using namespace std;

vector<string> m_getline() {
    string s;
    getline(cin, s);
    if (s.substr(0, 3) == "say") {
        s = s.substr(4);
        s.resize(min((int)s.size(), 80));
        cout << s << '\n';
        return {};
    }
    stringstream ss(s);
    vector<string> vs;
    while (ss >> s) {
        vs.push_back(s);
    }
    return vs;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int d;
        cin >> d;
        cin.ignore(1, '\n');
        char c[3][3] = {
            {' ', 'o', ' '},
            {'/', '|', '\\'},
            {'/', ' ', '\\'}
        };
        string left = "left", right = "right";
        for (int dd = 0; dd  < d; ++dd) {
            auto vs = m_getline();
            if (vs.empty()) {
                continue;
            }
            if (vs.front() == left) {
                if (vs.size() == 4) {
                    // left hand
                    if (vs.back() == "head") {
                        // left hand to head
                        c[0][2] = ')';
                        c[1][2] = ' ';
                    } else if (vs.back() == "hip") {
                        c[0][2] = ' ';
                        c[1][2] = '>';
                    } else {
                        c[0][2] = ' ';
                        c[1][2] = '\\';
                    }
                } else {
                    // left leg
                    if (vs.back() == "in") {
                        c[2][2] = '>';
                    } else {
                        c[2][2] = '\\';
                    }
                }
            } else if (vs.front() == right) {
                if (vs.size() == 4) {
                    // right hand
                    if (vs.back() == "head") {
                        c[0][0] = '(';
                        c[1][0] = ' ';
                    } else if (vs.back() == "hip") {
                        c[0][0] = ' ';
                        c[1][0] = '<';
                    } else {
                        c[0][0] = ' ';
                        c[1][0] = '/';
                    }
                } else {
                    // right leg
                    if (vs.back() == "in") {
                        c[2][0] = '<';
                    } else {
                        c[2][0] = '/';
                    }
                }
            } else {
                // turn
                char te[3][3];
                map<char, char> notchar = {{'(', ')'}, {' ', ' '}, {')', '('}, {'<', '>'}, {'>', '<'}, {'\\', '/'}, 
                {'/', '\\'}};
                
                te[0][0] = notchar[c[0][2]];
                te[0][1] = c[0][1];
                te[0][2] = notchar[c[0][0]];
                
                te[1][0] = notchar[c[1][2]];
                te[1][1] = c[1][1];
                te[1][2] = notchar[c[1][0]];
                
                te[2][0] = notchar[c[2][2]];
                te[2][1] = c[2][1];
                te[2][2] = notchar[c[2][0]];
                
                for (int i = 0; i < 3; ++i) {
                    for (int j = 0; j < 3; ++j) {
                        c[i][j] = te[i][j];
                    }
                }
                
                swap(left, right);
            }
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    cout << c[i][j];
                }
                cout << '\n';
            }
        }
    }
}