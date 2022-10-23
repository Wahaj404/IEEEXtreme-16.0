/***********

  MK-1311

***********/
#include <bits/stdc++.h>
using namespace std;

void solve(int tt);

#define fi first
#define se second
#define pb push_back
#define nl '\n'

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...)
#endif

int32_t main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int tt = 1; 
  cin >> tt;
  for(int i = 0; i < tt; i++) {
    solve(i);
  }
  cerr << "time taken : " << (float)clock() / CLOCKS_PER_SEC << " secs" << endl;
  return 0;
}



int dirx[4] = {1, 0, 0, -1};
int diry[4] = {0, -1, 1, 0};
char dir[4] = {'D', 'L', 'R', 'U'};

vector<tuple<int, int, string>> paths;
vector<vector<char>> a;
vector<vector<int>> vis;
vector<vector<int>> dist, dist2;
int n, m;
int mxE = -1e9;
int ri, rj;

void bfs(int i, int j) {
  queue<pair<pair<int,int>,string>> q;
  q.push({{i,j},""});
  vis[i][j] = true;
  while (!q.empty()) {
    auto current = q.front();
    q.pop();

    if (current.first.first == ri && current.first.second == rj) {
      paths.push_back(make_tuple(ri,rj,current.second));
    }

    for(int d = 0; d < 4; ++d) {
      int ti = current.first.first + dirx[d];
      int tj = current.first.second + diry[d];
      if (ti < 0 || ti >= n || tj < 0 || tj >= m || a[ti][tj] == 'X') {
        continue;
      }
      if (vis[ti][tj]) continue;
      vis[ti][tj] = true;
      q.push({{ti, tj}, current.second + dir[d]});
    }
  }
}




void solve(int tt) {
  cin >> n >> m;
  paths.clear();
  a.clear();
  dist.clear();
  dist2.clear();
  vis.clear();
  vis.resize(n, vector<int>(m, 0));
  dist.resize(n, vector<int>(m, 1e9));
  dist2.resize(n, vector<int>(m, 1e9));
  queue<pair<int, int>> q;
  int si = 0, sj = 0;
  a.resize(n, vector<char>(m));
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < m; j++) {
      cin >> a[i][j];
      if(a[i][j] == 'P') {
        si = i, sj = j;
        dist2[i][j] = 0;
      }
      if (a[i][j] == 'G') {
        q.emplace(i, j);
        dist[i][j] = 0;
      }
    }
  }
  while(!q.empty()) {
    auto t = q.front();
    q.pop();
    for(int d = 0; d < 4; d++) {
      int ti = t.fi + dirx[d];
      int tj = t.se + diry[d];
      if(ti >= 0 && ti < n && tj >= 0 && tj < m && a[ti][tj] != 'X') {
        if(dist[ti][tj] > dist[t.fi][t.se] + 1) {
          dist[ti][tj] = dist[t.fi][t.se] + 1;
          q.emplace(ti, tj);
        }
      }
    }
  }
  q.emplace(si, sj);

  while(!q.empty()) {
    auto t = q.front();
    q.pop();
    for(int d = 0; d < 4; d++) {
      int ti = t.fi + dirx[d];
      int tj = t.se + diry[d];
      if(ti >= 0 && ti < n && tj >= 0 && tj < m && a[ti][tj] != 'X') {
        if(dist2[ti][tj] > dist2[t.fi][t.se] + 1) {
          dist2[ti][tj] = dist2[t.fi][t.se] + 1;
          q.emplace(ti, tj);
        }
      }
    }
  }


  for(int i = 0; i < n; i++) {
    for(int j = 0; j < m; j++) {
      if(dist2[i][j] >= dist[i][j]) {
        dist[i][j] = 1e9;
      }
    } 
  }

  debug(dist);

  vis[si][sj] = true;
  q.emplace(si, sj);
  mxE = dist[si][sj];
  while(!q.empty()) {
    auto t = q.front();
    q.pop();
    for(int d = 0; d < 4; d++) {
      int ti = t.fi + dirx[d];
      int tj = t.se + diry[d];
      if(ti >= 0 && ti < n && tj >= 0 && tj < m && a[ti][tj] != 'X' && dist[ti][tj] != 1e9 && !vis[ti][tj]) {
        if(mxE < dist[ti][tj]) {
          mxE = dist[ti][tj];
          ri = ti;
          rj = tj;
        }
        vis[ti][tj] = 1;
        q.emplace(ti, tj);
      }
    }
  }
  for(int i = 0; i < n; i++) {
    bool found = false;
    for(int j = 0; j < m; j++) {
      if(vis[i][j] && mxE == dist[i][j]) {
        ri = i;
        rj = j;
        found = true;
        break;
      }
    }
    if(found) break;
  }
  debug(mxE, ri, rj);

  for(int i = 0; i < n; i++) {
    for(int j = 0; j < m; j++) {
      vis[i][j] = false;
    }
  }

  cout << "Case #" << tt + 1 << ": ";
  string str;
  bfs(si, sj);
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < m; j++) {
      vis[i][j] = false;
    }
  }
  if(dist[si][sj] == 1e9) {
    cout << "INFINITE ";
    for(int i = 0; i < n; i++) {
      for(int j = 0; j < m; j++) {        
        if(a[i][j] == 'P') {
          cout << "STAY" << endl;
          return;
        }
        if(a[i][j] == '.' && dist2[i][j] != 1e9) {
          ri = i, rj = j;
          bfs(si, sj);
          string ans;
          int mnS = 1e9;
          for(auto [x, y, z] : paths) {
            if(x == ri && y == rj) {
              mnS = min(mnS, (int) z.size());
            }
          }
          for(auto [x, y, z] : paths) {
            if(x == ri && y == rj && mnS == (int) z.size()) {
              if(ans.empty()) {
                ans = z;
              } else {
                ans = min(ans, z);
              }
            }
          }
          if(ans.empty()) {
            cout << "STAY" << endl;
            return;
          }
          cout << ans << endl;
          return;
        }
      }
    }
    cout << "STAY" << endl;
    return;
  }
  cout << max(mxE - 1, 1) << ' ';
  sort(paths.begin(), paths.end());
  string ans;
  int mnS = 1e9;
  for(auto [x, y, z] : paths) {
    debug(x, y, z);
    if(x == ri && y == rj) {
      mnS = min(mnS, (int) z.size());
    }
  }
  for(auto [x, y, z] : paths) {
    if(x == ri && y == rj && mnS == (int) z.size()) {
      if(ans.empty()) {
        ans = z;
      } else {
        ans = min(ans, z);
      }
    }
  }
  if(ans.empty()) {
    cout << "STAY" << endl;
    return;
  }
  cout << ans << endl;
}

/*

*/    